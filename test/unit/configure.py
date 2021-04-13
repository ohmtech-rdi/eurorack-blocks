#!/usr/bin/env python3
#
#     configure.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import fileinput
import os
import platform
import sys
import subprocess

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'gyp', 'pylib'))
import gyp



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



"""
==============================================================================
Name : configure_native
==============================================================================
"""

def configure_native ():
   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % os.path.join (PATH_THIS, 'artifacts'),
   ]

   gyp.main (gyp_args + ['test.gyp'])

   if platform.system () == 'Darwin':
      post_process_xcode ()



"""
==============================================================================
Name : post_process_xcode
==============================================================================
"""

def post_process_xcode ():
   file = os.path.join (PATH_THIS, 'artifacts', 'test.xcodeproj', 'project.pbxproj')

   for line in fileinput.input (file, inplace = 1):
      print (line, end=' ')

      if 'BuildIndependentTargetsInParallel' in line:
         print ('\t\t\t\tLastUpgradeCheck = 1200;')



"""
==============================================================================
Name : configure_ninja
==============================================================================
"""

def configure_ninja ():
   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % os.path.join (PATH_THIS, 'artifacts'),
   ]

   gyp_args += ['--format', 'ninja']

   gyp.main (gyp_args + ['test.gyp'])



"""
==============================================================================
Name : configure
==============================================================================
"""

def configure ():
   os.chdir (PATH_THIS)
   configure_native ()
   configure_ninja ()



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (configure ())

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
