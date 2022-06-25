##############################################################################
#
#     kicad_pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
import re
import subprocess
import zipfile
from . import s_expression


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')

PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm

class KicadPcb:

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_gerber (self, path, root):
      for module in root.modules:
         self.fill_zones (path, module)
         self.generate_module_gerber (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):

      self.base_pcb = self.load (module.board.pcb.path)
      self.base_net = self.load (module.board.net.path)

      remove_all_pads = not module.route.is_wire
      self.remove_board_pads (module, remove_all_pads)

      self.fetch_board_references (self.base_net)

      self.collect_nets ()

      for control in module.controls:
         self.generate_control (module, control)

      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      if os.path.exists (path_pcb) and module.route.is_manual:
         base = self.load (path_pcb)
         def is_not_module (node):
            return node.kind != 'module'
         base.entities = list (filter (is_not_module, base.entities))

         for module_node in self.base_pcb.filter_kind ('module'):
            base.add (module_node)

         writer = s_expression.Writer ()
         writer.write (base, path_pcb)

      else:
         writer = s_expression.Writer ()
         writer.write (self.base_pcb, path_pcb)

      if module.route.is_wire:
         self.fill_zones (path, module)

      self.generate_module_gerber (path, module)

      path_net = os.path.join (path, '%s.net' % module.name)
      writer = s_expression.Writer ()
      writer.write (self.base_net, path_net)


   #--------------------------------------------------------------------------
   # Remove wire pads and associated traces either:
   # - When the associated pin is unused
   # - Or always, when 'all' is True

   def remove_board_pads (self, module, all=False):
      net_numbers = []

      # filter pins to remove and collect net numbers of traces to remove
      def filter_module (node):
         if node.kind == 'module' and node.entities [1].value.startswith ('TestPoint:TestPoint_Pad'):
            pad_node = node.first_kind ('pad')
            net_node = pad_node.first_kind ('net')
            net_number = net_node.entities [1].value

            if all:
               net_numbers.append (net_number)
               return False

            for fp_text_node in node.filter_kind ('fp_text'):
               if fp_text_node.entities [1].value in ['reference', 'user'] \
                  and fp_text_node.entities [2].value in module.unused_pins:
                     net_numbers.append (net_number)
                     return False

         return True

      self.base_pcb.entities = list (filter (filter_module, self.base_pcb.entities))

      # filter segments (traces) with matchin net number to remove
      def filter_segment (node):
         if node.kind == 'segment':
            net_node = node.first_kind ('net')
            net_number = net_node.entities [1].value
            if net_number in net_numbers:
               return False
         return True

      self.base_pcb.entities = list (filter (filter_segment, self.base_pcb.entities))


   #--------------------------------------------------------------------------
   # Make a map from net name (pin name) to net number

   def collect_nets (self):
      self.nets = {}

      for net_node in self.base_pcb.filter_kind ('net'):
         self.nets [net_node.entities [2].value] = net_node.entities [1].value


   #--------------------------------------------------------------------------
   # Retrieve already used board references for control reference allocations

   def fetch_board_references (self, export_node):

      self.board_references = []

      components_node = export_node.first_kind ('components')
      comp_nodes = components_node.filter_kind ('comp')
      for comp_node in comp_nodes:
         reference = comp_node.property ('ref')
         self.board_references.append (reference)


   #--------------------------------------------------------------------------

   def fill_zones (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      if platform.system () == 'Darwin':
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/3.8/bin/python3.8'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
      elif platform.system () == 'Windows':
         kicad_python_path = 'c:/Program Files/KiCad/6.0/bin/python.exe'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = 'c:/Program Files/KiCad/bin/python.exe'
      else:
         kicad_python_path = 'python'

      subprocess.check_call (
         [
            kicad_python_path,
            os.path.join (PATH_THIS, 'fill_zones.py'),
            path_pcb
         ],
         cwd = PATH_THIS
      )


   #--------------------------------------------------------------------------

   def generate_module_gerber (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      if platform.system () == 'Darwin':
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/3.8/bin/python3.8'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
      elif platform.system () == 'Windows':
         kicad_python_path = 'c:/Program Files/KiCad/6.0/bin/python.exe'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = 'c:/Program Files/KiCad/bin/python.exe'
      else:
         kicad_python_path = 'python'

      subprocess.check_call (
         [
            kicad_python_path,
            os.path.join (PATH_THIS, 'generate_gerber.py'),
            path, path_pcb
         ],
         cwd = PATH_THIS
      )

      def zipdir (path, zip_file):
         for root, dirs, files in os.walk (path):
            for file in files:
               zip_file.write (os.path.join (root, file), file)

      path_zip = os.path.join (path, '%s.gerber.zip' % module.name)
      zip_file = zipfile.ZipFile (path_zip, 'w', zipfile.ZIP_DEFLATED)
      gerber_dir = os.path.join (path, 'gerber')
      zipdir (gerber_dir, zip_file)
      zip_file.close ()


   #--------------------------------------------------------------------------

   def generate_control (self, module, control):
      for part in control.parts:
         ref_map = self.make_ref_map (part.net)
         self.generate_control_add_pcb (part.pcb, control, ref_map)
         self.generate_control_add_net (part.net, control, ref_map)


   #--------------------------------------------------------------------------
   # For each reference, find an available index for the component category
   # (eg. RV, D, J, etc.)
   # Algorithm is N^2 but that shouldn't be a big deal

   def make_ref_map (self, export_node):
      def alloc_ref (base):
         index = 1
         while '%s%d' % (base, index) in self.board_references:
            index += 1
         return '%s%d' % (base, index)

      ref_map = {}

      components_node = export_node.first_kind ('components')
      comp_nodes = components_node.filter_kind ('comp')
      for comp_node in comp_nodes:
         reference = comp_node.property ('ref')
         ref_split = list (filter (None, re.split (r'(\d+)', reference)))
         new_reference = alloc_ref (ref_split [0])
         ref_map [reference] = new_reference
         self.board_references.append (new_reference)

      return ref_map


   #--------------------------------------------------------------------------

   def generate_control_add_pcb (self, component, control, ref_map):
      component = self.move (component, control.position)
      component = self.rename_references (component, control, ref_map)
      component = self.rename_cascade_to (component, control)
      component = self.rename_cascade_from (component, control)
      component = self.rename_pins (component, control)
      component = self.relink_nets (component, control)
      for element in component.entities:
         self.base_pcb.add (element)


   #--------------------------------------------------------------------------

   def generate_control_add_net (self, component, control, ref_map):
      base_components_node = self.base_net.first_kind ('components')

      components_node = component.first_kind ('components')
      comp_nodes = components_node.filter_kind ('comp')
      for comp_node in comp_nodes:
         ref_node = comp_node.first_kind ('ref')
         reference = ref_node.entities [1].value
         ref_node.entities [1].value = ref_map [reference]
         base_components_node.add (comp_node)


   #--------------------------------------------------------------------------

   def make_gr_line (self, start_x, start_y, end_x, end_y):
      node = s_expression.List ()
      node.add (s_expression.Symbol ('gr_line'))

      start = s_expression.List ()
      start.add (s_expression.Symbol ('start'))
      start.add (s_expression.FloatLiteral (start_x))
      start.add (s_expression.FloatLiteral (start_y))
      node.add (start)

      end = s_expression.List ()
      end.add (s_expression.Symbol ('end'))
      end.add (s_expression.FloatLiteral (end_x))
      end.add (s_expression.FloatLiteral (end_y))
      node.add (end)

      layer = s_expression.List ()
      layer.add (s_expression.Symbol ('layer'))
      layer.add (s_expression.Symbol ('Edge.Cuts'))
      node.add (layer)

      width = s_expression.List ()
      width.add (s_expression.Symbol ('width'))
      width.add (s_expression.FloatLiteral (0.15))
      node.add (width)

      return node



   #--------------------------------------------------------------------------

   def load (self, path):
      with open (path, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      return parser.parse (content, 'kicad_pcb')


   #--------------------------------------------------------------------------
   # Rename all module references (including pads)

   def rename_references (self, component, control, ref_map):
      for module_node in component.filter_kind ('module'):
         for fp_text_node in module_node.filter_kind ('fp_text'):
            if fp_text_node.entities [1].value == 'reference':
               reference = fp_text_node.entities [2].value
               fp_text_node.entities [2].value = ref_map [reference]

      return component


   #--------------------------------------------------------------------------
   # Rename graphic text pin to actual pin name

   def rename_pins (self, component, control):
      name_map = {}
      if control.is_pin_single:
         name_map ['pin'] = control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['pin%d' % index] = name

      for gr_text_node in component.filter_kind ('gr_text'):
         text = gr_text_node.entities [1].value
         if text in name_map:
            gr_text_node.entities [1].value = name_map [text]

      return component


   #--------------------------------------------------------------------------
   # Relink nets of component to the one of the board

   def relink_nets (self, component, control):
      name_map = {}
      if control.is_pin_single:
         name_map ['Pin0'] = control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['Pin%d' % index] = name

      name_map ['GND'] = 'GND'
      name_map ['+3V3'] = '+3V3'

      if control.cascade_from is None:
         name_map ['Cascade0'] = 'GND'
      else:
         name_map ['Cascade0'] = control.cascade_from.reference.pin.name

      for module_node in component.filter_kind ('module'):
         for pad_node in module_node.filter_kind ('pad'):
            net_node = pad_node.first_kind ('net')
            if net_node != None:
               net_name = net_node.entities [2].value
               if net_name in name_map:
                  pin_name = name_map [net_name]
                  net_node.entities [1].value = self.nets [pin_name]
                  net_node.entities [2].value = pin_name

      return component


   #--------------------------------------------------------------------------
   # Rename graphic text 'cascade_to' pin (if any) to actual pin name

   def rename_cascade_to (self, component, control):
      if control.cascade_to is None:
         return self.rename_cascade (component, 'cascade_to', None)
      else:
         return self.rename_cascade (component, 'cascade_to', control.cascade_to.index)


   #--------------------------------------------------------------------------
   # Rename graphic text 'cascade_from' pin (if any) to actual pin name

   def rename_cascade_from (self, component, control):
      if control.cascade_from is None:
         return self.rename_cascade (component, 'cascade_from', None)
      else:
         return self.rename_cascade (component, 'cascade_from', control.cascade_from.index)


   #--------------------------------------------------------------------------

   def rename_cascade (self, component, cascade_type, cascade_index):
      for gr_text_node in component.filter_kind ('gr_text'):
         text = gr_text_node.entities [1].value
         if text == cascade_type:
            if cascade_index is None:
               gr_text_node.entities [1].value = '""'
            else:
               gr_text_node.entities [1].value = 'K%d' % (cascade_index + 1)

      return component


   #--------------------------------------------------------------------------
   # Move top level objects module, gr_text and segment (traces) to their
   # new position

   def move (self, component, position):

      for node in component.filter_kinds (['module', 'gr_text']):
         at_node = node.first_kind ('at')
         x = float (at_node.entities [1].value) + position.x.mm
         y = float (at_node.entities [2].value) + position.y.mm
         at_node.entities [1] = s_expression.FloatLiteral (x)
         at_node.entities [2] = s_expression.FloatLiteral (y)

      for node in component.filter_kind ('gr_circle'):
         for pos_node in node.filter_kinds (['center', 'end']):
            x = float (pos_node.entities [1].value) + position.x.mm
            y = float (pos_node.entities [2].value) + position.y.mm
            pos_node.entities [1] = s_expression.FloatLiteral (x)
            pos_node.entities [2] = s_expression.FloatLiteral (y)

      for node in component.filter_kind ('segment'):
         for endpoint in node.filter_kinds (['start', 'end']):
            x = float (endpoint.entities [1].value) + position.x.mm
            y = float (endpoint.entities [2].value) + position.y.mm
            endpoint.entities [1] = s_expression.FloatLiteral (x)
            endpoint.entities [2] = s_expression.FloatLiteral (y)

      return component
