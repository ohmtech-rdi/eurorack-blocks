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

from ..generators.vcvrack.panel import Panel as vcvrackPanel
from ..generators.vcvrack.manifest import Manifest as vcvrackManifest
from ..generators.vcvrack.code import Code as vcvrackCode
from ..generators.vcvrack.deploy import Deploy as vcvrackDeploy

from ..generators.front_panel.milling import Milling as front_panelMilling
from ..generators.front_panel.printing import Printing as front_panelPrinting


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.abspath (os.path.join (PATH_THIS, 'artifacts'))


class TestGenerators (unittest.TestCase):

   def setUp(self):
      if not os.path.exists (PATH_ARTIFACTS):
         os.makedirs (PATH_ARTIFACTS)

   def make_ast_001 (self):
      root = ast.Root ()

      module = ast.Module ()
      module.name = 'Test'
      module.width = 10 * 5.08 # 10hp
      module.material = ast.Material ()

      module.header = ast.Header ()
      label = ast.Label ()
      label.text = 'Test Header'
      module.header.labels.append (label)

      module.footer = ast.Footer ()
      label = ast.Label ()
      label.text = 'Test Footer'
      module.footer.labels.append (label)

      label = ast.Label ()
      label.text = 'Test Module Center'
      label.positioning.value = 'center'
      module.labels.append (label)

      line = ast.Line ()
      position = ast.Position ()
      position.x = 0
      position.y = 1
      line.points.append (position)
      position = ast.Position ()
      position.x = 2
      position.y = 3
      line.points.append (position)
      module.lines.append (line)

      line = ast.Line ()
      position = ast.Position ()
      position.x = 4.5
      position.y = 5.6
      line.points.append (position)
      position = ast.Position ()
      position.x = 5.08
      position.y = -8.0
      line.points.append (position)
      module.lines.append (line)

      control = ast.Control ()
      control.type = 'Pot'
      control.property = 'test'
      control.position = ast.Position ()
      control.position.x = 10.2
      control.position.y = 10.3
      control.style.value = 'rogan.6ps'
      label = ast.Label ()
      label.text = 'Test Center'
      label.positioning.value = 'center'
      control.labels.append (label)
      label = ast.Label ()
      label.text = 'Test Left'
      label.positioning.value = 'left'
      control.labels.append (label)
      label = ast.Label ()
      label.text = 'Test Top'
      label.positioning.value = 'top'
      control.labels.append (label)
      label = ast.Label ()
      label.text = 'Test Right'
      label.positioning.value = 'right'
      control.labels.append (label)
      label = ast.Label ()
      label.text = 'Test Bottom'
      label.positioning.value = 'bottom'
      control.labels.append (label)
      module.controls.append (control)

      control = ast.Control ()
      control.type = 'Switch'
      control.property = 'switch1'
      control.position = ast.Position ()
      control.position.x = 1.0
      control.position.y = 2.0
      control.style.value = 'dailywell.2ms1'
      control.rotation = 90
      module.controls.append (control)

      control = ast.Control ()
      control.type = 'Switch'
      control.property = 'switch2'
      control.position = ast.Position ()
      control.position.x = 3.0
      control.position.y = 4.0
      control.style.value = 'dailywell.2ms3'
      control.rotation = -90
      module.controls.append (control)

      control = ast.Control ()
      control.type = 'Switch'
      control.property = 'switch3'
      control.position = ast.Position ()
      control.position.x = 5.0
      control.position.y = 5.08
      control.style.value = 'dailywell.2ms1'
      control.rotation = 180
      module.controls.append (control)

      control = ast.Control ()
      control.type = 'GateOut'
      control.property = 'gate_out'
      control.position = ast.Position ()
      control.position.x = 10.0
      control.position.y = 50.01
      control.style.value = 'thonk.pj398sm.knurled'
      label = ast.Label ()
      label.text = 'OUT'
      label.positioning.value = 'top'
      control.labels.append (label)
      module.controls.append (control)

      root.modules.append (module)
      return root


   def make_ast_002 (self):
      root = self.make_ast_001 ()
      root.modules [0].material.color = 'black'
      return root


   def make_ast_003 (self):
      root = self.make_ast_001 ()
      root.modules [0].material.name = 'brushed_aluminum'
      return root


   def make_ast_004 (self):
      root = self.make_ast_001 ()
      root.modules [0].material.name = 'brushed_aluminum'
      root.modules [0].material.color = 'black'
      return root


   def make_ast_005 (self):
      root = self.make_ast_001 ()
      root.modules [0].material.name = 'aluminum_coated'
      root.modules [0].material.color = 'white'
      return root


   def make_ast_006 (self):
      root = self.make_ast_001 ()
      root.modules [0].material.name = 'aluminum_coated'
      root.modules [0].material.color = 'black'
      return root


   def make_ast_007 (self):
      root = self.make_ast_001 ()
      root.modules [0].footer = None
      return root


   def make_ast_008 (self):
      root = self.make_ast_001 ()
      root.modules [0].material.color = 'black'
      root.modules [0].footer = None
      return root


   def test_generators_001 (self):

      generators = [
         ('vcvrack_panel', vcvrackPanel ()),
         ('vcvrack_manifest', vcvrackManifest ()),
         ('vcvrack_code', vcvrackCode ()),
         ('vcvrack_deploy', vcvrackDeploy ()),

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
               generator.generate ('test_generators_%s_%s' % (generator_name, root_name), PATH_THIS, root)
            except:                                # pragma: no cover
               self.fail (traceback.format_exc ()) # pragma: no cover



if __name__ == '__main__':
   unittest.main ()
