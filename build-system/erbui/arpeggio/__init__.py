# -*- coding: utf-8 -*-
###############################################################################
# Name: arpeggio.py
# Purpose: PEG parser interpreter
# Author: Igor R. Dejanović <igor DOT dejanovic AT gmail DOT com>
# Copyright: (c) 2009-2017 Igor R. Dejanović <igor DOT dejanovic AT gmail DOT com>
# License: MIT License
#
# This is an implementation of packrat parser interpreter based on PEG
# grammars. Grammars are defined using Python language constructs or the PEG
# textual notation.
###############################################################################

#pylint: disable-all

from __future__ import print_function, unicode_literals
import sys
import codecs
import re
import bisect
import types

__version__ = "1.9.0"

# isstr check if object is of string type.
# This works for both python 2 and 3
# Taken from http://stackoverflow.com/questions/11301138/how-to-check-if-variable-is-string-with-python-2-and-3-compatibility
try:
    basestring  # attempt to evaluate basestring
    def isstr(s):
        return isinstance(s, basestring)
except NameError:
    def isstr(s):
        return isinstance(s, str)

if sys.version < '3':
    text = unicode
else:
    text = str

DEFAULT_WS = '\t\n\r '
NOMATCH_MARKER = 0


class ArpeggioError(Exception):
    """
    Base class for arpeggio errors.
    """
    def __init__(self, message):
        self.message = message

    def __str__(self):
        return repr(self.message)


class GrammarError(ArpeggioError):
    """
    Error raised during parser building phase used to indicate error in the
    grammar definition.
    """


class SemanticError(ArpeggioError):
    """
    Error raised during the phase of semantic analysis used to indicate
    semantic error.
    """


class NoMatch(Exception):
    """
    Exception raised by the Match classes during parsing to indicate that the
    match is not successful.

    Args:
        rules (list of ParsingExpression): Rules that are tried at the position
            of the exception.
        position (int): A position in the input stream where exception
            occurred.
        parser (Parser): An instance of a parser.
    """
    def __init__(self, rules, position, parser):
        self.rules = rules
        self.position = position
        self.parser = parser

    def __str__(self):
        def rule_to_exp_str(rule):
            if hasattr(rule, '_exp_str'):
                # Rule may override expected report string
                return rule._exp_str
            elif rule.root:
                return rule.rule_name
            elif isinstance(rule, Match) and \
                    not isinstance(rule, EndOfFile):
                return "'{}'".format(rule.to_match)
            else:
                return rule.name

        if not self.rules:
            err_message = "Not expected input"
        else:
            what_is_expected = ["{}".format(rule_to_exp_str(r))
                                for r in self.rules]
            what_str = " or ".join(what_is_expected)
            err_message = "Expected {}".format(what_str)

        return "{} at position {}{} => '{}'."\
            .format(err_message,
                    "{}:".format(self.parser.file_name)
                    if self.parser.file_name else "",
                    text(self.parser.pos_to_linecol(self.position)),
                    self.parser.context(position=self.position))

    def __unicode__(self):
        return self.__str__()


def flatten(_iterable):
    '''Flattening of python iterables.'''
    result = []
    for e in _iterable:
        if hasattr(e, "__iter__") and not type(e) in [text, NonTerminal]:
            result.extend(flatten(e))
        else:
            result.append(e)
    return result


class DebugPrinter(object):
    """
    Mixin class for adding debug print support.

    Attributes:
        debug (bool): If true debugging messages will be printed.
        _current_ident(int): Current identation level for prints.
    """

    def __init__(self, **kwargs):

        self.debug = kwargs.pop("debug", False)
        self.file = kwargs.pop("file", sys.stdout)
        self._current_ident = 0

        super(DebugPrinter, self).__init__(**kwargs)

    def dprint(self, message, ident_change=0):
        """
        Handle debug message. Print to the stream specified by the 'file'
        keyword argument at the current indentation level. Default stream is
        stdout.
        """
        if ident_change < 0:
            self._current_ident += ident_change

        print(("%s%s" % ("   " * self._current_ident, message)),
              file=self.file)

        if ident_change > 0:
            self._current_ident += ident_change


# ---------------------------------------------------------
# Parser Model (PEG Abstract Semantic Graph) elements


