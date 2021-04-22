##############################################################################
#
#     parser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from .arpeggio import ParserPython, visit_parse_tree, NoMatch

from .error import ParseError
from .grammar import GRAMMAR_ROOT, comment
from .visitor import Visitor
from .analyser import Analyser



class Parser:
   def __init__ (self, grammar_root=GRAMMAR_ROOT):
      self._parser = ParserPython (grammar_root, comment, autokwd=True)

   def parse (self, input_text, file_name):
      parse_tree = self._get_parse_tree (input_text, file_name)
      ast = self._get_ast (parse_tree)
      return self._analyse_ast (ast)

   def _get_parse_tree (self, input_text, file_name):
      try:
         cst = self._parser.parse (input_text, file_name)
         return cst
      except NoMatch as err:
         raise ParseError (err)

   def _get_ast (self, parse_tree):
      visitor = Visitor (self._parser)
      ast = visit_parse_tree (parse_tree, visitor)
      return ast

   def _analyse_ast (self, ast):
      analyser = Analyser ()
      analyser.analyse (ast)
      return ast
