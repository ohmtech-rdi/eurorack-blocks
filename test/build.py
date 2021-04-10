#!/usr/bin/env python3
#
#     build.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import argparse
import os
import platform
import shutil
import subprocess
import sys



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



"""
==============================================================================
Name : parse_args
==============================================================================
"""

def parse_args ():
   arg_parser = argparse.ArgumentParser ()

   arg_parser.add_argument(
      '-c', '--configuration',
      default = 'Release',
      choices = ['Debug', 'Release'],
      help = 'The build configuration to use. Defaults to Release'
   )

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : build
==============================================================================
"""

def build (args):
   cmd = [
      'ninja',
      '-C', os.path.join (PATH_THIS, 'artifacts', 'out', args.configuration)
   ]

   return subprocess.check_call (cmd)



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (build (parse_args ()))

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