class ParsingExpression(object):
    """
    An abstract class for all parsing expressions.
    Represents the node of the Parser Model.

    Attributes:
        elements: A list (or other python object) used as a staging structure
            for python based grammar definition. Used in _from_python for
            building nodes list of child parser expressions.
        rule_name (str): The name of the parser rule if this is the root rule.
        root (bool):  Does this parser expression represents the
            root of the parser rule? The root parser rule will create
            non-terminal node of the parse tree during parsing.
        nodes (list of ParsingExpression): A list of child parser expressions.
        suppress (bool): If this is set to True than no ParseTreeNode will be
            created for this ParsingExpression. Default False.
    """
    def __init__(self, *elements, **kwargs):

        if len(elements) == 1:
            elements = elements[0]
        self.elements = elements

        self.rule_name = kwargs.get('rule_name', '')
        self.root = kwargs.get('root', False)

        nodes = kwargs.get('nodes', [])
        if not hasattr(nodes, '__iter__'):
            nodes = [nodes]
        self.nodes = nodes

        self.suppress = kwargs.get('suppress', False)

        # Memoization. Every node cache the parsing results for the given input
        # positions.
        self._result_cache = {}  # position -> parse tree at the position

    @property
    def desc(self):
        return "{}{}".format(self.name, "-" if self.suppress else "")

    @property
    def name(self):
        if self.root:
            return "%s=%s" % (self.rule_name, self.__class__.__name__)
        else:
            return self.__class__.__name__

    @property
    def id(self):
        if self.root:
            return self.rule_name
        else:
            return id(self)

    def _clear_cache(self, processed=None):
        """
        Clears memoization cache. Should be called on input change and end
        of parsing.

        Args:
            processed (set): Set of processed nodes to prevent infinite loops.
        """

        self._result_cache = {}

        if not processed:
            processed = set()

        for node in self.nodes:
            if node not in processed:
                processed.add(node)
                node._clear_cache(processed)

    def parse(self, parser):

        if parser.debug:
            name = self.name
            if name.startswith('__asgn'):
                name = "{}[{}]".format(self.name, self._attr_name)
            parser.dprint(">> Matching rule {}{} at position {} => {}"
                          .format(name,
                                  " in {}".format(parser.in_rule)
                                  if parser.in_rule else "",
                                  parser.position,
                                  parser.context()), 1)

        # Current position could change in recursive calls
        # so save it.
        c_pos = parser.position

        # Memoization.
        # If this position is already parsed by this parser expression use
        # the result
        if parser.memoization:
            try:
                result, new_pos = self._result_cache[c_pos]
                parser.position = new_pos
                parser.cache_hits += 1
                if parser.debug:
                    parser.dprint(
                        "** Cache hit for [{}, {}] = '{}' : new_pos={}"
                        .format(name, c_pos, text(result), text(new_pos)))
                    parser.dprint(
                        "<<+ Matched rule {} at position {}"
                        .format(name, new_pos), -1)

                # If NoMatch is recorded at this position raise.
                if result is NOMATCH_MARKER:
                    raise parser.nm

                # else return cached result
                return result

            except KeyError:
                parser.cache_misses += 1

        # Remember last parsing expression and set this as
        # the new last.
        last_pexpression = parser.last_pexpression
        parser.last_pexpression = self

        if self.rule_name:
            # If we are entering root rule
            # remember previous root rule name and set
            # this one on the parser to be available for
            # debugging messages
            previous_root_rule_name = parser.in_rule
            parser.in_rule = self.rule_name

        try:
            result = self._parse(parser)
            if self.suppress or (type(result) is list and
                                 result and result[0] is None):
                result = None

        except NoMatch:
            parser.position = c_pos  # Backtracking
            # Memoize NoMatch at this position for this rule
            if parser.memoization:
                self._result_cache[c_pos] = (NOMATCH_MARKER, c_pos)
            raise

        finally:
            # Recover last parsing expression.
            parser.last_pexpression = last_pexpression

            if parser.debug:
                parser.dprint("<<{} rule {}{} at position {} => {}"
                              .format("- Not matched"
                                      if parser.position is c_pos
                                      else "+ Matched",
                                      name,
                                      " in {}".format(parser.in_rule)
                                      if parser.in_rule else "",
                                      parser.position,
                                      parser.context()), -1)

            # If leaving root rule restore previous root rule name.
            if self.rule_name:
                parser.in_rule = previous_root_rule_name

        # For root rules flatten non-terminal/list
        if self.root and result and not isinstance(result, Terminal):
            if not isinstance(result, NonTerminal):
                result = flatten(result)

            # Tree reduction will eliminate Non-terminal with single child.
            if parser.reduce_tree and len(result) == 1:
                result = result[0]

            # If the result is not parse tree node it must be a plain list
            # so create a new NonTerminal.
            if not isinstance(result, ParseTreeNode):
                result = NonTerminal(self, result)

        # Result caching for use by memoization.
        if parser.memoization:
            self._result_cache[c_pos] = (result, parser.position)

        return result


class Sequence(ParsingExpression):
    """
    Will match sequence of parser expressions in exact order they are defined.
    """

    def __init__(self, *elements, **kwargs):
        super(Sequence, self).__init__(*elements, **kwargs)
        self.ws = kwargs.pop('ws', None)
        self.skipws = kwargs.pop('skipws', None)

    def _parse(self, parser):
        results = []
        c_pos = parser.position

        if self.ws is not None:
            old_ws = parser.ws
            parser.ws = self.ws

        if self.skipws is not None:
            old_skipws = parser.skipws
            parser.skipws = self.skipws

        # Prefetching
        append = results.append

        try:
            for e in self.nodes:
                result = e.parse(parser)
                if result:
                    append(result)

        except NoMatch:
            parser.position = c_pos     # Backtracking
            raise

        finally:
            if self.ws is not None:
                parser.ws = old_ws
            if self.skipws is not None:
                parser.skipws = old_skipws

        if results:
            return results


class OrderedChoice(Sequence):
    """
    Will match one of the parser expressions specified. Parser will try to
    match expressions in the order they are defined.
    """
    def _parse(self, parser):
        result = None
        match = False
        c_pos = parser.position
        for e in self.nodes:
            try:
                result = e.parse(parser)
                if result is not None:
                    match = True
                    result = [result]
                    break
            except NoMatch:
                parser.position = c_pos  # Backtracking

        if not match:
            parser._nm_raise(self, c_pos, parser)

        return result


class Repetition(ParsingExpression):
    """
    Base class for all repetition-like parser expressions (?,*,+)
    Args:
        eolterm(bool): Flag that indicates that end of line should
            terminate repetition match.
    """
    def __init__(self, *elements, **kwargs):
        super(Repetition, self).__init__(*elements, **kwargs)
        self.eolterm = kwargs.get('eolterm', False)
        self.sep = kwargs.get('sep', None)


class Optional(Repetition):
    """
    Optional will try to match parser expression specified and will not fail
    in case match is not successful.
    """
    def _parse(self, parser):
        result = None
        c_pos = parser.position

        try:
            result = [self.nodes[0].parse(parser)]
        except NoMatch:
            parser.position = c_pos  # Backtracking

        return result


class ZeroOrMore(Repetition):
    """
    ZeroOrMore will try to match parser expression specified zero or more
    times. It will never fail.
    """
    def _parse(self, parser):
        results = []

        if self.eolterm:
            # Remember current eolterm and set eolterm of
            # this repetition
            old_eolterm = parser.eolterm
            parser.eolterm = self.eolterm

        # Prefetching
        append = results.append
        p = self.nodes[0].parse
        sep = self.sep.parse if self.sep else None
        result = None

        while True:
            try:
                c_pos = parser.position
                if sep and result:
                    sep_result = sep(parser)
                    if not sep_result:
                        break
                    append(sep_result)
                result = p(parser)
                if not result:
                    break
                append(result)
            except NoMatch:
                parser.position = c_pos  # Backtracking
                break

        if self.eolterm:
            # Restore previous eolterm
            parser.eolterm = old_eolterm

        return results


