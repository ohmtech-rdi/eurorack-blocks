#!/usr/bin/env python3
#
#     action_max.py
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
import erbb
import erbui



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

def find_erbb ():
   files = os.listdir (PATH_PROJECT)
   for file in files:
      if file.endswith ('.erbb'):
         return file

   return None

def find_erbui ():
   files = os.listdir (PATH_PROJECT)
   for file in files:
      if file.endswith ('.erbui'):
         return file

   return None


if __name__ == '__main__':
   try:
      project_path = os.path.abspath (PATH_PROJECT)
      artifacts_path = os.path.join (project_path, 'artifacts')

      ast_erbb = erbb.parse (find_erbb ())
      erbb.generate_max (project_path, ast_erbb)

      ast_erbui = erbui.parse (find_erbui ())
      erbui.generate_max (artifacts_path, ast_erbui)

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
