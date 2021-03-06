##############################################################################
#
#     kicad_pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
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

      for control in module.controls:
         self.generate_control (control)

      writer = s_expression.Writer ()
      writer.write (self.base, path_pcb)


   #--------------------------------------------------------------------------

   def generate_control (self, control):
      if control.style.is_alpha_9mm:
         component = self.load_component (os.path.join (PATH_THIS, 'alpha.9mm', 'alpha.9mm.kicad_pcb'))

      elif control.style.is_songhuei_9mm:
         component = self.load_component (os.path.join (PATH_THIS, 'songhuei.9mm', 'songhuei.9mm.kicad_pcb'))

      elif control.style.is_thonk_pj398sm:
         component = self.load_component (os.path.join (PATH_THIS, 'thonk.pj398sm', 'thonk.pj398sm.kicad_pcb'))

      component = self.move (component, control.position)
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
            and node.entities [0].value in ['version', 'host', 'general', 'page', 'layers', 'setup', 'net', 'net_class']:
            return False
         return True

      component = self.load (path)
      component.entities = list (filter (filter_func, component.entities))

      self.remove_net_recursive (component)

      return component


   #--------------------------------------------------------------------------

   def remove_net_recursive (self, node):
      def filter_func (node):
         if isinstance (node, s_expression.List) and node.entities \
            and isinstance (node.entities [0], s_expression.Symbol) \
            and node.entities [0].value == 'net':
            return False
         return True

      for element in node.entities:
         if isinstance (element, s_expression.List):
            element.entities = list (filter (filter_func, element.entities))
            self.remove_net_recursive (element)


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


