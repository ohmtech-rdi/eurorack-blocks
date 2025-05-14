##############################################################################
#
#     panel.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################




import math
import os
import platform
import random
import sys

from ... import ast
from ... import adapter
from ..kicad import pcb

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))
PATH_ROOT = os.path.abspath (os.path.dirname (PATH_BUILD_SYSTEM))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')

if platform.system () == 'Darwin':
   os.environ ['DYLD_FALLBACK_LIBRARY_PATH'] = os.path.join (PATH_TOOLCHAIN, 'bin')
elif platform.system () == 'Windows':
   bin_dir = os.path.join (PATH_BUILD_SYSTEM, 'toolchain', 'msys2_mingw64', 'bin')
   os.environ ['PATH'] = '%s;%s' % (bin_dir, os.environ ['PATH'])
   if sys.version_info >= (3, 8):
      os.add_dll_directory (bin_dir)

PATH_FONT_DDIN_BOLD = os.path.join (PATH_ROOT, 'include', 'erb', 'vcvrack', 'design', 'd-din', 'D-DIN-Bold.otf')
PATH_FONT_SCRIPT = os.path.join (PATH_ROOT, 'include', 'erb', 'vcvrack', 'design', 'indie-flower', 'IndieFlower-Regular.ttf')

sys.path.insert (0, PATH_PY3_PACKAGES)
import cairocffi
import cairosvg
import freetype



MM_TO_PT = 72.0 / 25.4
PT_TO_MM = 1.0 / MM_TO_PT