class OneOrMore(Repetition):
    """
    OneOrMore will try to match parser expression specified one or more times.
    """
    def _parse(self, parser):
        results = []
        first = True

        if self.eolterm:
            # Remember current eolterm and set eolterm of
            # this repetition
            old_eolterm = parser.eolterm
            parser.eolterm = self.eolterm

        # Prefetching
        append = results.append
        p = self.nodes[0].parse
        sep = self.sep.parse if self.sep else None
        result = None

        try:
            while True:
                try:
                    c_pos = parser.position
                    if sep and result:
                        sep_result = sep(parser)
                        if not sep_result:
                            break
                        append(sep_result)
                    result = p(parser)
                    if not result:
                        break
                    append(result)
                    first = False
                except NoMatch:
                    parser.position = c_pos  # Backtracking

                    if first:
                        raise

                    break
        finally:
            if self.eolterm:
                # Restore previous eolterm
                parser.eolterm = old_eolterm

        return results


class UnorderedGroup(Repetition):
    """
    Will try to match all of the parsing expression in any order.
    """
    def _parse(self, parser):
        results = []
        c_pos = parser.position

        if self.eolterm:
            # Remember current eolterm and set eolterm of
            # this repetition
            old_eolterm = parser.eolterm
            parser.eolterm = self.eolterm

        # Prefetching
        append = results.append
        nodes_to_try = set(self.nodes)
        sep = self.sep.parse if self.sep else None
        result = None
        sep_result = None
        first = True

        while nodes_to_try:
            sep_exc = None

            # Separator
            c_loc_pos_sep = parser.position
            if sep and not first:
                try:
                    sep_result = sep(parser)
                except NoMatch as e:
                    parser.position = c_loc_pos_sep     # Backtracking

                    # This still might be valid if all remaining subexpressions
                    # are optional and none of them will match
                    sep_exc = e

            c_loc_pos = parser.position
            match = True
            all_optionals_fail = True
            for e in set(nodes_to_try):
                try:
                    result = e.parse(parser)
                    if result:
                        if sep_exc:
                            raise sep_exc
                        if sep_result:
                            append(sep_result)
                        first = False
                        match = True
                        all_optionals_fail = False
                        append(result)
                        nodes_to_try.remove(e)
                        break

                except NoMatch:
                    match = False
                    parser.position = c_loc_pos     # local backtracking

            if not match or all_optionals_fail:
                # If sep is matched backtrack it
                parser.position = c_loc_pos_sep
                break

        if self.eolterm:
            # Restore previous eolterm
            parser.eolterm = old_eolterm

        if not match:
            # Unsucessful match of the whole PE - full backtracking
            parser.position = c_pos
            parser._nm_raise(self, c_pos, parser)

        if results:
            return results


class SyntaxPredicate(ParsingExpression):
    """
    Base class for all syntax predicates (and, not, empty).
    Predicates are parser expressions that will do the match but will not
    consume any input.
    """


class And(SyntaxPredicate):
    """
    This predicate will succeed if the specified expression matches current
    input.
    """
    def _parse(self, parser):
        c_pos = parser.position
        for e in self.nodes:
            try:
                e.parse(parser)
            except NoMatch:
                parser.position = c_pos
                raise
        parser.position = c_pos


class Not(SyntaxPredicate):
    """
    This predicate will succeed if the specified expression doesn't match
    current input.
    """
    def _parse(self, parser):
        c_pos = parser.position
        old_in_not = parser.in_not
        parser.in_not = True
        try:
            for e in self.nodes:
                try:
                    e.parse(parser)
                except NoMatch:
                    parser.position = c_pos
                    return
            parser.position = c_pos
            parser._nm_raise(self, c_pos, parser)
        finally:
            parser.in_not = old_in_not


class Empty(SyntaxPredicate):
    """
    This predicate will always succeed without consuming input.
    """
    def _parse(self, parser):
        pass


class Decorator(ParsingExpression):
    """
    Decorator are special kind of parsing expression used to mark
    a containing pexpression and give it some special semantics.
    For example, decorators are used to mark pexpression as lexical
    rules (see :class:Lex).
    """


class Combine(Decorator):
    """
    This decorator defines pexpression that represents a lexeme rule.
    This rules will always return a Terminal parse tree node.
    Whitespaces will be preserved. Comments will not be matched.
    """
    def _parse(self, parser):
        results = []

        oldin_lex_rule = parser.in_lex_rule
        parser.in_lex_rule = True
        c_pos = parser.position
        try:
            for parser_model_node in self.nodes:
                results.append(parser_model_node.parse(parser))

            results = flatten(results)

            # Create terminal from result
            return Terminal(self, c_pos,
                            "".join([x.flat_str() for x in results]))
        except NoMatch:
            parser.position = c_pos  # Backtracking
            raise
        finally:
            parser.in_lex_rule = oldin_lex_rule


class Match(ParsingExpression):
    """
    Base class for all classes that will try to match something from the input.
    """
    def __init__(self, rule_name, root=False):
        super(Match, self).__init__(rule_name=rule_name, root=root)

    @property
    def name(self):
        if self.root:
            return "%s=%s(%s)" % (self.rule_name, self.__class__.__name__,
                                  self.to_match)
        else:
            return "%s(%s)" % (self.__class__.__name__, self.to_match)

    def _parse_comments(self, parser):
        """Parse comments."""

        try:
            parser.in_parse_comments = True
            if parser.comments_model:
                try:
                    while True:
                        # TODO: Consumed whitespaces and comments should be
                        #       attached to the first match ahead.
                        parser.comments.append(
                            parser.comments_model.parse(parser))
                        if parser.skipws:
                            # Whitespace skipping
                            pos = parser.position
                            ws = parser.ws
                            i = parser.input
                            length = len(i)
                            while pos < length and i[pos] in ws:
                                pos += 1
                            parser.position = pos
                except NoMatch:
                    # NoMatch in comment matching is perfectly
                    # legal and no action should be taken.
                    pass
        finally:
            parser.in_parse_comments = False

    def parse(self, parser):

        if parser.skipws and not parser.in_lex_rule:
            # Whitespace skipping
            pos = parser.position
            ws = parser.ws
            i = parser.input
            length = len(i)
            while pos < length and i[pos] in ws:
                pos += 1
            parser.position = pos

        if parser.debug:
            parser.dprint(
                "?? Try match rule {}{} at position {} => {}"
                .format(self.name,
                        " in {}".format(parser.in_rule)
                        if parser.in_rule else "",
                        parser.position,
                        parser.context()))

        if parser.skipws and parser.position in parser.comment_positions:
            # Skip comments if already parsed.
            parser.position = parser.comment_positions[parser.position]
        else:
            if not parser.in_parse_comments and not parser.in_lex_rule:
                comment_start = parser.position
                self._parse_comments(parser)
                parser.comment_positions[comment_start] = parser.position

        result = self._parse(parser)
        if not self.suppress:
            return result


