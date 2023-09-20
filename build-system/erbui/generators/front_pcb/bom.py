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
from ..kicad import sch


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

            file_format = generator_args.get ('file_format', '{module.name}.bom.csv')
            line_format = generator_args ['line_format']
            header_map = generator_args ['header_map']
            include_non_empty = generator_args ['include_non_empty']
            projection = generator_args ['projection']
            excluded_references = module.excluded_references

            bom = self.make_bom (module.sch_symbols, line_format, header_map, include_non_empty, projection, excluded_references)

            filename = file_format.format (module=module)
            path_bom = os.path.join (path, filename)

            with open (path_bom, 'w', encoding='utf-8') as file:
               file.write (bom)


   #--------------------------------------------------------------------------

   def make_bom (self, symbols, line_format, header_map, include_non_empty, projection, excluded_references=set()):

      field_names = [e for e in header_map if e not in ['references', 'quantity']]
      parts = self.make_parts (symbols, field_names, include_non_empty, projection, excluded_references)

      bom = line_format.format (**header_map)

      for part in parts:
         bom += line_format.format (**part)

      return bom


   #--------------------------------------------------------------------------

   def make_parts (self, symbols, field_names, include_non_empty, projection, excluded_references):

      key_quantity_map = {}
      def inc_key (key):
         if key in key_quantity_map:
            key_quantity_map [key] += 1
         else:
            key_quantity_map [key] = 1

      key_references_map = {}
      def inc_reference (key, reference):
         if key in key_references_map:
            key_references_map [key].add (reference)
         else:
            key_references_map [key] = {reference}

      key_desc_map = {}

      for symbol in symbols:
         reference = symbol.property ('Reference')
         if symbol.in_bom and reference and reference not in excluded_references and reference [0] != '#':   # eg. #PWRxxx
            fields = {field_name: symbol.property (field_name) if symbol.property (field_name) is not None else '' for field_name in field_names}
            if include_non_empty.format (**fields):
               key = projection.format (**fields)
               inc_key (key)
               inc_reference (key, reference)
               key_desc_map [key] = fields

      parts = []

      for key, quantity in key_quantity_map.items ():
         references = key_references_map [key]
         part = {
            'references': ', '.join (sorted (references)),
            'quantity': quantity,
         }
         part.update (key_desc_map [key])
         desc = key_desc_map [key]
         parts.append (part)

      return parts
