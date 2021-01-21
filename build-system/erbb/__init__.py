##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

import fileinput
import os
import platform
import shutil
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'gyp', 'pylib'))
import gyp



"""
==============================================================================
Name: configure
==============================================================================
"""

def configure (name, path):
   configure_native (name, path)
   configure_daisy (name, path)



"""
==============================================================================
Name: configure_native
==============================================================================
"""

def configure_native (name, path):
   path_artifacts = os.path.join (path, 'artifacts')

   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % path_artifacts,
   ]

   gyp.main (gyp_args + ['%s.gyp' % name])

   if platform.system () == 'Darwin':
      file = os.path.join (path_artifacts, '%s.xcodeproj' % name, 'project.pbxproj')

      for line in fileinput.input (file, inplace = 1):
         print line,

         if 'BuildIndependentTargetsInParallel' in line:
            print '\t\t\t\tLastUpgradeCheck = 1000;'



"""
==============================================================================
Name: configure_daisy
==============================================================================
"""

def configure_daisy (name, path):
   path_artifacts = os.path.join (path, 'artifacts')

   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % path_artifacts,
      '--format', 'ninja-linux',
      '-D', 'OS=daisy',
      '-D', 'GYP_CROSSCOMPILE',
   ]

   os.environ.update ({
      'CC': 'arm-none-eabi-gcc',
      'CXX': 'arm-none-eabi-g++',
      'AR': 'arm-none-eabi-ar',
   })

   gyp.main (gyp_args + ['%s.gyp' % name])



"""
==============================================================================
Name : build
==============================================================================
"""

def build (name, path):
   path_artifacts = os.path.join (path, 'artifacts')
   configuration = 'Release'

   cmd = [
      'ninja',
      '-C', os.path.join (path_artifacts, 'out', configuration),
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : objcopy
==============================================================================
"""

def objcopy (name, path):
   path_artifacts = os.path.join (path, 'artifacts')
   configuration = 'Release'

   print 'OBJCOPY %s' % name

   file_elf = os.path.join (path_artifacts, 'out', configuration, name)
   file_bin = os.path.join (path_artifacts, 'out', configuration, '%s.bin' % name)

   shutil.copyfile (file_elf, file_bin)

   cmd = [
      'arm-none-eabi-objcopy',
      '-O', 'binary',
      '-S', file_bin,
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : deploy
==============================================================================
"""

def deploy (name, path):
   path_artifacts = os.path.join (path, 'artifacts')
   file_bin = os.path.join (path_artifacts, 'out', 'Release', '%s.bin' % name)

   if not os.path.exists (file_bin):
      sys.exit ('Unknown target %s' % name)

   print 'Enter the system bootloader by holding the BOOT button down,'
   print 'and then pressing, and releasing the RESET button.'

   raw_input ("Press Enter to continue...")

   print 'Flashing...'

   cmd = [
      'dfu-util',
      '-a', '0',
      '-i', '0',
      '-s', '0x08000000:leave',
      '-D', file_bin,
      '-d', '0483:df11',
   ]

   subprocess.check_call (cmd)

   print 'OK.'
