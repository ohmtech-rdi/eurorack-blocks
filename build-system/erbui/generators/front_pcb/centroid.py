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

            file_format = generator_args.get ('file_format', '{module.name}.centroid.csv')
            line_format = generator_args ['line_format']
            header_map = generator_args ['header_map']
            layer_map = generator_args ['layer_map']
            mounting_key = generator_args ['mounting_key']
            mounting_value = generator_args ['mounting_value']
            distance_format = generator_args ['distance_format']

            centroid = self.make_centroid (generator_args, module.pcb, module.sch_symbols)

            filename = file_format.format (module=module)
            path_centroid = os.path.join (path, filename)

            with open (path_centroid, 'w', encoding='utf-8') as file:
               file.write (centroid)


   #--------------------------------------------------------------------------

   def make_centroid (self, args, pcb, symbols):
      line_format = args ['line_format']
      header_map = args ['header_map']

      field_names = [e for e in header_map if e not in ['x', 'y', 'layer', 'rotation']]
      field_names.append ('ReelRotation')
      parts_sch = self.make_sch_parts (args, symbols, field_names)

      origin_x, origin_y = self.find_origin (args, pcb)
      parts_pcb = self.make_pcb_parts (args, pcb, origin_x, origin_y, parts_sch)

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
   # Find the corner point in the cutting layer.

   def find_origin (self, args, module_pcb):

      origin_name = args ['position']['origin']
      if origin_name == 'absolute':
         return (0, 0)  # no need for corner detection

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
      top = None
      right = None
      bottom = None

      for gr_shape in module_pcb.gr_shapes:
         if isinstance (gr_shape, pcb.GrLine) and gr_shape.layer == 'Edge.Cuts':
            left = gr_min (left, min (gr_shape.start.x, gr_shape.end.x))
            top = gr_min (top, min (gr_shape.start.y, gr_shape.end.y))
            right = gr_max (right, max (gr_shape.start.x, gr_shape.end.x))
            bottom = gr_max (bottom, max (gr_shape.start.y, gr_shape.end.y))

      if origin_name == 'corner-left-top':
         return (left, top)

      elif origin_name == 'corner-left-bottom':
         return (left, bottom)

      else:
         raise Exception ('unsupported position origin "%s"' % origin_name)


   #--------------------------------------------------------------------------

   def make_pcb_parts (self, args, pcb, origin_x, origin_y, parts_sch):

      layer_map = args ['layer_map']
      distance_format = args ['distance_format']
      position_y_axis_orientation = args ['position']['y_axis_orientation']
      rotation_y_axis_orientation = args ['rotation']['y_axis_orientation']
      rotation_zero = args ['rotation']['zero']
      rotation_range_min = int (args ['rotation']['range']['min'])
      rotation_range_max = int (args ['rotation']['range']['max'])

      if position_y_axis_orientation == 'upward':
         y_mul = -1
      elif position_y_axis_orientation == 'downward':
         y_mul = 1
      else:
         raise Exception ('unsupported y_axis_orientation "%s"' % position_y_axis_orientation)

      if rotation_y_axis_orientation == 'upward':
         rot_mul = 1
      elif rotation_y_axis_orientation == 'downward':
         rot_mul = -1
      else:
         raise Exception ('unsupported y_axis_orientation "%s"' % position_y_axis_orientation)

      if rotation_zero == 'native':
         rot_mul_offset = 0
      elif rotation_zero == 'reel':
         rot_mul_offset = 1
      else:
         raise Exception ('unsupported y_axis_orientation "%s"' % position_y_axis_orientation)

      parts = {}

      for footprint in pcb.footprints:
         rot_orientation = 1
         if footprint.layer == 'F.Cu':
            layer = layer_map ['top']
            rot_orientation = 1
         elif footprint.layer == 'B.Cu':
            layer = layer_map ['bottom']
            rot_orientation = -1
         else:
            assert False

         reel_rotation = 0
         if footprint.reference in parts_sch:
            reel_rotation_str = parts_sch [footprint.reference]['ReelRotation']
            if reel_rotation_str is not None:
               reel_rotation = int (reel_rotation_str)

         x = footprint.at.x - origin_x
         y = (footprint.at.y - origin_y) * y_mul
         rotation = footprint.at.rotation if footprint.at.rotation else 0
         rotation -= reel_rotation * rot_mul_offset
         rotation *= rot_mul * rot_orientation
         if rotation < rotation_range_min:
            rotation += 360
         if rotation > rotation_range_max:
            rotation -= 360

         parts [footprint.reference] = {
            'layer': layer,
            'x': distance_format.format (distance = x),
            'y': distance_format.format (distance = y),
            'rotation': rotation
         }

      return parts


   #--------------------------------------------------------------------------

   def make_sch_parts (self, args, symbols, field_names):

      mounting_key = args ['mounting_key']
      mounting_value = args ['mounting_value']

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
