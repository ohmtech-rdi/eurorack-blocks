#!/usr/bin/env python3
#
#     action_data.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import os
import subprocess
import sys

PATH_ROOT = '%PATH_ROOT%'

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

def find_erbb ():
   files = os.listdir (os.getcwd ())
   for file in files:
      if file.endswith ('.erbb'):
         return file

   return None

if __name__ == '__main__':
   try:
      project_path = os.path.abspath (os.getcwd ())

      ast = erbb.parse (find_erbb ())
      erbb.generate_data (project_path, ast)

   except subprocess.CalledProcessError as error:
      print ('Action exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
