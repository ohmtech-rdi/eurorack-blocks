##############################################################################
#
#     printing.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import cairocffi
import math
import os

from ..detail.panel import Panel as detailPanel



MM_TO_PT = 72.0 / 25.4
MODULE_HEIGHT = 128.5#mm



class Printing:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_pdf = os.path.join (path, '%s.pdf' % module.name)

      surface = cairocffi.PDFSurface (path_pdf, module.width.pt, MODULE_HEIGHT * MM_TO_PT)
      context = cairocffi.Context (surface)

      panel = detailPanel ()
      panel.generate_module (context, module)

      surface.finish ()
