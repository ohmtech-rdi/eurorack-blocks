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

      path_net = os.path.join (path, '%s.net' % module.name)
      parts = self.load_net (path_net)

      line_format = '{references};{description};{remarks};{quantity};{distributor};{part_number};{url}\n'

      header = {
         'references': 'Reference',
         'description': 'Description',
         'remarks': 'Remarks',
         'distributor': 'Distributor',
         'part_number': 'Distributor Part Number',
         'url': 'Distributor Part URL',
         'quantity': 'Quantity'
      }

      bom = line_format.format (**header)

      for part in parts:
         bom += line_format.format (**part)

      path_bom = os.path.join (path, '%s.bom.csv' % module.name)

      with open (path_bom, 'w', encoding='utf-8') as file:
         file.write (bom)


   #--------------------------------------------------------------------------

   def load_net (self, path_net):

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
            dist = None
            dist_part_number = ''
            remarks = ''
            for field_node in field_nodes:
               if field_node.property ('name') == 'Description':
                  description = field_node.entities [2].value
               elif field_node.property ('name') == 'Dist':
                  dist = field_node.entities [2].value
               elif field_node.property ('name') == 'DistLink':
                  dist_link = field_node.entities [2].value
               elif field_node.property ('name') == 'DistPartNumber':
                  dist_part_number = field_node.entities [2].value
               elif field_node.property ('name') == 'Remarks':
                  remarks = field_node.entities [2].value
            if dist != None:
               key = ' - '.join ([dist_part_number, description])
               inc_key (key)
               inc_reference (key, reference)
               key_desc_map [key] = {
                  'description': description,
                  'remarks': remarks,
                  'dist': dist,
                  'dist_link': dist_link,
                  'dist_part_number': dist_part_number,
               }

      parts = []

      for key, quantity in key_quantity_map.items ():
         desc = key_desc_map [key]
         references = key_references_map [key]
         part = {
            'description': desc ['description'],
            'remarks': desc ['remarks'],
            'distributor': desc ['dist'],
            'part_number': desc ['dist_part_number'],
            'url': desc ['dist_link'],
            'quantity': quantity,
            'references': ', '.join (references)
         }
         parts.append (part)

      return parts
