##############################################################################
#
#     milling.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import ezdxf
import math
import os



PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm

class Milling:

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

      drill_size = self.get_drill_size (control.style)
      drill_radius = drill_size / 2

      msp.add_circle ((control.position.x.mm, PANEL_HEIGHT - control.position.y.mm), drill_radius)


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



   #--------------------------------------------------------------------------
   #
   # Reference:
   # Alpha: https://www.thonk.co.uk/wp-content/uploads/2017/05/Alpha-D-shaft.pdf
   # SongHuei: https://www.thonk.co.uk/wp-content/uploads/2014/10/R0904N_Thonk.pdf
   # DailyWell: https://www.thonk.co.uk/wp-content/uploads/2017/05/DW1-SPDT-ON-ON-2MS1T1B1M2QES.pdf
   # Thonkiconn: https://www.thonk.co.uk/wp-content/uploads/2018/07/Thonkiconn_Jack_Datasheet-new.jpg
   # C&K: https://www.thonk.co.uk/wp-content/uploads/2015/01/CK-Switch.pdf

   def get_drill_size (self, style):
      if style.is_alpha_9mm:
         return 7.5

      elif style.is_songhuei_9mm:
         return 6.8

      elif style.is_dailywell_2ms:
         return 4.95

      elif style.is_led_3mm:
         return 3.1

      elif style.is_thonk_pj398sm:
         return 6.5

      elif style.is_ck_d6r:
         return 9.6

      elif style.is_tl1105:
         return 5.2

      else:
         raise Exception ('unsupported control style %s' % style.name)
