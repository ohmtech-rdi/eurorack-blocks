##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

from __future__ import print_function
from builtins import input
import fileinput
import multiprocessing
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
   configure_vscode (name, path)



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

   cwd = os.getcwd ()
   os.chdir (path)
   gyp.main (gyp_args + ['%s.gyp' % name])
   os.chdir (cwd)

   if platform.system () == 'Darwin':
      file = os.path.join (path_artifacts, '%s.xcodeproj' % name, 'project.pbxproj')

      for line in fileinput.input (file, inplace = 1):
         print (line, end = '')

         if 'BuildIndependentTargetsInParallel' in line:
            print ('\t\t\t\tLastUpgradeCheck = 1000;')

   configure_native_vcvrack (path)



"""
==============================================================================
Name: configure_native_vcvrack
==============================================================================
"""

def configure_native_vcvrack (path):
   path_artifacts = os.path.join (path, 'artifacts')
   path_py = os.path.join (path_artifacts, 'generate_vcvrack.py')
   path_template = os.path.join (PATH_THIS, 'generate_vcvrack_template.py')

   with open (path_template, 'r') as file:
      template = file.read ()

   template = template.replace ('%PATH_ROOT%', PATH_ROOT)

   with open (path_py, 'w') as file:
      file.write (template)



"""
==============================================================================
Name: configure_daisy
==============================================================================
"""

def configure_daisy (name, path):
   path_artifacts = os.path.join (path, 'artifacts')

   libdaisy_flash_lds_path = os.path.join (
      PATH_ROOT, 'submodules', 'libDaisy', 'core', 'STM32H750IB_flash.lds'
   )

   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % path_artifacts,
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



"""
==============================================================================
Name: configure_vscode
==============================================================================
"""

def configure_vscode (name, path):
   path_vscode = os.path.join (path, '.vscode')
   if not os.path.exists (path_vscode):
      os.makedirs (path_vscode)

   configure_vscode_launch (name, path)
   configure_vscode_tasks (name, path)



"""
==============================================================================
Name: configure_vscode_launch
==============================================================================
"""

def configure_vscode_launch (name, path):
   path_template = os.path.join (PATH_THIS, 'vscode', 'launch.json')

   path_artifacts = os.path.join (path, 'artifacts')
   file_elf = os.path.abspath (os.path.join (path_artifacts, 'out', 'Debug', '%s-daisy' % name))
   file_svd = os.path.abspath (os.path.join (os.path.dirname (PATH_THIS), 'svd', 'STM32H750x.svd'))
   path_launch = os.path.join (path, '.vscode', 'launch.json')

   with open (path_template, 'r') as file:
      template = file.read ()

   template = template.replace ('%executable%', file_elf)
   template = template.replace ('%svd_file%', file_svd)

   with open (path_launch, 'w') as file:
      file.write (template)



"""
==============================================================================
Name: configure_vscode_tasks
==============================================================================
"""

def configure_vscode_tasks (name, path):
   path_template = os.path.join (PATH_THIS, 'vscode', 'tasks.json')
   path_launch = os.path.join (path, '.vscode', 'tasks.json')

   with open (path_template, 'r') as file:
      template = file.read ()

   with open (path_launch, 'w') as file:
      file.write (template)



"""
==============================================================================
Name : build
==============================================================================
"""

def build (name, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   cmd = [
      'ninja',
      '-C', os.path.join (path_artifacts, 'out', configuration),
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_target
==============================================================================
"""

def build_target (name, target, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   cmd = [
      'ninja',
      '-C', os.path.join (path_artifacts, 'out', configuration),
      target
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_native_target
==============================================================================
"""

def build_native_target (name, target, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   if platform.system () == 'Darwin':
      conf_dir = os.path.join (path_artifacts, 'build', configuration)

      if not os.path.exists (conf_dir):
         os.makedirs (conf_dir)

      xcodebuild_path = '/Applications/Xcode.app/Contents/Developer/usr/bin/xcodebuild'

      if not os.path.exists (xcodebuild_path):
         # fallback to selected Xcode
         developer_path = subprocess.check_output (['xcode-select', '-p']).decode ('utf-8').rstrip ()
         xcodebuild_path = developer_path + '/usr/bin/xcodebuild'

      cmd = [
         xcodebuild_path,
         '-project', os.path.join (path_artifacts, '%s.xcodeproj' % name),
         '-configuration', configuration,
         '-target', target,
         '-parallelizeTargets',
         'SYMROOT=%s' % os.path.join (path_artifacts, 'build')
      ]

      subprocess.check_call (cmd)

   elif platform.system () == 'Linux':
      cmd = [
         'make',
         '-k',
         '-C', path_artifacts,
         '-j', '%d' % multiprocessing.cpu_count (),
         target
      ]

      subprocess.check_call (cmd)



"""
==============================================================================
Name : objcopy
==============================================================================
"""

def objcopy (name, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   print ('OBJCOPY %s' % name)

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

def deploy (name, path, configuration, force_dfu_util=False):
   if shutil.which ('openocd') is not None and not force_dfu_util:
      deploy_openocd (name, path, configuration)
   else:
      deploy_dfu_util (name, path, configuration)



"""
==============================================================================
Name : deploy_dfu_util
==============================================================================
"""

def deploy_dfu_util (name, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')
   file_bin = os.path.join (path_artifacts, 'out', configuration, '%s.bin' % name)

   if not os.path.exists (file_bin):
      sys.exit ('Unknown target %s' % name)

   print ('Enter the system bootloader by holding the BOOT button down,')
   print ('and then pressing, and releasing the RESET button.')

   input ("Press Enter to continue...")

   print ('Flashing...')

   cmd = [
      'dfu-util',
      '-a', '0',
      '-i', '0',
      '-s', '0x08000000:leave',
      '-D', file_bin,
      '-d', '0483:df11',
   ]

   subprocess.check_call (cmd)

   print ('OK.')



"""
==============================================================================
Name : deploy_openocd
==============================================================================
"""

def deploy_openocd (name, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')
   file_elf = os.path.join (path_artifacts, 'out', configuration, '%s' % name)

   if not os.path.exists (file_elf):
      sys.exit ('Unknown target %s' % name)

   cmd = [
      'openocd',
      '--search', '/usr/local/share/openocd/scripts',
      '--file', 'interface/stlink.cfg',
      '--file', 'target/stm32h7x.cfg',
      '--command', 'program %s verify reset exit' % file_elf
   ]

   subprocess.check_call (cmd)

   print ('OK.')
