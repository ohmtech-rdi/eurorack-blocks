##############################################################################
#
#     error.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

import copy
import os
import re
from difflib import get_close_matches

from .arpeggio import EndOfFile, Match
from . import adapter
from . import ast
from . import grammar



class Error (Exception):

   class Part:
      def __init__ (self):
         self.type = ''
         self.msg = ""
         self.source_context = None

      def get_category (self, colored):
         if colored:
            category_map = {
               'error': '\033[91merror:\033[0m',
               'note': '\033[90mnote:\033[0m',
               'hint': '\033[33mhint:\033[0m',
               'fixit': '\033[33mfixit:\033[0m',
               'help': '\033[94mhelp:\033[0m',
            }
            return category_map [self.type]
         else:
            return self.type + ':'



   def __init__ (self):
      super (Error, self).__init__ ()
      self.colored = False
      self._parts = []

   def __str__ (self):
      ret = ''
      for part in self._parts:
         if part.type in ('error', 'note', 'hint', 'fixit'):
            category = part.get_category (self.colored)
            ret += '%s: %s %s\n' % (part.source_context.location, category, part.msg)

         elif part.type == 'help':
            category = part.get_category (self.colored)
            ret += '%s %s\n' % (category, part.msg)

         elif part.type == 'context':
            crop_area = part.source_context.crop_area
            cs = '\033[32m' if self.colored else ''
            ce = '\033[0m' if self.colored else ''
            ret += '   %s\n   %s%s%s\n' % (crop_area [0], cs, crop_area [1], ce)

      return ret

   def color (self):
      self.colored = True

   def add_error (self, msg, source_context):
      assert isinstance (source_context, adapter.SourceContext)
      part = Error.Part ()
      part.type = 'error'
      part.msg = msg
      part.source_context = source_context
      self._parts.append (part)

   def add_note (self, msg, source_context):
      assert isinstance (source_context, adapter.SourceContext)
      part = Error.Part ()
      part.type = 'note'
      part.msg = msg
      part.source_context = source_context
      self._parts.append (part)

   def add_context (self, source_context):
      assert isinstance (source_context, adapter.SourceContext)
      if source_context._parser.file_name is None:
         return # ignore

      part = Error.Part ()
      part.type = 'context'
      part.source_context = source_context
      self._parts.append (part)

   def add_context_fixit (self, source_context, substitution):
      assert isinstance (source_context, adapter.SourceContext)
      assert source_context.focus_position is not None
      assert source_context._parser.file_name is not None

      part = Error.Part ()
      part.type = 'context'
      part.source_context = source_context
      part.source_context.proximal_substitution = substitution
      self._parts.append (part)

   def add_hint (self, msg, source_context):
      assert isinstance (source_context, adapter.SourceContext)
      part = Error.Part ()
      part.type = 'hint'
      part.msg = msg
      part.source_context = source_context
      self._parts.append (part)

   def add_fixit (self, source_context):
      assert isinstance (source_context, adapter.SourceContext)
      part = Error.Part ()
      part.type = 'fixit'
      part.source_context = source_context
      self._parts.append (part)

   def add_help (self, article):
      part = Error.Part ()
      part.type = 'help'
      base_url = 'https://github.com/ohmtech-rdi/eurorack-blocks/tree/main'
      help_article = '%s/build-system/erbb/documentation/help/%s.md' % (base_url, article)
      help_intro = "Please visit the following URL to learn more about this issue:\n"
      part.msg = help_intro + help_article
      self._parts.append (part)



#-- undefined_reference ------------------------------------------------------
#
#  Build an undefined reference error.
#  - 'reference': the reference that can not be resolved
#  - 'fixit_declarations_sc' a list of source contexts for declarations
#  that are potential candidates for correction.

def undefined_reference (reference, fixit_declarations_sc):
   assert isinstance (reference, ast.Alias) or isinstance (reference, ast.ManufacturerReference)

   err = Error ()
   context = reference.source_context_part ('reference')
   err.add_error ("Undefined reference to '%s'" % context, context)
   err.add_context (context)

   for declaration_sc in fixit_declarations_sc:
      err.add_note ("did you mean '%s'?" % declaration_sc, declaration_sc)
      err.add_context (declaration_sc)

   return err



#-- unknown_pin --------------------------------------------------------------
#
#  Build an unknown pin error.
#  - 'pin': the pin which name is not known
#  - 'pin_names' a list pin names that are potential candidates for correction.

