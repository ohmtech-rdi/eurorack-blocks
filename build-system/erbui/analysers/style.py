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

      if module.route.is_wire:
         manufacturer_path = os.path.join (PATH_FRONT_PCB, 'diy-wire.py')
      else:
         manufacturer_path = os.path.join (PATH_FRONT_PCB, 'diy-manual.py')

      module.manufacturer_base_path = os.path.dirname (manufacturer_path)

      with open (manufacturer_path, 'r', encoding='utf-8') as file:
         module.manufacturer_data = eval (file.read ())

      manufacturer_style_set = self.make_manufacturer_style_set (module.manufacturer_data)

      for control in module.controls:
         self.analyse_control (module, control, manufacturer_style_set)


   #--------------------------------------------------------------------------

   def make_manufacturer_style_set (self, manufacturer_data):
      style_set = set ()
      for kind, style_parts_arr in manufacturer_data ['controls'].items ():
         for style_parts in style_parts_arr:
            style_set = style_set.union (style_parts ['styles'])

      return style_set


   #--------------------------------------------------------------------------

   def analyse_control (self, module, control, manufacturer_style_set):

      styles = set ()

      if control.style is not None:
         control_styles = control.style.keyword_names
         for keyword in control_styles:
            if keyword.value not in manufacturer_style_set:
               raise error.unknown_style (keyword, manufacturer_style_set)
            styles.add (keyword.value)

      cur_common_nbr = -1
      cur_element = None

      styles_parts_arr = module.manufacturer_data ['controls'][control.kind]

      for styles_parts in styles_parts_arr:
         common_nbr = len (styles.intersection (styles_parts ['styles']))
         if common_nbr > cur_common_nbr:
            cur_common_nbr = common_nbr
            cur_styles_parts = styles_parts

      for unknown in styles.difference (cur_styles_parts ['styles']):
         for keyword in control_styles:
            if keyword.value == unknown:
               raise error.incompatible_style (keyword, cur_styles_parts ['styles'])

      component_list = cur_styles_parts ['parts']

      for component_name in component_list:
         pcb, net = self.load_pcb_net (module.manufacturer_base_path, component_name)
         self.rotate (pcb, control)

         control.parts.append (ast.Control.Part (pcb, net))


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