class RegExMatch(Match):
    '''
    This Match class will perform input matching based on Regular Expressions.

    Args:
        to_match (regex string): A regular expression string to match.
            It will be used to create regular expression using re.compile.
        ignore_case(bool): If case insensitive match is needed.
            Default is None to support propagation from global parser setting.
        multiline(bool): allow regex to works on multiple lines
            (re.DOTALL flag). Default is None to support propagation from
            global parser setting.
        str_repr(str): A string that is used to represent this regex.
        re_flags: flags parameter for re.compile if neither ignore_case
            or multiple are set.

    '''
    def __init__(self, to_match, rule_name='', root=False, ignore_case=None,
                 multiline=None, str_repr=None, re_flags=re.MULTILINE):
        super(RegExMatch, self).__init__(rule_name, root)
        self.to_match_regex = to_match
        self.ignore_case = ignore_case
        self.multiline = multiline
        self.explicit_flags = re_flags

        self.to_match = str_repr if str_repr is not None else to_match

    def compile(self):
        flags = self.explicit_flags
        if self.multiline is True:
            flags |= re.DOTALL
        if self.multiline is False and flags & re.DOTALL:
            flags -= re.DOTALL
        if self.ignore_case is True:
            flags |= re.IGNORECASE
        if self.ignore_case is False and flags & re.IGNORECASE:
            flags -= re.IGNORECASE
        self.regex = re.compile(self.to_match_regex, flags)

    def __str__(self):
        return self.to_match

    def __unicode__(self):
        return self.__str__()

    def _parse(self, parser):
        c_pos = parser.position
        m = self.regex.match(parser.input, c_pos)
        if m:
            matched = m.group()
            if parser.debug:
                parser.dprint(
                    "++ Match '%s' at %d => '%s'" %
                    (matched, c_pos, parser.context(len(matched))))
            parser.position += len(matched)
            if matched:
                return Terminal(self, c_pos, matched, extra_info=m)
        else:
            if parser.debug:
                parser.dprint("-- NoMatch at {}".format(c_pos))
            parser._nm_raise(self, c_pos, parser)


class StrMatch(Match):
    """
    This Match class will perform input matching by a string comparison.

    Args:
        to_match (str): A string to match.
        ignore_case(bool): If case insensitive match is needed.
            Default is None to support propagation from global parser setting.
    """
    def __init__(self, to_match, rule_name='', root=False, ignore_case=None):
        super(StrMatch, self).__init__(rule_name, root)
        self.to_match = to_match
        self.ignore_case = ignore_case

    def _parse(self, parser):
        c_pos = parser.position
        input_frag = parser.input[c_pos:c_pos+len(self.to_match)]
        if self.ignore_case:
            match = input_frag.lower() == self.to_match.lower()
        else:
            match = input_frag == self.to_match
        if match:
            if parser.debug:
                parser.dprint(
                    "++ Match '{}' at {} => '{}'"
                    .format(self.to_match, c_pos,
                            parser.context(len(self.to_match))))
            parser.position += len(self.to_match)

            # If this match is inside sequence than mark for suppression
            suppress = type(parser.last_pexpression) is Sequence

            return Terminal(self, c_pos, self.to_match, suppress=suppress)
        else:
            if parser.debug:
                parser.dprint(
                    "-- No match '{}' at {} => '{}'"
                    .format(self.to_match, c_pos,
                            parser.context(len(self.to_match))))
            parser._nm_raise(self, c_pos, parser)

    def __str__(self):
        return self.to_match

    def __unicode__(self):
        return self.__str__()

    def __eq__(self, other):
        return self.to_match == text(other)

    def __hash__(self):
        return hash(self.to_match)


# HACK: Kwd class is a bit hackish. Need to find a better way to
#       introduce different classes of string tokens.
class Kwd(StrMatch):
    """
    A specialization of StrMatch to specify keywords of the language.
    """
    def __init__(self, to_match):
        super(Kwd, self).__init__(to_match)
        self.to_match = to_match
        self.root = True
        self.rule_name = 'keyword'


class EndOfFile(Match):
    """
    The Match class that will succeed in case end of input is reached.
    """
    def __init__(self):
        super(EndOfFile, self).__init__("EOF")

    @property
    def name(self):
        return "EOF"

    def _parse(self, parser):
        c_pos = parser.position
        if len(parser.input) == c_pos:
            return Terminal(EOF(), c_pos, '', suppress=True)
        else:
            if parser.debug:
                parser.dprint("!! EOF not matched.")
            parser._nm_raise(self, c_pos, parser)


def EOF():
    return EndOfFile()

# ---------------------------------------------------------


# ---------------------------------------------------
# Parse Tree node classes

class ParseTreeNode(object):
    """
    Abstract base class representing node of the Parse Tree.
    The node can be terminal(the leaf of the parse tree) or non-terminal.

    Attributes:
        rule (ParsingExpression): The rule that created this node.
        rule_name (str): The name of the rule that created this node if
            root rule or empty string otherwise.
        position (int): A position in the input stream where the match
            occurred.
        position_end (int, read-only): A position in the input stream where
            the node ends.
            This position is one char behind the last char contained in this
            node. Thus, position_end - position = length of the node.
        error (bool): Is this a false parse tree node created during error
            recovery.
        comments : A parse tree of comment(s) attached to this node.
    """
    def __init__(self, rule, position, error):
        assert rule
        assert rule.rule_name is not None
        self.rule = rule
        self.rule_name = rule.rule_name
        self.position = position
        self.error = error
        self.comments = None

    @property
    def name(self):
        return "%s [%s]" % (self.rule_name, self.position)

    @property
    def position_end(self):
        "Must be implemented in subclasses."
        raise NotImplementedError

    def visit(self, visitor):
        """
        Visitor pattern implementation.

        Args:
            visitor(PTNodeVisitor): The visitor object.
        """
        if visitor.debug:
            visitor.dprint("Visiting {}  type:{} str:{}"
                           .format(self.name, type(self).__name__, text(self)))

        children = SemanticActionResults()
        if isinstance(self, NonTerminal):
            for node in self:
                child = node.visit(visitor)
                # If visit returns None suppress that child node
                if child is not None:
                    children.append_result(node.rule_name, child)

        visit_name = "visit_%s" % self.rule_name
        if hasattr(visitor, visit_name):
            # Call visit method.
            result = getattr(visitor, visit_name)(self, children)

            # If there is a method with 'second' prefix save
            # the result of visit for post-processing
            if hasattr(visitor, "second_%s" % self.rule_name):
                visitor.for_second_pass.append((self.rule_name, result))

            return result

        elif visitor.defaults:
            # If default actions are enabled
            return visitor.visit__default__(self, children)