class Panel:
   def __init__ (self):
      self.width = None
      self.height = None

      self.header_center_y = 5.0#mm
      self.footer_center_y = -5.0#mm

      self.positioning_margin = 0.75#mm

      self.current_box = None
      self.current_font_height = None
      self.current_position_x = None
      self.current_position_y = None


   #--------------------------------------------------------------------------

   def generate_module (self, context, module, render_mode=None):

      context.set_fill_rule (cairocffi.FILL_RULE_EVEN_ODD)

      self.width = module.width.mm
      self.height = module.height.mm
      self.footer_center_y += self.height

      self.current_font_height = 14.0#pt
      self.current_position_x = self.width * 0.5
      self.current_position_y = self.height * 0.5

      if render_mode == 'simulator':
         self.generate_back (context, module, render_mode)

      self.generate_header (context, module, render_mode, module.header)
      self.generate_footer (context, module, render_mode, module.footer)

      for label in module.labels:
         self.generate_label (context, module, render_mode, label)

      for image in module.images:
         self.generate_image (context, module, render_mode, image)

      for line in module.lines:
         self.generate_line (context, module, render_mode, line)

      for control in module.controls:
         self.generate_control (context, module, render_mode, control)

      if render_mode == 'simulator':
         for sticker in module.stickers:
            self.generate_sticker (context, module, sticker)


   #--------------------------------------------------------------------------

   def generate_back (self, context, module, render_mode):
      context.rectangle (0, 0, self.width * MM_TO_PT, self.height * MM_TO_PT)

      material = module.material

      if material.is_aluminum_natural or material.is_brushed_aluminum_natural:
         panel_gray = 0.9

      elif material.is_aluminum_black or material.is_brushed_aluminum_black or material.is_aluminum_coated_black or material.is_pcb:
         panel_gray = 0.1

      elif material.is_aluminum_coated_white:
         panel_gray = 1.0

      alt_render_mode = 'translucence_no_fill'

      self.generate_header (context, module, alt_render_mode, module.header)
      self.generate_footer (context, module, alt_render_mode, module.footer)

      for label in module.labels:
         self.generate_label (context, module, alt_render_mode, label)

      for image in module.images:
         self.generate_image (context, module, alt_render_mode, image)

      for line in module.lines:
         self.generate_line (context, module, alt_render_mode, line)

      for control in module.controls:
         self.generate_control (context, module, alt_render_mode, control)

      context.set_source_rgb (panel_gray, panel_gray, panel_gray)
      context.fill ()



   #--------------------------------------------------------------------------

   def generate_header (self, context, module, render_mode, header):
      old_current_position_y = self.current_position_y
      self.current_position_y = self.header_center_y

      for label in header.labels:
         self.generate_label (context, module, render_mode, label)

      for image in header.images:
         self.generate_image (context, module, render_mode, image)

      self.current_position_y = old_current_position_y


   #--------------------------------------------------------------------------

   def generate_footer (self, context, module, render_mode, footer):
      old_current_position_y = self.current_position_y
      self.current_position_y = self.footer_center_y

      if footer:
         for label in footer.labels:
            self.generate_label (context, module, render_mode, label)

         for image in footer.images:
            self.generate_image (context, module, render_mode, image)

      else:
         if module.material.is_light:
            filepath = os.path.join (PATH_THIS, 'erb.footer.black.svg')
         elif module.material.is_dark:
            filepath = os.path.join (PATH_THIS, 'erb.footer.white.svg')

         image = ast.Image (filepath)

         self.generate_image (context, module, render_mode, image)

      self.current_position_y = old_current_position_y


   #--------------------------------------------------------------------------

   def generate_control (self, context, module, render_mode, control):
      if len (control.labels) == 0: return

      old_current_position_x = self.current_position_x
      self.current_position_x = control.position.x.mm

      old_current_position_y = self.current_position_y
      self.current_position_y = control.position.y.mm

      old_current_font_height = self.current_font_height
      self.current_font_height = 8.5#pt

      box = self.get_control_bounds (control)
      box.left -= control.position.x.mm
      box.top -= control.position.y.mm
      box.right -= control.position.x.mm
      box.bottom -= control.position.y.mm
      self.current_box = box

      for label in control.labels:
         self.generate_label (context, module, render_mode, label, control)

      self.current_box = None
      self.current_font_height = old_current_font_height
      self.current_position_x = old_current_position_x
      self.current_position_y = old_current_position_y


   #--------------------------------------------------------------------------

   def get_control_bounds (self, control):

      bounds = pcb.Bounds (None, None, None, None)

      for part in control.parts:
         bounds.union (part.pcb.get_bounds ('Dwgs.User'))

      return bounds


   #--------------------------------------------------------------------------

   def generate_label (self, context, module, render_mode, label, control=None):

      if render_mode == 'simulator' and not label.is_layer_silkscreen: return
      if render_mode == 'silkscreen' and not label.is_layer_silkscreen: return
      if render_mode == 'translucence' and not label.is_layer_translucence: return
      if render_mode == 'translucence_no_fill' and not label.is_layer_translucence: return

      position_x, position_y, align_x, align_y = self.process_label_position (label, control)

      if module.material.is_light:
         if control is not None and control.is_kind_out:
            fill_gray = 0.3
         else:
            fill_gray = 0.0
      elif module.material.is_dark:
         fill_gray = 1.0

      width_pt, _, _, _ = self.measure_text (
         context, PATH_FONT_DDIN_BOLD, self.current_font_height, label.text
      )

      # Base ascent and descent on characters that are going to be used
      # Freetype ascender/descender is hinted and far from Quartz values
      _, _, ascent, descent = self.measure_text (
         context, PATH_FONT_DDIN_BOLD, self.current_font_height,
         'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890'
      )

      if control is not None and control.is_kind_out and not module.material.is_dark:
         self.generate_back_out_path (context, module, control)

      position_x_pt = position_x * MM_TO_PT - width_pt * align_x
      position_y_pt = position_y * MM_TO_PT + ascent * align_y

      with context:
         context.translate (position_x_pt, position_y_pt)
         if render_mode != 'translucence_no_fill':
            context.set_source_rgb (fill_gray, fill_gray, fill_gray)
         self.draw_text (context, PATH_FONT_DDIN_BOLD, self.current_font_height, label.text, render_mode)


   #--------------------------------------------------------------------------

   def generate_sticker (self, context, module, sticker):
      position_x = sticker.position.x.mm
      position_y = sticker.position.y.mm
      align_x = 0.5
      align_y = 0.5

      width_pt, height_pt, _, _ = self.measure_text (
         context, PATH_FONT_SCRIPT, 10, sticker.text
      )

      position_x_cpt = position_x * MM_TO_PT
      position_y_cpt = position_y * MM_TO_PT
      position_x_pt = position_x_cpt - width_pt * align_x
      position_y_pt = position_y_cpt + height_pt * align_y

      angle = random.uniform (-0.05, 0.05)

      with context:
         context.translate (position_x_cpt, position_y_cpt + 0.25)
         context.rotate (angle)
         context.translate (-position_x_cpt, -position_y_cpt - 0.25)

         context.rectangle (position_x_pt - 3, position_y_pt + 0.25 - height_pt - 3, width_pt + 6, height_pt + 6)
         context.set_source_rgb (0.3, 0.3, 0.3)
         context.fill ()

      with context:
         context.translate (position_x_cpt, position_y_cpt)
         context.rotate (angle)
         context.translate (-position_x_cpt, -position_y_cpt)

         context.rectangle (position_x_pt - 3, position_y_pt - height_pt - 3, width_pt + 6, height_pt + 6)
         context.set_source_rgb (1.0, 1.0, 1.0)
         context.fill ()

         context.move_to (position_x_pt, position_y_pt)
         context.set_source_rgb (0.1, 0.1, 0.1)
         self.draw_text (context, PATH_FONT_SCRIPT, 10, sticker.text, 'simulator')


   #--------------------------------------------------------------------------

   def process_label_position (self, label, control):
      position_x = self.current_position_x
      position_y = self.current_position_y

      if label.position: # override
         position_x = label.position.x.mm
         position_y = label.position.y.mm
         align_x = 0.5
         align_y = 0.5

      elif control is None: # center
         align_x = 0.5
         align_y = 0.5

      elif label.positioning is None:
         if control.kind in ['AudioIn', 'AudioOut', 'CvIn', 'CvOut', 'GateIn', 'GateOut']: # top
            position_y += self.current_box.top - self.positioning_margin
            align_x = 0.5
            align_y = 0
         else: # bottom
            position_y += self.current_box.bottom + self.positioning_margin
            align_x = 0.5
            align_y = 1

      elif label.positioning.is_center:
         align_x = 0.5
         align_y = 0.5

      elif label.positioning.is_left:
         position_x += self.current_box.left - self.positioning_margin
         align_x = 1
         align_y = 0.5

      elif label.positioning.is_top:
         position_y += self.current_box.top - self.positioning_margin
         align_x = 0.5
         align_y = 0

      elif label.positioning.is_right:
         position_x += self.current_box.right + self.positioning_margin
         align_x = 0
         align_y = 0.5

      elif label.positioning.is_bottom:
         position_y += self.current_box.bottom + self.positioning_margin
         align_x = 0.5
         align_y = 1

      else:
         raise Exception ('unsupported positioning %s' % label.positioning.value)

      if label.offset:
         position_x += label.offset.x.mm
         position_y += label.offset.y.mm

      return position_x, position_y, align_x, align_y


   #--------------------------------------------------------------------------

   def generate_back_out_path (self, context, module, control):

      left = (control.position.x.mm - 5.4) * MM_TO_PT
      right = (control.position.x.mm + 5.4) * MM_TO_PT
      top = (control.position.y.mm - 8.4) * MM_TO_PT
      bottom = (control.position.y.mm + 5.4) * MM_TO_PT
      radius = 2.0 * MM_TO_PT
      degrees = math.pi / 180.0

      context.new_sub_path ()
      context.arc (right - radius, top + radius, radius, -90 * degrees, 0 * degrees)
      context.arc (right - radius, bottom - radius, radius, 0 * degrees, 90 * degrees)
      context.arc (left + radius, bottom - radius, radius, 90 * degrees, 180 * degrees)
      context.arc (left + radius, top + radius, radius, 180 * degrees, 270 * degrees)
      context.close_path ()


   #--------------------------------------------------------------------------

   def generate_line (self, context, module, render_mode, line):

      if render_mode == 'simulator' and not line.is_layer_silkscreen: return
      if render_mode == 'silkscreen' and not line.is_layer_silkscreen: return
      if render_mode == 'translucence' and not line.is_layer_translucence: return
      if render_mode == 'translucence_no_fill' and not line.is_layer_translucence: return

      line_width = 0.7

      material = module.material

      if material.is_aluminum_natural or material.is_brushed_aluminum_natural or material.is_aluminum_coated_white:
         line_gray = 0.0

      elif material.is_aluminum_black or material.is_brushed_aluminum_black or material.is_aluminum_coated_black or material.is_pcb:
         line_gray = 1.0

      for i in range (len (line.points) - 1):
         x1 = line.points [i].x.pt
         y1 = line.points [i].y.pt
         x2 = line.points [i+1].x.pt
         y2 = line.points [i+1].y.pt
         self.generate_line_segment (context, line_gray, x1, y1, x2, y2, line_width, render_mode)


   #--------------------------------------------------------------------------

   def generate_line_segment (self, context, gray, x1, y1, x2, y2, width, render_mode):

      vx = y2 - y1
      vy = - (x2 - x1)
      norm = math.sqrt (vx * vx + vy * vy)
      if norm < 0.0001: return

      scale = (width / 2) / norm
      vx *= scale
      vy *= scale

      context.new_sub_path ()
      context.move_to (x1 + vx, y1 + vy)
      context.line_to (x2 + vx, y2 + vy)
      context.line_to (x2 - vx, y2 - vy)
      context.line_to (x1 - vx, y1 - vy)
      context.close_path ()

      if render_mode != 'translucence_no_fill':
         context.set_source_rgb (gray, gray, gray)
         context.fill ()


   #--------------------------------------------------------------------------

   def generate_image (self, context, module, render_mode, image):

      if render_mode == 'simulator' and not image.is_layer_silkscreen: return
      if render_mode == 'silkscreen' and not image.is_layer_silkscreen: return
      if render_mode == 'translucence' and not image.is_layer_translucence: return
      if render_mode == 'translucence_no_fill' and not image.is_layer_translucence: return

      with open (image.file, 'rb') as file:
         tree = cairosvg.parser.Tree (file_obj=file)
         surface = ContextOnlySurface (tree, context)

         if render_mode == 'translucence_no_fill':
            surface.stroke_and_fill = False

         width_pt = surface.context_width
         height_pt = surface.context_height

         position_x_pt = self.current_position_x * MM_TO_PT - width_pt * 0.5
         position_y_pt = self.current_position_y * MM_TO_PT - height_pt * 0.5

         with context:
            context.translate (position_x_pt, position_y_pt)
            context.scale (surface.context_scale)

            surface.draw (tree)


   #-- curve_quadratic_to -------------------------------------------------------

   def curve_quadratic_to (self, context, x1, y1, x2, y2):
      x0, y0 = context.get_current_point ()
      context.curve_to (
         x1 * 2.0 / 3.0 + x0 * 1.0 / 3.0, y1 * 2.0 / 3.0 + y0 * 1.0 / 3.0,
         x1 * 2.0 / 3.0 + x2 * 1.0 / 3.0, y1 * 2.0 / 3.0 + y2 * 1.0 / 3.0,
         x2, y2
      )


   #--------------------------------------------------------------------------

   def draw_glyph (self, context, glyph, x, y, render_mode):
      outline = glyph.outline
      outline_data = list (zip (outline.points, outline.tags))

      def tag_on (pts, index):
         return freetype.FT_Curve_Tag (pts [index][1]) == freetype.FT_Curve_Tag_On

      def tag_cubic (pts, index):
         return freetype.FT_Curve_Tag (pts [index][1]) == freetype.FT_Curve_Tag_Cubic

      start = 0
      end = 0

      for i in range (len (outline.contours)):
         end = outline.contours [i]
         points = outline_data [start:end+1] # end inclusive
         points.append (points [0]) # close contour

         # Decompose in segments and bezier arcs
         segments = [[points [0],],]
         for j in range (1, len (points)):
            segments [-1].append (points [j])
            if tag_on (points, j) and j < len (points)-1:
               segments.append ([points[j],])

         # Draw each segment
         context.move_to (x + points [0][0][0] / 64, y - points [0][0][1] / 64)

         for segment in segments:
            if len (segment) == 2:
               context.line_to (x + segment [1][0][0] / 64, y - segment [1][0][1] / 64)

            elif len (segment) == 3: # Truetype
               self.curve_quadratic_to (
                  context,
                  x + segment [1][0][0] / 64, y - segment[1][0][1] / 64,
                  x + segment [2][0][0] / 64, y - segment[2][0][1] / 64
               )

            elif len (segment) == 4 and tag_cubic (segment, 1) and tag_cubic (segment, 2):
               context.curve_to (
                  x + segment [1][0][0] / 64, y - segment [1][0][1] / 64,
                  x + segment [2][0][0] / 64, y - segment [2][0][1] / 64,
                  x + segment [3][0][0] / 64, y - segment [3][0][1] / 64,
               )
            else: # Truetype successive conic
               for j in range (1, len (segment) - 1):
                  # Create virtual "on" point in between
                  middle_x = (segment [j][0][0] + segment [j + 1][0][0]) * 0.5
                  middle_y = (segment [j][0][1] + segment [j + 1][0][1]) * 0.5
                  self.curve_quadratic_to (
                     context,
                     x + segment [j][0][0] / 64, y - segment[j][0][1] / 64,
                     x + middle_x / 64, y - middle_y / 64
                  )

         start = end+1


   #--------------------------------------------------------------------------

   def draw_text (self, context, font_path, font_size, text, render_mode):
      face = freetype.Face (font_path)
      face.set_char_size (int (font_size * 64))
      pc = 0
      x = 0
      y = 0
      for c in text:
         face.load_char (c, freetype.FT_LOAD_NO_HINTING)
         glyph = face.glyph
         kerning = face.get_kerning (pc, c)
         x += kerning.x / 64.0
         self.draw_glyph (context, glyph, x, y, render_mode)
         x += glyph.advance.x / 64.0
         pc = c

      if render_mode != 'translucence_no_fill':
         context.fill ()



   #--------------------------------------------------------------------------

   def measure_text (self, context, font_path, font_size, text):
      face = freetype.Face (font_path)
      face.set_char_size (int (font_size * 64))
      pc = 0
      width = 0.0
      x = 0.0
      x_min = 0.0
      x_max = 0.0
      y_min = 0.0
      y_max = 0.0
      for c in text:
         face.load_char (c, freetype.FT_LOAD_NO_HINTING)
         glyph = face.glyph
         outline = glyph.outline
         kerning = face.get_kerning (pc, c)
         bbox = glyph.outline.get_bbox ()
         x += kerning.x
         x_min = min (x_min, x + bbox.xMin)
         x_max = max (x_max, x + bbox.xMax)
         y_min = min (y_min, bbox.yMin)
         y_max = max (y_max, bbox.yMax)
         x += glyph.advance.x
         pc = c

      width = (x_max - x_min) / 64.0
      height = (y_max - y_min) / 64.0
      ascent = y_max / 64.0
      descent = - y_min / 64.0

      return (width, height, ascent, descent)



#-----------------------------------------------------------------------------

class ContextOnlySurface (cairosvg.surface.Surface):
   def __init__ (self, tree, context):
      self.context = context

      # cache stuff
      self.markers = {}
      self.gradients = {}
      self.patterns = {}
      self.masks = {}
      self.paths = {}
      self.filters = {}
      self.images = {}
      self.tree_cache = {(tree.url, tree.get('id')): tree}

      self.dpi = 72 # used in `size` for pt units

      # state stuff
      self.context_width, self.context_height, viewbox = cairosvg.helpers.node_format (self, tree) # used in `size` for % units
      self.context_scale = self.context_width / (viewbox [2] - viewbox [0])

      self.font_size = cairosvg.helpers.size(self, '12pt')
      self.cursor_position = [0, 0]
      self.cursor_d_position = [0, 0]
      self.text_path_width = 0
      self._old_parent_node = self.parent_node = None
      self.stroke_and_fill = True

      self.map_rgba = None
      self.map_image = None
