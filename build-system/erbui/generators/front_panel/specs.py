##############################################################################
#
#     specs.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
import subprocess

from ..kicad import pcb


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')

PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm



class Specs:

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):

      for generator in module.manufacturer_data ['generators']:
         if generator ['id'] == 'front_panel/specs':
            generator_args = generator ['args']

            file_format = generator_args.get ('file_format', '{module.name}.specs.txt')

            width_hp = round (module.width.mm / HP_TO_MM)
            width_mm = self.get_final_width (width_hp)
            height_mm = PANEL_HEIGHT

            header_format = generator_args ['header_format']
            specs = header_format.format (module=module)

            panel_format = generator_args ['panel_format']
            specs += panel_format.format (width_mm=width_mm, width_hp=width_hp, height_mm=height_mm)
            specs += 'Coodinates\' origin is bottom left of panel\n\n'

            specs += self.generate_mounting_holes (module, generator_args)

            for control in module.controls:
               specs += self.generate_control (control, generator_args)

            filename = file_format.format (module=module)
            path_specs = os.path.join (path, filename)

            with open (path_specs, 'w', encoding='utf-8') as file:
               file.write (specs)


   #--------------------------------------------------------------------------
   #
   # Reference: http://www.doepfer.de/a100_man/a100m_e.htm

   def generate_mounting_holes (self, module, generator_args):

      circle_format = generator_args ['circle_format']

      left = 7.5
      hole_size = 3.2
      edge_v = 3.0

      hole_radius = hole_size / 2

      specs = circle_format.format (**{'x': left, 'y': edge_v, 'diameter': hole_radius * 2.0})
      specs += circle_format.format (**{'x': left, 'y': PANEL_HEIGHT - edge_v, 'diameter': hole_radius * 2.0})

      width_hp = round (module.width.mm / HP_TO_MM)

      if width_hp >= 10:
         right = left + (width_hp - 3) * HP_TO_MM

         specs += circle_format.format (**{'x': right, 'y': edge_v, 'diameter': hole_radius * 2.0})
         specs += circle_format.format (**{'x': right, 'y': PANEL_HEIGHT - edge_v, 'diameter': hole_radius * 2.0})

      return specs


   #--------------------------------------------------------------------------

   def generate_control (self, control, generator_args):
      specs = ''
      for part in control.parts:
         specs += self.generate_control_part (control, part, generator_args)

      return specs


   #--------------------------------------------------------------------------

   def generate_control_part (self, control, part, generator_args):

      circle_format = generator_args ['circle_format']
      rounded_rectangle_format = generator_args ['rounded_rectangle_format']

      specs = ''

      pcb_root = part.pcb

      for gr_shape in part.pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrCircle) and gr_shape.layer == 'Eco1.User':
            specs += circle_format.format (**{
               'x': gr_shape.center.x,
               'y': PANEL_HEIGHT - gr_shape.center.y,
               'diameter': gr_shape.radius * 2.0
            })

         elif isinstance (gr_shape, pcb.GrRect) and gr_shape.layer == 'Eco1.User':
            start_x = min (gr_shape.start.x, gr_shape.end.x)
            end_x = max (gr_shape.start.x, gr_shape.end.x)
            start_y = max (gr_shape.start.y, gr_shape.end.y)
            end_y = min (gr_shape.start.y, gr_shape.end.y)

            specs += rounded_rectangle_format.format (**{
               'left': start_x,
               'bottom': PANEL_HEIGHT - start_y,
               'width': end_x - start_x,
               'height': start_y - end_y,
               'radius': 1.5  # drill bit 3mm
            })

      return specs


   #--------------------------------------------------------------------------
   #
   # Reference: http://www.doepfer.de/a100_man/a100m_e.htm

   def get_final_width (self, width_hp):
      hp_width_map = {
         2: 9.8,
         4: 20.00,
         6: 30.00,
         8: 40.30,
         10: 50.50,
         12: 60.60,
         14: 70.80,
         16: 80.90,
         18: 91.30,
         20: 101.30,
         21: 106.30, # quarter of 84Hp
         22: 111.40,
         28: 141.90,
         42: 213.00,
      }

      if width_hp in hp_width_map:
         return hp_width_map [width_hp]

      else:
         raise Exception ('unsupported module width hp %d' % width_hp)
