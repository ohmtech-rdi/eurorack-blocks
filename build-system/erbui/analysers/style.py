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

import math
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
         component_list = self.get_comp_path_route_wire (control.style)
      else:
         component_list = self.get_comp_path_route_manual (control.style)

      for base_path, component_name in component_list:
         pcb, net = self.load_pcb_net (base_path, component_name)
         self.rotate (pcb, control)

         control.parts.append (ast.Control.Part (pcb, net))


   #--------------------------------------------------------------------------

   def get_comp_path_route_wire (self, style):
      if style.name == 'rogan.6ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.6ps')]
      elif style.name == 'rogan.5ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.5ps')]
      elif style.name == 'rogan.3ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.3ps')]
      elif style.name == 'rogan.2ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.2ps')]
      elif style.name == 'rogan.1ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.1ps')]
      elif style.name == 'rogan.2s.black':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.2s.black')]
      elif style.name == 'rogan.1s':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.1s')]
      elif style.name == 'rogan.1s.black':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'rogan.1s.black')]
      elif style.name == 'sifam.dbn151.white':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'sifam.dbn151.white')]
      elif style.name == 'sifam.drn111.white':
         return [(PATH_FRONT_PCB, 'alpha.9mm.wire'), (PATH_FRONT_PCB, 'sifam.drn111.white')]
      elif style.name == 'songhuei.9mm':
         return [(PATH_FRONT_PCB, 'songhuei.9mm.wire')]
      elif style.name == 'thonk.pj398sm.knurled':
         return [(PATH_FRONT_PCB, 'thonk.pj398sm.wire'), (PATH_FRONT_PCB, 'thonk.pj398sm.knurled')]
      elif style.name == 'thonk.pj398sm.hex':
         return [(PATH_FRONT_PCB, 'thonk.pj398sm.wire'), (PATH_FRONT_PCB, 'thonk.pj398sm.hex')]
      elif style.name == 'ck.d6r.black':
         return [(PATH_FRONT_PCB, 'ck.d6r.black.wire')]
      elif style.name == 'tl1105':
         return [(PATH_FRONT_PCB, 'tl1105.wire'), (PATH_FRONT_PCB, '1rblk')]
      elif style.name == 'dailywell.2ms1':
         return [(PATH_FRONT_PCB, 'dailywell.2ms1.wire')]
      elif style.name == 'dailywell.2ms3':
         return [(PATH_FRONT_PCB, 'dailywell.2ms3.wire')]
      elif style.name == 'led.3mm.red':
         return [(PATH_FRONT_PCB, 'led.3mm.red.wire')]
      elif style.name == 'led.3mm.green':
         return [(PATH_FRONT_PCB, 'led.3mm.green.wire')]
      elif style.name == 'led.3mm.yellow':
         return [(PATH_FRONT_PCB, 'led.3mm.yellow.wire')]
      elif style.name == 'led.3mm.orange':
         return [(PATH_FRONT_PCB, 'led.3mm.orange.wire')]
      elif style.name == 'led.3mm.green_red':
         return [(PATH_FRONT_PCB, 'led.3mm.bi.green_red.wire')]
      elif style.name == 'led.3mm.rgb':
         return [(PATH_FRONT_PCB, 'led.3mm.rgb.wire')]
      else:
         print ('unsupported style %s' % style.name)


   #--------------------------------------------------------------------------

   def get_comp_path_route_manual (self, style):
      if style.name == 'rogan.6ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.6ps')]
      elif style.name == 'rogan.5ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.5ps')]
      elif style.name == 'rogan.3ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.3ps')]
      elif style.name == 'rogan.2ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.2ps')]
      elif style.name == 'rogan.1ps':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.1ps')]
      elif style.name == 'rogan.2s.black':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.2s.black')]
      elif style.name == 'rogan.1s':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.1s')]
      elif style.name == 'rogan.1s.black':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'rogan.1s.black')]
      elif style.name == 'sifam.dbn151.white':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'sifam.dbn151.white')]
      elif style.name == 'sifam.drn111.white':
         return [(PATH_FRONT_PCB, 'alpha.9mm.manual'), (PATH_FRONT_PCB, 'sifam.drn111.white')]
      elif style.name == 'songhuei.9mm':
         return [(PATH_FRONT_PCB, 'songhuei.9mm.manual')]
      elif style.name == 'thonk.pj398sm.knurled':
         return [(PATH_FRONT_PCB, 'thonk.pj398sm.manual'), (PATH_FRONT_PCB, 'thonk.pj398sm.knurled')]
      elif style.name == 'thonk.pj398sm.hex':
         return [(PATH_FRONT_PCB, 'thonk.pj398sm.manual'), (PATH_FRONT_PCB, 'thonk.pj398sm.hex')]
      elif style.name == 'ck.d6r.black':
         return [(PATH_FRONT_PCB, 'ck.d6r.black.manual')]
      elif style.name == 'tl1105':
         return [(PATH_FRONT_PCB, 'tl1105.manual'), (PATH_FRONT_PCB, '1rblk')]
      elif style.name == 'dailywell.2ms1':
         return [(PATH_FRONT_PCB, 'dailywell.2ms1.manual')]
      elif style.name == 'dailywell.2ms3':
         return [(PATH_FRONT_PCB, 'dailywell.2ms3.manual')]
      elif style.name == 'led.3mm.red':
         return [(PATH_FRONT_PCB, 'led.3mm.red.manual')]
      elif style.name == 'led.3mm.green':
         return [(PATH_FRONT_PCB, 'led.3mm.green.manual')]
      elif style.name == 'led.3mm.yellow':
         return [(PATH_FRONT_PCB, 'led.3mm.yellow.manual')]
      elif style.name == 'led.3mm.orange':
         return [(PATH_FRONT_PCB, 'led.3mm.orange.manual')]
      elif style.name == 'led.3mm.green_red':
         return [(PATH_FRONT_PCB, 'led.3mm.bi.green_red.manual')]
      elif style.name == 'led.3mm.rgb':
         return [(PATH_FRONT_PCB, 'led.3mm.rgb.manual')]
      else:
         print ('unsupported style %s' % style.name)


   #--------------------------------------------------------------------------

   def load_pcb_net (self, base_path, component_name):

      pcb_path = os.path.join (base_path, component_name, '%s.kicad_pcb' % component_name)
      pcb = self.load_kicad_pcb (pcb_path)

      net_path = os.path.join (base_path, component_name, '%s.net' % component_name)
      net = self.load_net (net_path)

      return (pcb, net)


   #--------------------------------------------------------------------------
   # Load a PCB and filter out all the unrelevant PCB description
   # Return a s_expression.List of:
   # - Power (GND and +3V3) nets only,
   # - modules, text and segments (traces)

   def load_kicad_pcb (self, path):
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


   #--------------------------------------------------------------------------

   def load_net (self, path):
      with open (path, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      return parser.parse (content, 'net')


   #--------------------------------------------------------------------------
   # Rotate top level objects module, gr_text and segment (traces) to their
   # new position

   def rotate (self, component, control):

      rotation_deg = (control.rotation.degree + 360) % 360 if control.rotation else 0
      rotation_rad = float (rotation_deg) * 2.0 * math.pi / 360.0

      # axis is top/down in pcb coordinates: invert rotation angle
      cos_a = math.cos (- rotation_rad)
      sin_a = math.sin (- rotation_rad)

      def rot (x, y):
         return (
            x * cos_a - y * sin_a,
            x * sin_a + y * cos_a
         )

      for node in component.filter_kinds (['module', 'gr_text']):
         at_node = node.first_kind ('at')
         x = float (at_node.entities [1].value)
         y = float (at_node.entities [2].value)
         if len (at_node.entities) == 3:
            at_node.entities.append (s_expression.FloatLiteral (0))
         angle = float (at_node.entities [3].value)
         x, y = rot (x, y)
         angle = (angle + rotation_deg + 360) % 360
         at_node.entities [1] = s_expression.FloatLiteral (x)
         at_node.entities [2] = s_expression.FloatLiteral (y)
         at_node.entities [3] = s_expression.FloatLiteral (angle)

      for node in component.filter_kind ('segment'):
         for endpoint in node.filter_kinds (['start', 'end']):
            x = float (endpoint.entities [1].value)
            y = float (endpoint.entities [2].value)
            x, y = rot (x, y)
            endpoint.entities [1] = s_expression.FloatLiteral (x)
            endpoint.entities [2] = s_expression.FloatLiteral (y)

      return component
