#!/usr/bin/env python3
#
#     test.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function

import os
import platform
import subprocess
import sys



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file=sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



##############################################################################

if __name__ == '__main__':
   subprocess.check_call (
      ['python3', '-m', 'unittest', 'discover'],
      cwd = PATH_THIS
   )
