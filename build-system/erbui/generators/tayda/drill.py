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
      if not module.format.is_1590bb2_portrait: return # not needed

      for generator in module.manufacturer_data ['generators']:
         if generator ['id'] == 'tayda/drill':
            path_json = os.path.join (path, '%s.tayda.json' % module.name)

            if module.format.is_1590bb2_portrait:
               enclosure_type = '1590BB2'

            root = {
               'name': module.name,
               'enclosure_type': enclosure_type,
               'is_public': 0,
               'is_archived': 0,
               'holes': [],
               'lines': [],
            }

            for control in module.controls:
               self.generate_control (root, module, control)

            content = json.dumps (root)

            with open (path_json, 'w', encoding='utf-8') as file:
               file.write (content)




   #--------------------------------------------------------------------------

   def generate_control (self, root, module, control):

      for part in control.parts:
         self.generate_control_part (root, module, control, part)
         self.generate_control_part_side (root, module, control, part)


   #--------------------------------------------------------------------------

   def generate_control_part (self, root, module, control, part):
      pcb_root = part.pcb

      box_side = 'A'

      for gr_shape in part.pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrCircle) and gr_shape.layer == 'Eco1.User':
            position_x = gr_shape.center.x - module.width.mm / 2.0
            position_y = module.height.mm / 2.0 - gr_shape.center.y
            root ['holes'].append ({
               'box_side': box_side,
               'diameter': round (2.0 * gr_shape.radius + 0.2, 2),
               'positionX': round (position_x, 2),
               'positionY': round (position_y, 2),
            })

         elif isinstance (gr_shape, pcb.GrRect) and gr_shape.layer == 'Eco1.User':
            # drill bit 3mm
            start_x = min (gr_shape.start.x, gr_shape.end.x) + 1.5 - module.width.mm / 2.0
            end_x = max (gr_shape.start.x, gr_shape.end.x) - 1.5 - module.width.mm / 2.0
            start_y = module.height.mm / 2.0 - (min (gr_shape.start.y, gr_shape.end.y) + 1.5)
            end_y = module.height.mm / 2.0 - (max (gr_shape.start.y, gr_shape.end.y) - 1.5)

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': round (start_x, 2),
               'positionY1': round (start_y, 2),
               'positionX2': round (end_x, 2),
               'positionY2': round (start_y, 2),
            })

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': round (end_x, 2),
               'positionY1': round (start_y, 2),
               'positionX2': round (end_x, 2),
               'positionY2': round (end_y, 2),
            })

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': round (end_x, 2),
               'positionY1': round (end_y, 2),
               'positionX2': round (start_x, 2),
               'positionY2': round (end_y, 2),
            })

            root ['lines'].append ({
               'box_side': box_side,
               'positionX1': round (start_x, 2),
               'positionY1': round (end_y, 2),
               'positionX2': round (start_x, 2),
               'positionY2': round (end_x, 2),
            })


   #--------------------------------------------------------------------------

   def generate_control_part_side (self, root, module, control, part):
      if not part.pcb_side: return # not needed

      pcb_root = part.pcb_side

      if part.side == 'left':
         box_side = 'C'
      elif part.side == 'top':
         box_side = 'B'
      elif part.side == 'right':
         box_side = 'E'
      elif part.side == 'bottom':
         box_side = 'D'

      if module.format.is_1590bb2_portrait:
         box_height = 33.75

      for gr_shape in part.pcb_side.gr_shapes:
         if isinstance (gr_shape, pcb.GrCircle) and gr_shape.layer == 'Eco1.User':
            if part.side == 'left':
               position_x = gr_shape.center.y - box_height / 2.0
               position_y = module.height.mm / 2.0 - gr_shape.center.x

            elif part.side == 'top':
               position_x = gr_shape.center.x - module.width.mm / 2.0
               position_y = box_height / 2.0 - gr_shape.center.y

            elif part.side == 'right':
               position_x = box_height / 2.0 - gr_shape.center.y
               position_y = module.height.mm / 2.0 - gr_shape.center.x

            elif part.side == 'bottom':
               position_x = gr_shape.center.x - module.width.mm / 2.0
               position_y = gr_shape.center.y - box_height / 2.0

            root ['holes'].append ({
               'box_side': box_side,
               'diameter': round (2.0 * gr_shape.radius + 0.2, 2),
               'positionX': round (position_x, 2),
               'positionY': round (position_y, 2),
            })
