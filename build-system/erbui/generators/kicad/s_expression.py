##############################################################################
#
#     s_expression.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from ...arpeggio import RegExMatch as _
from ...arpeggio import Optional, ZeroOrMore, EOF, Combine, And
from ...arpeggio import PTNodeVisitor
from ...arpeggio import ParserPython, visit_parse_tree, NoMatch



#--- Grammar -----------------------------------------------------------------

def symbol ():             return _(r'[^\s()]+')
def string_literal ():     return _(r'\"(?:\\"|.)*?\"')
def float_literal ():      return _(r'[-+]?[0-9]+\.[0-9]+(?=[\s()])')
def integer_literal ():    return _(r'[-+]?[0-9]+(?=[\s()])')

def list ():               return '(', ZeroOrMore (any), ')'
def any ():                return [ list, string_literal, float_literal, integer_literal, symbol ]

def root ():               return any, EOF

GRAMMAR_ROOT = root


#--- AST ---------------------------------------------------------------------

class Node:
   def __init__ (self):
      self.parent = None

   @property
   def is_symbol (self): return isinstance (self, Symbol)

   @property
   def is_string_literal (self): return isinstance (self, StringLiteral)

   @property
   def is_float_literal (self): return isinstance (self, FloatLiteral)

   @property
   def is_integer_literal (self): return isinstance (self, IntegerLiteral)

   @property
   def is_list (self): return isinstance (self, List)

   # kind
   # return foo in the s-expression (foo ... ) or None

   @property
   def kind (self):
      if self.is_list and self.entities and self.entities [0].is_symbol:
         return self.entities [0].value
      else:
         return None


class Symbol (Node):
   def __init__ (self, value):
      assert value is not None
      super (Symbol, self).__init__ ()
      self.value = value

   def __eq__ (self, other):
      if not other.is_symbol: return False
      return self.value == other.value

class StringLiteral (Node):
   def __init__ (self, value):
      assert value is not None
      super (StringLiteral, self).__init__ ()
      if len (value) >= 2:
         if value [0] == '"':
            value = value [1:-1]
      self.value = value

   def __eq__ (self, other):
      if not other.is_string_literal: return False
      return self.value == other.value

class FloatLiteral (Node):
   def __init__ (self, value):
      assert value is not None
      super (FloatLiteral, self).__init__ ()
      self.value = float (value)

   def __eq__ (self, other):
      if not other.is_float_literal: return False
      return self.value == other.value

class IntegerLiteral (Node):
   def __init__ (self, value):
      assert value is not None
      super (IntegerLiteral, self).__init__ ()
      self.value = int (value)

   def __eq__ (self, other):
      if not other.is_integer_literal: return False
      return self.value == other.value

class List (Node):
   def __init__ (self):
      super (List, self).__init__ ()
      self.entities = []

   def __eq__ (self, other):
      if other is None: return False
      if not other.is_list: return False
      if len (self.entities) != len (other.entities): return False
      for pair in zip (self.entities, other.entities):
         if pair [0] != pair [1]: return False
      return True

   def add (self, entity):
      assert isinstance (entity, Node)
      entity.parent = self
      self.entities.append (entity)
      return entity

   def filter_kind (self, kind):
      return [e for e in self.entities if e.kind == kind]

   def filter_kinds (self, kinds):
      return [e for e in self.entities if e.kind in kinds]

   def first_kind (self, kind):
      return next (iter (self.filter_kind (kind)), None)

   def property (self, kind):
      node = self.first_kind (kind)
      if node is None: return None
      return node.entities [1].value

   @staticmethod
   def generate (kind):
      list = List ()
      list.add (Symbol (kind))
      return list

   @staticmethod
   def generate_property (kind, value):
      list = List.generate (kind)
      if isinstance (value, str):
         list.add (StringLiteral (value))
      elif isinstance (value, float):
         list.add (FloatLiteral (value))
      elif isinstance (value, int):
         list.add (IntegerLiteral (value))
      else:
         assert False

      return list

   @staticmethod
   def generate_property_symbol (kind, value):
      list = List.generate (kind)
      list.add (Symbol (value))
      return list


#--- Visitor -----------------------------------------------------------------

class Visitor (PTNodeVisitor):
   def __init__ (self, parser, **kwargs):
      super (Visitor, self).__init__ (defaults=True, **kwargs)
      self.parser = parser

   def visit_symbol (self, node, children):
      return Symbol (node.value)

   def visit_string_literal (self, node, children):
      return StringLiteral (node.value)

   def visit_float_literal (self, node, children):
      return FloatLiteral (node.value)

   def visit_integer_literal (self, node, children):
      return IntegerLiteral (node.value)

   def visit_list (self, node, children):
      list = List ()
      for entity in children.any:
         list.add (entity)
      return list


#--- Parser ------------------------------------------------------------------

class Parser:
   def __init__ (self):
      self.parser = ParserPython (GRAMMAR_ROOT, autokwd=True)

   def parse (self, input_text, file_name):
      cst = self.parser.parse (input_text, file_name)
      visitor = Visitor (self.parser)
      ast = visit_parse_tree (cst, visitor)
      return ast


#--- Writer ------------------------------------------------------------------

class Writer:
   def write (self, ast, filename):
      content = self.write_any (ast)
      with open (filename, 'w', encoding='utf-8') as file:
         file.write (content)

   def write_any (self, node, indent=0):
      if node.is_symbol:
         return node.value + ' '
      elif node.is_string_literal:
         return '"' + node.value + '" '
      elif node.is_float_literal:
         return '%f ' % node.value
      elif node.is_integer_literal:
         return '%d ' % node.value
      elif node.is_list:
         content = '\n' + ('  ' * indent) + '('
         for subnode in node.entities:
            content += self.write_any (subnode, indent + 1)
         content += ')'
         return content
