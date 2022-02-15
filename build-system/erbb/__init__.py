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

from .parser import Parser
from .generators.action.action import Action
from .generators.init.project import Project as initProject
from .generators.vcvrack.project import Project as vcvrackProject
from .generators.daisy.project import Project as daisyProject
from .generators.vscode.launch import Launch as vscodeLaunch
from .generators.vscode.tasks import Tasks as vscodeTasks
from .generators.data.code import Code as dataCode
from .generators.max.code import Code as maxCode
from .generators.max.project import Project as maxProject



"""
==============================================================================
Name: parse
==============================================================================
"""

def parse (filepath):
   with open (filepath, "r") as data:
      input_text = data.read ()

   parser = Parser ()
   return parser.parse (input_text, filepath)



"""
==============================================================================
Name: init
==============================================================================
"""

def init (path, name):
   generator = initProject ()
   generator.generate (path, name)



"""
==============================================================================
Name: max_init
==============================================================================
"""

def max_init (path, name):
   generator = maxProject ()
   generator.generate (path, name)



"""
==============================================================================
Name: generate_gyp
==============================================================================
"""

def generate_gyp (path, ast):
   path_artifacts = os.path.join (path, 'artifacts')

   if not os.path.exists (path_artifacts):
      os.makedirs (path_artifacts)

   generate_gyp_vcvrack (path, ast)
   generate_gyp_daisy (path, ast)

   action = Action ()
   action.generate (path, ast)



"""
==============================================================================
Name: generate_gyp_vcvrack
==============================================================================
"""

def generate_gyp_vcvrack (path, ast):
   path_artifacts = os.path.join (path, 'artifacts')

   generator = vcvrackProject ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_gyp_daisy
==============================================================================
"""

def generate_gyp_daisy (path, ast):
   path_artifacts = os.path.join (path, 'artifacts')

   generator = daisyProject ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_data
==============================================================================
"""

def generate_data (path, ast):
   path_artifacts = os.path.join (path, 'artifacts')

   generator = dataCode ()
   generator.generate (path_artifacts, ast)



"""
==============================================================================
Name: generate_max
==============================================================================
"""

def generate_max (path, ast):
   path_artifacts = os.path.join (path, 'artifacts')

   if not os.path.exists (path_artifacts):
      os.makedirs (path_artifacts)

   generator = maxCode ()
   generator.generate (path_artifacts, ast)



"""
==============================================================================
Name: configure
==============================================================================
"""

def configure (path, ast):
   configure_vcvrack (path)
   configure_daisy (path)
   configure_vscode (path, ast)



"""
==============================================================================
Name: configure_vcvrack
==============================================================================
"""

def configure_vcvrack (path):
   path_artifacts = os.path.join (path, 'artifacts')

   if platform.system () == 'Linux':
      gyp_args = [
         '--depth=.',
         '--generator-output=%s/simulator' % path_artifacts,
         '--format', 'ninja'
      ]
   elif platform.system () == 'Darwin':
      gyp_args = [
         '--depth=.',
         '--generator-output=%s' % path_artifacts,
      ]

   cwd = os.getcwd ()
   os.chdir (path)
   gyp.main (gyp_args + ['project_vcvrack.gyp'])
   os.chdir (cwd)

   if platform.system () == 'Darwin':
      project_path = os.path.join (path_artifacts, 'project_vcvrack.xcodeproj')

      file = os.path.join (project_path, 'project.pbxproj')

      for line in fileinput.input (file, inplace = 1):
         print (line, end = '')

         if 'BuildIndependentTargetsInParallel' in line:
            print ('\t\t\t\tLastUpgradeCheck = 2000;')



"""
==============================================================================
Name: configure_daisy
==============================================================================
"""

def configure_daisy (path):
   path_artifacts = os.path.join (path, 'artifacts')

   gyp_args = [
      '--depth=.',
      '--generator-output=%s/daisy' % path_artifacts,
      '--format', 'ninja-linux',
      '-D', 'OS=daisy',
      '-D', 'GYP_CROSSCOMPILE',
   ]

   os.environ.update ({
      'CC': 'arm-none-eabi-gcc',
      'CXX': 'arm-none-eabi-g++',
      'AR': 'arm-none-eabi-ar',
   })

   cwd = os.getcwd ()
   os.chdir (path)
   gyp.main (gyp_args + ['project_daisy.gyp'])
   os.chdir (cwd)



"""
==============================================================================
Name: configure_vscode
==============================================================================
"""

