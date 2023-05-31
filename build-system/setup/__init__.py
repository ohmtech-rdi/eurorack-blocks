##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import platform
import shutil
import subprocess
import sys
import tarfile
import time
import urllib.request
import zipfile

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')



"""
==============================================================================
Name: check_environment
==============================================================================
"""

def check_environment ():
   if platform.system () == 'Darwin':
      check_environment_macos ()



"""
==============================================================================
Name: check_environment_macos
==============================================================================
"""

def check_environment_macos ():
   macos_version = platform.mac_ver ()[0].split ('.')
   macos_version_major = int (macos_version [0])
   macos_version_minor = int (macos_version [1])

   if macos_version_major >= 11:
      pass # all good
   elif macos_version_major == 10 and macos_version_minor == 15:
      print ('\033[33mWarning: macOS %d.%d has limited support.\033[0m' % (macos_version_major, macos_version_minor))
      print ('\033[90mDebugging with a ST-link v3 might not work properly, for example.')
      print ('Please consider upgrading to macOS Big Sur or later.\033[0m')
   else:
      print ('\033[91mSorry, macOS %d.%d is not supported.\033[0m' % (macos_version_major, macos_version_minor))
      print ('Please consider upgrading to macOS Big Sur or later.')
      sys.exit (1)

   try:
      subprocess.check_call (
         ['/usr/bin/xcodebuild', '-version'],
         stdout=subprocess.DEVNULL,
         stderr=subprocess.DEVNULL
      )
   except:
      print ('\033[91mError: Xcode is not installed.\033[0m')
      print ('\033[90mXcode tools like make or xcodebuild are required.')
      print ('You can find it here:\033[0m')
      print ('\033[94mhttps://developer.apple.com/xcode/\033[0m')
      print ('Please install Xcode.')
      sys.exit (1)



"""
==============================================================================
Name: download
==============================================================================
"""

def download (url, name):
   prev_time = time.time ()
   def show_progress (block_num, block_size, total_size):
      nonlocal prev_time
      cur_time = time.time ()
      if cur_time > prev_time + 1:
         prev_time = cur_time
         current = round (block_num * block_size / total_size * 100, 2)
         print ('Downloading %s... %s%%  ' % (name, current), end='\r')

   urllib.request.urlretrieve (
      url,
      os.path.join (PATH_TOOLCHAIN, name),
      show_progress
   )



"""
==============================================================================
Name: install_kicad_macos
==============================================================================
"""

def install_kicad_macos ():
   name = 'kicad_minimal_macos_6.0.11-0.tar.gz'
   download (
      'https://github.com/ohmtech-rdi/erb-toolchain-macos-kicad-6/releases/download/v0.1/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with tarfile.open (os.path.join (PATH_TOOLCHAIN, name), mode='r:gz') as tf:
      tf.extractall (PATH_TOOLCHAIN)



"""
==============================================================================
Name: install_kicad_windows
==============================================================================
"""

def install_kicad_windows ():
   name = 'kicad_minimal_windows_6.0.11-0.tar.gz'
   download (
      'https://github.com/ohmtech-rdi/erb-toolchain-windows-kicad-6/releases/download/v0.1/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with tarfile.open (os.path.join (PATH_TOOLCHAIN, name), mode='r:gz') as tf:
      tf.extractall (PATH_TOOLCHAIN)



"""
==============================================================================
Name: install_msys2_mingw64
==============================================================================
"""

def install_msys2_mingw64 ():
   name = 'msys2_mingw64.zip'
   download (
      'https://github.com/ohmtech-rdi/erb-toolchain-msys2-mingw64/releases/download/v0.2/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with zipfile.ZipFile (os.path.join (PATH_TOOLCHAIN, name), 'r') as zip_ref:
      zip_ref.extractall (os.path.join (PATH_TOOLCHAIN))



"""
==============================================================================
Name: install_gnu_arm_embedded_macos
==============================================================================
"""

def install_gnu_arm_embedded_macos ():
   name = 'gcc-arm-none-eabi-10.3-2021.10-mac.tar.bz2'
   download (
      'https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with tarfile.open (os.path.join (PATH_TOOLCHAIN, name), mode='r:bz2') as tf:
      tf.extractall (PATH_TOOLCHAIN)



"""
==============================================================================
Name: install_gnu_arm_embedded_windows
==============================================================================
"""

def install_gnu_arm_embedded_windows ():
   name = 'gcc-arm-none-eabi-10.3-2021.10-win32.zip'
   download (
      'https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with zipfile.ZipFile (os.path.join (PATH_TOOLCHAIN, name), 'r') as zip_ref:
      zip_ref.extractall (PATH_TOOLCHAIN)



"""
==============================================================================
Name: install_python_requirements
==============================================================================
"""

def install_python_requirements ():
   os.makedirs (PATH_PY3_PACKAGES)

   print ('Installing python packages...')

   # Start by installing a version of pip after 22.2. This version introduces
   # the 'universal2' that some our dependencies, like freetype-py, depends
   # on, in order to install the wheel we need.

   subprocess.check_call (
      [
         sys.executable,
         '-m', 'pip', 'install',
         '--quiet', '--quiet', '--quiet',
         '--disable-pip-version-check',
         '--log', os.path.join (PATH_TOOLCHAIN, 'pip-install-pip.log.txt'),
         '--target', PATH_PY3_PACKAGES,
         'pip==23.1.2',
      ]
   )

   # pip install --target does not support well shared namespaces. Here with
   # the bin/ folder which is used for `pip` binaries, which we don't use
   # so remove that folder before installing requirements.

   shutil.rmtree (os.path.join (PATH_PY3_PACKAGES, 'bin'))

   subprocess.check_call (
      [
         sys.executable,
         '-m', 'pip', 'install',
         '--quiet', '--quiet', '--quiet',
         '--disable-pip-version-check',
         '--log', os.path.join (PATH_TOOLCHAIN, 'pip-install-reqs.log.txt'),
         '--target', PATH_PY3_PACKAGES,
         '--report', os.path.join (PATH_TOOLCHAIN, 'pip-report.json'),
         '--requirement', os.path.join (PATH_ROOT, 'requirements.txt'),
      ],
      cwd=PATH_PY3_PACKAGES
   )



"""
==============================================================================
Name: check_toolchain
==============================================================================
"""

def check_toolchain ():
   print ('Checking toolchain...')

   if platform.system () == 'Windows':
      bin_dir = os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64', 'bin')
      os.environ ['PATH'] = '%s;%s' % (bin_dir, os.environ ['PATH'])
      if sys.version_info >= (3, 8):
         os.add_dll_directory (bin_dir)

   sys.path.insert (0, PATH_PY3_PACKAGES)
   import cairocffi
   import cairosvg
   import freetype
   import svg2mod
   import soundfile
   import ezdxf

   print ('OK.')
