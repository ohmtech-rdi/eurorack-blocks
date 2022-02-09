#!/usr/bin/env python3
#
#     postbuild_objcopy.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import os
import shutil
import subprocess
import sys

PATH_ROOT = '%PATH_ROOT%'

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

def find_erbb ():
   files = os.listdir (os.getcwd ())
   for file in files:
      if file.endswith ('.erbb'):
         return file

   return None

if __name__ == '__main__':
   try:
      project_path = os.path.abspath (os.getcwd ())
      product_dir = sys.argv [1]
      module_name = sys.argv [2]

      file_elf = os.path.join (project_path, product_dir, module_name)
      file_bin = os.path.join (project_path, product_dir, '%s.bin' % module_name)

      if os.stat (file_elf).st_size == 0:
         sys.exit (0)

      shutil.copyfile (file_elf, file_bin)
      cmd = [
         'arm-none-eabi-objcopy',
         '-O', 'binary',
         '-S', file_bin,
      ]

      subprocess.check_call (cmd)

   except subprocess.CalledProcessError as error:
      print ('Action exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
