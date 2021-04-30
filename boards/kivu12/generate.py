#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
from collections import Counter
import logging
import math
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

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
   args.input_net = os.path.join (PATH_THIS, 'kivu12.net')
   args.input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_pcb (args)
   kcgen.generate_pcb (args)
   kcgen.generate_bom (args)
   kcgen.generate_pickplace (args)
   #kcgen.generate_assembly_plan (args)




##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (generate ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
