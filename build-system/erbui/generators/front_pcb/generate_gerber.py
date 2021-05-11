#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     generate_gerber.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'kcgen'))
import kcgen



##############################################################################

if sys.version_info < (2, 7):
   print ('This script requires python 2.7 or greater.', file = sys.stderr)
   sys.exit (1)




"""
==============================================================================
Name : generate
==============================================================================
"""

def generate ():
   args = lambda: None
   args.input_net = sys.argv [2] # dummy
   args.input_pcb = sys.argv [2]
   args.manufacturer = 'pcbpool'
   args.output_dir = sys.argv [1]

   kcgen.generate_pcb (args)




##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (generate ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
