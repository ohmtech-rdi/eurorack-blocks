##############################################################################
#
#     dxf.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import ezdxf
import math
import os



PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm

class Dxf:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_dxf = os.path.join (path, '%s.dxf' % module.name)

      doc = ezdxf.new (units=ezdxf.units.MM)
      msp = doc.modelspace ()

      width_hp = round (module.width.mm / HP_TO_MM)
      final_width = self.get_final_width (width_hp)

      msp.add_line ((0, 0), (final_width, 0))
      msp.add_line ((final_width, 0), (final_width, PANEL_HEIGHT))
      msp.add_line ((final_width, PANEL_HEIGHT), (0, PANEL_HEIGHT))
      msp.add_line ((0, PANEL_HEIGHT), (0, 0))

      self.generate_mounting_holes (msp, module)

      for control in module.controls:
         self.generate_control (msp,  control)

      doc.saveas (path_dxf)


   #--------------------------------------------------------------------------
   #
   # Reference: http://www.doepfer.de/a100_man/a100m_e.htm

   def generate_mounting_holes (self, msp, module):

      left = 7.5
      hole_size = 3.2
      edge_v = 3.0

      hole_radius = hole_size / 2

      msp.add_circle ((left, edge_v), hole_radius)
      msp.add_circle ((left, PANEL_HEIGHT - edge_v), hole_radius)

      width_hp = round (module.width.mm / HP_TO_MM)

      if width_hp >= 10:
         right = left + (width_hp - 3) * HP_TO_MM
         msp.add_circle ((right, edge_v), hole_radius)
         msp.add_circle ((right, PANEL_HEIGHT - edge_v), hole_radius)


   #--------------------------------------------------------------------------

   def generate_control (self, msp, control):

      for part in control.parts:
         for node in part.pcb.filter_kind ('gr_circle'):
            if node.property ('layer') == 'Eco1.User':
               center_node = node.first_kind ('center')
               center_x = float (center_node.entities [1].value)
               center_y = float (center_node.entities [2].value)
               end_node = node.first_kind ('end')
               end_x = float (end_node.entities [1].value)
               end_y = float (end_node.entities [2].value)
               vec_x = end_x - center_x
               vec_y = end_y - center_y
               drill_radius = math.sqrt (vec_x * vec_x + vec_y * vec_y)

               x = control.position.x.mm + center_x
               y = control.position.y.mm + center_y

               msp.add_circle ((x, PANEL_HEIGHT - y), drill_radius)



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
