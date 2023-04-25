##############################################################################
#
#     panel.py
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



class Panel:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_svg_pp = os.path.join (path, 'panel_vcvrack-preprocess.svg')
      path_svg = os.path.join (path, 'panel_vcvrack.svg')

      surface = cairocffi.SVGSurface (path_svg_pp, module.width.pt, MODULE_HEIGHT * MM_TO_PT)
      surface.set_document_unit (cairocffi.SVG_UNIT_PT)
      context = cairocffi.Context (surface)

      panel = detailPanel ()
      panel.generate_module (context, module, simulated=True)

      surface.finish ()

      self.post_process (path_svg_pp, path_svg)


   #--------------------------------------------------------------------------
   # VCV Rack doesn't interpret properly rgb() color style.
   # Post-process the file to solve that problem.

   def post_process (self, path_svg_pp, path_svg):
      with open (path_svg_pp, 'r', encoding='utf-8') as file_pp:
         with open (path_svg, 'w', encoding='utf-8') as file:
            for line in file_pp:
               line = self.post_process_line (line)
               file.write (line)


   #--------------------------------------------------------------------------
   # Note: fragile parser

   def post_process_line (self, line):
      def percent_to_hex (ps):
         s = ps [:-1]
         f = float (s) * 2.55
         i = int (f)
         return '%0.2x' % i

      while 'rgb(' in line:
         start = line.find ('rgb(')
         end = line.find (')')
         sub = line [start+4:end]
         arr = sub.split (',')
         color_hex = '#' + ''.join (map (lambda s: percent_to_hex (s), arr))
         line = line.replace (line [start:end+1], color_hex)

      return line