class Terminal(ParseTreeNode):
    """
    Leaf node of the Parse Tree. Represents matched string.

    Attributes:
        rule (ParsingExpression): The rule that created this terminal.
        position (int): A position in the input stream where match occurred.
        value (str): Matched string at the given position or missing token
            name in the case of an error node.
        suppress(bool): If True this terminal can be ignored in semantic
            analysis.
        extra_info(object): additional information (e.g. the re matcher
            object)
    """

    __slots__ = ['rule', 'rule_name', 'position', 'error', 'comments',
                 'value', 'suppress', 'extra_info']

    def __init__(self, rule, position, value, error=False, suppress=False,
                 extra_info=None):
        super(Terminal, self).__init__(rule, position, error)
        self.value = value
        self.suppress = suppress
        self.extra_info = extra_info

    @property
    def desc(self):
        if self.value:
            return "%s '%s' [%s]" % (self.rule_name, self.value, self.position)
        else:
            return "%s [%s]" % (self.rule_name, self.position)

    @property
    def position_end(self):
        return self.position + len(self.value)

    def flat_str(self):
        return self.value

    def __str__(self):
        return self.value

    def __unicode__(self):
        return self.__str__()

    def __repr__(self):
        return self.desc

    def __eq__(self, other):
        return text(self) == text(other)


class NonTerminal(ParseTreeNode, list):
    """
    Non-leaf node of the Parse Tree. Represents language syntax construction.
    At the same time used in ParseTreeNode navigation expressions.
    See test_ptnode_navigation_expressions.py for examples of navigation
    expressions.

    Attributes:
        nodes (list of ParseTreeNode): Children parse tree nodes.
        _filtered (bool): Is this NT a dynamically created filtered NT.
            This is used internally.

    """

    __slots__ = ['rule', 'rule_name', 'position', 'error', 'comments',
                 '_filtered', '_expr_cache']

    def __init__(self, rule, nodes, error=False, _filtered=False):

        # Inherit position from the first child node
        position = nodes[0].position if nodes else 0

        super(NonTerminal, self).__init__(rule, position, error)

        self.extend(flatten([nodes]))
        self._filtered = _filtered

    @property
    def value(self):
        """Terminal protocol."""
        return text(self)

    @property
    def desc(self):
        return self.name

    @property
    def position_end(self):
        return self[-1].position_end if self else self.position

    def flat_str(self):
        """
        Return flatten string representation.
        """
        return "".join([x.flat_str() for x in self])

    def __str__(self):
        return " | ".join([text(x) for x in self])

    def __unicode__(self):
        return self.__str__()

    def __repr__(self):
        return "[ %s ]" % ", ".join([repr(x) for x in self])

    def __getattr__(self, rule_name):
        """
        Find a child (non)terminal by the rule name.

        Args:
            rule_name(str): The name of the rule that is referenced from
                this node rule.
        """
        # Prevent infinite recursion
        if rule_name in ['_expr_cache', '_filtered', 'rule', 'rule_name',
                         'position', 'append', 'extend']:
            raise AttributeError

        try:
            # First check the cache
            if rule_name in self._expr_cache:
                return self._expr_cache[rule_name]
        except AttributeError:
            # Navigation expression cache. Used for lookup by rule name.
            self._expr_cache = {}

        # If result is not found in the cache collect all nodes
        # with the given rule name and create new NonTerminal
        # and cache it for later access.
        nodes = []
        rule = None
        for n in self:
            if self._filtered:
                # For filtered NT rule_name is a rule on
                # each of its children
                for m in n:
                    if m.rule_name == rule_name:
                        nodes.append(m)
                        rule = m.rule
            else:
                if n.rule_name == rule_name:
                    nodes.append(n)
                    rule = n.rule

        result = NonTerminal(rule=rule, nodes=nodes, _filtered=True)
        self._expr_cache[rule_name] = result
        return result


# ----------------------------------------------------
# Semantic Actions
#
class PTNodeVisitor(DebugPrinter):
    """
    Base class for all parse tree visitors.
    """
    def __init__(self, defaults=True, **kwargs):
        """
        Args:
            defaults(bool): If the default visit method should be applied in
                case no method is defined.
        """
        self.for_second_pass = []
        self.defaults = defaults

        super(PTNodeVisitor, self).__init__(**kwargs)

    def visit__default__(self, node, children):
        """
        Called if no visit method is defined for the node.

        Args:
            node(ParseTreeNode):
            children(processed children ParseTreeNode-s):
        """
        if isinstance(node, Terminal):
            # Default for Terminal is to convert to string unless suppress flag
            # is set in which case it is suppressed by setting to None.
            retval = text(node) if not node.suppress else None
        else:
            retval = node
            # Special case. If only one child exist return it.
            if len(children) == 1:
                retval = children[0]
            else:
                # If there is only one non-string child return
                # that by default. This will support e.g. bracket
                # removals.
                last_non_str = None
                for c in children:
                    if not isstr(c):
                        if last_non_str is None:
                            last_non_str = c
                        else:
                            # If there is multiple non-string objects
                            # by default convert non-terminal to string
                            if self.debug:
                                self.dprint("*** Warning: Multiple "
                                            "non-string objects found in "
                                            "default visit. Converting non-"
                                            "terminal to a string.")
                            retval = text(node)
                            break
                else:
                    # Return the only non-string child
                    retval = last_non_str

        return retval


