##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import io
import os
import platform
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.request
import zipfile

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (PATH_THIS))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')
PATH_FRONT_PCB = os.path.join (PATH_BUILD_SYSTEM, 'erbui', 'generators', 'front_pcb')



"""
==============================================================================
Name: check_environment
==============================================================================
"""

def check_environment ():
   if ' ' in PATH_ROOT:
      # make doesn't support spaces in paths, and libDaisy depends on it
      print ('\033[91mError: The path to eurorack-blocks contains an unsupported space character.\033[0m')
      print ('\033[90mThe "make" program doesn\'t support it, unfortunately.\033[0m')
      print ('Please move the eurorack-blocks folder elsewhere and run this command again.')
      sys.exit (1)

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
   def get_content_with_progress (response):
      length = response.getheader ('content-length')
      block_size = 1000000  # default value
      if length:
         length = int (length)
         block_size = max (4096, length // 20)
         content = io.BytesIO ()
         size = 0
         while True:
            buffer = response.read (block_size)
            if not buffer:
               break
            content.write (buffer)
            size += len (buffer)
            percent = int ((size / length)*100)
            print (f'Downloading {name}... {percent}%%  ', end='\r')
         return content.getvalue ()

   cafile = os.path.join (PATH_TOOLCHAIN, 'certs.pem')
   if not os.path.exists (cafile):
      certificate_url = 'https://mkcert.org/generate/'
      urllib.request.urlretrieve (certificate_url, cafile)

   import ssl
   ssl_context = ssl.create_default_context (cafile=cafile)

   with urllib.request.urlopen (url, context=ssl_context) as response:
      content = get_content_with_progress (response)
      with open (os.path.join (PATH_TOOLCHAIN, name), 'wb') as file:
         file.write (content)



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
Name: install_toolchain_macos
==============================================================================
"""

def install_toolchain_macos ():
   macos_version = platform.mac_ver ()[0].split ('.')
   macos_version_major = int (macos_version [0])
   macos_version_minor = int (macos_version [1])

   if macos_version_major >= 11:
      name = 'toolchain_big_sur.tar.gz'
   elif macos_version_major == 10 and macos_version_minor == 15:
      name = 'toolchain_catalina.tar.gz'
   else:
      assert False

   download (
      'https://github.com/ohmtech-rdi/erb-toolchain-macos/releases/download/v0.2/%s' % name,
      name
   )

   print ('Extracting %s...            ' % name)
   with tarfile.open (os.path.join (PATH_TOOLCHAIN, name), mode='r:gz') as tf:
      tf.extractall (PATH_TOOLCHAIN)

   class LibraryNode:
      def __init__ (self, filepath):
         self.filepath = filepath
         self.children = []
         self.marked = False

   library_nodes = []

   for file in os.listdir (os.fsencode (os.path.join (PATH_TOOLCHAIN, 'bin'))):
      filename = os.fsdecode (file)
      filepath = os.path.join (PATH_TOOLCHAIN, 'bin', filename)
      if os.path.islink (filepath): continue # skip symlinks

      subprocess.check_call (
         ['install_name_tool', '-id', filepath, filepath],
         stderr=subprocess.DEVNULL
      )
      library_node = LibraryNode (filepath)
      output = subprocess.check_output (['otool', '-L', filepath]).decode (sys.stdout.encoding)
      lines = output.split ('\n')
      for line in lines:
         line = line.strip ()
         path = line.split (' ')[0]
         if '@@ERB@@' in path:
            lib = path.split ('/')[-1]
            lib_path = os.path.join (PATH_TOOLCHAIN, 'bin', lib)
            subprocess.check_call (
               ['install_name_tool', '-change', path, lib_path, filepath],
               stderr=subprocess.DEVNULL
            )
            library_node.children.append (lib_path)
      library_nodes.append (library_node)

   # code signing requires children of a dylib to be already signed before
   # signing the parent dylib.
   # Use topological sort to achieve this.

   library_sorted = []

   def visit (node): # assume no cycles
      if node.marked: return
      for child in node.children:
         for library_node in library_nodes:
            if library_node.filepath == child:
               visit (library_node)
      node.marked = True
      library_sorted.insert (0, node)

   for library_node in library_nodes:
      visit (library_node)

   library_sorted.reverse ()

   for lib in library_sorted:
      codesign_adhoc_macos (lib.filepath)



"""
==============================================================================
Name: codesign_adhoc_macos
==============================================================================
"""

def codesign_adhoc_macos (filepath):

   if os.path.islink (filepath):
      return

   ret = subprocess.call (
      [
         'codesign', '--sign', '-',
         '--force',
         filepath
      ],
      stderr=subprocess.DEVNULL,
      stdout=subprocess.DEVNULL
   )
   if ret == 0:
      return # OK

   # (this comment from homebrew signing process)
   # If codesigning fail, it may be a bug in Apple's codesign utility
   # A known workaround is to copy the file to another inode, then move it back
   # erasing the previous file. Then sign again.

   filename = filepath.split ('/')[-1]

   with tempfile.TemporaryDirectory () as dir:
      shutil.copy (filepath, os.path.join (dir, filename))
      shutil.move (os.path.join (dir, filename), filepath)

   subprocess.check_call (
      [
         'codesign', '--sign', '-',
         '--force',
         filepath
      ],
      stderr=subprocess.DEVNULL,
      stdout=subprocess.DEVNULL
   )



"""
==============================================================================
Name: install_msys2_mingw64
==============================================================================
"""

def install_msys2_mingw64 ():
   name = 'msys2_mingw64.zip'
   download (
      'https://github.com/ohmtech-rdi/erb-toolchain-msys2-mingw64/releases/download/v0.3/%s' % name,
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
Name: install_xcode_support
==============================================================================
"""

def install_xcode_support ():
   print ('Adding Xcode support...')

   developer_path = subprocess.check_output (['xcode-select', '-p']).decode ('utf-8').rstrip ()
   contents_path = os.path.abspath (os.path.dirname (developer_path))
   info_path = os.path.join (contents_path, 'Info')

   PATH_XCODE = os.path.join (PATH_THIS, 'xcode')
   PATH_XCODE_PREFS = os.path.join (os.path.expanduser ('~'), 'Library', 'Developer', 'Xcode')
   PATH_XCODE_PLUGINS = os.path.join (PATH_XCODE_PREFS, 'Plug-ins')
   PATH_XCODE_SPECS = os.path.join (PATH_XCODE_PREFS, 'Specifications')

   xcode_uuid = subprocess.check_output (['defaults', 'read', info_path, 'DVTPlugInCompatibilityUUID']).decode ('utf-8').rstrip ()
   xcode_version = int (subprocess.check_output (['defaults', 'read', info_path, 'DTXcode']).decode ('utf-8').rstrip ())

   xcode11 = xcode_version >= 1100 and xcode_version < 1200

   if not os.path.exists (PATH_XCODE_PLUGINS):
      os.makedirs (PATH_XCODE_PLUGINS)

   if not os.path.exists (PATH_XCODE_SPECS):
      os.makedirs (PATH_XCODE_SPECS)

   def install_ideplugin (name):
      shutil.rmtree (os.path.join (PATH_XCODE_PLUGINS, '%s.ideplugin' % name), ignore_errors = True)
      shutil.copytree (
         os.path.join (PATH_XCODE, '%s.ideplugin' % name),
         os.path.join (PATH_XCODE_PLUGINS, '%s.ideplugin' % name)
      )

      path_info_plist = os.path.join (PATH_XCODE_PLUGINS, '%s.ideplugin' % name, 'Contents', 'Info.plist')

      with open (path_info_plist, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%uuid%', xcode_uuid)

      with open (path_info_plist, 'w', encoding='utf-8') as file:
         file.write (template)

   install_ideplugin ('Erbb')
   install_ideplugin ('Erbui')

   if xcode11:
      # Credits for the solution goes to the
      # Xcode GraphQL syntax highlighting project
      # https://github.com/apollographql/xcode-graphql

      source_resources = os.path.join (contents_path, 'SharedFrameworks', 'SourceModel.framework', 'Versions', 'A', 'Resources')
      specs_path = os.path.join (source_resources, 'LanguageSpecifications')

      shutil.copyfile (
         os.path.join (PATH_XCODE, 'Erbb.xclangspec'),
         os.path.join (specs_path, 'Erbb.xclangspec')
      )

      shutil.copyfile (
         os.path.join (PATH_XCODE, 'Erbui.xclangspec'),
         os.path.join (specs_path, 'Erbui.xclangspec')
      )

      metadata_path = os.path.join (source_resources, 'LanguageMetadata')

      shutil.copyfile (
         os.path.join (PATH_XCODE, 'Xcode.SourceCodeLanguage.Erbb.plist'),
         os.path.join (metadata_path, 'Xcode.SourceCodeLanguage.Erbb.plist')
      )

      shutil.copyfile (
         os.path.join (PATH_XCODE, 'Xcode.SourceCodeLanguage.Erbui.plist'),
         os.path.join (metadata_path, 'Xcode.SourceCodeLanguage.Erbui.plist')
      )

   else:
      shutil.copyfile (
         os.path.join (PATH_XCODE, 'Erbb.xclangspec'),
         os.path.join (PATH_XCODE_SPECS, 'Erbb.xclangspec')
      )

      shutil.copyfile (
         os.path.join (PATH_XCODE, 'Erbui.xclangspec'),
         os.path.join (PATH_XCODE_SPECS, 'Erbui.xclangspec')
      )



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
         '--no-user',
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
         '--no-user',
         '--report', os.path.join (PATH_TOOLCHAIN, 'pip-report.json'),
         '--requirement', os.path.join (PATH_ROOT, 'requirements.txt'),
      ],
      cwd=PATH_PY3_PACKAGES
   )



