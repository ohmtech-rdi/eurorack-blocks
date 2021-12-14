#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     import_ses.py
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
Name : import_ses
==============================================================================
"""

def import_ses ():
   input_pcb = sys.argv [1]
   input_ses = sys.argv [2]

   board = pcbnew.LoadBoard (input_pcb)
   ok = pcbnew.ImportSpecctraSES (input_ses)
   if not ok:
      print ('SES import failed.')
      sys.exit(1)

   pcbnew.SaveBoard (input_pcb, board)



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (import_ses ())

   except subprocess.CalledProcessError as error:
      print ('Command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
