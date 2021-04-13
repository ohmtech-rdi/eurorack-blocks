##############################################################################
#
#     parser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from . import ast



class Parser:
   def __init__ (self):
      self.filepath = None


   #--------------------------------------------------------------------------

   def parse (self, input_text, filepath):
      self.filepath = filepath
      dict = eval (input_text)
      return self.parse_root (dict)


   #--------------------------------------------------------------------------

   def parse_root (self, dict):
      node = ast.Root ()

      if 'modules' not in dict:
         raise KeyError ('missing modules')

      modules = dict ['modules']

      if not modules:
         raise KeyError ('missing modules')

      for module in modules:
         node.modules.append (self.parse_module (module))

      return node


   #--------------------------------------------------------------------------

   def parse_module (self, dict):
      node = ast.Module ()

      if 'name' not in dict:
         raise KeyError ('missing module name')
      node.name = dict.get ('name')

      if 'width' not in dict:
         raise KeyError ('missing module width')
      node.width = self.to_mm (dict ['width'])

      node.material = self.parse_material (dict.get ('material'))

      node.header = self.parse_header (dict.get ('header'))
      node.footer = self.parse_footer (dict.get ('footer'))

      node.images = self.parse_images (dict.get ('images'))
      node.labels = self.parse_labels (dict.get ('labels'))
      node.lines = self.parse_lines (dict.get ('lines'))

      if 'controls' not in dict:
         raise KeyError ('missing controls')

      controls = dict ['controls']

      if not controls:
         raise KeyError ('missing controls')

      for control in controls:
         node.controls.append (self.parse_control (control))

      return node


   #--------------------------------------------------------------------------

   def parse_material (self, dict):
      node = ast.Material ()

      if not dict:
         return node # return default

      if 'name' not in dict:
         raise KeyError ('missing material name')

      node.name = dict ['name']

      if 'color' in dict:
         node.color = dict ['color']

      return node


   #--------------------------------------------------------------------------

   def parse_header (self, dict):
      node = ast.Header ()

      if not dict:
         return node # return default

      node.labels = self.parse_labels (dict.get ('labels'))
      node.images = self.parse_images (dict.get ('images'))

      return node


   #--------------------------------------------------------------------------

   def parse_footer (self, dict):
      node = ast.Footer ()

      if not dict:
         return node # return default

      node.labels = self.parse_labels (dict.get ('labels'))
      node.images = self.parse_images (dict.get ('images'))

      return node


   #--------------------------------------------------------------------------

   def parse_control (self, dict):
      node = ast.Control ()

      if 'type' not in dict:
         raise KeyError ('missing control type')

      node.type = dict ['type']

      if 'property' not in dict:
         raise KeyError ('missing control property')
      node.property = dict ['property']

      if 'position' not in dict:
         raise KeyError ('missing control position')
      node.position = self.parse_position (dict ['position'])

      if 'style' not in dict:
         raise KeyError ('missing control style')
      node.style.value = dict ['style']

      node.rotation = self.to_angle_degree (dict.get ('rotation'))

      node.labels = self.parse_labels (dict.get ('labels'))

      return node


   #--------------------------------------------------------------------------

   def parse_labels (self, arr):
      node = []

      if not arr:
         return node # return default

      for label in arr:
         node.append (self.parse_label (label))

      return node


   #--------------------------------------------------------------------------

   def parse_label (self, dict):
      node = ast.Label ()

      if 'text' not in dict:
         raise KeyError ('missing label text')

      node.text = dict ['text']

      node.font = self.parse_font (dict.get ('font'))

      if 'positioning' in dict:
         node.positioning.value = dict ['positioning']

      node.position = self.parse_position (dict.get ('position'))

      if 'offset' in dict:
         node.offset = self.parse_offset (dict ['offset'])

      return node


   #--------------------------------------------------------------------------

   def parse_font (self, dict):
      node = ast.Font ()

      if not dict:
         return None # return None

      if 'family' not in dict:
         raise KeyError ('missing font family')

      node.family = dict ['family']

      if 'size' not in dict:
         raise KeyError ('missing font size')

      size_str = dict ['size']
      unit = val_str [-2:]
      value = val_str [:-2]

      if unit != 'pt':
         raise Exception ('unsupported font size unit %s' % unit)

      node.size = float (value)

      return node


   #--------------------------------------------------------------------------

   def parse_images (self, arr):
      node = []

      if not arr:
         return node # return default

      for image in arr:
         node.append (self.parse_image (image))

      return node


   #--------------------------------------------------------------------------

   def parse_image (self, dict):
      node = ast.Image ()

      if 'file' not in dict:
         raise KeyError ('missing image file')

      node.file = dict ['file']

      return node


   #--------------------------------------------------------------------------

   def parse_lines (self, arr):
      node = []

      if not arr:
         return node # return default

      for line in arr:
         node.append (self.parse_line (line))

      return node


   #--------------------------------------------------------------------------

   def parse_line (self, arr):
      node = ast.Line ()

      for position in arr:
         node.points.append (self.parse_position (position))

      return node


   #--------------------------------------------------------------------------

   def parse_position (self, dict):
      node = ast.Position ()

      if not dict:
         return None # return None

      if 'x' not in dict:
         raise KeyError ('missing position x')
      node.x = self.to_mm (dict ['x'])

      if 'y' not in dict:
         raise KeyError ('missing position y')
      node.y = self.to_mm (dict ['y'])

      return node


   #--------------------------------------------------------------------------

   def parse_offset (self, dict):
      return self.parse_position (dict)


   #--------------------------------------------------------------------------

   def to_mm (self, val_str):
      unit = val_str [-2:]
      value = val_str [:-2]

      if unit == 'mm':
         return float (value)

      elif unit == 'cm':
         return float (value) * 10

      elif unit == 'hp':
         return float (value) * 5.08

      else:
         raise Exception ('unknown unit %s' % unit)


   #--------------------------------------------------------------------------

   def to_angle_degree (self, val_str):
      if not val_str:
         return 0.0 # return default

      if val_str.endswith ('°CCW'):
         value = val_str [:-4]
         return float (value)

      elif val_str.endswith ('°CW'):
         value = val_str [:-3]
         return - float (value)

      else:
         raise Exception ('unknown angle unit in %s' % val_str)
