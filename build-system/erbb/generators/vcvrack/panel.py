##############################################################################
#
#     panel.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import cairocffi
import math
import os

from ..detail.panel import Panel as detailPanel



MM_TO_PT = 72.0 / 25.4
MODULE_HEIGHT = 128.5#mm



class Panel:

   #--------------------------------------------------------------------------

   def generate (self, name, path, root):
      for module in root.modules:
         self.generate_module (name, path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, name, path, module):
      path_artifacts = os.path.join (path, 'artifacts')
      path_svg_pp = os.path.join (path_artifacts, '%s-preprocess.svg' % name)
      path_svg = os.path.join (path_artifacts, '%s.svg' % name)

      surface = cairocffi.SVGSurface (path_svg_pp, module.width * MM_TO_PT, MODULE_HEIGHT * MM_TO_PT)
      context = cairocffi.Context (surface)

      panel = detailPanel ()
      panel.generate_module (context, module, render_back=True)

      surface.finish ()

      self.post_process (path_svg_pp, path_svg)


   #--------------------------------------------------------------------------
   # VCV Rack doesn't interpret properly rgb:() color style.
   # Post-process the file to solve that problem.

   def post_process (self, path_svg_pp, path_svg):
      with open (path_svg_pp, 'r') as file_pp:
         with open (path_svg, 'w') as file:
            for line in file_pp:
               # Good enough for now
               line = line.replace ('rgb(100%,100%,100%)', '#ffffff')
               line = line.replace ('rgb(90%,90%,90%)', '#e6e6e6')
               line = line.replace ('rgb(30%,30%,30%)', '#4d4d4d')
               line = line.replace ('rgb(10%,10%,10%)', '#191919')
               line = line.replace ('rgb(10.196078%,10.196078%,10.196078%)', '#191919')
               line = line.replace ('rgb(0%,0%,0%)', '#000000')
               file.write (line)