def unknown_pin (pin, pin_names):
   assert isinstance (pin, ast.Pin)

   err = Error ()
   pin_name = pin.source_context_part ('name')
   err.add_error ("Unknown pin '%s'" % pin_name, pin_name)
   err.add_context (pin_name)

   matches = get_close_matches (pin.name, pin_names)

   if matches:
      builtin = adapter.BuiltIn (matches [0])
      pin_name = pin.source_context_part ('name')
      sc = adapter.SourceContext.from_token (builtin)
      err.add_note ("did you mean '%s'?" % sc, sc)
      err.add_context_fixit (pin_name, "%s" % sc)

   return err



#-- already_used_pin ---------------------------------------------------------
#
#  Build an already used pin error.
#  - 'pin': the pin for which hardware pin has already been used
#  - 'previous_pin': the previous declaration

def already_used_pin (pin, previous_pin):
   assert isinstance (pin, ast.Pin)
   assert isinstance (previous_pin, ast.Pin)

   name = pin.source_context_part ('name')
   previous_name = previous_pin.source_context_part ('name')

   err = Error ()
   err.add_error ("'%s' already used" % name, name)
   err.add_context (name)
   err.add_note ("previously used here:", previous_name)
   err.add_context (previous_name)

   return err



#-- unknown_style ------------------------------------------------------------
#
#  Build an unknown style error.
#  - 'style': the style which name is not known
#  - 'style_names' an iteratable style names that are potential candidates for
#    correction.

def unknown_style (style, style_names):
   assert isinstance (style, adapter.Keyword)

   err = Error ()
   context = adapter.SourceContext.from_token (style)
   err.add_error ("Unknown style '%s'" % context, context)
   err.add_context (context)

   matches = get_close_matches (str (context), style_names, n=1, cutoff=0.5)

   if matches:
      builtin = adapter.BuiltIn (matches [0])
      sc = adapter.SourceContext.from_token (builtin)
      context = adapter.SourceContext.from_token (style)
      err.add_note ("did you mean '%s'?" % sc, sc)
      err.add_context_fixit (context, "%s" % sc)

   return err



#-- incompatible_style -------------------------------------------------------
#
#  Build an incompatible style error.
#  - 'style': the style which name is not known
#  - 'style_names' an iteratable style names that is the current styles
#    selection

def incompatible_style (style, style_names):
   assert isinstance (style, adapter.Keyword)

   err = Error ()
   context = adapter.SourceContext.from_token (style)
   err.add_error ("Incompatible style '%s'" % context, context)
   err.add_context (context)

   computed_style = ', '.join (style_names)
   builtin = adapter.BuiltIn (computed_style)
   sc = adapter.SourceContext.from_token (builtin)
   err.add_note ("for selected styles '%s'" % computed_style, sc)

   return err



#-- missing_required ---------------------------------------------------------
#
#  Build a missing required error for properties that are just to be defined
#  exactly once.
#  - 'declaration': the declaration for which name has already been declared
#  - 'previous_declaration': the previous declaration

def missing_required (parent, type):
   assert isinstance (parent, ast.Node)
   assert issubclass (type, ast.Node)

   parent_name = parent.source_context_part ('name')
   type_name = type.typename ()

   err = Error ()
   err.add_error ("No '%s' defined in '%s'" % (type_name, parent.name), parent_name)
   err.add_context (parent_name)
   return err



#-- multiple_definition ------------------------------------------------------
#
#  Build a multiple definition error for properties that are just meant to be
#  defined once.
#  - 'parent': the parent node where multiple definitions occured
#  - 'nodes': the list of multiple nodes

def multiple_definition (parent, nodes):
   assert isinstance (parent, ast.Node)
   assert isinstance (nodes, list)

   parent_name = parent.source_context_part ('name')

   kind = nodes [0].typename ()

   err = Error ()
   err.add_error ("'%s' defined multiple times in '%s'" % (kind, parent.name), parent_name)
   err.add_context (parent_name)
   for node in nodes:
      name = node.source_context_part ('name')
      err.add_note ("defined here:", name)
      err.add_context (name)
   return err



#-- reserved_name ------------------------------------------------------------
#
#  Build a reserved name error.
#  - 'source_context': the name which is reserved

def reserved_name (source_context):
   err = Error ()
   err.add_error ("'%s' name is reserved" % source_context, source_context)
   err.add_context (source_context)
   return err



#-- unsupported_feature ------------------------------------------------------
#
#  Build an unsupported feature error.
#  - 'feature': a brief description about the unsupported feature
#  - 'source_context': the source context of the unsupported feature

def unsupported_feature (feature, source_context):
   assert isinstance (feature, str)
   err = Error ()
   err.add_error ("%s is not supported" % feature, source_context)
   err.add_context (source_context)
   return err



