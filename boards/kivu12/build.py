#!/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'kcgen'))
import kcgen



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)



"""
==============================================================================
Name : build
==============================================================================
"""

def build ():
   args = lambda: None
   args.input_net = os.path.join (PATH_THIS, 'kivu12.net')
   args.input_pcb = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')
   args.manufacturer = 'pcbpool'
   args.output_dir = os.path.join (PATH_THIS, 'artifacts')

   kcgen.generate_pcb (args)
   kcgen.generate_bom (args)
   kcgen.generate_pickplace (args)
   kcgen.generate_assembly_plan (args)



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (build ())

   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Build command exited with %d' % error.returncode
      sys.exit(1)
