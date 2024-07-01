##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

from __future__ import print_function
from builtins import input
import asyncio
import multiprocessing
import os
import platform
import shutil
import subprocess
import sys
import time

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')

sys.path.insert (0, PATH_PY3_PACKAGES)
import serial
import serial.tools.list_ports

if platform.system () == 'Darwin':
   MAKE_CMD = 'make'
   DFU_CMD = os.path.join (PATH_TOOLCHAIN, 'bin', 'dfu-util')
   OPENOCD_CMD = os.path.join (PATH_TOOLCHAIN, 'bin', 'openocd')
   OPENOCD_SCRIPTS = os.path.join (PATH_TOOLCHAIN, 'share', 'openocd', 'scripts')
   GDB_CMD = os.path.join (PATH_TOOLCHAIN, 'gcc-arm-none-eabi-10.3-2021.10', 'bin', 'arm-none-eabi-gdb')

elif platform.system () == 'Windows':
   MAKE_CMD = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin', 'mingw32-make.exe')
   DFU_CMD = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin', 'dfu-util.exe')
   OPENOCD_CMD = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin', 'openocd.exe')
   OPENOCD_SCRIPTS = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'share', 'openocd', 'scripts')
   GDB_CMD = os.path.join (PATH_TOOLCHAIN, 'gcc-arm-none-eabi-10.3-2021.10', 'bin', 'arm-none-eabi-gdb')

else:
   MAKE_CMD = 'make'
   DFU_CMD = 'dfu-util'
   OPENOCD_CMD = 'openocd'
   OPENOCD_SCRIPTS = '/usr/local/share/openocd/scripts'
   GDB_CMD = 'arm-none-eabi-gdb'


sys.path.insert (0, os.path.join (PATH_ROOT, 'build-system'))
import setup


from .parser import Parser
from .generators.action.action import Action
from .generators.init.project import Project as initProject
from .generators.simulator.xcode import Xcode as simulatorXcode
from .generators.simulator.make import Make as simulatorMake
from .generators.daisy.make import Make as daisyMake
from .generators.perf.make import Make as perfMake
from .generators.fuzz.make import Make as fuzzMake
from .generators.vcvrack.project import Project as vcvrackProject
from .generators.vscode.c_cpp_properties import CCppProperties as vscodeCCppProperties
from .generators.vscode.extensions import Extensions as vscodeExtensions
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
Name: check_environment
==============================================================================
"""

def check_environment (path):
   if ' ' in path:
      # make doesn't support spaces in paths
      print ('\033[91mError: The path to this project contains an unsupported space character.\033[0m')
      print ('\033[90mThe "make" program doesn\'t support it, unfortunately.\033[0m')
      print ('Please move your project folder elsewhere and run this command again.')
      sys.exit (1)



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
   configure_simulator_xcode (path, ast)
   configure_simulator_make (path, ast)
   configure_daisy (path, ast)
   configure_perf (path, ast)
   configure_fuzz (path, ast)
   configure_vscode (path, ast)



"""
==============================================================================
Name: configure_simulator_native
==============================================================================
"""

def configure_simulator_xcode (path, ast):
   if platform.system () == 'Darwin':
      generator = simulatorXcode ()
      generator.generate (path, ast)



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
Name: configure_perf
==============================================================================
"""

def configure_perf (path, ast):
   generator = perfMake ()
   generator.generate (path, ast)



"""
==============================================================================
Name: configure_fuzz
==============================================================================
"""

def configure_fuzz (path, ast):
   generator = fuzzMake ()
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
   configure_vscode_extensions (path, ast)
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
Name: configure_vscode_extensions
==============================================================================
"""

def configure_vscode_extensions (path, ast):
   generator = vscodeExtensions ()
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
Name : build_daisy_target
==============================================================================
"""

