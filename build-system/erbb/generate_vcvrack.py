#!/usr/bin/env python3
#
#     configure.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbui



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      filepath = sys.argv [1]
      output_path = os.path.abspath (os.path.join (os.path.dirname (filepath), 'artifacts'))

      ast = erbui.parse_ui (filepath)
      erbui.generate_vcvrack (output_path, ast)

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
