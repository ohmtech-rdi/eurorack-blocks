##############################################################################
#
#     centroid.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
import subprocess
from . import s_expression


class Centroid:

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      for generator in module.manufacturer_data ['generators']:
         if generator ['id'] == 'front_pcb/centroid':
            generator_args = generator ['args']

      line_format = generator_args ['line_format']
      header_map = generator_args ['header_map']
      layer_map = generator_args ['layer_map']
      mounting_key = generator_args ['mounting_key']
      mounting_value = generator_args ['mounting_value']

      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)
      path_net = os.path.join (path, '%s.net' % module.name)

      left, bottom = self.find_left_bottom (module)
      parts_pcb = self.load_pcb (path_pcb, left, bottom)

      field_names = [e for e in header_map if e not in ['x', 'y', 'layer', 'rotation']]
      parts_net = self.load_net (path_net, field_names, mounting_key, mounting_value)

      parts = []
      for part in parts_pcb:
         if part in parts_net:
            dict = parts_pcb [part]
            dict.update (parts_net [part])
            parts.append (dict)

      centroid = line_format.format (**header_map)

      for part in parts:
         centroid += line_format.format (**part)

      path_centroid = os.path.join (path, '%s.centroid.csv' % module.name)

      with open (path_centroid, 'w', encoding='utf-8') as file:
         file.write (centroid)


   #--------------------------------------------------------------------------

   def find_left_bottom (self, module):

      def gr_min (cur, new):
         if cur is None:
            return new
         else:
            return min (cur, new)

      def gr_max (cur, new):
         if cur is None:
            return new
         else:
            return max (cur, new)

      left = None
      bottom = None

      with open (module.board.pcb.path, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      root_node = parser.parse (content, 'kicad_pcb')

      gr_line_nodes = root_node.filter_kind ('gr_line')

      for gr_line_node in gr_line_nodes:
         layer_node = gr_line_node.first_kind ('layer')
         layer_node_value = layer_node.entities [1].value
         if layer_node_value == 'Edge.Cuts':
            start_node = gr_line_node.first_kind ('start')
            x = start_node.entities [1].value
            y = start_node.entities [2].value
            left = gr_min (left, x)
            bottom = gr_max (bottom, y)

            end_node = gr_line_node.first_kind ('end')
            x = end_node.entities [1].value
            y = end_node.entities [2].value
            left = gr_min (left, x)
            bottom = gr_max (bottom, y)

      return (left, bottom)


   #--------------------------------------------------------------------------

   def load_pcb (self, path_pcb, left, bottom):
      with open (path_pcb, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      root_node = parser.parse (content, 'kicad_pcb')

      parts = {}

      for module in root_node.filter_kind ('module'):
         layer = module.property ('layer')
         if layer == 'F.Cu':
            layer = 'top'
         elif layer == 'B.Cu':
            layer = 'bottom'
         else:
            assert False
         at_node = module.first_kind ('at')
         x = float (at_node.entities [1].value) - left
         y = bottom - float (at_node.entities [2].value)
         rotation = float (at_node.entities [3].value) if len (at_node.entities) == 4 else 0
         fp_text_nodes = module.filter_kind ('fp_text')
         reference = None
         for fp_text_node in fp_text_nodes:
            if fp_text_node.entities [1].value == 'reference':
               reference = fp_text_node.entities [2].value
         parts [reference] = {
            'layer': layer,
            'x': x,
            'y': y,
            'rotation': rotation
         }

      return parts


   #--------------------------------------------------------------------------

   def load_net (self, path_net, field_names, mounting_key, mounting_value):

      with open (path_net, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      export_node = parser.parse (content, 'net')

      parts = {}

      components_node = export_node.first_kind ('components')
      comp_nodes = components_node.filter_kind ('comp')
      for comp_node in comp_nodes:
         reference = comp_node.property ('ref')
         fields_node = comp_node.first_kind ('fields')
         if fields_node != None:
            field_nodes = fields_node.filter_kind ('field')
            fields = {}
            place = False
            for field_name in field_names:
               field_value = ''
               for field_node in field_nodes:
                  if field_node.property ('name') == field_name:
                     field_value = field_node.entities [2].value
                  if field_node.property ('name') == mounting_key:
                     place = field_node.entities [2].value == mounting_value
               fields [field_name] = field_value

            if place:
               parts [reference]= fields

      return parts
