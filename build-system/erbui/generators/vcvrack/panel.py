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



class Panel:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_svg_pp = os.path.join (path, 'panel_vcvrack-preprocess.svg')
      path_svg = os.path.join (path, 'panel_vcvrack.svg')

      if module.format.is_3u:
         surface = cairocffi.SVGSurface (path_svg_pp, module.width.pt, MODULE_HEIGHT * MM_TO_PT)
      elif module.format.is_1590bb2_portrait:
         surface = cairocffi.SVGSurface (path_svg_pp, 21 * 5.08 * MM_TO_PT, MODULE_HEIGHT * MM_TO_PT)

      surface.set_document_unit (cairocffi.SVG_UNIT_PT)
      context = cairocffi.Context (surface)

      offset_x = 0
      offset_y = 0

      if module.format.is_1590bb2_portrait:
         offset_x = 6.34 * MM_TO_PT
         offset_y = 9.0 * MM_TO_PT

      with context:
         context.translate (offset_x, offset_y)
         panel = detailPanel ()
         panel.generate_module (context, module, render_mode='simulator')

      if module.format.is_1590bb2_portrait:
         context.rectangle (0, 0, 21 * 5.08 * MM_TO_PT, MODULE_HEIGHT * MM_TO_PT)

         left = 6.34 * MM_TO_PT
         right = (21 * 5.08 - 6.34) * MM_TO_PT
         top = 9.0 * MM_TO_PT
         bottom = 128.5 * MM_TO_PT
         radius = 5.0 * MM_TO_PT
         degrees = math.pi / 180.0

         context.new_sub_path ()
         context.arc (right - radius, top + radius, radius, -90 * degrees, 0 * degrees)
         context.arc (right - radius, bottom - radius, radius, 0 * degrees, 90 * degrees)
         context.arc (left + radius, bottom - radius, radius, 90 * degrees, 180 * degrees)
         context.arc (left + radius, top + radius, radius, 180 * degrees, 270 * degrees)
         context.close_path ()

         gray = 0.25
         context.set_source_rgb (gray, gray, gray)
         context.fill ()

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
