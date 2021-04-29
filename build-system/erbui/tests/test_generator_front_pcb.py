#!/usr/bin/env python
#
#     test_generator_front_pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import unittest
import traceback

from .. import ast
from . import mock

from ..generators.front_pcb.kicad_pcb import KicadPcb
from ..generators.front_pcb.s_expression import Writer


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.abspath (os.path.join (PATH_THIS, 'artifacts'))
PATH_ERBUI = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_FRONT_PCB = os.path.join (PATH_ERBUI, 'generators', 'front_pcb')


class TestGeneratorFrontPcb (unittest.TestCase):

   def setUp(self):
      if not os.path.exists (PATH_ARTIFACTS):
         os.makedirs (PATH_ARTIFACTS)

   def test_001 (self):
      gen = KicadPcb ()
      component = gen.load_component (
         os.path.join (PATH_FRONT_PCB, 'alpha.9mm', 'alpha.9mm.kicad_pcb')
      )

      writer = Writer ()
      writer.write (component, os.path.join (PATH_ARTIFACTS, 'alpha.9mm.load.kicad_pcb'))

   def test_002 (self):
      gen = KicadPcb ()
      component = gen.load_component (
         os.path.join (PATH_FRONT_PCB, 'thonk.pj398sm', 'thonk.pj398sm.kicad_pcb')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('10mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('20mm'), 'mm'),
      )
      component = gen.move (component, position)

      writer = Writer ()
      writer.write (component, os.path.join (PATH_ARTIFACTS, 'thonk.pj398sm.move.kicad_pcb'))

   def test_002b (self):
      gen = KicadPcb ()
      component = gen.load_component (
         os.path.join (PATH_FRONT_PCB, 'alpha.9mm', 'alpha.9mm.kicad_pcb')
      )

      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('10mm'), 'mm'),
         ast.DistanceLiteral (mock.literal ('20mm'), 'mm'),
      )
      component = gen.move (component, position)

      writer = Writer ()
      writer.write (component, os.path.join (PATH_ARTIFACTS, 'alpha.9mm.move.kicad_pcb'))

   def test_003 (self):
      module = ast.Module (mock.identifier ('test_generator_front_pcb_003'))
      module.entities.append (ast.Width (ast.DistanceLiteral (mock.literal ('10hp'), 'hp')))

      control = ast.Control (
         mock.identifier ('test'),
         mock.keyword ('Trim')
      )
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('5hp'), 'hp'),
         ast.DistanceLiteral (mock.literal ('32mm'), 'mm'),
      )
      control.entities.append (position)
      style = ast.Style (mock.keyword ('songhuei.9mm'))
      control.entities.append (style)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('test'),
         mock.keyword ('Pot')
      )
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('5hp'), 'hp'),
         ast.DistanceLiteral (mock.literal ('64mm'), 'mm'),
      )
      control.entities.append (position)
      style = ast.Style (mock.keyword ('rogan.6ps'))
      control.entities.append (style)
      module.entities.append (control)

      control = ast.Control (
         mock.identifier ('test'),
         mock.keyword ('CvIn')
      )
      position = ast.Position (
         ast.DistanceLiteral (mock.literal ('5hp'), 'hp'),
         ast.DistanceLiteral (mock.literal ('96mm'), 'mm'),
      )
      control.entities.append (position)
      style = ast.Style (mock.keyword ('thonk.pj398sm.hex'))
      control.entities.append (style)
      module.entities.append (control)

      gen = KicadPcb ()
      gen.generate_module (PATH_ARTIFACTS, module)



if __name__ == '__main__':
   unittest.main ()
