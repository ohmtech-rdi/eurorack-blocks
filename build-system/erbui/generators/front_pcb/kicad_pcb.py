##############################################################################
#
#     kicad_pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
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
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      self.base = self.load (module.board.pcb.path)

      remove_all_pads = not module.route.is_wire
      self.remove_board_pads (module, remove_all_pads)

      self.collect_nets ()

      for control in module.controls:
         self.generate_control (control)

      writer = s_expression.Writer ()
      writer.write (self.base, path_pcb)

      if module.route.is_wire:
         self.fill_zones (path, module)
         self.generate_module_gerber (path, module)


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

      self.base.entities = list (filter (filter_module, self.base.entities))

      # filter segments (traces) with matchin net number to remove
      def filter_segment (node):
         if node.kind == 'segment':
            net_node = node.first_kind ('net')
            net_number = net_node.entities [1].value
            if net_number in net_numbers:
               return False
         return True

      self.base.entities = list (filter (filter_segment, self.base.entities))


   #--------------------------------------------------------------------------
   # Make a map from net name (pin name) to net number

   def collect_nets (self):
      self.nets = {}

      for net_node in self.base.filter_kind ('net'):
         self.nets [net_node.entities [2].value] = net_node.entities [1].value


   #--------------------------------------------------------------------------

   def fill_zones (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      if platform.system () == 'Darwin':
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
      elif platform.system () == 'Windows':
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
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
      elif platform.system () == 'Windows':
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

   def generate_control (self, control):
      if control.style.is_alpha_9mm:
         component = self.load_component (os.path.join (PATH_THIS, 'alpha.9mm', 'alpha.9mm.kicad_pcb'))

      elif control.style.is_songhuei_9mm:
         component = self.load_component (os.path.join (PATH_THIS, 'songhuei.9mm', 'songhuei.9mm.kicad_pcb'))

      elif control.style.is_thonk_pj398sm:
         if control.cascade_from is None:
            component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.tn-gnd.kicad_pcb'))
         else:
            component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.tn-cascade.kicad_pcb'))

      elif control.style.is_ck_d6r:
         component = self.load_component (os.path.join (PATH_THIS, 'ckd6r', 'ckd6r.kicad_pcb'))

      elif control.style.is_tl1105:
         component = self.load_component (os.path.join (PATH_THIS, 'tl1105', 'tl1105.kicad_pcb'))

      elif control.style.is_dailywell_2ms:
         component = self.load_component (os.path.join (PATH_THIS, 'dailywell.2ms', 'dailywell.2ms.kicad_pcb'))

      elif control.style.is_led_3mm:
         if control.style.is_led_3mm_green_red:
            component = self.load_component (os.path.join (PATH_THIS, 'led.3mm.bi', 'led.3mm.bi.kicad_pcb'))
         elif control.style.is_led_3mm_rgb:
            component = self.load_component (os.path.join (PATH_THIS, 'led.3mm.rgb', 'led.3mm.rgb.kicad_pcb'))
         else:
            component = self.load_component (os.path.join (PATH_THIS, 'led.3mm', 'led.3mm.kicad_pcb'))

      else:
         print ('unsupported block %s' % control.style.name)

      component = self.rotate (component, control)
      component = self.move (component, control.position)
      component = self.rename_references (component, control)
      component = self.rename_pins (component, control)
      component = self.relink_nets (component, control)

      for element in component.entities:
         self.base.add (element)

      if control.cascade_to is not None:
         component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.do.kicad_pcb'))
         component = self.rotate (component, control)
         component = self.move (component, control.position)
         component = self.rename_references (component, control)
         component = self.rename_cascade_to (component, control.cascade_to.index)
         component = self.relink_nets (component, control)
         for element in component.entities:
            self.base.add (element)

      if control.cascade_from is not None:
         component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.di.kicad_pcb'))
         component = self.rotate (component, control)
         component = self.move (component, control.position)
         component = self.rename_references (component, control)
         component = self.rename_cascade_from (component, control.cascade_from.index)
         component = self.relink_nets (component, control)
         for element in component.entities:
            self.base.add (element)


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
   # Load a PCB and filter out all the unrelevant PCB description
   # Return a s_expression.List of:
   # - Power (GND and +3V3) nets only,
   # - modules, text and segments (traces)

   def load_component (self, path):

      def filter_func (node):
         if isinstance (node, s_expression.Symbol) and node.value == 'kicad_pcb':
            return False

         if node.kind in ['version', 'host', 'general', 'page', 'layers', 'setup', 'net_class', 'net']:
            return False

         # keep all the rest (modules, text, etc.)
         return True

      component = self.load (path)
      component.entities = list (filter (filter_func, component.entities))

      return component


   #--------------------------------------------------------------------------
   # Rename all module references (including pads)
   # by preprending the control name, to ensure
   # unique components reference names for the DRC checker.

   def rename_references (self, component, control):
      for module_node in component.filter_kind ('module'):
         for fp_text_node in module_node.filter_kind ('fp_text'):
            if fp_text_node.entities [1].value == 'reference':
               fp_text_node.entities [2].value = control.name + fp_text_node.entities [2].value

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
         name_map ['Net-(Pin0-Pad1)'] = control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['Net-(Pin%d-Pad1)' % index] = name

      name_map ['GND'] = 'GND'
      name_map ['+3V3'] = '+3V3'

      if control.cascade_from is not None:
         name_map ['Net-(Cascade0-Pad1)'] = control.cascade_from.reference.pin.name

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

   def rename_cascade_to (self, component, cascade_index):
      return self.rename_cascade (component, 'cascade_to', cascade_index)


   #--------------------------------------------------------------------------
   # Rename graphic text 'cascade_from' pin (if any) to actual pin name

   def rename_cascade_from (self, component, cascade_index):
      return self.rename_cascade (component, 'cascade_from', cascade_index)


   #--------------------------------------------------------------------------

   def rename_cascade (self, component, cascade_type, cascade_index):
      for gr_text_node in component.filter_kind ('gr_text'):
         text = gr_text_node.entities [1].value
         if text == cascade_type:
            gr_text_node.entities [1].value = 'K%d' % (cascade_index + 1)

      return component


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

      for node in component.filter_kind ('segment'):
         for endpoint in node.filter_kinds (['start', 'end']):
            x = float (endpoint.entities [1].value) + position.x.mm
            y = float (endpoint.entities [2].value) + position.y.mm
            endpoint.entities [1] = s_expression.FloatLiteral (x)
            endpoint.entities [2] = s_expression.FloatLiteral (y)

      return component
