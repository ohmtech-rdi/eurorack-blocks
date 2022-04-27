##############################################################################
#
#     bom.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
import subprocess
from . import s_expression


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')


class Bom:

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):

      for generator in module.manufacturer_data ['generators']:
         if generator ['id'] == 'front_pcb/bom':
            generator_args = generator ['args']

      line_format = generator_args ['line_format']
      header_map = generator_args ['header_map']
      include_non_empty = generator_args ['include_non_empty']
      projection = generator_args ['projection']

      field_names = [e for e in header_map if e not in ['references', 'quantity']]

      path_net = os.path.join (path, '%s.net' % module.name)
      parts = self.load_net (path_net, field_names, include_non_empty, projection)

      bom = line_format.format (**header_map)

      for part in parts:
         bom += line_format.format (**part)

      path_bom = os.path.join (path, '%s.bom.csv' % module.name)

      with open (path_bom, 'w', encoding='utf-8') as file:
         file.write (bom)


   #--------------------------------------------------------------------------

   def load_net (self, path_net, field_names, include_non_empty, projection):

      key_quantity_map = {}
      def inc_key (key):
         if key in key_quantity_map:
            key_quantity_map [key] += 1
         else:
            key_quantity_map [key] = 1

      key_references_map = {}
      def inc_reference (key, reference):
         if key in key_references_map:
            key_references_map [key].append (reference)
         else:
            key_references_map [key] = [reference]

      key_desc_map = {}

      with open (path_net, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      export_node = parser.parse (content, 'net')

      # in export:components
      # check for comp:fields:field:name:Dist if not empty
      # use field:name:DistPartNumber for quantity count

      components_node = export_node.first_kind ('components')
      comp_nodes = components_node.filter_kind ('comp')
      for comp_node in comp_nodes:
         reference = comp_node.property ('ref')
         fields_node = comp_node.first_kind ('fields')
         if fields_node != None:
            field_nodes = fields_node.filter_kind ('field')
            fields = {}
            for field_name in field_names:
               field_value = ''
               for field_node in field_nodes:
                  if field_node.property ('name') == field_name:
                     field_value = field_node.entities [2].value
               fields [field_name] = field_value

            if include_non_empty.format (**fields):
               key = projection.format (**fields)
               inc_key (key)
               inc_reference (key, reference)
               key_desc_map [key] = fields

      parts = []

      for key, quantity in key_quantity_map.items ():
         references = key_references_map [key]
         part = {
            'references': ', '.join (references),
            'quantity': quantity,
         }
         part.update (key_desc_map [key])
         desc = key_desc_map [key]
         parts.append (part)

      return parts
