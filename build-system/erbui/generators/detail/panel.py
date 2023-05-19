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

if platform.system () == 'Windows':
   os.environ ['PATH'] = '%s;%s' % (os.path.join (PATH_BUILD_SYSTEM, 'lib'), os.environ ['PATH'])
   if sys.version_info >= (3, 8):
      os.add_dll_directory (os.path.join (PATH_BUILD_SYSTEM, 'lib'))

import cairocffi
import cairosvg



MM_TO_PT = 72.0 / 25.4
PT_TO_MM = 1.0 / MM_TO_PT



class Panel:
   def __init__ (self):
      self.width = None
      self.height = 128.5

      self.font_family = 'D-DIN'
      self.font_slant = cairocffi.FONT_SLANT_NORMAL
      self.font_weight = cairocffi.FONT_WEIGHT_BOLD

      self.header_center_y = 5.0#mm
      self.footer_center_y = -5.0#mm

      self.positioning_margin = 0.75#mm

      self.current_box = None
      self.current_font_height = None
      self.current_position_x = None
      self.current_position_y = None


   #--------------------------------------------------------------------------

   def generate_module (self, context, module, simulated=False):

      context.set_fill_rule (cairocffi.FILL_RULE_EVEN_ODD)

      self.width = module.width.mm
      self.footer_center_y += self.height

      self.current_font_height = 14.0#pt
      self.current_position_x = self.width * 0.5
      self.current_position_y = self.height * 0.5

      if simulated:
         self.generate_back (context, module)

      self.generate_header (context, module, module.header)
      self.generate_footer (context, module, module.footer)

      for label in module.labels:
         self.generate_label (context, module, label)

      for image in module.images:
         self.generate_image (context, module, image)

      for line in module.lines:
         self.generate_line (context, module, line)

      for control in module.controls:
         self.generate_control (context, module, control)

      if simulated:
         for sticker in module.stickers:
            self.generate_sticker (context, module, sticker)


   #--------------------------------------------------------------------------

   def generate_back (self, context, module):
      context.rectangle (0, 0, self.width * MM_TO_PT, self.height * MM_TO_PT)

      material = module.material

      if material.is_aluminum_natural or material.is_brushed_aluminum_natural:
         panel_gray = 0.9

      elif material.is_aluminum_black or material.is_brushed_aluminum_black or material.is_aluminum_coated_black or material.is_pcb:
         panel_gray = 0.1

      elif material.is_aluminum_coated_white:
         panel_gray = 1.0

      context.set_source_rgb (panel_gray, panel_gray, panel_gray)
      context.fill()


   #--------------------------------------------------------------------------

   def generate_header (self, context, module, header):
      old_current_position_y = self.current_position_y
      self.current_position_y = self.header_center_y

      for label in header.labels:
         self.generate_label (context, module, label)

      for image in header.images:
         self.generate_image (context, module, image)

      self.current_position_y = old_current_position_y


   #--------------------------------------------------------------------------

   def generate_footer (self, context, module, footer):
      old_current_position_y = self.current_position_y
      self.current_position_y = self.footer_center_y

      if footer:
         for label in footer.labels:
            self.generate_label (context, module, label)

         for image in footer.images:
            self.generate_image (context, module, image)

      else:
         if module.material.is_light:
            filepath = os.path.join (PATH_THIS, 'erb.footer.black.svg')
         elif module.material.is_dark:
            filepath = os.path.join (PATH_THIS, 'erb.footer.white.svg')

         image = ast.Image (filepath)

         self.generate_image (context, module, image)

      self.current_position_y = old_current_position_y


   #--------------------------------------------------------------------------

   def generate_control (self, context, module, control):
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
         self.generate_label (context, module, label, control)

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

   def generate_label (self, context, module, label, control=None):
      position_x, position_y, align_x, align_y = self.process_label_position (label, control)

      if module.material.is_light:
         if control is not None and control.is_kind_out:
            fill_gray = 0.3
         else:
            fill_gray = 0.0
      elif module.material.is_dark:
         fill_gray = 1.0

      context.select_font_face (self.font_family, self.font_slant, self.font_weight)
      context.set_font_size (self.current_font_height)

      xbearing, ybearing, width_pt, height_pt, dx, dy = context.text_extents (label.text)
      ascent, descent, height, max_x_advance, max_y_advance = context.font_extents ()

      if control is not None and control.is_kind_out and not module.material.is_dark:
         self.generate_back_out_path (context, module, control)

      position_x_pt = position_x * MM_TO_PT - width_pt * align_x
      position_y_pt = position_y * MM_TO_PT + ascent * align_y

      context.move_to (position_x_pt, position_y_pt)
      context.text_path (label.text)
      context.set_source_rgb (fill_gray, fill_gray, fill_gray)
      context.fill ()


   #--------------------------------------------------------------------------

   def generate_sticker (self, context, module, sticker):
      position_x = sticker.position.x.mm
      position_y = sticker.position.y.mm
      align_x = 0.5
      align_y = 0.5

      context.select_font_face ('IndieFlower', cairocffi.FONT_SLANT_NORMAL, cairocffi.FONT_WEIGHT_NORMAL)
      context.set_font_size (10)

      xbearing, ybearing, width_pt, height_pt, dx, dy = context.text_extents (sticker.text)

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
         context.text_path (sticker.text)
         context.set_source_rgb (0.1, 0.1, 0.1)
         context.fill ()


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
         position_x += label.offset.x
         position_y += label.offset.y

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

   def generate_line (self, context, module, line):
      for index, position in enumerate (line.points):
         if index == 0:
            context.move_to (position.x.pt, position.y.pt)
         else:
            context.line_to (position.x.pt, position.y.pt)

      material = module.material

      if material.is_aluminum_natural or material.is_brushed_aluminum_natural or material.is_aluminum_coated_white:
         line_gray = 0.0

      elif material.is_aluminum_black or material.is_brushed_aluminum_black or material.is_aluminum_coated_black or material.is_pcb:
         line_gray = 1.0

      context.set_source_rgb (line_gray, line_gray, line_gray)
      context.set_line_width (0.7)
      context.set_line_join (cairocffi.LINE_JOIN_ROUND)
      context.set_line_cap (cairocffi.LINE_CAP_BUTT)
      context.stroke ()


   #--------------------------------------------------------------------------

   def generate_image (self, context, module, image):
      with open (image.file) as file:
         tree = cairosvg.parser.Tree (file_obj=file)
         surface = ContextOnlySurface (tree, context)

         width_pt = surface.context_width * 0.75
         height_pt = surface.context_height * 0.75

         position_x_pt = self.current_position_x * MM_TO_PT - width_pt * 0.5
         position_y_pt = self.current_position_y * MM_TO_PT - height_pt * 0.5

         with context:
            context.translate (position_x_pt, position_y_pt)
            context.scale (0.75)

            surface.draw (tree)


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

       self.dpi = 96 # used in `size` for pt units

       # state stuff
       self.context_width, self.context_height, viewbox = cairosvg.helpers.node_format (self, tree) # used in `size` for % units

       self.font_size = cairosvg.helpers.size(self, '12pt')
       self.cursor_position = [0, 0]
       self.cursor_d_position = [0, 0]
       self.text_path_width = 0
       self._old_parent_node = self.parent_node = None
       self.stroke_and_fill = True

       self.map_rgba = None
       self.map_image = None
