#!/usr/bin/env python3
#
#     deploy.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import argparse
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb

PROJECT = 'sampler'



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



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



##############################################################################

if __name__ == '__main__':
   try:
      args = parse_args ()

      erbb.deploy ('%s-daisy' % PROJECT, PATH_THIS, args.configuration)

   except subprocess.CalledProcessError as error:
      print ('Deploy command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
