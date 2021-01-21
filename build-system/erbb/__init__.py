##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

import fileinput
import os
import shutil
import subprocess
import sys

sys.path.insert(0, "../submodules/gyp/pylib/")
import gyp



PATH_THIS = os.path.abspath (os.path.dirname (__file__))



"""
==============================================================================
Name: configure
==============================================================================
"""

def configure (name, path):
   configure_xcode (name, path)
   configure_daisy (name, path)



"""
==============================================================================
Name: configure_xcode
==============================================================================
"""

def configure_xcode (name, path):
   path_artifacts = os.path.join (path, 'artifacts')

   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % path_artifacts,
   ]

   gyp.main (gyp_args + ['%s.gyp' % name])

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
      name,
   ]

   subprocess.check_call (cmd)

   print 'OBJCOPY'

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

   print 'Enter the system bootloader by holding the BOOT button down,'
   print 'and then pressing, and releasing the RESET button.'

   raw_input ("Press Enter to continue...")

   print 'Flashing...'

   file_bin = os.path.join (path_artifacts, 'out', 'Release', '%s.bin' % name)

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
