#!/usr/bin/env python
#
#     test_parser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

import unittest
import traceback
from .. import grammar
from .. import adapter
from .. import error
from .. import parser


class TestParser (unittest.TestCase):

   def parse (self, source, grammar_root = grammar.GRAMMAR_ROOT):
      p = parser.Parser (grammar_root)
      parse_tree = p._get_parse_tree (source, 'test')
      ast = p._get_ast (parse_tree, 'test')
      return ast

   def parse_library (self, source, grammar_root = grammar.GRAMMAR_LIBRARY_ROOT):
      p = parser.Parser (grammar_root)
      parse_tree = p._get_parse_tree (source, 'test')
      ast = p._get_ast (parse_tree, 'test')
      return ast

   def test_module_001 (self):
      source = 'module Foo { define bar=0 }'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 1)
      define = module.entities [0]
      self.assertTrue (define.is_define)
      self.assertEqual (define.key, 'bar')
      self.assertEqual (define.value, '0')

   def test_module_001b (self):
      source = 'module Foo { define bar=0 define bar2=bar3 }'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 2)
      define = module.entities [0]
      self.assertTrue (define.is_define)
      self.assertEqual (define.key, 'bar')
      self.assertEqual (define.value, '0')
      define2 = module.entities [1]
      self.assertTrue (define2.is_define)
      self.assertEqual (define2.key, 'bar2')
      self.assertEqual (define2.value, 'bar3')

   def test_module_002 (self):
      source = 'module Foo { base ".." }'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 1)
      base = module.entities [0]
      self.assertTrue (base.is_base)
      self.assertEqual (base.path, '..')

   def test_module_003 (self):
      source = 'module Foo { sources { file "foo"\nfile "bar"} }'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 1)
      sources = module.entities [0]
      self.assertTrue (sources.is_sources)
      self.assertEqual (len (sources.entities), 2)
      file1 = sources.entities [0]
      self.assertTrue (file1.is_file)
      self.assertEqual (file1.path, 'foo')
      file2 = sources.entities [1]
      self.assertTrue (file2.is_file)
      self.assertEqual (file2.path, 'bar')

   def test_library_001 (self):
      source = 'define bar=0'

      try:
         library = self.parse_library (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (library.is_library)
      self.assertEqual (len (library.entities), 1)
      define = library.entities [0]
      self.assertTrue (define.is_define)
      self.assertEqual (define.key, 'bar')
      self.assertEqual (define.value, '0')

   def test_library_002 (self):
      source = 'base ".."'

      try:
         library = self.parse_library (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (library.is_library)
      self.assertEqual (len (library.entities), 1)
      base = library.entities [0]
      self.assertTrue (base.is_base)
      self.assertEqual (base.path, '..')

   def test_library_003 (self):
      source = 'sources { file "foo"\nfile "bar"}'

      try:
         library = self.parse_library (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (library.is_library)
      self.assertEqual (len (library.entities), 1)
      sources = library.entities [0]
      self.assertTrue (sources.is_sources)
      self.assertEqual (len (sources.entities), 2)
      file1 = sources.entities [0]
      self.assertTrue (file1.is_file)
      self.assertEqual (file1.path, 'foo')
      file2 = sources.entities [1]
      self.assertTrue (file2.is_file)
      self.assertEqual (file2.path, 'bar')




if __name__ == '__main__':
   unittest.main ()
