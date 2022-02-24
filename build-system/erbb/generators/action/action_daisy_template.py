#!/usr/bin/env python3
#
#     action_daisy.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import os
import subprocess
import sys

PATH_ROOT = '%PATH_ROOT%'
PATH_PROJECT = '%PATH_PROJECT%'

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbui



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

def find_erbui ():
   files = os.listdir (PATH_PROJECT)
   for file in files:
      if file.endswith ('.erbui'):
         return os.path.join (PATH_PROJECT, file)

   return None

if __name__ == '__main__':
   try:
      project_path = os.path.abspath (PATH_PROJECT)
      artifacts_path = os.path.join (project_path, 'artifacts')

      ast = erbui.parse (find_erbui ())
      erbui.generate_daisy (artifacts_path, ast)

   except subprocess.CalledProcessError as error:
      print ('Action exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
