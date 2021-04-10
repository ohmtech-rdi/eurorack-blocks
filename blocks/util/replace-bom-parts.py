#!/usr/bin/env python3
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
import argparse
import ast
import logging
import os
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))



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

   arg_parser.add_argument (
      'file',
      help = 'Replacement dictionary file to use.'
   )

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

   return arg_parser.parse_args (sys.argv[1:])


"""
==============================================================================
Name : replace_sch_if_in_line
==============================================================================
"""

def replace_sch_if_in_line (line, match, pattern_start, pattern_end, replacement):
   if match in line:
      start_index = line.find (pattern_start) + len (pattern_start)
      start_line = line [0:start_index]
      end_index = line.find (pattern_end, start_index + 1)
      end_line = line [end_index:]
      return '%s%s%s' % (start_line, replacement, end_line)
   else:
      return line



"""
==============================================================================
Name : replace_sch
==============================================================================
"""

def replace_sch (target_path, replacement_dict):

   with open (target_path) as target_file:
      target_content = target_file.readlines ()

   original_part = replacement_dict ['OriginalDistPartNumber']

   for line_nbr, line in enumerate (target_content):
      search_pattern = ' "%s" ' % original_part
      if search_pattern in line and 'CNN "DistPartNumber"' in line:
         logging.info ('Sch: Found match on line %d' % line_nbr)

         fields_start_line_nbr = line_nbr
         while True:
            line_alt = target_content [fields_start_line_nbr]
            if '$Comp' in line_alt:
               #logging.info ('Sch: Found start on line %d' % fields_start_line_nbr)
               break
            else:
               fields_start_line_nbr -= 1

         fields_end_line_nbr = line_nbr
         while True:
            line_alt = target_content [fields_end_line_nbr]
            if '$EndComp' in line_alt:
               #logging.info ('Sch: Found end on line %d' % fields_start_line_nbr)
               break
            else:
               fields_end_line_nbr += 1

         for fields_line_nbr in range (fields_start_line_nbr, fields_end_line_nbr + 1):
            target_content [fields_line_nbr] = replace_sch_if_in_line (
               target_content [fields_line_nbr],
               'CNN "DistPartNumber"', '"', '"',
               '%s' % replacement_dict ['Replacement']['DistPartNumber']
            )
            target_content [fields_line_nbr] = replace_sch_if_in_line (
               target_content [fields_line_nbr],
               'CNN "Description"', '"', '"',
               '%s' % replacement_dict ['Replacement']['Description']
            )
            target_content [fields_line_nbr] = replace_sch_if_in_line (
               target_content [fields_line_nbr],
               'CNN "DistLink"', '"', '"',
               '%s' % replacement_dict ['Replacement']['DistLink']
            )

   with open (target_path, 'w') as target_file:
      for line in target_content:
        target_file.write (line)



"""
==============================================================================
Name : replace_net_if_in_line
==============================================================================
"""

def replace_net_if_in_line (line, pattern_start, pattern_end, replacement):
   if pattern_start in line:
      start_index = line.find (pattern_start) + len (pattern_start)
      start_line = line [0:start_index]
      end_index = line.find (pattern_end, start_index + 1)
      end_line = line [end_index:]
      return '%s%s%s' % (start_line, replacement, end_line)
   else:
      return line



"""
==============================================================================
Name : replace_net
==============================================================================
"""

def replace_net (target_path, replacement_dict):

   with open (target_path) as target_file:
      target_content = target_file.readlines ()

   original_part = replacement_dict ['OriginalDistPartNumber']

   for line_nbr, line in enumerate (target_content):
      search_pattern = '(field (name DistPartNumber) %s)' % original_part
      if search_pattern in line:
         logging.info ('Net: Found match on line %d' % line_nbr)

         fields_start_line_nbr = line_nbr
         while True:
            line_alt = target_content [fields_start_line_nbr]
            if '(fields\n' in line_alt:
               #logging.info ('Net: Found start on line %d' % fields_start_line_nbr)
               break
            else:
               fields_start_line_nbr -= 1

         fields_end_line_nbr = line_nbr
         while True:
            line_alt = target_content [fields_end_line_nbr]
            if '(field' in line_alt and '))\n' in line_alt:
               #logging.info ('Net: Found end on line %d' % fields_start_line_nbr)
               break
            else:
               fields_end_line_nbr += 1

         for fields_line_nbr in range (fields_start_line_nbr, fields_end_line_nbr + 1):
            target_content [fields_line_nbr] = replace_net_if_in_line (
               target_content [fields_line_nbr],
               '(name DistPartNumber) ', ')\n',
               '%s' % replacement_dict ['Replacement']['DistPartNumber']
            )
            target_content [fields_line_nbr] = replace_net_if_in_line (
               target_content [fields_line_nbr],
               '(name Description) ', ')\n',
               '"%s"' % replacement_dict ['Replacement']['Description']
            )
            target_content [fields_line_nbr] = replace_net_if_in_line (
               target_content [fields_line_nbr],
               '(name DistLink) ', ')\n',
               '%s' % replacement_dict ['Replacement']['DistLink']
            )

   with open (target_path, 'w') as target_file:
      for line in target_content:
        target_file.write (line)



"""
==============================================================================
Name : replace_net_sch
==============================================================================
"""

def replace_net_sch (base_path, name, replacement_dict):
   replace_sch (os.path.join (base_path, '%s.sch' % name), replacement_dict)
   replace_net (os.path.join (base_path, '%s.net' % name), replacement_dict)


"""
==============================================================================
Name : replace
==============================================================================
"""

def replace (args):
   with open (args.file, "r") as replacement_file_data:
      replacement_dict = ast.literal_eval (replacement_file_data. read())

   inputs = [
      # (base-path, name)
      ('audio-in-daisy', 'audio-in-daisy'),
      ('audio-out-daisy', 'audio-out-daisy'),
      ('button', 'button'),
      ('cv-in', 'cv-in'),
      ('gate-in', 'gate-in'),
      ('gate-out', 'gate-out'),
      ('led', 'led'),
      ('led-bi', 'led-bi'),
      ('multiplexer', 'multiplexer'),
      ('pot', 'pot'),
      ('power-bus', 'power-bus'),
      ('regulator-daisy', 'regulator-daisy'),
      ('slider', 'slider'),
      ('switch', 'switch'),
      ('trim', 'trim'),
   ]

   for input in inputs:
      replace_net_sch (os.path.join (PATH_ROOT, input [0]), input [1], replacement_dict)



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (replace (parse_args ()))

   except subprocess.CalledProcessError as error:
      print ('Replace command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
