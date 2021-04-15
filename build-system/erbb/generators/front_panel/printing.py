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

   def generate (self, name, path, root):
      for module in root.modules:
         self.generate_module (name, path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, name, path, module):
      path_artifacts = os.path.join (path, 'artifacts')
      path_pdf = os.path.join (path_artifacts, '%s.pdf' % name)

      surface = cairocffi.PDFSurface (path_pdf, module.width * MM_TO_PT, MODULE_HEIGHT * MM_TO_PT)
      context = cairocffi.Context (surface)

      panel = detailPanel ()
      panel.generate_module (context, module, render_back=False)

      surface.finish ()
