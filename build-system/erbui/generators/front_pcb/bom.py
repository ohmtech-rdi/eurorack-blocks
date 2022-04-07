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

      parts = self.generate_board (module)
      parts.extend (self.generate_controls (module))

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

   def generate_board (self, module):

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

      with open (module.board.net.path, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      export_node = parser.parse (content, 'kicad_pcb')

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
            for field_node in field_nodes:
               if field_node.property ('name') == 'Description':
                  description = field_node.entities [2].value
               elif field_node.property ('name') == 'Dist':
                  dist = field_node.entities [2].value
               elif field_node.property ('name') == 'DistLink':
                  dist_link = field_node.entities [2].value
               elif field_node.property ('name') == 'DistPartNumber':
                  dist_part_nbr = field_node.entities [2].value
            if dist != None:
               key = dist_part_nbr
               inc_key (key)
               inc_reference (key, reference)
               key_desc_map [key] = {
                  'description': description,
                  'dist': dist,
                  'dist_link': dist_link,
                  'dist_part_nbr': dist_part_nbr,
               }

      parts = []

      for key, quantity in key_quantity_map.items ():
         desc = key_desc_map [key]
         references = key_references_map [key]
         part = {
            'description': desc ['description'],
            'remarks': '',
            'distributor': desc ['dist'],
            'part_number': desc ['dist_part_nbr'],
            'url': desc ['dist_link'],
            'quantity': quantity,
            'references': ', '.join (references)
         }
         parts.append (part)

      return parts


   #--------------------------------------------------------------------------

   def generate_controls (self, module):

      name_quantity_map = {} # control.style.name: quantity

      def inc_part (part_name):
         if part_name in name_quantity_map:
            name_quantity_map [part_name] += 1
         else:
            name_quantity_map [part_name] = 1

      for control in module.controls:
         inc_part (control.style.name)

         if control.style.is_alpha_9mm:
            inc_part ('alpha.9mm')
         elif control.style.is_thonk_pj398sm:
            inc_part ('thonk.pj398sm')
         elif control.style.is_tl1105:
            inc_part ('1rblk') # button cap

      parts = []

      for name, quantity in name_quantity_map.items ():
         func_name = 'generate_%s' % name.replace ('.', '_')
         part = getattr (self, func_name)()
         part ['quantity'] = quantity
         part ['references'] = ''
         if 'remarks' not in part:
            part ['remarks'] = ''
         parts.append (part)

      return parts


   #--------------------------------------------------------------------------

   def generate_alpha_9mm (self):
      return {
         'description': 'B100K - D shaft - Alpha Vertical 9mm Potentiometer',
         'remarks': 'Choose 50K or 10K if 100K is not available',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/alpha-9mm-pots-dshaft/',
      }

   def generate_songhuei_9mm (self):
      return {
         'description': 'B100K (or 50K or 10K) - Song Huei TALL Trimmer Potentiometer',
         'remarks': 'Choose 50K or 10K if 100K is not available',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/ttpots/',
      }

   #--------------------------------------------------------------------------

   def generate_thonk_pj398sm (self):
      return {
         'description': 'Thonkiconn Mono 3.5mm Audio Jacks (PJ398SM)',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/thonkiconn/',
      }

   def generate_thonk_pj398sm_knurled (self):
      return {
         'description': 'Knurled Nuts',
         'remarks': 'One nut bag contains already 50 pieces',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/thonkiconn/',
      }

   def generate_thonk_pj398sm_hex (self):
      return {
         'description': 'Hex Nuts',
         'remarks': 'One nut bag contains already 50 pieces',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/thonkiconn/',
      }

   #--------------------------------------------------------------------------

   def generate_rogan_6ps (self):
      return {
         'description': '6PS - X-Large Pointer (D Shaft) - Rogan PT Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_5ps (self):
      return {
         'description': '5PS - Larger Pointer (D Shaft) - Rogan PT Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_3ps (self):
      return {
         'description': '3PS - Large Pointer (D Shaft) - Rogan PT Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_2ps (self):
      return {
         'description': '2PS - Medium Pointer (D Shaft) - Rogan PT Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_2s_black (self):
      return {
         'description': '2S - Medium Encoder BLACK (D Shaft) - Rogan PT Plastic Knob',
         'remarks': 'Choose Black',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_1ps (self):
      return {
         'description': '1PS - Small Pointer (D Shaft) - Rogan PT Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_1s (self):
      return {
         'description': '1S - Small Encoder WHITE (D Shaft) - Rogan PT Plastic Knob',
         'remarks': 'Choose white',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   def generate_rogan_1s_black (self):
      return {
         'description': '1S - Small Encoder BLACK (D Shaft) - Rogan PT Plastic Knob',
         'remarks': 'Choose black',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/',
      }

   #--------------------------------------------------------------------------

   def generate_sifam_dbn151_white (self):
      return {
         'description': 'White Large Skirt D - Sifam Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/intellijel-white-knobs/',
      }

   def generate_sifam_drn111_white (self):
      return {
         'description': 'White Small Skirt D - Sifam Plastic Knob',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/intellijel-white-knobs/',
      }

   #--------------------------------------------------------------------------

   def generate_dailywell_2ms1 (self):
      return {
         'description': 'DW1 - SPDT ON-ON - Dailywell Sub-mini Toggle Switch',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/sub-mini-toggle-switches/',
      }

   def generate_dailywell_2ms3 (self):
      return {
         'description': 'DW2 - SPDT ON-OFF-ON - Dailywell Sub-mini Toggle Switch',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/sub-mini-toggle-switches/',
      }

   #--------------------------------------------------------------------------

   def generate_ck_d6r_black (self):
      return {
         'description': 'C&K TACTILE SWITCH',
         'remarks': 'Choose black',
         'distributor': 'Thonk',
         'part_number': '',
         'url': 'https://www.thonk.co.uk/shop/radio-music-switch/',
      }

   #--------------------------------------------------------------------------

   def generate_tl1105 (self):
      return {
         'description': 'SWITCH TACTILE SPST-NO 0.05A 12V',
         'distributor': 'Digikey',
         'part_number': 'EG1862-ND',
         'url': 'https://www.digikey.com/en/products/detail/e-switch/TL1105SPF250Q/271559',
      }

   def generate_1rblk (self):
      return {
         'description': 'CAP PUSHBUTTON ROUND BLACK',
         'distributor': 'Digikey',
         'part_number': 'EG1882-ND',
         'url': 'https://www.digikey.com/en/products/detail/e-switch/1RBLK/271579',
      }

   #--------------------------------------------------------------------------

   def generate_led_3mm_red (self):
      return {
         'description': 'LED RED DIFFUSED T-1 T/H',
         'distributor': 'Digikey',
         'part_number': '754-1606-ND',
         'url': 'https://www.digikey.com/en/products/detail/kingbright/WP710A10ID/2769809',
      }

   def generate_led_3mm_green (self):
      return {
         'description': 'LED GREEN DIFFUSED T-1 T/H',
         'distributor': 'Digikey',
         'part_number': '754-1603-ND',
         'url': 'https://www.digikey.com/en/products/detail/kingbright/WP710A10GD/2769808',
      }

   def generate_led_3mm_yellow (self):
      return {
         'description': 'LED YELLOW DIFFUSED T-1 T/H',
         'distributor': 'Digikey',
         'part_number': '754-1602-ND',
         'url': 'https://www.digikey.com/en/products/detail/kingbright/WP710A10YD/2769824',
      }

   def generate_led_3mm_orange (self):
      return {
         'description': 'LED ORANGE DIFFUSED T-1 T/H',
         'distributor': 'Digikey',
         'part_number': '754-1892-ND',
         'url': 'https://www.digikey.com/en/products/detail/kingbright/WP710A10ND/3084190',
      }

   def generate_led_3mm_green_red (self):
      return {
         'description': 'LED GREEN/RED DIFFUSED T-1 T/H',
         'distributor': 'Digikey',
         'part_number': '754-1221-ND',
         'url': 'https://www.digikey.com/en/products/detail/kingbright/WP3VEGW/1747620',
      }


   #--------------------------------------------------------------------------

   def load (self, path):
      with open (path, 'r', encoding='utf-8') as file:
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



