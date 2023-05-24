##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import sys
import tarfile
import time
import urllib.request
import zipfile

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')


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
         print ('Downloading %s... %s%%' % (name, current), end='\r')

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
      'https://github.com/ohmtech-rdi/erb-toolchain-msys2-mingw64/releases/download/v0.1/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with zipfile.ZipFile (os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64.zip'), 'r') as zip_ref:
      zip_ref.extractall (os.path.join (PATH_TOOLCHAIN, 'msys2_mingw64'))
