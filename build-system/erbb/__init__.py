##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

from __future__ import print_function
from builtins import input
import asyncio
import fileinput
import multiprocessing
import os
import platform
import shutil
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')

if platform.system () == 'Windows':
   MAKE_CMD = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin', 'mingw32-make.exe')
   DFU_CMD = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin', 'dfu-util.exe')
   OPENOCD_CMD = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin', 'openocd.exe')
   OPENOCD_SCRIPTS = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'share', 'openocd', 'scripts')
else:
   MAKE_CMD = 'make'
   DFU_CMD = 'dfu-util'
   OPENOCD_CMD = 'openocd'
   OPENOCD_SCRIPTS = '/usr/local/share/openocd/scripts'

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'gyp-next', 'pylib'))
import gyp

from .parser import Parser
from .generators.action.action import Action
from .generators.init.project import Project as initProject
from .generators.simulator.make import Make as simulatorMake
from .generators.daisy.make import Make as daisyMake
from .generators.vcvrack.project import Project as vcvrackProject
from .generators.vscode.c_cpp_properties import CCppProperties as vscodeCCppProperties
from .generators.vscode.workspace import Workspace as vscodeWorkspace
from .generators.vscode.launch import Launch as vscodeLaunch
from .generators.vscode.tasks import Tasks as vscodeTasks
from .generators.data.code import Code as dataCode
from .generators.max.code import Code as maxCode
from .generators.max.project import Project as maxProject
from .generators.faust.code import Code as faustCode
from .generators.faust.project import Project as faustProject



"""
==============================================================================
Name: parse
==============================================================================
"""

def parse (filepath):
   with open (filepath, 'r', encoding='utf-8') as data:
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
Name: faust_init
==============================================================================
"""

def faust_init (path, name):
   generator = faustProject ()
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
Name: generate_faust
==============================================================================
"""

def generate_faust (path, ast):
   path_artifacts = os.path.join (path, 'artifacts')

   if not os.path.exists (path_artifacts):
      os.makedirs (path_artifacts)

   generator = faustCode ()
   generator.generate (path_artifacts, ast)



"""
==============================================================================
Name: configure
==============================================================================
"""

def configure (path, ast):
   configure_simulator_native (path)
   configure_simulator_make (path, ast)
   configure_daisy (path, ast)
   configure_vscode (path, ast)



"""
==============================================================================
Name: configure_simulator_native
==============================================================================
"""

def configure_simulator_native (path):
   path_artifacts = os.path.join (path, 'artifacts')

   if platform.system () == 'Darwin':
      gyp_args = [
         '--depth=.',
         '--generator-output=%s' % path_artifacts,
      ]

      cwd = os.getcwd ()
      os.chdir (path)
      gyp.main (gyp_args + ['project_vcvrack.gyp'])
      os.chdir (cwd)

      project_path = os.path.join (path_artifacts, 'project_vcvrack.xcodeproj')

      file = os.path.join (project_path, 'project.pbxproj')

      for line in fileinput.input (file, inplace = 1):
         print (line, end = '')

         if 'BuildIndependentTargetsInParallel' in line:
            print ('\t\t\t\tLastUpgradeCheck = 2000;')



"""
==============================================================================
Name: configure_simulator_make
==============================================================================
"""

def configure_simulator_make (path, ast):
   generator = simulatorMake ()
   generator.generate (path, ast)



"""
==============================================================================
Name: configure_daisy
==============================================================================
"""

def configure_daisy (path, ast):
   generator = daisyMake ()
   generator.generate (path, ast)



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
   configure_vscode_c_cpp_properties (path, ast)
   configure_vscode_workspace (path, ast)



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
Name: configure_vscode_c_cpp_properties
==============================================================================
"""

def configure_vscode_c_cpp_properties (path, ast):
   generator = vscodeCCppProperties ()
   generator.generate (path, ast)



"""
==============================================================================
Name: configure_vscode_c_cpp_properties
==============================================================================
"""

def configure_vscode_c_cpp_properties (path, ast):
   generator = vscodeCCppProperties ()
   generator.generate (path, ast)



"""
==============================================================================
Name: configure_vscode_workspace
==============================================================================
"""

def configure_vscode_workspace (path, ast):
   generator = vscodeWorkspace ()
   generator.generate (path, ast)



"""
==============================================================================
Name: cleanup
==============================================================================
"""

def cleanup (path):
   project_gyp = os.path.join (path, 'project_vcvrack.gyp')
   if os.path.exists (project_gyp):
      os.remove (project_gyp)



"""
==============================================================================
Name : build_daisy_all
==============================================================================
"""

def build_daisy_all (path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   build_libdaisy ()

   os.environ ['CONFIGURATION'] = configuration

   cmd = [
      MAKE_CMD,
      '--jobs',
      '--directory=%s' % os.path.join (path_artifacts, 'daisy')
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_daisy_target
==============================================================================
"""

