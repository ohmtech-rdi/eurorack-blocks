##############################################################################
#
#     parser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from .arpeggio import ParserPython, visit_parse_tree, NoMatch

from .error import ParseError
from .grammar import GRAMMAR_ROOT, GRAMMAR_LIBRARY_ROOT, comment
from .visitor import Visitor
from .analyser import Analyser

import os


class Parser:
   def __init__ (self, grammar_root=GRAMMAR_ROOT):
      self._parser = ParserPython (grammar_root, comment, autokwd=True)

   def parse (self, input_text, file_name):
      parse_tree = self._get_parse_tree (input_text, file_name)
      ast = self._get_ast (parse_tree, file_name)

      for module in ast.modules:
         for import_ in module.imports:
            self._merge_import (module, import_)

      return self._analyse_ast (ast)

   def parse_library (self, input_text, file_name):
      parse_tree = self._get_parse_tree (input_text, file_name)
      ast = self._get_ast (parse_tree, file_name)

      for import_ in ast.imports:
         self._merge_import (ast, import_)

      return ast

   def _merge_import (self, node, import_):
      import_path = import_.path
      try:
         file = open (import_path, 'r')
      except OSError:
         err = error.Error ()
         context = import_.literal
         err.add_error ("Cannot open file for import '%s'" % context, context)
         err.add_context (context)
         raise err

      with file:
         input_text = file.read ()

      import_parser = Parser (grammar_root=GRAMMAR_LIBRARY_ROOT)
      import_ast = import_parser.parse_library (input_text, import_path)

      node.entities.extend (import_ast.entities)

   def _get_parse_tree (self, input_text, file_name):
      try:
         cst = self._parser.parse (input_text, file_name)
         return cst
      except NoMatch as err:
         raise ParseError (err)

   def _get_ast (self, parse_tree, file_name):
      visitor = Visitor (self._parser)
      visitor.set_filename (file_name)
      ast = visit_parse_tree (parse_tree, visitor)
      return ast

   def _analyse_ast (self, ast):
      analyser = Analyser ()
      analyser.analyse (ast)
      return ast
