#!/usr/bin/env python3
#
#     erbuic.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3---------------------------------------------------------------------


from __future__ import print_function

import argparse
import logging
import os
import sys

from erbb.error import Error
from erbb.parser import Parser
from erbb.generators import front_panel
from erbb.generators import vcvrack



#--------------------------------------------------------------------------

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file=sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



#-- parse_args ------------------------------------------------------------
#
#  Description:
#  Parse command line arguments

def parse_args ():
   arg_parser = argparse.ArgumentParser ()

   arg_parser.add_argument (
      '-q', '--quiet',
      dest = 'logging_level', default = logging.INFO,
      action = 'store_const', const = logging.ERROR,
      help = 'Provides less output.'
   )

   arg_parser.add_argument (
      '-v', '--verbose',
      dest = 'logging_level', default = logging.INFO,
      action = 'store_const', const = logging.DEBUG,
      help = 'Provides more output.'
   )

   arg_parser.add_argument (
      '-i', '--input',
      help = 'The input file.'
   )

   arg_parser.add_argument (
      '-g', '--generator',
      default = 'vcvrack',
      choices = ['null', 'front-panel', 'vcvrack'],
      help = 'The generator to use. Defaults to vcvrack.'
   )

   arg_parser.add_argument (
      '-o', '--output-dir',
      default = '.',
      help = 'The output directory. Defaults to current directory.'
   )

   arg_parser.add_argument (
      '--no-diagnostics-color',
      action = 'store_true',
      help = 'Turn off color diagnostics.'
   )

   return arg_parser.parse_args (sys.argv[1:])



#-- read_ast --------------------------------------------------------------
#
#  Description:
#  Read input model file and transform it to an AST

def read_ast (args):
   if args.input is None:
      if args.no_diagnostics_color:
         logging.error ("fatal error: No input file")
      else:
         logging.error ("\033[91mfatal error:\033[0m No input file")
      sys.exit (1)

   try:
      file = open (args.input, 'r', encoding='utf-8')
   except IOError as e:
      if args.no_diagnostics_color:
         logging.error ("fatal error: Unable to open for read '%s' file: %s", args.input, e.strerror)
      else:
         logging.error ("\033[91mfatal error:\033[0m Unable to open for read '%s' file: %s", args.input, e.strerror)
      sys.exit (1)

   with file:
      file_content = file.read ()
      parser = Parser ()
      try:
         ast = parser.parse (file_content, os.path.basename (args.input))
      except Error as error:
         if not args.no_diagnostics_color:
            error.color ()
         logging.error ("%s", str (error))
         sys.exit (1)

   return ast



#-- main ------------------------------------------------------------------

def main (args):
   if not hasattr (args, 'stream'):
      args.stream = sys.stdout
   logging.basicConfig (format = '%(message)s', level = args.logging_level, stream = args.stream)

   ast = read_ast (args)

   if not os.path.exists (args.output_dir):
      os.makedirs (args.output_dir)

   try:
      if args.generator == 'null':
         pass # nothing

      elif args.generator == 'front-panel':
         front_panel.generate (ast, args)

      elif args.generator == 'vcvrack':
         vcvrack.generate (ast, args)

   except Error as error:
      if not args.no_diagnostics_color:
         error.color ()
      logging.error ("%s", str (error))
      sys.exit (1)



#--------------------------------------------------------------------------

if __name__ == '__main__':
   sys.exit (main (parse_args ()))