def build_daisy_target (target, path, configuration, semihosting):
   path_artifacts = os.path.join (path, 'artifacts')

   build_libdaisy ()

   os.environ ['CONFIGURATION'] = configuration
   if semihosting:
      os.environ ['SEMIHOSTING'] = '1'

   cmd = [
      MAKE_CMD,
      '--jobs',
      '--directory=%s' % os.path.join (path_artifacts, 'daisy')
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_performance_target
==============================================================================
"""

def build_performance_target (target, path, logger):
   path_artifacts = os.path.join (path, 'artifacts')

   build_libdaisy ()

   os.environ ['CONFIGURATION'] = 'Release'

   if logger == 'auto':
      if stlink_plugged ():
         logger = 'semihosting'
      else:
         logger = 'usb'

   if logger == 'semihosting':
      os.environ ['SEMIHOSTING'] = '1'

   cmd = [
      MAKE_CMD,
      '--jobs',
      '--directory=%s' % os.path.join (path_artifacts, 'perf')
   ]

   subprocess.check_call (cmd)



"""
==============================================================================
Name : build_fuzz_target
==============================================================================
"""

def build_fuzz_target (target, path, logger):
   path_artifacts = os.path.join (path, 'artifacts')

   build_libdaisy ()

   os.environ ['CONFIGURATION'] = 'Release'

   if logger == 'auto':
      if stlink_plugged ():
         logger = 'semihosting'
      else:
         logger = 'usb'

   if logger == 'semihosting':
      os.environ ['SEMIHOSTING'] = '1'

   cmd = [
      MAKE_CMD,
      '--jobs',
      '--directory=%s' % os.path.join (path_artifacts, 'fuzz')
   ]

   subprocess.check_call (cmd)



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
Name : stlink_plugged
==============================================================================
"""

def stlink_plugged ():
   # taken front openocd scripts/interface/stlink.cfg
   stlink_vid_pids = [
      (0x0483, 0x3744),
      (0x0483, 0x3748),
      (0x0483, 0x374b),
      (0x0483, 0x374d),
      (0x0483, 0x374e),
      (0x0483, 0x374f),
      (0x0483, 0x3752),
      (0x0483, 0x3753),
      (0x0483, 0x3754),
   ]

   for port in serial.tools.list_ports.comports ():
      if (port.vid, port.pid) in stlink_vid_pids:
         return True

   return False



"""
==============================================================================
Name : daisy_plugged
==============================================================================
"""

def daisy_plugged ():
   vid_pids = [
      (0x0483, 0x5740), # Could clash with st-link
   ]

   for port in serial.tools.list_ports.comports ():
      if (port.vid, port.pid) == (0x0483, 0x5740) and 'Daisy' in port.description:
         return True

   return False



"""
==============================================================================
Name : deploy_daisy
==============================================================================
"""

def deploy_daisy (name, section, path, configuration, programmer):
   path_artifacts = os.path.join (path, 'artifacts')

   if programmer == 'auto':
      if section != 'flash':
         programmer = 'dfu'
      elif stlink_plugged ():
         programmer = 'stlink'
      else:
         programmer = 'dfu'

   if programmer == 'stlink':
      if section != 'flash':
         print ('Install option \'stlink\' doesn\'t support programming to %s.' % section)
         print ('Please use option \'dfu\' instead.')
         sys.exit ()

      file_elf = os.path.join (path_artifacts, 'daisy', configuration, '%s.elf' % name)
      deploy_openocd (name, file_elf)

   elif programmer == 'dfu':
      file_bin = os.path.join (path_artifacts, 'daisy', configuration, '%s.bin' % name)
      deploy_dfu_util (name, section, file_bin)



"""
==============================================================================
Name : deploy_performance
==============================================================================
"""

def deploy_performance (name, section, path, programmer):
   path_artifacts = os.path.join (path, 'artifacts')

   if programmer == 'auto':
      if section != 'flash':
         programmer = 'dfu'
      elif stlink_plugged ():
         programmer = 'stlink'
      else:
         programmer = 'dfu'

   if programmer == 'stlink':
      if section != 'flash':
         print ('Install option \'stlink\' doesn\'t support programming to %s.' % section)
         print ('Please use option \'dfu\' instead.')
         sys.exit ()

      file_elf = os.path.join (path_artifacts, 'perf', 'Release', '%s.elf' % name)
      deploy_openocd (name, file_elf)

   elif programmer == 'dfu':
      file_bin = os.path.join (path_artifacts, 'perf', 'Release', '%s.bin' % name)
      deploy_dfu_util (name, section, file_bin)



"""
==============================================================================
Name : deploy_fuzz
==============================================================================
"""

def deploy_fuzz (name, section, path, programmer):
   path_artifacts = os.path.join (path, 'artifacts')

   if programmer == 'auto':
      if section != 'flash':
         programmer = 'dfu'
      elif stlink_plugged ():
         programmer = 'stlink'
      else:
         programmer = 'dfu'

   if programmer == 'stlink':
      if section != 'flash':
         print ('Install option \'stlink\' doesn\'t support programming to %s.' % section)
         print ('Please use option \'dfu\' instead.')
         sys.exit ()

      file_elf = os.path.join (path_artifacts, 'fuzz', 'Release', '%s.elf' % name)
      deploy_openocd (name, file_elf)

   elif programmer == 'dfu':
      file_bin = os.path.join (path_artifacts, 'fuzz', 'Release', '%s.bin' % name)
      deploy_dfu_util (name, section, file_bin)



"""
==============================================================================
Name : deploy_bootloader
==============================================================================
"""

def deploy_bootloader (variant):
   libdaisy_bootloader_bin = os.path.join (
      PATH_ROOT, 'submodules', 'libDaisy', 'core', 'dsy_bootloader_v6_2-%s.bin' % variant
   )

   deploy_dfu_util ('dsy_bootloader_v6_2-%s' % variant, 'flash', libdaisy_bootloader_bin)



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
   elif section == 'qspi' or section == 'sram':
      print ('Enter the Daisy bootloader by pressing the RESET button.')
   else:
      assert False

   input ("Press Enter to continue...")

   print ('Uploading %s to %s section...' % (name, section))

   if section == 'flash':
      section_address = '0x08000000'
   elif section == 'qspi' or section == 'sram':
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



"""
==============================================================================
Name : deploy_simulator
==============================================================================
"""

def deploy_simulator (name, path, configuration):
   path_artifacts = os.path.join (path, 'artifacts')
   package_path = os.path.join (path_artifacts, 'simulator', configuration, 'package')

   if not os.path.exists (package_path):
      sys.exit ('Unknown target %s' % name)

   if platform.system () == 'Darwin':
      rack2_folder = os.path.abspath (
         os.path.join (os.path.expanduser ("~"), 'Library', 'Application Support', 'Rack2')
      )
      if platform.machine () == 'x86_64':
         vcv_plugins_path = os.path.join (rack2_folder, 'plugins-mac-x64')
      elif platform.machine () == 'arm64':
         vcv_plugins_path = os.path.join (rack2_folder, 'plugins-mac-arm64')
      else:
         sys.exit (1)

   elif platform.system () == 'Windows':
      vcv_plugins_path = os.path.abspath (
         os.path.join (os.environ ['LOCALAPPDATA'], 'Rack2', 'plugins-win-x64')
      )

   elif platform.system () == 'Linux':
      xdg_data_home = os.environ.get('XDG_DATA_HOME', os.path.abspath (os.path.join (os.path.expanduser ("~"), '.local', 'share')))
      vcv_plugins_path = os.path.abspath (
         os.path.join (xdg_data_home, 'Rack2', 'plugins-lin-x64')
      )

   vcv_plugin_path = os.path.join (vcv_plugins_path, name)
   vcv_plugin_res_path = os.path.join (vcv_plugin_path, 'res')

   if not os.path.exists (vcv_plugin_path):
      os.makedirs (vcv_plugin_path)

   shutil.copyfile (
         os.path.join (package_path, 'plugin.json'),
         os.path.join (vcv_plugin_path, 'plugin.json')
      )

   if platform.system () == 'Darwin':
      plugin_path = os.path.join (vcv_plugin_path, 'plugin.dylib')
      shutil.copyfile (
         os.path.join (package_path, 'plugin.dylib'),
         plugin_path
      )

      subprocess.check_call (
         ['install_name_tool', '-id', plugin_path, plugin_path],
         stderr=subprocess.DEVNULL
      )

      setup.codesign_adhoc_macos (plugin_path)

   elif platform.system () == 'Windows':
      shutil.copyfile (
         os.path.join (package_path, 'plugin.dll'),
         os.path.join (vcv_plugin_path, 'plugin.dll')
      )

   elif platform.system () == 'Linux':
      shutil.copyfile (
         os.path.join (package_path, 'plugin.so'),
         os.path.join (vcv_plugin_path, 'plugin.so')
      )


   if os.path.exists (vcv_plugin_res_path):
      shutil.rmtree (vcv_plugin_res_path)

   shutil.copytree (
      os.path.join (package_path, 'res'),
      vcv_plugin_res_path
   )

   print ('OK.')



"""
==============================================================================
Name : run_performance
==============================================================================
"""

def run_performance ():
   if stlink_plugged ():
      run_performance_semihosting ()
   else:
      run_performance_usb ()



"""
==============================================================================
Name : run_performance_semihosting
==============================================================================
"""

def run_performance_semihosting ():
   openocd_cmd = [
      OPENOCD_CMD,
      '--search', OPENOCD_SCRIPTS,
      '--file', 'interface/stlink.cfg',
      '--file', 'target/stm32h7x.cfg',
   ]

   gdb_cmd = [
      GDB_CMD,
      '--ex', 'target extended-remote localhost:3333',   # connect to openocd gdb-server
      '--ex', 'monitor reset halt',                      # restart device and stop execution
      '--ex', 'monitor arm semihosting enable',          # activate semihosting
      '--ex', 'continue',                                # run
   ]

   proc_openocd = subprocess.Popen (openocd_cmd)
   proc_gdb = subprocess.Popen (gdb_cmd)

   try:
      while True:
         pass
   except KeyboardInterrupt:
      proc_gdb.kill ()
      proc_openocd.kill ()



"""
==============================================================================
Name : run_performance_usb
==============================================================================
"""

def run_performance_usb ():
   print ('Waiting for Daisy...')
   print ('(Press the RESET button if it doesn\'t connect)')

   while not daisy_plugged ():
      print ('.', end='', flush=True)
      time.sleep (0.5)

   print ('')

   device = None
   for port in serial.tools.list_ports.comports ():
      if (port.vid, port.pid) == (0x0483, 0x5740): # Daisy Seed Built In
         device = port.device

   assert device
   daisy = serial.Serial (device, 115200, timeout=0)

   while True:
      nbr = daisy.in_waiting
      print (daisy.read (nbr).decode ('utf-8'), end='')



"""
==============================================================================
Name : run_fuzz
==============================================================================
"""

def run_fuzz ():
   if stlink_plugged ():
      run_fuzz_semihosting ()
   else:
      run_fuzz_usb ()



"""
==============================================================================
Name : run_fuzz_semihosting
==============================================================================
"""

def run_fuzz_semihosting ():
   openocd_cmd = [
      OPENOCD_CMD,
      '--search', OPENOCD_SCRIPTS,
      '--file', 'interface/stlink.cfg',
      '--file', 'target/stm32h7x.cfg',
   ]

   gdb_cmd = [
      GDB_CMD,
      '--ex', 'target extended-remote localhost:3333',   # connect to openocd gdb-server
      '--ex', 'monitor reset halt',                      # restart device and stop execution
      '--ex', 'monitor arm semihosting enable',          # activate semihosting
      '--ex', 'continue',                                # run
   ]

   proc_openocd = subprocess.Popen (openocd_cmd)
   proc_gdb = subprocess.Popen (gdb_cmd)

   try:
      while True:
         pass
   except KeyboardInterrupt:
      proc_gdb.kill ()
      proc_openocd.kill ()



"""
==============================================================================
Name : run_fuzz_usb
==============================================================================
"""

def run_fuzz_usb ():
   print ('Waiting for Daisy...')
   print ('(Press the RESET button if it doesn\'t connect)')

   while not daisy_plugged ():
      print ('.', end='', flush=True)
      time.sleep (0.5)

   print ('')

   device = None
   for port in serial.tools.list_ports.comports ():
      if (port.vid, port.pid) == (0x0483, 0x5740): # Daisy Seed Built In
         device = port.device

   assert device
   daisy = serial.Serial (device, 115200, timeout=0)

   while True:
      nbr = daisy.in_waiting
      print (daisy.read (nbr).decode ('utf-8'), end='')
