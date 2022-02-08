#!/usr/bin/env python3
#
#     configure.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import fileinput
import os
import platform
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import erbb

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'gyp', 'pylib'))
import gyp



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

def configure_vcvrack (name, path):
   path_artifacts = os.path.join (path, 'artifacts')

   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % path_artifacts,
   ]

   cwd = os.getcwd ()
   os.chdir (path)
   gyp.main (gyp_args + ['%s.gyp' % name])
   os.chdir (cwd)

   if platform.system () == 'Darwin':
      project_path = os.path.join (path_artifacts, '%s.xcodeproj' % name)

      file = os.path.join (project_path, 'project.pbxproj')

      for line in fileinput.input (file, inplace = 1):
         print (line, end = '')

         if 'BuildIndependentTargetsInParallel' in line:
            print ('\t\t\t\tLastUpgradeCheck = 2000;')


def configure_daisy (name, path):
   path_artifacts = os.path.join (path, 'artifacts')

   libdaisy_flash_lds_path = os.path.join (
      PATH_ROOT, 'submodules', 'libDaisy', 'core', 'STM32H750IB_flash.lds'
   )

   gyp_args = [
      '--depth=.',
      '--generator-output=%s/daisy' % path_artifacts,
      '--format', 'ninja-linux',
      '-D', 'OS=daisy',
      '-D', 'GYP_CROSSCOMPILE',
      '-D', 'erbb_flash_lds=%s' % libdaisy_flash_lds_path,
   ]

   os.environ.update ({
      'CC': 'arm-none-eabi-gcc',
      'CXX': 'arm-none-eabi-g++',
      'AR': 'arm-none-eabi-ar',
   })

   cwd = os.getcwd ()
   os.chdir (path)
   gyp.main (gyp_args + ['%s.gyp' % name])
   os.chdir (cwd)


def configure (name, path):
   configure_vcvrack (name, path)
   configure_daisy (name, path)


if __name__ == '__main__':
   try:
      configure ('test', PATH_THIS)

      # create dummy file to be compatible with erb-daisy
      with open (os.path.join (PATH_THIS, 'artifacts', 'main_daisy.cpp'), 'wb') as f:
         pass

      # create dummy file to be compatible with erb-daisy and erb-vcvrack
      with open (os.path.join (PATH_THIS, 'artifacts', 'plugin_generated_data.cpp'), 'wb') as f:
         pass

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
