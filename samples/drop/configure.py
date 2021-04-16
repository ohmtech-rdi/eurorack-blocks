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
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      ast = erbb.parse_ui ('Drop.erbui', PATH_THIS)

      erbb.configure ('drop', PATH_THIS)
      erbb.generate_vcvrack_panel ('drop', PATH_THIS, ast)
      erbb.generate_vcvrack_manifest ('drop', PATH_THIS, ast)
      erbb.generate_vcvrack_code ('drop', PATH_THIS, ast)
      erbb.generate_vcvrack_deploy ('drop', PATH_THIS, ast)

      erbb.generate_front_panel_milling ('drop', PATH_THIS, ast)
      erbb.generate_front_panel_printing ('drop', PATH_THIS, ast)

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
