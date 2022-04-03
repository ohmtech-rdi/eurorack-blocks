#!/usr/bin/env python
#
#     test_generators.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import unittest
import traceback

from .. import ast
from . import mock

from ..generators.vcvrack.panel import Panel as vcvrackPanel
from ..generators.vcvrack.manifest import Manifest as vcvrackManifest
from ..generators.vcvrack.code import Code as vcvrackCode

from ..generators.front_panel.milling import Milling as front_panelMilling
from ..generators.front_panel.printing import Printing as front_panelPrinting


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.abspath (os.path.join (PATH_THIS, 'artifacts'))


class TestGenerators (unittest.TestCase):

   def setUp(self):
      if not os.path.exists (PATH_ARTIFACTS):
         os.makedirs (PATH_ARTIFACTS)

   def make_ast_001 (self):
      global_namespace = ast.GlobalNamespace ()

      module = ast.Module (mock.identifier ('Test'), None)
      module.add (ast.Width (ast.DistanceLiteral (mock.literal ('10hp'), 'hp')))
      module.add (ast.Material (mock.keyword ('aluminum'), None))

      header = ast.Header ()
      label = ast.Label (ast.StringLiteral (mock.literal ('Test Header')))
      header.add (label)
      module.add (header)

      footer = ast.Footer ()
      label = ast.Label (ast.StringLiteral (mock.literal ('Test Footer')))
      footer.add (label)
      module.add (footer)

      label = ast.Label (ast.StringLiteral (mock.literal ('Test Module Center')))
      positioning = ast.Positioning (mock.keyword ('center'))
      label.add (positioning)
      module.add (label)

      line = ast.Line ()
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('0mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('1mm'), 'mm'),
      )
      line.add (position)
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('2mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('3mm'), 'mm'),
      )
      line.add (position)
      module.add (line)

      line = ast.Line ()
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('4.5mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('5.6mm'), 'mm'),
      )
      line.add (position)
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('1hp'), 'hp'),
         ast.DistanceLiteral (mock.literal ('-8.0mm'), 'mm'),
      )
      line.add (position)
      module.add (line)

      control = ast.Control (
         mock.identifier ('test'),
         mock.keyword ('Pot')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('10.2mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('10.3mm'), 'mm'),
      )
      control.add (position)

      style = ast.Style (mock.keyword ('rogan.6ps'))
      control.add (style)

      label = ast.Label (ast.StringLiteral (mock.literal ('Test Center')))
      positioning = ast.Positioning (mock.keyword ('center'))
      label.add (positioning)
      control.add (label)

      label = ast.Label (ast.StringLiteral (mock.literal ('Test Left')))
      positioning = ast.Positioning (mock.keyword ('left'))
      label.add (positioning)
      control.add (label)

      label = ast.Label (ast.StringLiteral (mock.literal ('Test Top')))
      positioning = ast.Positioning (mock.keyword ('top'))
      label.add (positioning)
      control.add (label)

      label = ast.Label (ast.StringLiteral (mock.literal ('Test Right')))
      positioning = ast.Positioning (mock.keyword ('right'))
      label.add (positioning)
      control.add (label)

      label = ast.Label (ast.StringLiteral (mock.literal ('Test Bottom')))
      positioning = ast.Positioning (mock.keyword ('bottom'))
      label.add (positioning)
      control.add (label)

      module.add (control)

      control = ast.Control (
         mock.identifier ('switch1'),
         mock.keyword ('Switch')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('1.0mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('2.0mm'), 'mm'),
      )
      control.add (position)

      style = ast.Style (mock.keyword ('dailywell.2ms1'))
      control.add (style)

      rotation = ast.Rotation (ast.RotationLiteral (mock.literal ('90°ccw'), '°ccw'))
      control.add (rotation)

      module.add (control)

      control = ast.Control (
         mock.identifier ('switch2'),
         mock.keyword ('Switch')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('3.0mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('4.0mm'), 'mm'),
      )
      control.add (position)

      style = ast.Style (mock.keyword ('dailywell.2ms3'))
      control.add (style)

      rotation = ast.Rotation (ast.RotationLiteral (mock.literal ('90°cw'), '°cw'))
      control.add (rotation)

      module.add (control)

      control = ast.Control (
         mock.identifier ('switch3'),
         mock.keyword ('Switch')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('5.0mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('1hp'), 'hp'),
      )
      control.add (position)

      style = ast.Style (mock.keyword ('dailywell.2ms3'))
      control.add (style)

      rotation = ast.Rotation (ast.RotationLiteral (mock.literal ('180°'), '°'))
      control.add (rotation)

      module.add (control)

      control = ast.Control (
         mock.identifier ('gate_out'),
         mock.keyword ('GateOut')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('10.00mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('50.01mm'), 'mm'),
      )
      control.add (position)

      style = ast.Style (mock.keyword ('thonk.pj398sm.knurled'))
      control.add (style)

      label = ast.Label (ast.StringLiteral (mock.literal ('OUT')))
      positioning = ast.Positioning (mock.keyword ('top'))
      label.add (positioning)
      control.add (label)

      module.add (control)

      global_namespace.add (module)
      return global_namespace


   def make_ast_002 (self):
      global_namespace = self.make_ast_001 ()
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_material]
      module.add (ast.Material (mock.keyword ('aluminum'), mock.keyword ('black')))
      return global_namespace


   def make_ast_003 (self):
      global_namespace = self.make_ast_001 ()
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_material]
      module.add (ast.Material (mock.keyword ('brushed_aluminum'), None))
      return global_namespace


   def make_ast_004 (self):
      global_namespace = self.make_ast_001 ()
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_material]
      module.add (ast.Material (mock.keyword ('brushed_aluminum'), mock.keyword ('black')))
      return global_namespace


   def make_ast_005 (self):
      global_namespace = self.make_ast_001 ()
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_material]
      module.add (ast.Material (mock.keyword ('aluminum_coated'), mock.keyword ('white')))
      return global_namespace


   def make_ast_006 (self):
      global_namespace = self.make_ast_001 ()
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_material]
      module.add (ast.Material (mock.keyword ('aluminum_coated'), mock.keyword ('black')))
      return global_namespace


   def make_ast_007 (self):
      global_namespace = self.make_ast_001 ()
      entities = global_namespace.modules [0].entities
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_footer]
      return global_namespace


   def make_ast_008 (self):
      global_namespace = self.make_ast_002 ()
      entities = global_namespace.modules [0].entities
      module = global_namespace.modules [0]
      module.entities = [entity for entity in module.entities if not entity.is_footer]
      return global_namespace


   def test_generators_001 (self):

      generators = [
         ('vcvrack_panel', vcvrackPanel ()),
         ('vcvrack_manifest', vcvrackManifest ()),
         ('vcvrack_code', vcvrackCode ()),

         ('front_panel_milling', front_panelMilling ()),
         ('front_panel_printing', front_panelPrinting ()),
      ]
      roots = [
         ('ast_001', self.make_ast_001 ()),
         ('ast_002', self.make_ast_002 ()),
         ('ast_003', self.make_ast_003 ()),
         ('ast_004', self.make_ast_004 ()),
         ('ast_005', self.make_ast_005 ()),
         ('ast_006', self.make_ast_006 ()),
         ('ast_007', self.make_ast_007 ()),
         ('ast_008', self.make_ast_008 ()),
      ]

      for generator_name, generator in generators:
         for root_name, root in roots:
            try:
               test_name = 'test_generators_%s_%s' % (generator_name, root_name)
               output_path = os.path.join (PATH_ARTIFACTS, test_name)

               if not os.path.exists (output_path):
                  os.makedirs (output_path)

               generator.generate (output_path, root)
            except:                                # pragma: no cover
               self.fail (traceback.format_exc ()) # pragma: no cover



if __name__ == '__main__':
   unittest.main ()