"""
==============================================================================
Name: optimize_kicad_pcb_sch_read
==============================================================================
"""

def optimize_kicad_pcb_sch_read ():
   print ('Optimizing erbb...')

   sys.path.insert (0, PATH_BUILD_SYSTEM)
   from erbui.generators.kicad import pcb, sch

   from erbui.grammar import GRAMMAR_MANUFACTURER_ROOT
   from erbui import parser

   pcb.Root.read (os.path.join (PATH_ROOT, 'boards', 'kivu12', 'hardware', 'kivu12.kicad_pcb'))
   sch.Root.read (os.path.join (PATH_ROOT, 'boards', 'kivu12', 'hardware', 'kivu12.kicad_sch'))

   p = parser.Parser (grammar_root=GRAMMAR_MANUFACTURER_ROOT)

   parts = set ()

   for lib in ['DiyWire.erbui', 'DiyManual.erbui']:
      manufacturer_path = os.path.join (PATH_FRONT_PCB, lib)
      with open (manufacturer_path, 'r', encoding='utf-8') as file:
         file_content = file.read ()
      gn = p.parse_manufacturer (file_content, manufacturer_path)
      manufacturer = gn.manufacturers [0]

      for control in manufacturer.controls:
         for part in control.parts:
            parts.add (part)

   for part in parts:
      pcb.Root.read (os.path.join (PATH_FRONT_PCB, part, '%s.kicad_pcb' % part))
      sch.Root.read (os.path.join (PATH_FRONT_PCB, part, '%s.kicad_sch' % part))



"""
==============================================================================
Name: check_toolchain
==============================================================================
"""

def check_toolchain ():
   print ('Checking toolchain...')

   if platform.system () == 'Darwin':
      os.environ ['DYLD_FALLBACK_LIBRARY_PATH'] = os.path.join (PATH_TOOLCHAIN, 'bin')

   elif platform.system () == 'Windows':
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
