#!/usr/bin/env python3
#
#     erbb
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3---------------------------------------------------------------------


import os
import platform
import subprocess
import sys


#--------------------------------------------------------------------------

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file=sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))


#-- main ---------------------------------------------------------------------

def main ():
   if platform.system () == 'Darwin':
      blender_path = '/Applications/Blender.app/Contents/MacOS/Blender'
   else:
      print ('Platform not supported.')
      sys.exit (1)

   subprocess.check_call (
      [
         blender_path,
         '--background',
         '--python', os.path.join (PATH_THIS, 'soldering-jig.py'),
      ],
      cwd = PATH_THIS
   )


#--------------------------------------------------------------------------

if __name__ == '__main__':
   sys.exit (main ())
