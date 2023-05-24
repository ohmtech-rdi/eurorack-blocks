##############################################################################
#
#     fill_zones.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

import os
import platform
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')

if platform.system () == 'Darwin':
   sys.path.insert (0, os.path.join (PATH_TOOLCHAIN, 'KiCad.app', 'Contents', 'Frameworks', 'Python.framework', 'Versions', '3.8', 'lib', 'python3.8', 'site-packages'))
elif platform.system () == 'Windows':
   sys.path.insert(0, "c:/Program Files/KiCad/6.0/bin/Lib/site-packages/")

import pcbnew



##############################################################################

if sys.version_info < (2, 7):
   print ('This script requires python 2.7 or greater.', file = sys.stderr)
   sys.exit (1)




"""
==============================================================================
Name : fill_zones
==============================================================================
"""

def fill_zones ():
   input_pcb = sys.argv [1]

   board = pcbnew.LoadBoard (input_pcb)

   filler = pcbnew.ZONE_FILLER (board)
   zones = board.Zones ()
   filler.Fill (zones)

   pcbnew.SaveBoard (input_pcb, board)




##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (fill_zones ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