def visit_parse_tree(parse_tree, visitor):
    """
    Applies visitor to parse_tree and runs the second pass
    afterwards.

    Args:
        parse_tree(ParseTreeNode):
        visitor(PTNodeVisitor):
    """
    if not parse_tree:
        raise Exception(
            "Parse tree is empty. You did call parse(), didn't you?")

    if visitor.debug:
        visitor.dprint("ASG: First pass")

    # Visit tree.
    result = parse_tree.visit(visitor)

    # Second pass
    if visitor.debug:
        visitor.dprint("ASG: Second pass")
    for sa_name, asg_node in visitor.for_second_pass:
        getattr(visitor, "second_%s" % sa_name)(asg_node)

    return result


class SemanticAction(object):
    """
    Semantic actions are executed during semantic analysis. They are in charge
    of producing Abstract Semantic Graph (ASG) out of the parse tree.
    Every non-terminal and terminal can have semantic action defined which will
    be triggered during semantic analysis.
    Semantic action triggering is separated in two passes. first_pass method is
    required and the method called second_pass is optional and will be called
    if exists after the first pass. Second pass can be used for forward
    referencing, e.g. linking to the declaration registered in the first pass
    stage.
    """
    def first_pass(self, parser, node, nodes):
        """
        Called in the first pass of tree walk.
        This is the default implementation used if no semantic action is
        defined.
        """
        if isinstance(node, Terminal):
            # Default for Terminal is to convert to string unless suppress flag
            # is set in which case it is suppressed by setting to None.
            retval = text(node) if not node.suppress else None
        else:
            retval = node
            # Special case. If only one child exist return it.
            if len(nodes) == 1:
                retval = nodes[0]
            else:
                # If there is only one non-string child return
                # that by default. This will support e.g. bracket
                # removals.
                last_non_str = None
                for c in nodes:
                    if not isstr(c):
                        if last_non_str is None:
                            last_non_str = c
                        else:
                            # If there is multiple non-string objects
                            # by default convert non-terminal to string
                            if parser.debug:
                                parser.dprint(
                                    "*** Warning: Multiple non-"
                                    "string objects found in applying "
                                    "default semantic action. Converting "
                                    "non-terminal to string.")
                            retval = text(node)
                            break
                else:
                    # Return the only non-string child
                    retval = last_non_str

        return retval


class SemanticActionResults(list):
    """
    Used in visitor methods call to supply results of semantic analysis
    of children parse tree nodes.
    Enables dot access by the name of the rule similar to NonTerminal
    tree navigation.
    Enables index access as well as iteration.
    """
    def __init__(self):
        self.results = {}

    def append_result(self, name, result):
        if name:
            if name not in self.results:
                self.results[name] = []
            self.results[name].append(result)

        self.append(result)

    def __getattr__(self, attr_name):
        if attr_name == 'results':
            raise AttributeError

        return self.results.get(attr_name, [])


# Common semantic actions
class SemanticActionSingleChild(SemanticAction):
    def first_pass(self, parser, node, children):
        return children[0]


class SemanticActionBodyWithBraces(SemanticAction):
    def first_pass(self, parser, node, children):
        return children[1:-1]


class SemanticActionToString(SemanticAction):
    def first_pass(self, parser, node, children):
        return text(node)

# ----------------------------------------------------
# Parsers


