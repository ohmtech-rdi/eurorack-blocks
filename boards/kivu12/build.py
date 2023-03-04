#!/usr/bin/env python3
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
import logging
import os
import platform
import shutil
import subprocess
import sys
import zipfile



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.join (PATH_THIS, 'artifacts')
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
from erbui.generators.front_pcb import bom
from erbui.generators.front_pcb import centroid
from erbui.generators.kicad import pcb
from erbui.generators.kicad import sch



"""
==============================================================================
Name : zipdir
==============================================================================
"""

def zipdir (path, zip_file):
   for root, dirs, files in os.walk (path):
      for file in files:
         zip_file.write (os.path.join (root, file))



"""
==============================================================================
Name : compress_gerber
==============================================================================
"""

def compress_gerber ():
   logging.info ('Compressing PCB gerber files')

   zip_path = os.path.join (PATH_ARTIFACTS, 'kivu12-gerber.zip')
   zip_file = zipfile.ZipFile (zip_path, 'w', zipfile.ZIP_DEFLATED)
   gerber_dir = os.path.join (PATH_ARTIFACTS, 'gerber')
   zipdir (gerber_dir, zip_file)
   zip_file.close ()
   #shutil.rmtree (gerber_dir)



"""
==============================================================================
Name : build_gerber
Description :
   The python executable bundled in Kicad 5.1.9 was not compiled with zlib.
   Therefore we need to separate into two scripts to be able to compress
   the gerber directory.
==============================================================================
"""

def build_gerber ():
   if platform.system () == 'Darwin':
      kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/3.8/bin/python3.8'
      if not os.path.exists (kicad_python_path):
         # pre KiCad 6
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
   elif platform.system () == 'Windows':
      kicad_python_path = 'c:/Program Files/KiCad/6.0/bin/python.exe'
      if not os.path.exists (kicad_python_path):
         # pre KiCad 6
         kicad_python_path = 'c:/Program Files/KiCad/bin/python.exe'
   else:
      kicad_python_path = 'python'

   subprocess.check_call (
      [
         kicad_python_path,
         os.path.join (PATH_THIS, 'generate.py'),
      ],
      cwd = PATH_THIS
   )

   compress_gerber ()



"""
==============================================================================
Name : build_bom
==============================================================================
"""

def build_bom ():
   kivu12_sch = sch.Root.read (os.path.join (PATH_THIS, 'kivu12.kicad_sch'))
   symbols = []
   symbols.extend (kivu12_sch.symbols)
   for sheet in kivu12_sch.sheets:
      sheet_file = sheet.property ('Sheet file')
      sheet_path = os.path.join (PATH_THIS, sheet_file)
      sheet_sch = sch.Root.read (sheet_path)
      symbols.extend (sheet_sch.symbols)

   line_format = '{references};{Description};{Remarks};{quantity};{Dist};{DistPartNumber};{DistLink}\n'
   header_map = {
      'references': 'References',
      'Description': 'Description',
      'Remarks': 'Remarks',
      'Dist': 'Distributor',
      'DistPartNumber': 'Distributor Part Number',
      'DistLink': 'Distributor Part URL',
      'quantity': 'Quantity',
   }
   include_non_empty = '{Dist}'
   projection = '{DistPartNumber};{Description}'

   bom_gen = bom.Bom ()
   kivu12_bom = bom_gen.make_bom (symbols, line_format, header_map, include_non_empty, projection)

   path_bom = os.path.join (PATH_ARTIFACTS, 'kivu12.bom.csv')

   with open (path_bom, 'w', encoding='utf-8') as file:
      file.write (kivu12_bom)



"""
==============================================================================
Name : build_bom_digikey
==============================================================================
"""

def build_bom_digikey ():
   kivu12_sch = sch.Root.read (os.path.join (PATH_THIS, 'kivu12.kicad_sch'))
   symbols = []
   symbols.extend (kivu12_sch.symbols)
   for sheet in kivu12_sch.sheets:
      sheet_file = sheet.property ('Sheet file')
      sheet_path = os.path.join (PATH_THIS, sheet_file)
      sheet_sch = sch.Root.read (sheet_path)
      symbols.extend (sheet_sch.symbols)

   line_format = '{DistPartNumber},{quantity}\n'
   header_map = {
      'DistPartNumber': 'Digi-Key Part Number',
      'quantity': 'Quantity',
   }
   include_non_empty = '{DistPartNumber}'
   projection = '{DistPartNumber}'

   bom_gen = bom.Bom ()
   kivu12_bom = bom_gen.make_bom (symbols, line_format, header_map, include_non_empty, projection)

   path_bom = os.path.join (PATH_ARTIFACTS, 'kivu12.bom.digikey.csv')

   with open (path_bom, 'w', encoding='utf-8') as file:
      file.write (kivu12_bom)



"""
==============================================================================
Name : build_centroid
==============================================================================
"""

def build_centroid ():
   kivu12_pcb = pcb.Root.read (os.path.join (PATH_THIS, 'kivu12.kicad_pcb'))
   kivu12_sch = sch.Root.read (os.path.join (PATH_THIS, 'kivu12.kicad_sch'))

   symbols = []
   symbols.extend (kivu12_sch.symbols)
   for sheet in kivu12_sch.sheets:
      sheet_file = sheet.property ('Sheet file')
      sheet_path = os.path.join (PATH_THIS, sheet_file)
      sheet_sch = sch.Root.read (sheet_path)
      symbols.extend (sheet_sch.symbols)

   line_format = '{Reference},{x},{y},{layer},{rotation}\n'
   header_map = {
      'Reference': 'Reference',
      'x': 'X',
      'y': 'Y',
      'layer': 'Layer',
      'rotation': 'Rotation',
   }
   layer_map = {
      'top': 'Top',
      'bottom': 'Bottom',
   }
   mounting_key = 'Place'
   mounting_value = 'Yes'

   centroid_gen = centroid.Centroid ()
   kivu12_centroid = centroid_gen.make_centroid (kivu12_pcb, symbols, line_format, header_map, layer_map, mounting_key, mounting_value)

   path_centroid = os.path.join (PATH_ARTIFACTS, 'kivu12.centroid.csv')

   with open (path_centroid, 'w', encoding='utf-8') as file:
      file.write (kivu12_centroid)



"""
==============================================================================
Name : build
==============================================================================
"""

def build ():

   if not os.path.exists (PATH_ARTIFACTS):
      os.makedirs (PATH_ARTIFACTS)

   build_gerber ()
   build_bom ()
   build_bom_digikey ()
   build_centroid ()



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (build ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
