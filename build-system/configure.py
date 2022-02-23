#!/usr/bin/env python3
#
#     configure.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import os
import sys
import subprocess

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (PATH_THIS))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'gyp-next', 'pylib'))
import gyp



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



"""
==============================================================================
Name : configure
==============================================================================
"""

def configure ():
   os.chdir (PATH_THIS)

   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % os.path.join (PATH_THIS, 'artifacts'),
   ]

   gyp.main (gyp_args + ['build-system.gyp'])



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (configure ())

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
