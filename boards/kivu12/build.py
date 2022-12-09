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
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))




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

   output_dir = os.path.join (PATH_THIS, 'artifacts')
   zip_path = os.path.join (output_dir, 'kivu12-gerber.zip')
   zip_file = zipfile.ZipFile (zip_path, 'w', zipfile.ZIP_DEFLATED)
   gerber_dir = os.path.join (output_dir, 'gerber')
   zipdir (gerber_dir, zip_file)
   zip_file.close ()
   #shutil.rmtree (gerber_dir)



"""
==============================================================================
Name : build
Description :
   The python executable bundled in Kicad 5.1.9 was not compiled with zlib.
   Therefore we need to separate into two scripts to be able to compress
   the gerber directory.
==============================================================================
"""

def build ():
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



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (build ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
