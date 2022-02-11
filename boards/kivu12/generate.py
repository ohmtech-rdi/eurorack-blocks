#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
from collections import Counter
import logging
import math
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

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
   args.input_net = os.path.join (PATH_THIS, 'kivu12.net')
   args.input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_pcb (args)



"""
==============================================================================
Name : generate_pickplace
==============================================================================
"""

def generate_pickplace ():
   args = lambda: None
   args.input_net = os.path.join (PATH_THIS, 'kivu12.net')
   args.input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_pickplace (args)



"""
==============================================================================
Name : generate_assembly_plan
==============================================================================
"""

def generate_assembly_plan ():
   args = lambda: None
   args.input_net = os.path.join (PATH_THIS, 'kivu12.net')
   args.input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_assembly_plan (args)



"""
==============================================================================
Name : generate_bom
==============================================================================
"""

def generate_bom ():
   args = lambda: None
   args.input_net = os.path.join (PATH_THIS, 'kivu12.net')
   args.input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_bom (args)



"""
==============================================================================
Name : generate_bom_digikey
==============================================================================
"""

def generate_bom_digikey ():

   distributor_parts = Counter ()
   components_metadata = {}

   input_net = os.path.join (PATH_THIS, 'kivu12.net')
   input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   design = kcgen.read_design (input_net, input_pcb)

   parts = Counter ()
   for reference in design.components:
      component = design.components [reference]
      if component.distributor.lower () == 'digikey':
         parts [component.distributor_part_number] += 1
         components_metadata [component.distributor_part_number] = component
   distributor_parts += parts

   output_dir = os.path.join (PATH_THIS, 'artifacts')
   with open (os.path.join (output_dir, 'kivu12.bom.digikey.csv'), 'w') as output:
      output.write ('"Diki-Key Part Number","Quantity"\n')
      for part in sorted (distributor_parts):
         device = components_metadata [part].device
         value = components_metadata [part].value
         if components_metadata [part].reference.startswith ('J'):
            value = ''
         description = components_metadata [part].description
         quantity = math.ceil (distributor_parts [part] * 1.1) # 10% more components
         output.write ('"%s","%d"\n' % (part, quantity))



"""
==============================================================================
Name : generate
==============================================================================
"""

def generate ():
   generate_gerber ()
   generate_pickplace ()
   #generate_assembly_plan ()
   generate_bom ()
   generate_bom_digikey ()



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (generate ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
