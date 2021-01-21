#!/usr/bin/env python
#
#     build.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (PATH_THIS))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      erbb.build ('test', PATH_THIS)

      erbb.objcopy ('audio-in-daisy', PATH_THIS)
      erbb.objcopy ('audio-out-daisy', PATH_THIS)
      erbb.objcopy ('button', PATH_THIS)
      erbb.objcopy ('cv-in', PATH_THIS)
      erbb.objcopy ('gate-in', PATH_THIS)
      erbb.objcopy ('gate-out', PATH_THIS)
      erbb.objcopy ('led-bi', PATH_THIS)
      erbb.objcopy ('led', PATH_THIS)
      erbb.objcopy ('pot', PATH_THIS)
      erbb.objcopy ('switch', PATH_THIS)

   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Run command exited with %d' % error.returncode
      sys.exit (1)