def build_daisy_target (target, path, configuration):
   build_daisy_all (path, configuration)



"""
==============================================================================
Name : build_libdaisy
==============================================================================
"""

def build_libdaisy ():

   print ('BUILD libDaisy')

   cmd = [
      MAKE_CMD,
      '--jobs',
      '--silent',
      '--directory=%s' % os.path.join (PATH_ROOT, 'submodules', 'libDaisy'),
   ]

   if platform.system () in ['Darwin', 'Windows']:
      PATH_ARM_BIN = os.path.join (PATH_TOOLCHAIN, 'gcc-arm-none-eabi-10.3-2021.10', 'bin')
      env = dict (
         os.environ,
         **{'GCC_PATH': PATH_ARM_BIN}
      )
      subprocess.check_call (cmd, env=env)
   else:
      subprocess.check_call (cmd)



"""
==============================================================================
Name : build_simulator_xcode_target
==============================================================================
"""

def build_simulator_xcode_target (target, path, configuration):
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
         '-project', os.path.join (path_artifacts, 'project_vcvrack.xcodeproj'),
         '-configuration', configuration,
         '-target', target,
         '-parallelizeTargets',
         '-PBXBuildsContinueAfterErrors=NO',
         'SYMROOT=%s' % os.path.join (path_artifacts, 'build')
      ]

      async def output_filter_err (input_stream, output_stream):
         while not input_stream.at_eof ():
            output = await input_stream.readline ()
            output_utf8 = output.decode ("utf-8")
            if not any (x in output_utf8 for x in ['DVTPlugInManager']):
               output_stream.buffer.write (output)
               output_stream.flush ()

      async def output_filter_out (input_stream, output_stream):
         log_all = False
         while not input_stream.at_eof ():
            output = await input_stream.readline ()
            output_utf8 = output.decode ("utf-8")
            if log_all:
               output_stream.buffer.write (output)
               output_stream.flush ()
            elif any (x in output_utf8 for x in ['PhaseScriptExecution ', 'PBXCp ', 'CompileC ', 'Ld ', '** BUILD SUCCEEDED **', 'warning:']):
               words = output_utf8.split (' ')
               if words [0] == 'PhaseScriptExecution':
                  action_beg = output_utf8.find ('\\"') + 2
                  action_end = output_utf8.find ('\\"', action_beg)
                  action = output_utf8 [action_beg:action_end].replace ('\\', '')
                  output_utf8 = 'ACTION %s\n' % action
               elif words [0] == 'PBXCp':
                  filename = words [1]
                  output_utf8 = 'COPY %s\n' % filename
               elif words [0] == 'CompileC':
                  filename = words [2]
                  output_utf8 = 'CXX %s\n' % filename
               elif words [0] == 'Ld':
                  filename = words [1]
                  output_utf8 = 'LINK %s\n' % filename
               output_stream.buffer.write (str.encode (output_utf8))
               output_stream.flush ()
            elif ': error:' in output_utf8:
               output_stream.buffer.write (output)
               output_stream.flush ()
               log_all = True

      async def run_command (command):
         process = await asyncio.create_subprocess_exec (
            *command, stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE
         )

         await asyncio.gather (
            output_filter_err (process.stderr, sys.stderr),
            output_filter_out (process.stdout, sys.stdout),
         )
         await process.wait ()

         if process.returncode != 0:
            raise subprocess.CalledProcessError (process.returncode, command)

      asyncio.run (run_command (cmd))



"""
==============================================================================
Name : build_simulator_make_target
==============================================================================
"""

def build_simulator_make_target (target, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')

   os.environ ["CONFIGURATION"] = configuration

   cmd = [
      MAKE_CMD,
      '--jobs',
      '--directory=%s' % os.path.join (path_artifacts, 'simulator'),
      'install'
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

      file_elf = os.path.join (path_artifacts, 'daisy', configuration, '%s.elf' % name)
      deploy_openocd (name, file_elf)
   else:
      file_bin = os.path.join (path_artifacts, 'daisy', configuration, '%s.bin' % name)
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
      DFU_CMD,
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
      OPENOCD_CMD,
      '--search', OPENOCD_SCRIPTS,
      '--file', 'interface/stlink.cfg',
      '--file', 'target/stm32h7x.cfg',
      '--command', 'program %s verify reset exit' % file_elf
   ]

   subprocess.check_call (cmd)

   print ('OK.')
