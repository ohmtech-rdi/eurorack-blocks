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

PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm

class KicadPcb:

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      board = module.board.name if module.board is not None else 'board.null'

      self.base = self.load (os.path.join (PATH_THIS, board, '%s.kicad_pcb' % board))

      self.remove_pads (module)

      self.collect_nets ()

      for control in module.controls:
         self.generate_control (control)

      writer = s_expression.Writer ()
      writer.write (self.base, path_pcb)

      self.fill_zones (path, module)
      self.generate_module_gerber (path, module)


   #--------------------------------------------------------------------------

   def remove_pads (self, module):
      net_numbers = []
      def filter_func (node):
         if isinstance (node, s_expression.List) and node.entities \
            and isinstance (node.entities [0], s_expression.Symbol) \
            and node.entities [0].value in ['module'] \
            and isinstance (node.entities [1], s_expression.Symbol) \
            and 'TestPoint:TestPoint_Pad' in node.entities [1].value:
            remove = False
            net_number = None
            for sub_node in node.entities:
               if isinstance (sub_node, s_expression.List) and sub_node.entities \
                  and isinstance (sub_node.entities [0], s_expression.Symbol) \
                  and sub_node.entities [0].value in ['fp_text'] \
                  and sub_node.entities [1].value in ['reference', 'user'] \
                  and sub_node.entities [2].value in module.unused_pins:
                     remove = True

               if isinstance (sub_node, s_expression.List) and sub_node.entities \
                  and isinstance (sub_node.entities [0], s_expression.Symbol) \
                  and sub_node.entities [0].value in ['pad']:
                  for ssub_node in sub_node.entities:
                     if isinstance (ssub_node, s_expression.List) and ssub_node.entities \
                        and isinstance (ssub_node.entities [0], s_expression.Symbol) \
                        and ssub_node.entities [0].value in ['net']:
                           net_number = ssub_node.entities [1].value
            if remove:
               net_numbers.append (net_number)
               return False

         return True

      self.base.entities = list (filter (filter_func, self.base.entities))

      self.remove_nets (net_numbers)


   #--------------------------------------------------------------------------

   def remove_nets (self, nets):
      def filter_func (node):
         if isinstance (node, s_expression.List) and node.entities \
            and isinstance (node.entities [0], s_expression.Symbol) \
            and node.entities [0].value in ['segment']:
            for sub_node in node.entities:
               if isinstance (sub_node, s_expression.List) and sub_node.entities \
                  and isinstance (sub_node.entities [0], s_expression.Symbol) \
                  and sub_node.entities [0].value in ['net'] \
                  and sub_node.entities [1].value in nets:
                  return False
         return True

      self.base.entities = list (filter (filter_func, self.base.entities))


   #--------------------------------------------------------------------------

   def collect_nets (self):
      self.nets = {}
      for element in self.base.entities:
         if isinstance (element, s_expression.List) \
            and element.entities [0].value == 'net':
            self.nets [element.entities [2].value] = element.entities [1].value


   #--------------------------------------------------------------------------

   def fill_zones (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      if platform.system () == 'Darwin':
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
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
         rotation = (control.rotation.degree_top_down + 360) % 360 if control.rotation else 0
         if rotation == 0:
            component = self.load_component (os.path.join (PATH_THIS, 'dailywell.2ms', 'dailywell.2ms.kicad_pcb'))
         elif rotation == 90:
            component = self.load_component (os.path.join (PATH_THIS, 'dailywell.2ms', 'dailywell.2ms.r90.kicad_pcb'))
         elif rotation == 270:
            component = self.load_component (os.path.join (PATH_THIS, 'dailywell.2ms', 'dailywell.2ms.r270.kicad_pcb'))
         else:
            print ('unsupported rotation %d for %s' % (rotation, control.style.name))

      elif control.style.is_led_3mm:
         if control.style.is_led_3mm_green_red:
            component = self.load_component (os.path.join (PATH_THIS, 'led.3mm.bi', 'led.3mm.bi.kicad_pcb'))
         elif control.style.is_led_3mm_rgb:
            component = self.load_component (os.path.join (PATH_THIS, 'led.3mm.rgb', 'led.3mm.rgb.kicad_pcb'))
         else:
            component = self.load_component (os.path.join (PATH_THIS, 'led.3mm', 'led.3mm.kicad_pcb'))

      else:
         print ('unsupported block %s' % control.style.name)

      component = self.move (component, control.position)
      component = self.rename_references (component, control)
      component = self.rename_pins (component, control)
      component = self.relink_pads (component, control)

      for element in component.entities:
         self.base.add (element)

      if control.cascade_to is not None:
         component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.do.kicad_pcb'))
         component = self.move (component, control.position)
         component = self.rename_references (component, control)
         component = self.rename_cascade (component, control.cascade_to.index)
         component = self.relink_pads (component, control)
         for element in component.entities:
            self.base.add (element)

      if control.cascade_from is not None:
         component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.di.kicad_pcb'))
         component = self.move (component, control.position)
         component = self.rename_references (component, control)
         component = self.rename_cascade (component, control.cascade_from.index)
         component = self.relink_pads (component, control)
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
      with open (path, 'r') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      return parser.parse (content, 'kicad_pcb')


   #--------------------------------------------------------------------------

   def load_component (self, path):

      def filter_func (node):
         if isinstance (node, s_expression.Symbol) and node.value == 'kicad_pcb':
            return False

         if isinstance (node, s_expression.List) and node.entities \
            and isinstance (node.entities [0], s_expression.Symbol) \
            and node.entities [0].value in ['version', 'host', 'general', 'page', 'layers', 'setup', 'net_class']:
            return False

         if isinstance (node, s_expression.List) and node.entities \
            and isinstance (node.entities [0], s_expression.Symbol) \
            and node.entities [0].value in ['net']:
               if len (node.entities) == 3:
                  if node.entities [2].value == 'GND':
                     return True
                  elif node.entities [2].value == '+3V3':
                     return True
                  else:
                     return False
               else:
                  return False

         return True

      component = self.load (path)
      component.entities = list (filter (filter_func, component.entities))

      #self.remove_net_recursive (component)

      return component


   #--------------------------------------------------------------------------

   def remove_net_recursive (self, node):
      def filter_func (node):
         if isinstance (node, s_expression.List) and node.entities \
            and isinstance (node.entities [0], s_expression.Symbol) \
            and node.entities [0].value == 'net':
               if len (node.entities) == 3:
                  if node.entities [2].value == 'GND':
                     return True
                  elif node.entities [2].value == '+3V3':
                     return True
                  else:
                     return False
               else:
                  return False
         return True

      for element in node.entities:
         if isinstance (element, s_expression.List):
            element.entities = list (filter (filter_func, element.entities))
            self.remove_net_recursive (element)


   #--------------------------------------------------------------------------

   def rename_references (self, component, control):
      for element in component.entities:
         entity = element.entities [0]
         element_name = entity.value
         if element_name in ['module']:
            self.rename_reference (element, control.name)

      return component


   #--------------------------------------------------------------------------

   def rename_reference (self, element, control_name):
      for property in element.entities:
         if isinstance (property, s_expression.List) \
            and property.entities [0].value == 'fp_text' \
            and property.entities [1].value == 'reference':
            property.entities [2].value = control_name + property.entities [2].value


   #--------------------------------------------------------------------------

   def rename_pins (self, component, control):
      name_map = {}
      if control.is_pin_single:
         name_map ['pin'] = control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['pin%d' % index] = name

      for element in component.entities:
         element_name = element.entities [0].value
         if element_name in ['gr_text']:
            element_text = element.entities [1].value
            if element_text in name_map:
               element.entities [1].value = name_map [element_text]

      return component


   #--------------------------------------------------------------------------

   def relink_pads (self, component, control):
      name_map = {}
      if control.is_pin_single:
         name_map ['Net-(Pin0-Pad1)'] = 'Net-(%s-Pad1)' % control.pin.name
      else:
         names = control.pins.names
         for index, name in enumerate (names):
            name_map ['Net-(Pin%d-Pad1)' % index] = 'Net-(%s-Pad1)' % name

      if control.cascade_from is not None:
         name_map ['Net-(Cascade0-Pad1)'] = 'Net-(%s-Pad1)' % control.cascade_from.reference.pin.name

      for element in component.entities:
         element_name = element.entities [0].value
         if element_name in ['module']:
            self.relink_pad (element, name_map)

      return component


   #--------------------------------------------------------------------------

   def relink_pad (self, element, name_map):
      for property in element.entities:
         if isinstance (property, s_expression.List) \
            and property.entities [0].value == 'pad':
            self.relink_pad_net (property, name_map)


   #--------------------------------------------------------------------------

   def relink_pad_net (self, element, name_map):
      for property in element.entities:
         if isinstance (property, s_expression.List) \
            and property.entities [0].value == 'net' \
            and property.entities [2].value in name_map:
            property.entities [2].value = name_map [property.entities [2].value]
            property.entities [1].value = self.nets [property.entities [2].value]


   #--------------------------------------------------------------------------

   def rename_cascade (self, component, cascade_index):
      for element in component.entities:
         element_name = element.entities [0].value
         if element_name in ['gr_text']:
            element_text = element.entities [1].value
            if element_text == 'cascade':
               element.entities [1].value = 'K%d' % (cascade_index + 1)

      return component


   #--------------------------------------------------------------------------

   def move (self, component, position):
      for element in component.entities:
         pass
         element_name = element.entities [0].value
         if element_name in ['module', 'gr_text']:
            self.move_at (element, position)
         elif element_name == 'segment':
            self.move_segment (element, position)
      return component


   #--------------------------------------------------------------------------

   def move_at (self, element, position):
      for property in element.entities:
         if isinstance (property, s_expression.List) \
            and property.entities [0].value == 'at':
            x = float (property.entities [1].value) + position.x.mm
            y = float (property.entities [2].value) + position.y.mm
            property.entities [1] = s_expression.FloatLiteral (x)
            property.entities [2] = s_expression.FloatLiteral (y)


   #--------------------------------------------------------------------------

   def move_segment (self, element, position):
      for property in element.entities:
         if isinstance (property, s_expression.List) \
            and property.entities [0].value in ['start', 'end']:
            x = float (property.entities [1].value) + position.x.mm
            y = float (property.entities [2].value) + position.y.mm
            property.entities [1] = s_expression.FloatLiteral (x)
            property.entities [2] = s_expression.FloatLiteral (y)


