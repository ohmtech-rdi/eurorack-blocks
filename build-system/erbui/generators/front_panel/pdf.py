##############################################################################
#
#     pdf.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
import sys

from ..detail.panel import Panel as detailPanel

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')

if platform.system () == 'Darwin':
   os.environ ['DYLD_FALLBACK_LIBRARY_PATH'] = os.path.join (PATH_TOOLCHAIN, 'bin')
elif platform.system () == 'Windows':
   bin_dir = os.path.join (PATH_BUILD_SYSTEM, 'toolchain', 'msys2_mingw64', 'bin')
   os.environ ['PATH'] = '%s;%s' % (bin_dir, os.environ ['PATH'])
   if sys.version_info >= (3, 8):
      os.add_dll_directory (bin_dir)

sys.path.insert (0, PATH_PY3_PACKAGES)
import cairocffi



MM_TO_PT = 72.0 / 25.4
MODULE_HEIGHT = 128.5#mm



class Pdf:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      if module.material.is_pcb: return # not needed

      path_pdf = os.path.join (path, '%s.pdf' % module.name)

      surface = cairocffi.PDFSurface (path_pdf, module.width.pt, MODULE_HEIGHT * MM_TO_PT)
      context = cairocffi.Context (surface)

      panel = detailPanel ()
      panel.generate_module (context, module)

      surface.finish ()