class Parser(DebugPrinter):
    """
    Abstract base class for all parsers.

    Attributes:
        comments_model: parser model for comments.
        comments(list): A list of ParseTreeNode for matched comments.
        sem_actions(dict): A dictionary of semantic actions keyed by the
            rule name.
        parse_tree(NonTerminal): The parse tree consisting of NonTerminal and
            Terminal instances.
        in_rule (str): Current rule name.
        in_parse_comments (bool): True if parsing comments.
        in_lex_rule (bool): True if in lexical rule. Currently used in Combine
            decorator to convert match to a single Terminal.
        in_not (bool): True if in Not parsing expression. Used for better error
            reporting.
        last_pexpression (ParsingExpression): Last parsing expression
            traversed.
    """

    # Not marker for NoMatch rules list. Used if the first unsuccessful rule
    # match is Not.
    FIRST_NOT = Not()

    def __init__(self, skipws=True, ws=None, reduce_tree=False, autokwd=False,
                 ignore_case=False, memoization=False, **kwargs):
        """
        Args:
            skipws (bool): Should the whitespace skipping be done.  Default is
                True.
            ws (str): A string consisting of whitespace characters.
            reduce_tree (bool): If true non-terminals with single child will be
                eliminated from the parse tree. Default is False.
            autokwd(bool): If keyword-like StrMatches are matched on word
                boundaries. Default is False.
            ignore_case(bool): If case is ignored (default=False)
            memoization(bool): If memoization should be used
                (a.k.a. packrat parsing)
        """

        super(Parser, self).__init__(**kwargs)

        # Used to indicate state in which parser should not
        # treat newlines as whitespaces.
        self._eolterm = False

        self.skipws = skipws
        if ws is not None:
            self.ws = ws
        else:
            self.ws = DEFAULT_WS

        self.reduce_tree = reduce_tree
        self.autokwd = autokwd
        self.ignore_case = ignore_case
        self.memoization = memoization
        self.comments_model = None
        self.comments = []
        self.comment_positions = {}
        self.sem_actions = {}

        self.parse_tree = None

        # Create regex used for autokwd matching
        flags = 0
        if ignore_case:
            flags = re.IGNORECASE
        self.keyword_regex = re.compile(r'[^\d\W]\w*', flags)

        # Keep track of root rule we are currently in.
        # Used for debugging purposes
        self.in_rule = ''

        self.in_parse_comments = False

        # Are we in lexical rule? If so do not
        # skip whitespaces.
        self.in_lex_rule = False

        # Are we in Not parsing expression?
        self.in_not = False

        # Last parsing expression traversed
        self.last_pexpression = None

    @property
    def ws(self):
        return self._ws

    @ws.setter
    def ws(self, new_value):
        self._real_ws = new_value
        self._ws = new_value
        if self.eolterm:
            self._ws = self._ws.replace('\n', '').replace('\r', '')

    @property
    def eolterm(self):
        return self._eolterm

    @eolterm.setter
    def eolterm(self, new_value):
        # Toggle newline char in ws on eolterm property set.
        # During eolterm state parser should not treat
        # newline as a whitespace.
        self._eolterm = new_value
        if self._eolterm:
            self._ws = self._ws.replace('\n', '').replace('\r', '')
        else:
            self._ws = self._real_ws

    def parse(self, _input, file_name=None):
        """
        Parses input and produces parse tree.

        Args:
            _input(str): An input string to parse.
            file_name(str): If input is loaded from file this can be
                set to file name. It is used in error messages.
        """
        self.position = 0  # Input position
        self.nm = None  # Last NoMatch exception
        self.line_ends = []
        self.input = _input
        self.file_name = file_name
        self.comment_positions = {}
        self.cache_hits = 0
        self.cache_misses = 0
        try:
            self.parse_tree = self._parse()
        except NoMatch as e:
            # Remove Not marker
            if e.rules[0] is Parser.FIRST_NOT:
                del e.rules[0]
            # Get line and column from position
            e.line, e.col = self.pos_to_linecol(e.position)
            raise
        finally:
            # At end of parsing clear all memoization caches.
            # Do this here to free memory.
            if self.memoization:
                self._clear_caches()

        # In debug mode export parse tree to dot file for
        # visualization
        if self.debug and self.parse_tree:
            from arpeggio.export import PTDOTExporter
            root_rule_name = self.parse_tree.rule_name
            PTDOTExporter().exportFile(
                self.parse_tree, "{}_parse_tree.dot".format(root_rule_name))
        return self.parse_tree

    def parse_file(self, file_name):
        """
        Parses content from the given file.
        Args:
            file_name(str): A file name.
        """
        with codecs.open(file_name, 'r', 'utf-8') as f:
            content = f.read()

        return self.parse(content, file_name=file_name)

    def getASG(self, sem_actions=None, defaults=True):
        """
        Creates Abstract Semantic Graph (ASG) from the parse tree.

        Args:
            sem_actions (dict): The semantic actions dictionary to use for
                semantic analysis. Rule names are the keys and semantic action
                objects are values.
            defaults (bool): If True a default semantic action will be
                applied in case no action is defined for the node.
        """
        if not self.parse_tree:
            raise Exception(
                "Parse tree is empty. You did call parse(), didn't you?")

        if sem_actions is None:
            if not self.sem_actions:
                raise Exception("Semantic actions not defined.")
            else:
                sem_actions = self.sem_actions

        if type(sem_actions) is not dict:
            raise Exception("Semantic actions parameter must be a dictionary.")

        for_second_pass = []

        def tree_walk(node):
            """
            Walking the parse tree and calling first_pass for every registered
            semantic actions and creating list of object that needs to be
            called in the second pass.
            """

            if self.debug:
                self.dprint(
                    "Walking down %s   type: %s  str: %s" %
                    (node.name, type(node).__name__, text(node)))

            children = SemanticActionResults()
            if isinstance(node, NonTerminal):
                for n in node:
                    child = tree_walk(n)
                    if child is not None:
                        children.append_result(n.rule_name, child)

            if self.debug:
                self.dprint("Processing %s = '%s'  type:%s len:%d" %
                            (node.name, text(node), type(node).__name__,
                             len(node) if isinstance(node, list) else 0))
                for i, a in enumerate(children):
                    self.dprint("  %d:%s type:%s" %
                                (i+1, text(a), type(a).__name__))

            if node.rule_name in sem_actions:
                sem_action = sem_actions[node.rule_name]
                if isinstance(sem_action, types.FunctionType):
                    retval = sem_action(self, node, children)
                else:
                    retval = sem_action.first_pass(self, node, children)

                if hasattr(sem_action, "second_pass"):
                    for_second_pass.append((node.rule_name, retval))

                if self.debug:
                    action_name = sem_action.__name__ \
                        if hasattr(sem_action, '__name__') \
                        else sem_action.__class__.__name__
                    self.dprint("  Applying semantic action %s" % action_name)

            else:
                if defaults:
                    # If no rule is present use some sane defaults
                    if self.debug:
                        self.dprint("  Applying default semantic action.")

                    retval = SemanticAction().first_pass(self, node, children)

                else:
                    retval = node

            if self.debug:
                if retval is None:
                    self.dprint("  Suppressed.")
                else:
                    self.dprint("  Resolved to = %s  type:%s" %
                                (text(retval), type(retval).__name__))
            return retval

        if self.debug:
            self.dprint("ASG: First pass")
        asg = tree_walk(self.parse_tree)

        # Second pass
        if self.debug:
            self.dprint("ASG: Second pass")
        for sa_name, asg_node in for_second_pass:
            sem_actions[sa_name].second_pass(self, asg_node)

        return asg

    def pos_to_linecol(self, pos):
        """
        Calculate (line, column) tuple for the given position in the stream.
        """
        if not self.line_ends:
            try:
                # TODO: Check this implementation on Windows.
                self.line_ends.append(self.input.index("\n"))
                while True:
                    try:
                        self.line_ends.append(
                            self.input.index("\n", self.line_ends[-1] + 1))
                    except ValueError:
                        break
            except ValueError:
                pass

        line = bisect.bisect_left(self.line_ends, pos)
        col = pos
        if line > 0:
            col -= self.line_ends[line - 1]
            if self.input[self.line_ends[line - 1]] in '\n\r':
                col -= 1
        return line + 1, col + 1

    def context(self, length=None, position=None):
        """
        Returns current context substring, i.e. the substring around current
        position.
        Args:
            length(int): If given used to mark with asterisk a length chars
                from the current position.
            position(int): The position in the input stream.
        """
        if not position:
            position = self.position
        if length:
            retval = "{}*{}*{}".format(
                text(self.input[max(position - 10, 0):position]),
                text(self.input[position:position + length]),
                text(self.input[position + length:position + 10]))
        else:
            retval = "{}*{}".format(
                text(self.input[max(position - 10, 0):position]),
                text(self.input[position:position + 10]))

        return retval.replace('\n', ' ').replace('\r', '')

    def _nm_raise(self, *args):
        """
        Register new NoMatch object if the input is consumed
        from the last NoMatch and raise last NoMatch.

        Args:
            args: A NoMatch instance or (value, position, parser)
        """

        rule, position, parser = args
        if self.nm is None or not parser.in_parse_comments:
            if self.nm is None or position > self.nm.position:
                if self.in_not:
                    self.nm = NoMatch([Parser.FIRST_NOT], position, parser)
                else:
                    self.nm = NoMatch([rule], position, parser)
            elif position == self.nm.position and isinstance(rule, Match) \
                    and not self.in_not:
                self.nm.rules.append(rule)

        raise self.nm

    def _clear_caches(self):
        """
        Clear memoization caches if packrat parser is used.
        """
        self.parser_model._clear_cache()
        if self.comments_model:
            self.comments_model._clear_cache()


