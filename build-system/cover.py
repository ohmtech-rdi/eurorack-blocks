#!/usr/bin/env python3
#
#     cover.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################


from __future__ import print_function

import os
import subprocess
import sys



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file=sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
COVERAGE = 'coverage3'



#-- erase_coverage_data ---------------------------------------------------

def erase_coverage_data ():
   subprocess.check_call (
      [COVERAGE, 'erase']
   )



#-- collect ---------------------------------------------------------------

def collect (module_name):
   subprocess.check_call (
      [COVERAGE, 'run', '-a', '-m', module_name],
      stdout = subprocess.DEVNULL,
      stderr = subprocess.STDOUT
   )



#-- report ----------------------------------------------------------------

def report ():
   EXCLUDED_PATHS = '*/gyp/*,*/arpeggio/*'

   subprocess.check_call (
      [COVERAGE, 'report', '--omit', EXCLUDED_PATHS]
   )

   subprocess.check_call (
      [COVERAGE, 'html', '--omit', EXCLUDED_PATHS]
   )



#-- main ------------------------------------------------------------------

def main ():
   os.chdir (PATH_THIS)

   erase_coverage_data ()

   collect ('erbui.tests.test_parser')

   report ()



##############################################################################

if __name__ == '__main__':
   sys.exit (main ())
