#!/usr/bin/env python
#
#     check.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

import os
import subprocess
import sys



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



"""
==============================================================================
Name: call_script
==============================================================================
"""

def call_script (path, script):
   print '%s/%s' % (path, script)
   subprocess.check_call (
      [os.path.join (path, script)],
      cwd = path
   )



"""
==============================================================================
Name: check_block_pcb
==============================================================================
"""

def check_block_pcb (name):
   call_script (os.path.join (PATH_THIS, name), 'build.py')



"""
==============================================================================
Name: check_kits
==============================================================================
"""

def check_kits ():
   kits_path = os.path.join (PATH_THIS, 'kits')
   call_script (kits_path, 'stats.py')
   call_script (kits_path, 'build.py')



"""
==============================================================================
Name: check_block_test
==============================================================================
"""

def check_block_test (name):
   test_path = os.path.join (PATH_THIS, name, 'test')
   call_script (test_path, 'configure.py')
   call_script (test_path, 'build.py')



"""
==============================================================================
Name: check
==============================================================================
"""

def check ():
   check_block_pcb ('audio-in-daisy')
   check_block_pcb ('audio-out-daisy')
   check_block_pcb ('button')
   check_block_pcb ('cv-in')
   check_block_pcb ('gate-in')
   check_block_pcb ('gate-out')
   check_block_pcb ('led')
   check_block_pcb ('led-bi')
   check_block_pcb ('multiplexer')
   check_block_pcb ('pot')
   check_block_pcb ('power-bus')
   check_block_pcb ('regulator-daisy')
   check_block_pcb ('slider')
   check_block_pcb ('switch')
   check_block_pcb ('trim')

   check_kits ()

   check_block_test ('audio-in-daisy')
   check_block_test ('audio-out-daisy')
   check_block_test ('button')
   check_block_test ('cv-in')
   check_block_test ('gate-in')
   check_block_test ('gate-out')
   check_block_test ('led')
   check_block_test ('led-bi')
   #check_block_test ('multiplexer')
   check_block_test ('pot')
   #check_block_test ('slider')
   check_block_test ('switch')
   #check_block_test ('trim')



##############################################################################

if __name__ == '__main__':
   try:
      check ()

   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Run command exited with %d' % error.returncode
      sys.exit (1)
