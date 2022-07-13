#!/usr/bin/env python
#
#     test_generator_kicad.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import unittest
import traceback

from ..generators.kicad import sch, pcb


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.abspath (os.path.join (PATH_THIS, 'artifacts'))
PATH_ERBUI = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_FRONT_PCB = os.path.join (PATH_ERBUI, 'generators', 'front_pcb')


class TestGeneratorKicad (unittest.TestCase):

   def setUp(self):
      if not os.path.exists (PATH_ARTIFACTS):
         os.makedirs (PATH_ARTIFACTS)

   def test_sch_000 (self):
      root = sch.Root.read (os.path.join (PATH_THIS, 'test_generator_kicad_asset_001.kicad_sch'))
      root.write (os.path.join (PATH_ARTIFACTS, 'test_generator_kicad_asset_001.kicad_sch'))

   def test_sch_001 (self):
      root = sch.Root.read (os.path.join (PATH_FRONT_PCB, 'alpha.9mm.manual', 'alpha.9mm.manual.kicad_sch'))
      root.write (os.path.join (PATH_ARTIFACTS, 'alpha.9mm.manual.kicad_sch'))

   def test_sch_002 (self):
      root = sch.Root.read (os.path.join (PATH_FRONT_PCB, 'alpha.9mm.wire', 'alpha.9mm.wire.kicad_sch'))
      root.write (os.path.join (PATH_ARTIFACTS, 'alpha.9mm.wire.kicad_sch'))

   def test_sch_003 (self):
      root = sch.Root.read (os.path.join (PATH_FRONT_PCB, 'rogan.2ps', 'rogan.2ps.kicad_sch'))
      root.write (os.path.join (PATH_ARTIFACTS, 'rogan.2ps.kicad_sch'))

   def test_pcb_001 (self):
      root = pcb.Root.read (os.path.join (PATH_FRONT_PCB, 'alpha.9mm.manual', 'alpha.9mm.manual.kicad_pcb'))
      root.write (os.path.join (PATH_ARTIFACTS, 'alpha.9mm.manual.kicad_pcb'))

   def test_pcb_002 (self):
      root = pcb.Root.read (os.path.join (PATH_FRONT_PCB, 'alpha.9mm.wire', 'alpha.9mm.wire.kicad_pcb'))
      root.write (os.path.join (PATH_ARTIFACTS, 'alpha.9mm.wire.kicad_pcb'))

   def test_pcb_003 (self):
      root = pcb.Root.read (os.path.join (PATH_FRONT_PCB, 'rogan.2ps', 'rogan.2ps.kicad_pcb'))
      root.write (os.path.join (PATH_ARTIFACTS, 'rogan.2ps.kicad_pcb'))



if __name__ == '__main__':
   unittest.main ()