class CrossRef(object):
    '''
    Used for rule reference resolving.
    '''
    def __init__(self, target_rule_name, position=-1):
        self.target_rule_name = target_rule_name
        self.position = position


class ParserPython(Parser):

    def __init__(self, language_def, comment_def=None, *args, **kwargs):
        """
        Constructs parser from python statements and expressions.

        Args:
            language_def (python function): A python function that defines
                the root rule of the grammar.
            comment_def (python function): A python function that defines
                the root rule of the comments grammar.
        """
        super(ParserPython, self).__init__(*args, **kwargs)

        # PEG Abstract Syntax Graph
        self.parser_model = self._from_python(language_def)

        self.comments_model = None
        if comment_def:
            self.comments_model = self._from_python(comment_def)
            self.comments_model.root = True
            self.comments_model.rule_name = comment_def.__name__

        # In debug mode export parser model to dot for
        # visualization
        if self.debug:
            from arpeggio.export import PMDOTExporter
            root_rule = language_def.__name__
            PMDOTExporter().exportFile(self.parser_model,
                                       "{}_parser_model.dot".format(root_rule))

    def _parse(self):
        return self.parser_model.parse(self)

    def _from_python(self, expression):
        """
        Create parser model from the definition given in the form of python
        functions returning lists, tuples, callables, strings and
        ParsingExpression objects.

        Returns:
            Parser Model (PEG Abstract Semantic Graph)
        """
        __rule_cache = {"EndOfFile": EndOfFile()}
        __for_resolving = []  # Expressions that needs crossref resolvnih
        self.__cross_refs = 0

        def inner_from_python(expression):
            retval = None
            if isinstance(expression, types.FunctionType):
                # If this expression is a parser rule
                rule_name = expression.__name__
                if rule_name in __rule_cache:
                    c_rule = __rule_cache.get(rule_name)
                    if self.debug:
                        self.dprint("Rule {} founded in cache."
                                    .format(rule_name))
                    if isinstance(c_rule, CrossRef):
                        self.__cross_refs += 1
                        if self.debug:
                            self.dprint("CrossRef usage: {}"
                                        .format(c_rule.target_rule_name))
                    return c_rule

                # Semantic action for the rule
                if hasattr(expression, "sem"):
                    self.sem_actions[rule_name] = expression.sem

                # Register rule cross-ref to support recursion
                __rule_cache[rule_name] = CrossRef(rule_name)

                curr_expr = expression
                while isinstance(curr_expr, types.FunctionType):
                    # If function directly returns another function
                    # go into until non-function is returned.
                    curr_expr = curr_expr()
                retval = inner_from_python(curr_expr)
                retval.rule_name = rule_name
                retval.root = True

                # Update cache
                __rule_cache[rule_name] = retval
                if self.debug:
                    self.dprint("New rule: {} -> {}"
                                .format(rule_name, retval.__class__.__name__))

            elif type(expression) is text or isinstance(expression, StrMatch):
                if type(expression) is text:
                    retval = StrMatch(expression, ignore_case=self.ignore_case)
                else:
                    retval = expression
                    if expression.ignore_case is None:
                        expression.ignore_case = self.ignore_case

                if self.autokwd:
                    to_match = retval.to_match
                    match = self.keyword_regex.match(to_match)
                    if match and match.span() == (0, len(to_match)):
                        retval = RegExMatch(r'{}\b'.format(to_match),
                                            ignore_case=self.ignore_case,
                                            str_repr=to_match)
                        retval.compile()

            elif isinstance(expression, RegExMatch):
                # Regular expression are not compiled yet
                # to support global settings propagation from
                # parser.
                if expression.ignore_case is None:
                    expression.ignore_case = self.ignore_case
                expression.compile()

                retval = expression

            elif isinstance(expression, Match):
                retval = expression

            elif isinstance(expression, UnorderedGroup):
                retval = expression
                for n in retval.elements:
                    retval.nodes.append(inner_from_python(n))
                if any((isinstance(x, CrossRef) for x in retval.nodes)):
                    __for_resolving.append(retval)

            elif isinstance(expression, Sequence) or \
                    isinstance(expression, Repetition) or \
                    isinstance(expression, SyntaxPredicate) or \
                    isinstance(expression, Decorator):
                retval = expression
                retval.nodes.append(inner_from_python(retval.elements))
                if any((isinstance(x, CrossRef) for x in retval.nodes)):
                    __for_resolving.append(retval)

            elif type(expression) in [list, tuple]:
                if type(expression) is list:
                    retval = OrderedChoice(expression)
                else:
                    retval = Sequence(expression)

                retval.nodes = [inner_from_python(e) for e in expression]
                if any((isinstance(x, CrossRef) for x in retval.nodes)):
                    __for_resolving.append(retval)

            else:
                raise GrammarError("Unrecognized grammar element '%s'." %
                                   text(expression))

            # Translate separator expression.
            if isinstance(expression, Repetition) and expression.sep:
                expression.sep = inner_from_python(expression.sep)

            return retval

        # Cross-ref resolving
        def resolve():
            for e in __for_resolving:
                for i, node in enumerate(e.nodes):
                    if isinstance(node, CrossRef):
                        self.__cross_refs -= 1
                        e.nodes[i] = __rule_cache[node.target_rule_name]

        parser_model = inner_from_python(expression)
        resolve()
        assert self.__cross_refs == 0, "Not all crossrefs are resolved!"
        return parser_model

    def errors(self):
        pass
