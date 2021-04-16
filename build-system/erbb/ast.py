##############################################################################
#
#     ast.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



# By default, all positions and distances are expressed in mm


class Root:
   def __init__ (self):
      self.modules = []


class Module:
   def __init__ (self):
      self.name = None
      self.width = None
      self.material = None
      self.header = None
      self.footer = None
      self.images = []
      self.labels = []
      self.lines = []
      self.controls = []


class Material:
   def __init__ (self):
      self.name = 'aluminum'
      self.color = None

   @property
   def is_light (self):
      return self.is_aluminum_natural or self.is_brushed_aluminum_natural or self.is_aluminum_coated_white

   @property
   def is_dark (self):
      return self.is_aluminum_black or self.is_brushed_aluminum_black or self.is_aluminum_coated_black

   @property
   def is_aluminum_natural (self):
      return self.name == 'aluminum' and self.color == None

   @property
   def is_aluminum_black (self):
      return self.name == 'aluminum' and self.color == 'black'

   @property
   def is_brushed_aluminum_natural (self):
      return self.name == 'brushed_aluminum' and self.color == None

   @property
   def is_brushed_aluminum_black (self):
      return self.name == 'brushed_aluminum' and self.color == 'black'

   @property
   def is_aluminum_coated_white (self):
      return self.name == 'aluminum_coated' and self.color == 'white'

   @property
   def is_aluminum_coated_black (self):
      return self.name == 'aluminum_coated' and self.color == 'black'


class Header:
   def __init__ (self):
      self.labels = []
      self.images = []


class Footer:
   def __init__ (self):
      self.labels = []
      self.images = []


class Control:
   def __init__ (self):
      self.type = None
      self.property = None
      self.position = None
      self.style = Style ()
      self.rotation = 0
      self.labels = []

   @property
   def is_type_out (self):
      return self.type == 'AudioOutDaisy' or self.type == 'GateOut'


class Style:
   def __init__ (self):
      self.value = None

   @property
   def is_alpha_9mm (self):
      return self.is_rogan

   @property
   def is_rogan (self):
      return self.is_rogan_6ps or self.is_rogan_5ps or self.is_rogan_3ps or self.is_rogan_2ps or self.is_rogan_1ps

   @property
   def is_rogan_6ps (self):
      return self.value == 'rogan.6ps'

   @property
   def is_rogan_5ps (self):
      return self.value == 'rogan.5ps'

   @property
   def is_rogan_3ps (self):
      return self.value == 'rogan.3ps'

   @property
   def is_rogan_2ps (self):
      return self.value == 'rogan.2ps'

   @property
   def is_rogan_1ps (self):
      return self.value == 'rogan.1ps'

   @property
   def is_songhuei_9mm (self):
      return self.value == 'songhuei.9mm'

   @property
   def is_dailywell_2ms (self):
      return self.is_dailywell_2ms1 or self.is_dailywell_2ms3

   @property
   def is_dailywell_2ms1 (self):
      return self.value == 'dailywell.2ms1' # spdt on-on

   @property
   def is_dailywell_2ms3 (self):
      return self.value == 'dailywell.2ms3' # spdt on-off-on

   @property
   def is_led_3mm (self):
      return self.is_led_3mm_red or self.is_led_3mm_green or self.is_led_3mm_yellow or self.is_led_3mm_orange or self.is_led_3mm_green_red

   @property
   def is_led_3mm_red (self):
      return self.value == 'led.3mm.red'

   @property
   def is_led_3mm_green (self):
      return self.value == 'led.3mm.green'

   @property
   def is_led_3mm_yellow (self):
      return self.value == 'led.3mm.yellow'

   @property
   def is_led_3mm_orange (self):
      return self.value == 'led.3mm.orange'

   @property
   def is_led_3mm_green_red (self):
      return self.value == 'led.3mm.green_red'

   @property
   def is_thonk_pj398sm (self):
      return self.is_thonk_pj398sm_knurled or self.is_thonk_pj398sm_hex

   @property
   def is_thonk_pj398sm_knurled (self):
      return self.value == 'thonk.pj398sm.knurled'

   @property
   def is_thonk_pj398sm_hex (self):
      return self.value == 'thonk.pj398sm.hex'

   @property
   def is_tl1105 (self):
      return self.value == 'tl1105'

   @property
   def is_ck_d6 (self):
      return self.is_ck_d6_black

   @property
   def is_ck_d6_black (self):
      return self.value == 'ck.d6.black'


class Label:
   def __init__ (self):
      self.text = None
      self.font = None
      self.positioning = Positioning ()
      self.position = None    # override
      self.offset = Position ()
      self.offset.x = 0.0
      self.offset.y = 0.0


class Font:
   def __init__ (self):
      self.family = None
      self.size = None # pt


class Positioning:
   def __init__ (self):
      self.value = 'center'

   @property
   def is_center (self):
      return self.value == 'center'

   @property
   def is_left (self):
      return self.value == 'left'

   @property
   def is_top (self):
      return self.value == 'top'

   @property
   def is_right (self):
      return self.value == 'right'

   @property
   def is_bottom (self):
      return self.value == 'bottom'


class Image:
   def __init__ (self):
      self.file = None


class Line:
   def __init__ (self):
      self.points = []


class Position:
   def __init__ (self):
      self.x = None
      self.y = None
