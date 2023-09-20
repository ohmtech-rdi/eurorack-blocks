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
from ..generators.kicad import pcb, sch

import math
import os
import re
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

      if module.board.pcb:
         module.pcb = pcb.Root.read (os.path.abspath (module.board.pcb.path))
         module.sch = sch.Root.read (os.path.abspath (module.board.sch.path))

         # Retrieve already used board references for control reference allocations
         for footprint in module.pcb.footprints:
            module.references.append (footprint.reference)

         for net in module.pcb.nets:
            module.net_name_index_map [net.name] = net.index

      manufacturer_style_set = self.analyse_module_manufacturer (global_namespace, module)

      for control in module.controls:
         self.analyse_control (module, control, manufacturer_style_set)

      if module.board.pcb:
         module.sch_symbols = self.collect_symbols (module)


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

         def visit (item):
            if isinstance (item, ast.GeneratorArgString):
               return { item.name: item.value }
            elif isinstance (item, ast.GeneratorArgDict):
               sub_args = {}
               for sub_item in item.items:
                  sub_args.update (visit (sub_item))
               return { item.name: sub_args }

         gen = {'id': generator.name, 'args': {}}

         for arg in generator.args:
            if isinstance (arg, ast.GeneratorArgString):
               gen ['args'].update (visit (arg))
            elif isinstance (arg, ast.GeneratorArgDict):
               gen ['args'].update (visit (arg))

         manufacturer_data ['generators'].append (gen)

      manufacturer_data ['controls'] = {
         'AudioIn': [],
         'AudioOut': [],
         'Button': [],
         'CvIn': [],
         'CvOut': [],
         'Encoder': [],
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
               {'styles': control.style, 'parts': control.parts, 'class': control.class_}
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

      if control.normalling_from is not None and control.normalling_from.is_nothing:
         styles.add ('erb.normalling.nothing')

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

      control.simulator_class = cur_styles_parts ['class']

      component_list = cur_styles_parts ['parts']

      for component_name in component_list:
         kicad_pcb, kicad_sch = self.load_kicad_pcb_sch (
            module, module.manufacturer_base_path, component_name
         )
         self.rename_normalling_to (kicad_pcb, control)
         self.rename_normalling_from (kicad_pcb, control)
         self.rename_pins (kicad_pcb, control)
         if module.board.pcb:
            self.relink_nets (kicad_pcb, module, control)
         self.rotate (kicad_pcb, control)
         self.translate (kicad_pcb, control)

         control.parts.append (ast.Control.Part (kicad_pcb, kicad_sch))


   #--------------------------------------------------------------------------

   def load_kicad_pcb_sch (self, module, base_path, component_name):

      kicad_pcb_path = os.path.abspath (os.path.join (base_path, component_name, '%s.kicad_pcb' % component_name))
      kicad_pcb = pcb.Root.read (kicad_pcb_path)

      kicad_sch_path = os.path.abspath (os.path.join (base_path, component_name, '%s.kicad_sch' % component_name))
      kicad_sch = sch.Root.read (kicad_sch_path)

      ref_map = self.make_ref_map (module, kicad_pcb)

      for footprint in kicad_pcb.footprints:
         reference = footprint.reference
         footprint.set_reference (ref_map [reference])

      for symbol in kicad_sch.symbols:
         reference = symbol.property ('Reference')
         if reference [0] != '#':   # eg. #PWRxxx
            symbol.set_property ('Reference', ref_map [reference])

      for symbol_instance in kicad_sch.symbol_instances:
         if symbol_instance.reference [0] != '#':   # eg. #PWRxxx
            symbol_instance.reference = ref_map [symbol_instance.reference]

      return (kicad_pcb, kicad_sch)


   #--------------------------------------------------------------------------
   # For each reference, find an available index for the component category
   # (eg. RV, D, J, etc.)
   # Algorithm is N^2 but that shouldn't be a big deal

   def make_ref_map (self, module, kicad_pcb):
      def alloc_ref (base):
         index = 1
         while '%s%d' % (base, index) in module.references:
            index += 1
         return '%s%d' % (base, index)

      ref_map = {}

      for footprint in kicad_pcb.footprints:
         reference = footprint.reference
         ref_split = list (filter (None, re.split (r'(\d+)', reference)))
         new_reference = alloc_ref (ref_split [0])
         ref_map [reference] = new_reference
         module.references.append (new_reference)

      return ref_map


   #--------------------------------------------------------------------------
   # Rename graphic text 'normalling_to' pin (if any) to actual pin name

   def rename_normalling_to (self, kicad_pcb, control):
      if control.normalling_to is None:
         self.rename_normalling (kicad_pcb, 'normalling_to', None)
      else:
         self.rename_normalling (kicad_pcb, 'normalling_to', control.normalling_to.index)


   #--------------------------------------------------------------------------
   # Rename graphic text 'normalling_from' pin (if any) to actual pin name

   def rename_normalling_from (self, kicad_pcb, control):
      if control.normalling_from is None:
         self.rename_normalling (kicad_pcb, 'normalling_from', None)
      else:
         self.rename_normalling (kicad_pcb, 'normalling_from', control.normalling_from.index)


   #--------------------------------------------------------------------------

   def rename_normalling (self, kicad_pcb, normalling_type, normalling_index):
      for gr_shape in kicad_pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrText) and gr_shape.value == normalling_type:
            if normalling_index is None:
               gr_shape.value = ''
            else:
               gr_shape.value = 'K%d' % (normalling_index + 1)


   #--------------------------------------------------------------------------
   # Rename graphic text pin to actual pin name

   def rename_pins (self, kicad_pcb, control):
      name_map = {}
      if control.is_pin_single:
         name_map ['pin'] = control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['pin%d' % index] = name

      for gr_shape in kicad_pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrText) and gr_shape.value in name_map:
            gr_shape.value = name_map [gr_shape.value]


   #--------------------------------------------------------------------------
   # Relink nets of component to the one of the board

   def relink_nets (self, kicad_pcb, module, control):
      name_map = {}
      if control.is_pin_single:
         name_map ['Pin0'] = control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['Pin%d' % index] = name

      name_map ['GND'] = 'GND'
      name_map ['+3V3'] = '+3V3'
      name_map ['3V3A'] = '3V3A'
      name_map ['3V3D'] = '3V3D'
      name_map ['3V3SW'] = '3V3SW'

      if control.normalling_from is None:
         name_map ['Normalling0'] = 'GND'
      elif control.normalling_from.is_nothing:
         name_map ['Normalling0'] = 'NPR0'
      else:
         name_map ['Normalling0'] = control.normalling_from.reference.pin.name

      for footprint in kicad_pcb.footprints:
         for pad in footprint.pads:
            if pad.net:
               net_name = pad.net.name
               net_suffix = ''
               if '.' in net_name:
                  [base, suffix] = net_name.split ('.')
                  net_name = base
                  net_suffix = '.' + suffix

               if net_name in name_map:
                  pin_name = name_map [net_name] + net_suffix
                  pad.net.index = module.net_name_index_map [pin_name]
                  pad.net.name = pin_name
               else:
                  # net not associated with board, prefix with control name
                  # to avoid net name clashing, and add to base pcb net list
                  pad.net.name = '%s-%s' % (control.name, pad.net.name)
                  if pad.net.name in module.net_name_index_map:
                     pad.net.index = module.net_name_index_map [pad.net.name]
                  else:
                     pad.net.index = -1
                     for net in module.pcb.nets:
                        pad.net.index = max (pad.net.index, net.index + 1)
                     module.net_name_index_map [pad.net.name] = pad.net.index
                     module.pcb.nets.append (pad.net)



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


   #--------------------------------------------------------------------------

   def collect_symbols (self, module):

      board_sch_path = module.board.sch.path
      board_sch_base_path = os.path.abspath (os.path.dirname (board_sch_path))

      symbols = []

      symbols.extend (module.sch.symbols)

      for sheet in module.sch.sheets:
         sheet_file = sheet.property ('Sheet file')
         sheet_path = os.path.abspath (os.path.join (board_sch_base_path, sheet_file))
         sheet_sch = sch.Root.read (sheet_path)
         symbols.extend (sheet_sch.symbols)

      for control in module.controls:
         for part in control.parts:
            symbols.extend (part.sch.symbols)

      return symbols
