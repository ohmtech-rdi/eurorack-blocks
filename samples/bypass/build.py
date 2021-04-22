#!/usr/bin/env python3
#
#     build.py
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
PATH_ARTIFACTS = os.path.join (PATH_THIS, 'artifacts')
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb
import erbui



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
      '--erb-target',
      default = 'daisy',
      choices = ['daisy', 'vcvrack'],
      help = 'The erb target to use. Defaults to daisy'
   )

   return arg_parser.parse_args (sys.argv[1:])



##############################################################################

if __name__ == '__main__':
   try:
      args = parse_args ()

      if args.erb_target == 'daisy':
         ast = erbui.parse_ui (os.path.join (PATH_THIS, 'Bypass.erbui'))
         erbui.generate_front_panel (PATH_ARTIFACTS, ast)

         erbb.build_target ('bypass', 'bypass-daisy', PATH_THIS)
         erbb.objcopy ('bypass-daisy', PATH_THIS)

      elif args.erb_target == 'vcvrack':
         erbb.build_native_target ('bypass', 'bypass-vcvrack', PATH_THIS)

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
