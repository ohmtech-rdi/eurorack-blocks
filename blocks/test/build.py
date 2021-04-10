#!/usr/bin/env python3
#
#     build.py
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
      targets = [
         'audio-in-daisy',
         'audio-out-daisy',
         'button',
         'cv-in',
         'cv-in2',
         'gate-in',
         'gate-out',
         'led-bi',
         'led',
         'multiplexer',
         'pot',
         'switch',
      ]

      for target in targets:
         erbb.build_target ('test', target, PATH_THIS)
         erbb.objcopy (target, PATH_THIS)

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
