#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from collections import Counter
import logging
import os
import shutil
import subprocess
import sys
import zipfile

sys.path.insert(0, "/Applications/Kicad/kicad.app/Contents/Frameworks/python/site-packages/")
import pcbnew

sys.path.insert(0, "../submodules/kcgen/")
import kcgen



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (PATH_THIS))




"""
==============================================================================
Name : generate_pcb_gerber
==============================================================================
"""

def zipdir (path, zip_file):
   for root, dirs, files in os.walk (path):
      for file in files:
         zip_file.write (os.path.join (root, file))



"""
==============================================================================
Name : build_gerber
==============================================================================
"""

def build_gerber ():
   args = lambda: None
   args.input_pcb = os.path.join (PATH_THIS, 'panel-daisy.kicad_pcb')
   args.input_net = ''
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_pcb (args)

   zip_path = os.path.join (args.output_dir, 'panel-daisy-gerber.zip')
   zip_file = zipfile.ZipFile (zip_path, 'w', zipfile.ZIP_DEFLATED)
   gerber_dir = os.path.join (args.output_dir, 'gerber')
   zipdir (gerber_dir, zip_file)
   zip_file.close ()
   shutil.rmtree (gerber_dir)



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
Name : build_bom_digikey
==============================================================================
"""

def build_bom_digikey ():
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
Name : build_bom_thonk
==============================================================================
"""

def build_bom_thonk ():
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
Name : build
==============================================================================
"""

def build ():
   build_gerber ()
   build_bom_digikey ()
   build_bom_thonk ()



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (build ())

   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Build command exited with %d' % error.returncode
      sys.exit(1)