def configure_vscode (path, ast):
   path_vscode = os.path.join (path, '.vscode')

   if not os.path.exists (path_vscode):
      os.makedirs (path_vscode)

   configure_vscode_launch (path, ast)
   configure_vscode_tasks (path, ast)



"""
==============================================================================
Name: configure_vscode_launch
==============================================================================
"""

def configure_vscode_launch (path, ast):
   generator = vscodeLaunch ()
   generator.generate (path, ast)



"""
==============================================================================
Name: configure_vscode_tasks
==============================================================================
"""

def configure_vscode_tasks (path, ast):
   generator = vscodeTasks ()
   generator.generate (path, ast)



"""
==============================================================================
Name: cleanup
==============================================================================
"""

def cleanup (path):
   if platform.system () == 'Darwin':
      os.remove (os.path.join (path, 'project_vcvrack.gyp'))
      os.remove (os.path.join (path, 'project_daisy.gyp'))



"""
==============================================================================
Name : build_daisy_all
==============================================================================
"""

def build_daisy_all (path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   cmd = [
      'ninja',
      '-C', os.path.join (path_artifacts, 'daisy', 'out', configuration),
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_daisy_target
==============================================================================
"""

def build_daisy_target (target, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   cmd = [
      'ninja',
      '-C', os.path.join (path_artifacts, 'daisy', 'out', configuration),
      target
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_simulator_target
==============================================================================
"""

def build_simulator_target (target, path, configuration):
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
         '-quiet',
         '-project', os.path.join (path_artifacts, 'project_vcvrack.xcodeproj'),
         '-configuration', configuration,
         '-target', target,
         '-parallelizeTargets',
         '-PBXBuildsContinueAfterErrors=NO',
         'SYMROOT=%s' % os.path.join (path_artifacts, 'build')
      ]

      subprocess.check_call (cmd)

   elif platform.system () == 'Linux':
      cmd = [
         'ninja',
         '-C', os.path.join (path_artifacts, 'simulator', 'out', configuration),
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

   file_elf = os.path.join (path_artifacts, 'daisy', 'out', configuration, name)
   file_bin = os.path.join (path_artifacts, 'daisy', 'out', configuration, '%s.bin' % name)

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

def deploy (name, section, path, configuration, force_dfu_util=False):
   path_artifacts = os.path.join (path, 'artifacts')

   if shutil.which ('openocd') is not None and not force_dfu_util:
      if section != 'flash':
         print ('Install option \'openocd\' doesn\'t support programming to %s.' % section)
         print ('Please use option \'dfu\' instead.')
         sys.exit ()

      file_elf = os.path.join (path_artifacts, 'daisy', 'out', configuration, '%s' % name)
      deploy_openocd (name, file_elf)
   else:
      file_bin = os.path.join (path_artifacts, 'daisy', 'out', configuration, '%s.bin' % name)
      deploy_dfu_util (name, section, file_bin)



"""
==============================================================================
Name : deploy_bootloader
==============================================================================
"""

def deploy_bootloader ():
   libdaisy_bootloader_bin = os.path.join (
      PATH_ROOT, 'submodules', 'libDaisy', 'core', 'dsy_bootloader_v4.bin'
   )

   deploy_dfu_util ('dsy_bootloader_v4', 'flash', libdaisy_bootloader_bin)



"""
==============================================================================
Name : deploy_dfu_util
==============================================================================
"""

def deploy_dfu_util (name, section, file_bin):
   if not os.path.exists (file_bin):
      sys.exit ('Unknown target %s' % name)

   if section == 'flash':
      print ('Enter the system bootloader by holding the BOOT button down,')
      print ('and then pressing, and releasing the RESET button.')
   elif section == 'qspi':
      print ('Enter the Daisy bootloader by pressing the RESET button.')
   else:
      assert False

   input ("Press Enter to continue...")

   print ('Uploading %s to %s section...' % (name, section))

   if section == 'flash':
      section_address = '0x08000000'
   elif section == 'qspi':
      section_address = '0x90040000'
   else:
      assert False

   cmd = [
      'dfu-util',
      '-a', '0',
      '-i', '0',
      '-s', '%s:leave' % section_address,
      '-D', file_bin,
      '-d', '0483:df11',
   ]

   subprocess.call (cmd)

   print ('OK.')



"""
==============================================================================
Name : deploy_openocd
==============================================================================
"""

def deploy_openocd (name, file_elf):
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
