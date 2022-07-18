##############################################################################
#
#     style.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from .. import adapter
from .. import ast
from .. import error
from .. import parser
from ..grammar import GRAMMAR_MANUFACTURER_ROOT
from ..generators.front_pcb import s_expression
from ..generators.kicad import pcb, sch

import math
import os
from difflib import get_close_matches

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
         self.analyse_module (global_namespace, module)

   #--------------------------------------------------------------------------

   def analyse_module (self, global_namespace, module):

      manufacturer_style_set = self.analyse_module_manufacturer (global_namespace, module)

      for control in module.controls:
         self.analyse_control (module, control, manufacturer_style_set)


   #--------------------------------------------------------------------------

   def analyse_module_manufacturer (self, global_namespace, module):

      if module.manufacturer_reference:
         manufacturer = None
         for m in global_namespace.manufacturers:
            if m.name == module.manufacturer_reference.name:
               manufacturer = m
         if manufacturer is None:
            possible_tokens = []
            for m in global_namespace.manufacturers:
               possible_tokens.append (m.identifier)

            def make_dict (fun, iterable):
               return dict (zip (map (fun, iterable), iterable))

            possible_names = make_dict (lambda x: x.value, possible_tokens)
            matches = get_close_matches (module.manufacturer_reference.name, possible_names.keys ())

            fixit_decl_tokens = [possible_names [match_name] for match_name in matches]
            fixit_decls_sc = [adapter.SourceContext.from_token (f) for f in fixit_decl_tokens]

            raise error.undefined_reference (module.manufacturer_reference, fixit_decls_sc)

         manufacturer_path = manufacturer.identifier._parser.file_name

      else:
         if module.route.is_wire:
            manufacturer_path = os.path.join (PATH_FRONT_PCB, 'DiyWire.erbui')
         else:
            manufacturer_path = os.path.join (PATH_FRONT_PCB, 'DiyManual.erbui')
         gn = self.load_manufacturer (manufacturer_path)
         manufacturer = gn.manufacturers [0]

      module.manufacturer_base_path = os.path.dirname (manufacturer_path)
      module.manufacturer_data = self.make_manufacturer_data (manufacturer)
      manufacturer_style_set = self.make_manufacturer_style_set (module.manufacturer_data)

      return manufacturer_style_set


   #--------------------------------------------------------------------------

   def load_manufacturer (self, manufacturer_path):
      p = parser.Parser (grammar_root=GRAMMAR_MANUFACTURER_ROOT)

      with open (manufacturer_path, 'r', encoding='utf-8') as file:
          file_content = file.read ()

      return p.parse_manufacturer (file_content, manufacturer_path)


   #--------------------------------------------------------------------------

   def make_manufacturer_data (self, manufacturer):
      manufacturer_data = {}

      manufacturer_data ['generators'] = []
      for generator in manufacturer.generators:
         gen = {'id': generator.name, 'args': {}}
         for arg in generator.args:
            if isinstance (arg, ast.GeneratorArgString):
               gen ['args'][arg.name] = arg.value
            elif isinstance (arg, ast.GeneratorArgDict):
               sub_args = {}
               for item in arg.items:
                  sub_args [item.name] = item.value
               gen ['args'][arg.name] = sub_args

         manufacturer_data ['generators'].append (gen)

      manufacturer_data ['controls'] = {
         'AudioIn': [],
         'AudioOut': [],
         'Button': [],
         'CvIn': [],
         'CvOut': [],
         'GateIn': [],
         'GateOut': [],
         'Led': [],
         'LedBi': [],
         'LedRgb': [],
         'Pot': [],
         'Switch': [],
         'Trim': [],
      }

      for control in manufacturer.controls:
         for kind in control.kinds:
            manufacturer_data ['controls'][kind].append (
               {'styles': control.style, 'parts': control.parts}
            )

      return manufacturer_data


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
         kicad_pcb, kicad_sch = self.load_kicad_pcb_sch (module.manufacturer_base_path, component_name)
         self.rotate (kicad_pcb, control)
         self.translate (kicad_pcb, control)

         control.parts.append (ast.Control.Part (kicad_pcb, kicad_sch))


   #--------------------------------------------------------------------------

   def load_kicad_pcb_sch (self, base_path, component_name):

      kicad_pcb_path = os.path.join (base_path, component_name, '%s.kicad_pcb' % component_name)
      kicad_pcb = pcb.Root.read (kicad_pcb_path)

      kicad_sch_path = os.path.join (base_path, component_name, '%s.kicad_sch' % component_name)
      kicad_sch = sch.Root.read (kicad_sch_path)

      return (kicad_pcb, kicad_sch)


   #--------------------------------------------------------------------------
   # Rotate top level objects to their new position

   def rotate (self, kicad_pcb, control):
      rotation_degree = (control.rotation.degree + 360) % 360 if control.rotation else 0
      rotation = pcb.Rotation (rotation_degree)
      kicad_pcb.rotate (rotation)


   #--------------------------------------------------------------------------
   # Translate top level objects to their new position

   def translate (self, kicad_pcb, control):
      kicad_pcb.translate (control.position.x.mm, control.position.y.mm)
