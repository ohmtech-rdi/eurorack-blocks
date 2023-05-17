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

if platform.system () == 'Windows' and sys.version_info >= (3, 8):
   # Starting from 3.8, Python no longer searches for DLLs in PATH
   os.add_dll_directory (r"C:\msys64\mingw64\bin")
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
