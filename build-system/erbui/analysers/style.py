##############################################################################
#
#     style.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from .. import adapter
from .. import ast
from .. import error
from ..generators.front_pcb import s_expression

import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_EBUI = os.path.dirname (PATH_THIS)
PATH_FRONT_PCB = os.path.join (PATH_EBUI, 'generators', 'front_pcb')



class AnalyserStyle:

   #--------------------------------------------------------------------------
   #
   # Reference:
   # Alpha: https://www.thonk.co.uk/wp-content/uploads/2017/05/Alpha-D-shaft.pdf
   # SongHuei: https://www.thonk.co.uk/wp-content/uploads/2014/10/R0904N_Thonk.pdf
   # DailyWell: https://www.thonk.co.uk/wp-content/uploads/2017/05/DW1-SPDT-ON-ON-2MS1T1B1M2QES.pdf
   # Thonkiconn: https://www.thonk.co.uk/wp-content/uploads/2018/07/Thonkiconn_Jack_Datasheet-new.jpg
   # C&K: https://www.thonk.co.uk/wp-content/uploads/2015/01/CK-Switch.pdf

   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):

      for module in global_namespace.modules:
         self.analyse_module (module)

   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      for control in module.controls:
         self.analyse_control (module, control)


   #--------------------------------------------------------------------------

   def analyse_control (self, module, control):
      if module.route.is_wire:
         self.analyse_control_route_wire (module, control)
      else:
         self.analyse_control_route_manual (module, control)

      rotation = (control.rotation.degree_top_down + 360) % 360 if control.rotation else 0

      if rotation == 0:
         pass # nothing

      elif rotation == 90:
         control.label_keepout_bounds.top = control.label_keepout_bounds.right
         control.label_keepout_bounds.right = control.label_keepout_bounds.bottom
         control.label_keepout_bounds.bottom = control.label_keepout_bounds.left
         control.label_keepout_bounds.left = control.label_keepout_bounds.top

      elif rotation == 180:
         control.label_keepout_bounds.top, control.label_keepout_bounds.bottom = control.label_keepout_bounds.top, control.label_keepout_bounds.bottom
         control.label_keepout_bounds.left, control.label_keepout_bounds.right = control.label_keepout_bounds.left, control.label_keepout_bounds.right

      elif rotation == 270:
         control.label_keepout_bounds.left = control.label_keepout_bounds.bottom
         control.label_keepout_bounds.bottom = control.label_keepout_bounds.right
         control.label_keepout_bounds.right = control.label_keepout_bounds.top
         control.label_keepout_bounds.top = control.label_keepout_bounds.left

   #--------------------------------------------------------------------------

   def analyse_control_route_wire (self, module, control):
      style = control.style.name
      if style == 'rogan.6ps':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_6ps_dshaft (control)
      elif style == 'rogan.5ps':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_5ps_dshaft (control)
      elif style == 'rogan.3ps':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_3ps_dshaft (control)
      elif style == 'rogan.2ps':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_2ps_dshaft (control)
      elif style == 'rogan.1ps':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_1ps_dshaft (control)
      elif style == 'rogan.2s.black':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_2s_black_dshaft (control)
      elif style == 'rogan.1s':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_1s_dshaft (control)
      elif style == 'rogan.1s.black':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_rogan_1s_black_dshaft (control)
      elif style == 'sifam.dbn151.white':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_sifam_dbn151_white_dshaft (control)
      elif style == 'sifam.drn111.white':
         self.analyse_control_alpha_9mm_dshaft_wire (control)
         self.analyse_control_sifam_drn111_white_dshaft (control)
      elif style == 'songhuei.9mm':
         self.analyse_control_songhuei_9mm_wire (control)
      elif style == 'dailywell.2ms1':
         self.analyse_control_dailywell_2ms1_wire (control)
      elif style == 'dailywell.2ms3':
         self.analyse_control_dailywell_2ms3_wire (control)
      elif style == 'ck.d6r.black':
         self.analyse_control_ck_d6r_black_wire (control)
      elif style == 'tl1105':
         self.analyse_control_tl1105_wire (control)
         self.analyse_control_1rblk (control)
      elif style == 'thonk.pj398sm.knurled':
         self.analyse_control_thonk_pj398sm_wire (control)
         self.analyse_control_thonk_pj398sm_nut_knurled (control)
      elif style == 'thonk.pj398sm.hex':
         self.analyse_control_thonk_pj398sm_wire (control)
         self.analyse_control_thonk_pj398sm_nut_hex (control)
      elif style == 'led.3mm.red':
         self.analyse_control_led_3mm_red_wire (control)
      elif style == 'led.3mm.green':
         self.analyse_control_led_3mm_green_wire (control)
      elif style == 'led.3mm.yellow':
         self.analyse_control_led_3mm_yellow_wire (control)
      elif style == 'led.3mm.orange':
         self.analyse_control_led_3mm_orange_wire (control)
      elif style == 'led.3mm.green_red':
         self.analyse_control_led_3mm_green_red_wire (control)
      elif style == 'led.3mm.rgb':
         self.analyse_control_led_3mm_rgb_wire (control)
      else:
         print ('Unsupported style %s' % style)
         assert False


   #--------------------------------------------------------------------------

   def analyse_control_route_manual (self, module, control):
      style = control.style.name
      if style == 'rogan.6ps':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_6ps_dshaft (control)
      elif style == 'rogan.5ps':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_5ps_dshaft (control)
      elif style == 'rogan.3ps':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_3ps_dshaft (control)
      elif style == 'rogan.2ps':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_2ps_dshaft (control)
      elif style == 'rogan.1ps':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_1ps_dshaft (control)
      elif style == 'rogan.2s.black':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_2s_black_dshaft (control)
      elif style == 'rogan.1s':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_1s_dshaft (control)
      elif style == 'rogan.1s.black':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_rogan_1s_black_dshaft (control)
      elif style == 'sifam.dbn151.white':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_sifam_dbn151_white_dshaft (control)
      elif style == 'sifam.drn111.white':
         self.analyse_control_alpha_9mm_dshaft_manual (control)
         self.analyse_control_sifam_drn111_white_dshaft (control)
      elif style == 'songhuei.9mm':
         self.analyse_control_songhuei_9mm_manual (control)
      elif style == 'dailywell.2ms1':
         self.analyse_control_dailywell_2ms1_manual (control)
      elif style == 'dailywell.2ms3':
         self.analyse_control_dailywell_2ms3_manual (control)
      elif style == 'ck.d6r.black':
         self.analyse_control_ck_d6r_black_manual (control)
      elif style == 'tl1105':
         self.analyse_control_tl1105_manual (control)
         self.analyse_control_1rblk (control)
      elif style == 'thonk.pj398sm.knurled':
         self.analyse_control_thonk_pj398sm_manual (control)
         self.analyse_control_thonk_pj398sm_nut_knurled (control)
      elif style == 'thonk.pj398sm.hex':
         self.analyse_control_thonk_pj398sm_manual (control)
         self.analyse_control_thonk_pj398sm_nut_hex (control)
      elif style == 'led.3mm.red':
         self.analyse_control_led_3mm_red_manual (control)
      elif style == 'led.3mm.green':
         self.analyse_control_led_3mm_green_manual (control)
      elif style == 'led.3mm.yellow':
         self.analyse_control_led_3mm_yellow_manual (control)
      elif style == 'led.3mm.orange':
         self.analyse_control_led_3mm_orange_manual (control)
      elif style == 'led.3mm.green_red':
         self.analyse_control_led_3mm_green_red_manual (control)
      elif style == 'led.3mm.rgb':
         self.analyse_control_led_3mm_rgb_manual (control)
      else:
         print ('Unsupported style %s' % style)
         assert False


   #--------------------------------------------------------------------------

   def analyse_control_alpha_9mm_dshaft_wire (self, control):
      control.bom_parts.extend (self.make_bom ('alpha.9mm'))
      control.panel_holes.append (ast.Control.HoleCircular (7.5))
      control.pcb = self.load_kicad_pcb ('alpha.9mm', 'alpha.9mm.wire.kicad_pcb')

   def analyse_control_alpha_9mm_dshaft_manual (self, control):
      control.bom_parts.extend (self.make_bom ('alpha.9mm'))
      control.panel_holes.append (ast.Control.HoleCircular (7.5))
      control.pcb = self.load_kicad_pcb ('alpha.9mm', 'alpha.9mm.manual.kicad_pcb')


   #--------------------------------------------------------------------------

   def analyse_control_songhuei_9mm_wire (self, control):
      control.bom_parts.extend (self.make_bom ('songhuei.9mm'))
      control.panel_holes.append (ast.Control.HoleCircular (6.8))
      control.pcb = self.load_kicad_pcb ('songhuei.9mm', 'songhuei.9mm.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 6.5 * 0.5, - 6.5 * 0.5, 6.5 * 0.5, 6.5 * 0.5
      )
      control.simulator_class = 'erb::SongHuei9'

   def analyse_control_songhuei_9mm_manual (self, control):
      control.bom_parts.extend (self.make_bom ('songhuei.9mm'))
      control.panel_holes.append (ast.Control.HoleCircular (6.8))
      control.pcb = self.load_kicad_pcb ('songhuei.9mm', 'songhuei.9mm.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 6.5 * 0.5, - 6.5 * 0.5, 6.5 * 0.5, 6.5 * 0.5
      )
      control.simulator_class = 'erb::SongHuei9'


   #--------------------------------------------------------------------------

   def analyse_control_thonk_pj398sm_wire (self, control):
      control.bom_parts.extend (self.make_bom ('thonk.pj398sm'))
      control.panel_holes.append (ast.Control.HoleCircular (6.5))
      control.pcb = self.load_kicad_pcb (('thonk.pj398sm'), 'thonk.pj398sm.wire.kicad_pcb')

   def analyse_control_thonk_pj398sm_manual (self, control):
      control.bom_parts.extend (self.make_bom ('thonk.pj398sm'))
      control.panel_holes.append (ast.Control.HoleCircular (6.5))
      control.pcb = self.load_kicad_pcb (('thonk.pj398sm'), 'thonk.pj398sm.manual.kicad_pcb')


   #--------------------------------------------------------------------------

   def analyse_control_rogan_6ps_dshaft (self, control):
      control.bom_parts.append ({
         'description': '6PS - X-Large Pointer (D Shaft) - Rogan PT Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 31.75 * 0.5, - 31.75 * 0.5, 31.75 * 0.5, 31.75 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan6Ps>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_5ps_dshaft (self, control):
      control.bom_parts.append ({
         'description': '5PS - Larger Pointer (D Shaft) - Rogan PT Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 21.33 * 0.5, - 21.33 * 0.5, 21.33 * 0.5, 21.33 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan5Ps>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_3ps_dshaft (self, control):
      control.bom_parts.append ({
         'description': '3PS - Large Pointer (D Shaft) - Rogan PT Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 18.47 * 0.5, - 18.47 * 0.5, 18.47 * 0.5, 18.47 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan3Ps>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_2ps_dshaft (self, control):
      control.bom_parts.append ({
         'description': '2PS - Medium Pointer (D Shaft) - Rogan PT Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 15.75 * 0.5, - 15.75 * 0.5, 15.75 * 0.5, 15.75 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan2Ps>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_1ps_dshaft (self, control):
      control.bom_parts.append ({
         'description': '1PS - Small Pointer (D Shaft) - Rogan PT Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 14.38 * 0.5, - 14.38 * 0.5, 14.38 * 0.5, 14.38 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan1Ps>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_2s_black_dshaft (self, control):
      control.bom_parts.append ({
         'description': '2S - Medium Encoder BLACK (D Shaft) - Rogan PT Plastic Knob',
         'remarks': 'Choose Black',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 15.75 * 0.5, - 15.75 * 0.5, 15.75 * 0.5, 15.75 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan2SBlack>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_1s_dshaft (self, control):
      control.bom_parts.append ({
         'description': '1S - Small Encoder WHITE (D Shaft) - Rogan PT Plastic Knob',
         'remarks': 'Choose white',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 14.38 * 0.5, - 14.38 * 0.5, 14.38 * 0.5, 14.38 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan1S>'


   #--------------------------------------------------------------------------

   def analyse_control_rogan_1s_black_dshaft (self, control):
      control.bom_parts.append ({
         'description': '1S - Small Encoder BLACK (D Shaft) - Rogan PT Plastic Knob',
         'remarks': 'Choose black',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 14.38 * 0.5, - 14.38 * 0.5, 14.38 * 0.5, 14.38 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::Rogan1SBlack>'


   #--------------------------------------------------------------------------

   def analyse_control_sifam_dbn151_white_dshaft (self, control):
      control.bom_parts.append ({
         'description': 'White Large Skirt D - Sifam Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/intellijel-white-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 18.5 * 0.5, - 18.5 * 0.5, 18.5 * 0.5, 18.5 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::SifamDbn151>'


   #--------------------------------------------------------------------------

   def analyse_control_sifam_drn111_white_dshaft (self, control):
      control.bom_parts.append ({
         'description': 'White Small Skirt D - Sifam Plastic Knob',
         'remarks': '',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/intellijel-white-knobs/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 14.2 * 0.5, - 14.2 * 0.5, 14.2 * 0.5, 14.2 * 0.5
      )
      control.simulator_class = 'erb::AlphaPot <erb::SifamDrn111>'


   #--------------------------------------------------------------------------

   def analyse_control_thonk_pj398sm_nut_knurled (self, control):
      control.bom_parts.append ({
         'description': 'Knurled Nuts',
         'remarks': 'One nut bag contains already 50 pieces',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/thonkiconn/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 8.0 * 0.5, - 8.0 * 0.5, 8.0 * 0.5, 8.0 * 0.5
      )
      control.simulator_class = 'erb::ThonkPj398SmKnurled'


   #--------------------------------------------------------------------------

   def analyse_control_thonk_pj398sm_nut_hex (self, control):
      control.bom_parts.append ({
         'description': 'Hex Nuts',
         'remarks': 'One nut bag contains already 50 pieces',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/thonkiconn/',
      })
      control.label_keepout_bounds = self.union_bounds (
         control, - 8.0 * 0.5, - 8.0 * 0.5, 8.0 * 0.5, 8.0 * 0.5
      )
      control.simulator_class = 'erb::ThonkPj398SmHex'


   #--------------------------------------------------------------------------

   def analyse_control_dailywell_2ms1_wire (self, control):
      control.bom_parts.extend (self.make_bom ('dailywell.2ms'))
      control.panel_holes.append (ast.Control.HoleCircular (4.95))
      control.pcb = self.load_kicad_pcb ('dailywell.2ms', 'dailywell.2ms.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.5, - 4.0, 3.5, 4.0
      )
      control.erb_class = 'Switch <2>'
      control.simulator_class = 'erb::Dailywell2Ms1'

   def analyse_control_dailywell_2ms1_manual (self, control):
      control.bom_parts.extend (self.make_bom ('dailywell.2ms'))
      control.panel_holes.append (ast.Control.HoleCircular (4.95))
      control.pcb = self.load_kicad_pcb ('dailywell.2ms', 'dailywell.2ms.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.5, - 4.0, 3.5, 4.0
      )
      control.erb_class = 'Switch <2>'
      control.simulator_class = 'erb::Dailywell2Ms1'


   #--------------------------------------------------------------------------

   def analyse_control_dailywell_2ms3_wire (self, control):
      control.bom_parts.extend (self.make_bom ('dailywell.2ms'))
      control.panel_holes.append (ast.Control.HoleCircular (4.95))
      control.pcb = self.load_kicad_pcb ('dailywell.2ms', 'dailywell.2ms.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.5, - 4.0, 3.5, 4.0
      )
      control.erb_class = 'Switch <3>'
      control.simulator_class = 'erb::Dailywell2Ms3'

   def analyse_control_dailywell_2ms3_manual (self, control):
      control.bom_parts.extend (self.make_bom ('dailywell.2ms'))
      control.panel_holes.append (ast.Control.HoleCircular (4.95))
      control.pcb = self.load_kicad_pcb ('dailywell.2ms', 'dailywell.2ms.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.5, - 4.0, 3.5, 4.0
      )
      control.erb_class = 'Switch <3>'
      control.simulator_class = 'erb::Dailywell2Ms3'


   #--------------------------------------------------------------------------

   def analyse_control_ck_d6r_black_wire (self, control):
      control.bom_parts.extend (self.make_bom ('ckd6r'))
      control.panel_holes.append (ast.Control.HoleCircular (9.6))
      control.pcb = self.load_kicad_pcb ('ckd6r', 'ckd6r.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 9.0 * 0.5, - 9.0 * 0.5, 9.0 * 0.5, 9.0 * 0.5
      )
      control.simulator_class = 'erb::Ckd6r'

   def analyse_control_ck_d6r_black_manual (self, control):
      control.bom_parts.extend (self.make_bom ('ckd6r'))
      control.panel_holes.append (ast.Control.HoleCircular (9.6))
      control.pcb = self.load_kicad_pcb ('ckd6r', 'ckd6r.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 9.0 * 0.5, - 9.0 * 0.5, 9.0 * 0.5, 9.0 * 0.5
      )
      control.simulator_class = 'erb::Ckd6r'


   #--------------------------------------------------------------------------

   def analyse_control_tl1105_wire (self, control):
      control.bom_parts.extend (self.make_bom ('tl1105'))
      control.pcb = self.load_kicad_pcb ('tl1105', 'tl1105.wire.kicad_pcb')

   def analyse_control_tl1105_manual (self, control):
      control.bom_parts.extend (self.make_bom ('tl1105'))
      control.pcb = self.load_kicad_pcb ('tl1105', 'tl1105.manual.kicad_pcb')

   def analyse_control_1rblk (self, control):
      control.bom_parts.append ({
         'description': 'CAP PUSHBUTTON ROUND BLACK',
         'remarks': '',
         'distributor': 'Digikey',
         'part_number': 'EG1882-ND',
         'url': 'https://www.digikey.com/en/products/detail/e-switch/1RBLK/271579',
      })
      control.panel_holes.append (ast.Control.HoleCircular (5.2))
      control.label_keepout_bounds = self.union_bounds (
         control, - 5.5 * 0.5, - 5.5 * 0.5, 5.5 * 0.5, 5.5 * 0.5
      )
      control.simulator_class = 'erb::Tl1105'


   #--------------------------------------------------------------------------

   def analyse_control_led_3mm_red_wire (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <RedLight>'

   def analyse_control_led_3mm_green_wire (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <GreenLight>'

   def analyse_control_led_3mm_yellow_wire (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <YellowLight>'

   def analyse_control_led_3mm_orange_wire (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <YellowLight>' # orange is missing

   def analyse_control_led_3mm_green_red_wire (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm.bi'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm.bi', 'led.3mm.bi.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <GreenRedLight>'

   def analyse_control_led_3mm_rgb_wire (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm.rgb'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm.rgb', 'led.3mm.rgb.wire.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'MediumLight <RedGreenBlueLight>'


   def analyse_control_led_3mm_red_manual (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <RedLight>'

   def analyse_control_led_3mm_green_manual (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <GreenLight>'

   def analyse_control_led_3mm_yellow_manual (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <YellowLight>'

   def analyse_control_led_3mm_orange_manual (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm', 'led.3mm.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <YellowLight>' # orange is missing

   def analyse_control_led_3mm_green_red_manual (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm.bi'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm.bi', 'led.3mm.bi.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <GreenRedLight>'

   def analyse_control_led_3mm_rgb_manual (self, control):
      control.bom_parts.extend (self.make_bom ('led.3mm.rgb'))
      control.panel_holes.append (ast.Control.HoleCircular (3.1))
      control.pcb = self.load_kicad_pcb ('led.3mm.rgb', 'led.3mm.rgb.manual.kicad_pcb')
      control.label_keepout_bounds = self.union_bounds (
         control, - 3.0 * 0.5, - 3.0 * 0.5, 3.0 * 0.5, 3.0 * 0.5
      )
      control.simulator_class = 'erb::Led3mm <RedGreenBlueLight>'


   #--------------------------------------------------------------------------

   class Bounds:
      def __init__ (self):
         self.left = None
         self.top = None
         self.right = None
         self.bottom = None

   def union_bounds (self, control, left, top, right, bottom):
      bounds = AnalyserStyle.Bounds ()

      if control.label_keepout_bounds is None:
         bounds.left = left
         bounds.top = top
         bounds.right = right
         bounds.bottom = bottom
      else:
         bounds.left = min (control.label_keepout_bounds.left, left)
         bounds.top = min (control.label_keepout_bounds.top, top)
         bounds.right = max (control.label_keepout_bounds.right, right)
         bounds.bottom = max (control.label_keepout_bounds.bottom, bottom)

      return bounds


   #--------------------------------------------------------------------------

   def make_bom (self, name):
      path = os.path.join (PATH_FRONT_PCB, name, '%s.net' % name)

      with open (path, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      export_node = parser.parse (content, 'kicad_pcb')

      bom_parts = []

      components_node = export_node.first_kind ('components')
      comp_nodes = components_node.filter_kind ('comp')
      for comp_node in comp_nodes:
         reference = comp_node.property ('ref')
         fields_node = comp_node.first_kind ('fields')
         if fields_node != None:
            field_nodes = fields_node.filter_kind ('field')
            dist = None
            for field_node in field_nodes:
               if field_node.property ('name') == 'Description':
                  description = field_node.entities [2].value
               elif field_node.property ('name') == 'Dist':
                  dist = field_node.entities [2].value
               elif field_node.property ('name') == 'DistLink':
                  dist_link = field_node.entities [2].value
               elif field_node.property ('name') == 'DistPartNumber':
                  dist_part_nbr = field_node.entities [2].value
            if dist != None:
               bom_parts.append ({
                  'reference': reference,
                  'description': description,
                  'remarks': '',
                  'distributor': dist,
                  'part_number': dist_part_nbr,
                  'url': dist_link,
               })

      return bom_parts


   #--------------------------------------------------------------------------

   def load_kicad_pcb (self, dirname, filename):
      path = os.path.join (PATH_FRONT_PCB, dirname, filename)

      def filter_func (node):
         if isinstance (node, s_expression.Symbol) and node.value == 'kicad_pcb':
            return False

         if node.kind in ['version', 'host', 'general', 'page', 'layers', 'setup', 'net_class', 'net']:
            return False

         # keep all the rest (modules, text, etc.)
         return True

      with open (path, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      component = parser.parse (content, 'kicad_pcb')
      component.entities = list (filter (filter_func, component.entities))

      return component
