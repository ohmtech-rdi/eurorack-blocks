##############################################################################
#
#     drill.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import json
import math
import os
import sys

from ..kicad import pcb

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



class Drill:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      if module.format.is_3u: return # not needed

      for generator in module.manufacturer_data ['generators']:
         if generator ['id'] == 'tayda/drill':
            path_template = os.path.join (PATH_THIS, 'drill_template.py')
            path_py = os.path.join (path, '%s.tayda.drill.py' % module.name)

            with open (path_template, 'r', encoding='utf-8') as file:
               template = file.read ()

            if module.format.is_1590bb2_portrait:
               enclosure_type = '1590BB2'
            elif module.format.is_1590dd_landscape:
               enclosure_type = '1590DD'

            root = {
               'name': module.name,
               'enclosure_type': enclosure_type, # tayda internal name
               'is_public': 0,
               'is_archived': 0,
               'holes': [],
               'lines': [],
            }

            if module.pcb_left:
               self.generate_pcb_side (root, module, module.pcb_left, 'left')
            if module.pcb_top:
               self.generate_pcb_side (root, module, module.pcb_top, 'top')
            if module.pcb_right:
               self.generate_pcb_side (root, module, module.pcb_right, 'right')
            if module.pcb_bottom:
               self.generate_pcb_side (root, module, module.pcb_bottom, 'bottom')

            for control in module.controls:
               self.generate_control (root, module, control)

            content = json.dumps (root)

            template = template.replace ('%module.name%', module.name)
            template = template.replace ('%body%', content)

            with open (path_py, 'w', encoding='utf-8') as file:
               file.write (template)




   #--------------------------------------------------------------------------

   def generate_control (self, root, module, control):

      for part in control.parts:
         self.generate_control_part (root, module, control, part)
         self.generate_control_part_side (root, module, control, part)


   #--------------------------------------------------------------------------

   def generate_control_part (self, root, module, control, part):
      self.generate_pcb_face (root, module, part.pcb)


   #--------------------------------------------------------------------------

   def generate_control_part_side (self, root, module, control, part):
      if not part.pcb_side: return # not needed

      self.generate_pcb_side (root, module, part.pcb_side, part.side)


   #--------------------------------------------------------------------------

   def generate_pcb_face (self, root, module, pcb_root):
      box_side = 'A'

      clearance = 0.1

      for gr_shape in pcb_root.gr_shapes:
         if isinstance (gr_shape, pcb.GrCircle) and gr_shape.layer == 'Eco1.User':
            position_x = gr_shape.center.x - module.width.mm / 2.0
            position_y = module.height.mm / 2.0 - gr_shape.center.y
            root ['holes'].append ({
               'box_side': box_side,
               'diameter': str (round (2.0 * gr_shape.radius + 2.0 * clearance, 2)),
               'positionX': str (round (position_x, 2)),
               'positionY': str (round (position_y, 2)),
            })

         elif isinstance (gr_shape, pcb.GrRect) and gr_shape.layer == 'Eco1.User':
            start_x = min (gr_shape.start.x, gr_shape.end.x) - module.width.mm / 2.0 - clearance
            end_x = max (gr_shape.start.x, gr_shape.end.x) - module.width.mm / 2.0 + clearance
            start_y = module.height.mm / 2.0 - min (gr_shape.start.y, gr_shape.end.y) + clearance
            end_y = module.height.mm / 2.0 - max (gr_shape.start.y, gr_shape.end.y) - clearance
            drill_size = 3.0
            offset = drill_size / 2.0 + clearance

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': str (round (start_x + offset, 2)),
               'positionY1': str (round (start_y, 2)),
               'positionX2': str (round (end_x - offset, 2)),
               'positionY2': str (round (start_y, 2)),
            })

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': str (round (end_x, 2)),
               'positionY1': str (round (start_y - offset, 2)),
               'positionX2': str (round (end_x, 2)),
               'positionY2': str (round (end_y + offset, 2)),
            })

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': str (round (end_x - offset, 2)),
               'positionY1': str (round (end_y, 2)),
               'positionX2': str (round (start_x + offset, 2)),
               'positionY2': str (round (end_y, 2)),
            })

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': str (round (start_x, 2)),
               'positionY1': str (round (end_y + offset, 2)),
               'positionX2': str (round (start_x, 2)),
               'positionY2': str (round (start_y - offset, 2)),
            })

            root ['holes'].append ({
               'box_side': box_side,
               'diameter': str (drill_size + 2.0 * clearance),
               'positionX': str (round (start_x + offset, 2)),
               'positionY': str (round (start_y - offset, 2)),
            })

            root ['holes'].append ({
               'box_side': box_side,
               'diameter': str (drill_size + 2.0 * clearance),
               'positionX': str (round (end_x - offset, 2)),
               'positionY': str (round (start_y - offset, 2)),
            })

            root ['holes'].append ({
               'box_side': box_side,
               'diameter': str (drill_size + 2.0 * clearance),
               'positionX': str (round (end_x - offset, 2)),
               'positionY': str (round (end_y + offset, 2)),
            })

            root ['holes'].append ({
               'box_side': box_side,
               'diameter': str (drill_size + 2.0 * clearance),
               'positionX': str (round (start_x + offset, 2)),
               'positionY': str (round (end_y + offset, 2)),
            })


   #--------------------------------------------------------------------------

   def generate_pcb_side (self, root, module, pcb_root, side):
      if side == 'left':
         box_side = 'C'
      elif side == 'top':
         box_side = 'B'
      elif side == 'right':
         box_side = 'E'
      elif side == 'bottom':
         box_side = 'D'

      # real height of box without lid
      # reference: https://www.hammfg.com/electronics/small-case/diecast/1590
      if module.format.is_1590bb2_portrait:
         box_height = 33.75
      elif module.format.is_1590dd_landscape:
         box_height = 33.0

      clearance = 0.1

      for gr_shape in pcb_root.gr_shapes:
         if isinstance (gr_shape, pcb.GrCircle) and gr_shape.layer == 'Eco1.User':
            if side == 'left':
               position_x = box_height / 2.0 - gr_shape.center.y
               position_y = module.height.mm / 2.0 - gr_shape.center.x

            elif side == 'top':
               position_x = gr_shape.center.x - module.width.mm / 2.0
               position_y = gr_shape.center.y - box_height / 2.0

            elif side == 'right':
               position_x = gr_shape.center.y - box_height / 2.0
               position_y = module.height.mm / 2.0 - gr_shape.center.x

            elif side == 'bottom':
               position_x = gr_shape.center.x - module.width.mm / 2.0
               position_y = box_height / 2.0 - gr_shape.center.y

            root ['holes'].append ({
               'box_side': box_side,
               'diameter': str (round (2.0 * gr_shape.radius + 2.0 * clearance, 2)),
               'positionX': str (round (position_x, 2)),
               'positionY': str (round (position_y, 2)),
            })
