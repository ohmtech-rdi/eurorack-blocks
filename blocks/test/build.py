#!/usr/bin/env python
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

if sys.version_info < (2, 7):
   print ('This script requires python 2.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      erbb.build ('test', PATH_THIS)

      erbb.objcopy ('audio-in-daisy', PATH_THIS)
      erbb.objcopy ('audio-out-daisy', PATH_THIS)
      erbb.objcopy ('button', PATH_THIS)
      erbb.objcopy ('cv-in', PATH_THIS)
      erbb.objcopy ('cv-in2', PATH_THIS)
      erbb.objcopy ('gate-in', PATH_THIS)
      erbb.objcopy ('gate-out', PATH_THIS)
      erbb.objcopy ('led-bi', PATH_THIS)
      erbb.objcopy ('led', PATH_THIS)
      erbb.objcopy ('multiplexer', PATH_THIS)
      erbb.objcopy ('pot', PATH_THIS)
      erbb.objcopy ('switch', PATH_THIS)

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
