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

   def test_module_001 (self):
      source = 'module Foo { width 10hp material aluminum }'

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
      width = module.entities [0]
      self.assertTrue (width.is_width)
      self.assertEqual (width.mm, 50.8)
      self.assertEqual (module.width.mm, 50.8)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      self.assertTrue (material.is_aluminum_natural)

   def test_module_001b (self):
      source = 'module Foo { width 10hp material aluminum black }'

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
      width = module.entities [0]
      self.assertTrue (width.is_width)
      self.assertEqual (width.mm, 50.8)
      self.assertEqual (module.width.mm, 50.8)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      self.assertTrue (material.is_aluminum_black)

   def test_module_002 (self):
      source = 'module Foo { width 10hp material aluminum header { label "TEST" }}'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 3)
      width = module.entities [0]
      self.assertTrue (width.is_width)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      header = module.entities [2]
      self.assertTrue (header.is_header)
      self.assertEqual (len (header.entities), 1)
      label = header.entities [0]
      self.assertTrue (label.is_label)
      self.assertEqual (label.text, 'TEST')
      self.assertIsNone (label.positioning)

   def test_module_003 (self):
      source = 'module Foo { width 10hp material aluminum footer { label "TEST" }}'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 3)
      width = module.entities [0]
      self.assertTrue (width.is_width)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      footer = module.entities [2]
      self.assertTrue (footer.is_footer)
      self.assertEqual (len (footer.entities), 1)
      label = footer.entities [0]
      self.assertTrue (label.is_label)
      self.assertEqual (label.text, 'TEST')
      self.assertIsNone (label.positioning)

   def test_module_004 (self):
      source = 'module Foo { width 10hp material aluminum control foo CvIn { position 1mm, 2mm style rogan.6ps }}'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 3)
      width = module.entities [0]
      self.assertTrue (width.is_width)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      control = module.entities [2]
      self.assertTrue (control.is_control)
      self.assertEqual (len (control.entities), 2)
      position = control.entities [0]
      self.assertTrue (position.is_position)
      self.assertEqual (position.x.mm, 1)
      self.assertEqual (position.y.mm, 2)
      style = control.entities [1]
      self.assertTrue (style.is_style)
      self.assertEqual (style.name, 'rogan.6ps')

   def test_module_005 (self):
      source = 'module Foo { width 10hp material aluminum control foo CvIn { position 1mm, 2mm style rogan.6ps label "TEST" {positioning top}}}'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 3)
      width = module.entities [0]
      self.assertTrue (width.is_width)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      control = module.entities [2]
      self.assertTrue (control.is_control)
      self.assertEqual (len (control.entities), 3)
      position = control.entities [0]
      self.assertTrue (position.is_position)
      style = control.entities [1]
      self.assertTrue (style.is_style)
      label = control.entities [2]
      self.assertTrue (label.is_label)
      self.assertEqual (label.text, 'TEST')
      self.assertTrue (label.positioning.is_top)

   def test_module_006 (self):
      source = 'module Foo { width 10hp material aluminum line { position 1mm, 2mm position 3mm, 4mm }}'

      try:
         global_namespace = self.parse (source)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (global_namespace.is_global_namespace)
      self.assertEqual (len (global_namespace.entities), 1)
      module = global_namespace.entities [0]
      self.assertTrue (module.is_module)
      self.assertEqual (module.name, 'Foo')
      self.assertEqual (len (module.entities), 3)
      width = module.entities [0]
      self.assertTrue (width.is_width)
      material = module.entities [1]
      self.assertTrue (material.is_material)
      line = module.entities [2]
      self.assertTrue (line.is_line)
      self.assertEqual (len (line.entities), 2)
      position = line.entities [0]
      self.assertTrue (position.is_position)
      self.assertEqual (position.x.mm, 1)
      self.assertEqual (position.y.mm, 2)
      position = line.entities [1]
      self.assertTrue (position.is_position)
      self.assertEqual (position.x.mm, 3)
      self.assertEqual (position.y.mm, 4)



if __name__ == '__main__':
   unittest.main ()
