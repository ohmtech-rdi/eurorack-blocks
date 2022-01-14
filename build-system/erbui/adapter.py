##############################################################################
#
#     adapter.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from bisect import bisect_left


#-- Token --------------------------------------------------------------------
#
#  Token represents a token of the lexing phase. It is constructed from a
#  node of the Arpeggio parse tree in the visit phase.
#  A token has:
#  - 'value', which represents the token value,
#  - 'position', which represents the token character position in the parser
#     input,
#  - 'length', which represents the token character length in the parser input.
#
#  Note: the token category is encoded when subclassing this type.

class Token:
   def __init__ (self, parser, node):
      self.value = node.value
      self.position = node.position
      self._parser = parser

   @property
   def length (self):
      return len (self.value)


#-- Identifier ---------------------------------------------------------------
#
#  Identifier is a kind of Token which name is chosen by the programmer.
#  Examples: 'foo', 'Track', 'do_something'

class Identifier (Token):
   @property
   def name (self):
      return self.value


#-- Keyword -----------------------------------------------------------------
#
#  Keyword is a kind of Token which name is used in the programming language.
#  Examples: 'module', 'control', 'center', 'rogan.6ps'

class Keyword (Token):
   pass


#-- BuiltIn -----------------------------------------------------------------
#
#  BuiltIn is a kind of Keyword which represents a declaration
#  for which there is no source file context,
#  as the declaration is implicitly built in the language itself
#  Examples: 'Bool', 'Int'

class BuiltIn (Keyword):
   def __init__ (self, value):
      node = lambda: None
      node.value = value
      node.position = 0
      parser = lambda: None
      parser.input = value
      parser.file_name = None
      super (BuiltIn, self).__init__ (parser, node)


#-- Symbol ------------------------------------------------------------------
#
#  Symbol is a kind of Token representing punctuation characters and
#  paired-delimiters.
#  Examples: '{', '}', ','

class Symbol (Token):
   pass


#-- Literal -----------------------------------------------------------------
#
#  Literal is a kind of Token which represents numerics, logics and textual
#  pieces.
#  Examples: 'true', '32.5', '"FREQ"'

class Literal (Token):
   pass


class LiteralSynthesized (Literal):
   def __init__ (self, value):
      node = lambda: None
      node.value = value
      node.position = 0
      parser = lambda: None
      parser.input = value
      parser.file_name = None
      super (LiteralSynthesized, self).__init__ (parser, node)


#-- SourceContext ------------------------------------------------------------
#
#  SourceContext represents a source context in the parser input. It defines:
#  - 'focus_position', which represents a focus position in the source
#  - 'proximal_begin/end', which represents a position range of interest around
#    the focus position,
#  - 'location', a computed string representing the location in the source.
#  - 'crop_area', which represents the line containing the focus point and
#    the focus point and proximal range for display.
#  - 'proximal_substitution', an optional string replacement for the proximal
#    range when rendering crop area.

class SourceContext:
   def __init__ (self):
      self.focus_position = None
      self.proximal_begin = None
      self.proximal_end = None
      self.proximal_substitution = None
      self._parser = None

   def __str__ (self):
      return self._parser.input [self.proximal_begin : self.proximal_end]

   @property
   def location (self):
      if self._parser.file_name is None:
         return '<builtin>'

      assert self.focus_position is not None
      line_pos, col_pos = self._parser.pos_to_linecol (self.focus_position)
      return '%s:%d:%d' % (self._parser.file_name, line_pos, col_pos)

   @property
   def crop_area (self):
      assert self.focus_position is not None
      assert self.proximal_begin is not None
      assert self.proximal_end is not None

      line_ends = list (self._parser.line_ends)
      line_nbr = bisect_left (line_ends, self.focus_position)
      line_ends.insert (0, 0)
      line_ends.append (len (self._parser.input))

      line_begin_pos = line_ends [line_nbr]
      line_end_pos = line_ends [line_nbr + 1]

      crop_area_str = self._parser.input [line_begin_pos : line_end_pos]
      crop_area_str = crop_area_str.strip ('\r\n')

      proximal_begin_pos = max (self.proximal_begin, line_begin_pos)
      proximal_end_pos = min (self.proximal_end, line_end_pos)
      proximal_length = proximal_end_pos - proximal_begin_pos

      line_proximal_begin_pos = proximal_begin_pos - line_begin_pos - 1

      if self.proximal_substitution:
         crop_area_str = crop_area_str [:line_proximal_begin_pos] + self.proximal_substitution + crop_area_str [line_proximal_begin_pos + proximal_length:]
         crop_area_layout = ' ' * line_proximal_begin_pos
         crop_area_layout += '~' * len (self.proximal_substitution)

      else:
         crop_area_layout = ' ' * line_proximal_begin_pos
         crop_area_layout += '~' * proximal_length

      focus_index = self.focus_position - line_begin_pos - 1
      crop_area_layout = crop_area_layout [:focus_index] + '^' + crop_area_layout [focus_index + 1:]

      return (crop_area_str, crop_area_layout)

   @staticmethod
   def from_token (token):
      ret = SourceContext ()
      if token.position is not None:
         ret.focus_position = token.position
         ret.proximal_begin = token.position
         ret.proximal_end = token.position + token.length
      ret._parser = token._parser
      return ret

   @staticmethod
   def from_token_range (first, last):
      ret = SourceContext ()
      assert first.position is not None
      assert last.position is not None
      assert first.position <= last.position
      assert first._parser is last._parser

      ret.focus_position = first.position
      ret.proximal_begin = first.position
      ret.proximal_end = last.position + last.length
      ret._parser = first._parser
      return ret

   @staticmethod
   def extend (base, second):
      assert isinstance (base, SourceContext)
      assert isinstance (second, SourceContext)
      assert base._parser is second._parser
      assert base.proximal_substitution is None
      assert second.proximal_substitution is None

      ret = SourceContext ()
      ret.focus_position = base.focus_position
      ret.proximal_begin = min (base.proximal_begin, second.proximal_begin)
      ret.proximal_end = max (base.proximal_end, second.proximal_end)
      ret._parser = base._parser
      return ret