class ParseError (Error):

   rules_str = {
      'string_literal': 'string literal',
      'float_mm_literal': 'millimeter literal',
      'float_cm_literal': 'centimeter literal',
      'float_hp_literal': 'HP literal',
      'float_deg_ccw_literal': 'CCW degree literal',
      'float_deg_cw_literal': 'CW degree literal',
      'module_name': 'module name',
      'material_name': 'material name',
      'material_color': 'material color',
      'control_name': 'control name',
   }


   def __init__ (self, no_match):
      super (ParseError, self).__init__ ()

      source_context = adapter.SourceContext ()
      source_context.focus_position = no_match.position
      source_context.proximal_begin = no_match.position
      source_context.proximal_end = no_match.position
      source_context._parser = no_match.parser

      rules_set = self._to_rule_names (no_match.rules)

      if rules_set == {'float_cm_literal', 'float_hp_literal', 'float_mm_literal'}:
         r = re.match (r'[0-9\.]+', no_match.parser.input [no_match.position:])
         if r:
            m = r.group (0)
            r2 = re.match (r'[0-9\.]+[a-zA-Z]*', no_match.parser.input [no_match.position:])
            m2 = r2.group (0)
            source_context.focus_position = source_context.proximal_end
            source_context.focus_position += len (m)
            source_context.proximal_end += len (m2)
            self.add_error ("Expected mm, cm, or hp unit", source_context)
            self.add_context (source_context)
            self.add_note ("did you mean '%smm'?" % m, source_context)
            self.add_context_fixit (copy.copy (source_context), "%smm" % m)
         else:
            r2 = re.match (r'[0-9\.a-zA-Z]+', no_match.parser.input [no_match.position:])
            m2 = r2.group (0)
            source_context.proximal_end += len (m2)
            self.add_error ('Expected length', source_context)
            self.add_context (source_context)

      else:
         expected_rules_message = self._get_expected_rules_message (no_match.rules)
         self.add_error (expected_rules_message, source_context)
         self.add_context (source_context)


   def _to_rule_names (self, rules):
      return {rule.rule_name for rule in rules if rule.root}


   def _get_expected_rules_message (self, rules):
      expected = {'keywords': [], 'control_kinds': [], 'control_styles': [], 'symbols': [], 'rule_names': []}
      rule_to_exclude = ['comment']

      def rule_to_exp_str (rule):
         if rule.root:
            return rule.rule_name

         if isinstance (rule, Match) and not isinstance (rule, EndOfFile):
            return "'{}'".format (rule.to_match)

         return rule.name


      for rule in list (dict.fromkeys (rules)):
         rule_name = rule_to_exp_str (rule)
         if rule_name not in rule_to_exclude:
            rule_name = rule_name.strip ("'")
            if rule_name in ParseError.rules_str:
               rule_name = ParseError.rules_str [rule_name]

            if rule_name in grammar.KEYWORDS:
               expected ['keywords'].append ("'{}'".format (rule_name))
            elif rule_name in grammar.CONTROL_KINDS:
               expected ['control_kinds'].append ("'{}'".format (rule_name))
            elif rule_name in grammar.SYMBOLS:
               expected ['symbols'].append ("'{}'".format (rule_name))
            else:
               expected ['rule_names'].append ("{}".format (rule_name))


      def prettify_choices (iterable):
         if len (iterable) == 1:
            return iterable [0]

         text = ", ".join (iterable [:-1])
         return '{} or {}'.format (text, iterable [-1])


      rule_names = sorted (expected ['rule_names'])
      keywords = sorted (expected ['keywords'])
      control_kinds = sorted (list (dict.fromkeys (expected ['control_kinds'])))
      control_styles = sorted (list (dict.fromkeys (expected ['control_styles'])))
      symbols = sorted (expected ['symbols'])

      what_is_expected = []
      if rule_names:
         what_is_expected.append ('{}'.format (prettify_choices (rule_names)))
      if keywords:
         what_is_expected.append ('{} {}'.format ('keyword', prettify_choices (keywords)))
      if control_kinds:
         what_is_expected.append ('{} {}'.format ('kind', prettify_choices (control_kinds)))
      if control_styles:
         what_is_expected.append ('{} {}'.format ('style', prettify_choices (control_styles)))
      if symbols:
         what_is_expected.append ('{} {}'.format ('symbol', prettify_choices (symbols)))

      if what_is_expected:
         return 'Expected {}'.format (prettify_choices (what_is_expected))

      return 'Unexpected Input' # pragma: no cover
