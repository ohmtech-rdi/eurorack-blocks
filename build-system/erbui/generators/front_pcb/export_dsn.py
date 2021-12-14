#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     export_dsn.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
import os
import subprocess
import sys

sys.path.insert(0, "/Applications/Kicad/kicad.app/Contents/Frameworks/python/site-packages/")
import pcbnew



##############################################################################

if sys.version_info < (2, 7):
   print ('This script requires python 2.7 or greater.', file = sys.stderr)
   sys.exit (1)




"""
==============================================================================
Name : export_dsn
==============================================================================
"""

def export_dsn ():
   input_pcb = sys.argv [1]
   output_dsn = sys.argv [2]

   board = pcbnew.LoadBoard (input_pcb)
   ok = pcbnew.ExportSpecctraDSN (board, output_dsn)
   if not ok:
      print ('DSN export failed.')
      sys.exit(1)



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (export_dsn ())

   except subprocess.CalledProcessError as error:
      print ('Command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
