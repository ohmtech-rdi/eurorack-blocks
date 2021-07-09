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
PATH_ARTIFACTS = os.path.join (PATH_THIS, 'artifacts')
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb
import erbui

PROJECT = 'sampler'
CLASS = 'Sampler'



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      ast = erbui.parse (os.path.join (PATH_THIS, '%s.erbui' % CLASS))

      erbb.configure (PROJECT, PATH_THIS)
      erbui.generate_ui (PATH_ARTIFACTS, ast)
      erbui.generate_daisy (PATH_ARTIFACTS, ast)
      erbui.generate_vcvrack (PATH_ARTIFACTS, ast)

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
