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
from ..kicad import pcb


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

      centroid = self.make_centroid (module.pcb, module.sch_symbols, line_format, header_map, layer_map, mounting_key, mounting_value)

      path_centroid = os.path.join (path, '%s.centroid.csv' % module.name)

      with open (path_centroid, 'w', encoding='utf-8') as file:
         file.write (centroid)


   #--------------------------------------------------------------------------

   def make_centroid (self, pcb, symbols, line_format, header_map, layer_map, mounting_key, mounting_value):

      left, bottom = self.find_left_bottom (pcb)
      parts_pcb = self.make_pcb_parts (pcb, left, bottom, layer_map)

      field_names = [e for e in header_map if e not in ['x', 'y', 'layer', 'rotation']]
      parts_sch = self.make_sch_parts (symbols, field_names, mounting_key, mounting_value)

      parts = []
      for part in parts_pcb:
         if part in parts_sch:
            dict = parts_pcb [part]
            dict.update (parts_sch [part])
            parts.append (dict)

      centroid = line_format.format (**header_map)

      for part in parts:
         centroid += line_format.format (**part)

      return centroid


   #--------------------------------------------------------------------------
   # Find the left bottom point in the cutting layer, as coordinates
   # are oriented up.

   def find_left_bottom (self, module_pcb):

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

      for gr_shape in module_pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrLine) and gr_shape.layer == 'Edge.Cuts':
            left = gr_min (left, gr_shape.start.x)
            bottom = gr_max (left, gr_shape.start.y)
            left = gr_min (left, gr_shape.end.x)
            bottom = gr_max (bottom, gr_shape.end.y)

      return (left, bottom)


   #--------------------------------------------------------------------------

   def make_pcb_parts (self, pcb, left, bottom, layer_map):

      parts = {}

      for footprint in pcb.footprints:
         if footprint.layer == 'F.Cu':
            layer = layer_map ['top']
         elif footprint.layer == 'B.Cu':
            layer = layer_map ['bottom']
         else:
            assert False

         x = footprint.at.x - left
         y = bottom - footprint.at.y
         rotation = footprint.at.rotation if footprint.at.rotation else 0
         parts [footprint.reference] = {
            'layer': layer,
            'x': x,
            'y': y,
            'rotation': rotation
         }

      return parts


   #--------------------------------------------------------------------------

   def make_sch_parts (self, symbols, field_names, mounting_key, mounting_value):

      parts = {}

      for symbol in symbols:
         reference = symbol.property ('Reference')
         fields = {}
         for field_name in field_names:
            fields [field_name] = symbol.property (field_name)
         place = symbol.property (mounting_key) == mounting_value
         if place:
            parts [reference] = fields

      return parts
