#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
from collections import Counter
import logging
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (PATH_THIS))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'kcgen'))
import kcgen



##############################################################################

if sys.version_info < (2, 7):
   print ('This script requires python 2.7 or greater.', file = sys.stderr)
   sys.exit (1)




"""
==============================================================================
Name : generate_gerber
==============================================================================
"""

def generate_gerber ():
   args = lambda: None
   args.input_pcb = os.path.join (PATH_THIS, 'panel-daisy.kicad_pcb')
   args.input_net = ''
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_pcb (args)



"""
==============================================================================
Name : make_blocks
==============================================================================
"""

def make_blocks ():
   conf = open (os.path.join (PATH_THIS, 'panel-daisy-conf.py'), "r").read ()
   dict = eval (conf)
   return dict



"""
==============================================================================
Name : generate_bom_digikey
==============================================================================
"""

def generate_bom_digikey ():
   blocks = make_blocks ();
   distributor_parts = Counter ()
   components_metadata = {}

   for block in blocks:
      quantity = blocks [block]
      block_net = os.path.join (PATH_ROOT, block, '%s.net' % block)
      block_pcb = os.path.join (PATH_ROOT, block, '%s.kicad_pcb' % block)
      design = kcgen.read_design (block_net, block_pcb)
      parts = Counter ()
      for reference in design.components:
         component = design.components [reference]
         if component.distributor.lower () == 'digikey':
            parts [component.distributor_part_number] += 1
            components_metadata [component.distributor_part_number] = component
      for part in parts.keys ():
         parts [part] = parts [part] * quantity
      distributor_parts += parts

   output_dir = os.path.join (PATH_THIS, 'artifacts')
   with open (os.path.join (output_dir, 'panel-daisy-bom-digikey.csv'), 'w') as output:
      output.write ('Diki-Key Part Number;Device;Value;Description;Quantity\n')
      for part in sorted (distributor_parts):
         device = components_metadata [part].device
         value = components_metadata [part].value
         if components_metadata [part].reference.startswith ('J'):
            value = ''
         description = components_metadata [part].description
         quantity = distributor_parts [part]
         output.write ('%s;%s;%s;%s;%d\n' % (part, device, value, description, quantity))



"""
==============================================================================
Name : generate_bom_thonk
==============================================================================
"""

def generate_bom_thonk ():
   blocks = make_blocks ();
   distributor_parts = Counter ()
   components_metadata = {}

   for block in blocks:
      quantity = blocks [block]
      block_net = os.path.join (PATH_ROOT, block, '%s.net' % block)
      block_pcb = os.path.join (PATH_ROOT, block, '%s.kicad_pcb' % block)
      design = kcgen.read_design (block_net, block_pcb)
      parts = Counter ()
      for reference in design.components:
         component = design.components [reference]
         if component.distributor.lower () == 'thonk':
            parts [component.distributor_part_number] += 1
            components_metadata [component.distributor_part_number] = component
      for part in parts.keys ():
         parts [part] = parts [part] * quantity
      distributor_parts += parts

   output_dir = os.path.join (PATH_THIS, 'artifacts')
   with open (os.path.join (output_dir, 'panel-daisy-bom-thonk.csv'), 'w') as output:
      output.write ('Thonk link;Device;Value;Description;Quantity\n')
      for part in sorted (distributor_parts):
         link = components_metadata [part].distributor_link
         device = components_metadata [part].device
         value = components_metadata [part].value
         if components_metadata [part].reference.startswith ('J'):
            value = ''
         description = components_metadata [part].description
         quantity = distributor_parts [part]
         output.write ('%s;%s;%s;%s;%d\n' % (link, device, value, description, quantity))



"""
==============================================================================
Name : generate
==============================================================================
"""

def generate ():
   generate_gerber ()
   generate_bom_digikey ()
   generate_bom_thonk ()



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (generate ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
