##############################################################################
#
#     dxf.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import sys

from ..kicad import pcb

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BUILD_SYSTEM = os.path.join (PATH_ROOT, 'build-system')
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')

sys.path.insert (0, PATH_PY3_PACKAGES)
import ezdxf



PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm

class Dxf:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      if module.material.is_pcb: return # not needed

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
         self.generate_control_part (msp, control, part)


   #--------------------------------------------------------------------------

   def generate_control_part (self, msp, control, part):
      pcb_root = part.pcb

      for gr_shape in part.pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrCircle) and gr_shape.layer == 'Eco1.User':
            msp.add_circle (
               (gr_shape.center.x, PANEL_HEIGHT - gr_shape.center.y),
               gr_shape.radius
            )

         elif isinstance (gr_shape, pcb.GrRect) and gr_shape.layer == 'Eco1.User':
            self.add_rounded_rectangle (
               msp,
               gr_shape.start.x, PANEL_HEIGHT - gr_shape.start.y,
               gr_shape.end.x, PANEL_HEIGHT - gr_shape.end.y,
               1.5   # drill bit 3mm
            )


   #--------------------------------------------------------------------------

   def add_rounded_rectangle (self, msp, start_x, start_y, end_x, end_y, radius):
      msp.add_arc ((start_x + radius, end_y + radius), radius, 180, 270)
      msp.add_line ((start_x + radius, end_y), (end_x - radius, end_y))
      msp.add_arc ((end_x - radius, end_y + radius), radius, 270, 360)
      msp.add_line ((end_x, end_y + radius), (end_x, start_y - radius))
      msp.add_arc ((end_x - radius, start_y - radius), radius, 0, 90)
      msp.add_line ((end_x - radius, start_y), (start_x + radius, start_y))
      msp.add_arc ((start_x + radius, start_y - radius), radius, 90, 180)
      msp.add_line ((start_x, start_y - radius), (start_x, end_y + radius))


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
