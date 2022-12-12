##############################################################################
#
#     sch.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
from . import s_expression

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



# -- Root --------------------------------------------------------------------

class Root:
   def __init__ (self):
      self.version = None
      self.generator = None
      self.uuid = None
      self.paper = None
      self.lib_symbols = []
      self.junctions = []
      self.wires = []
      self.global_labels = []
      self.symbols = []
      self.sheets = []
      self.sheet_instances = []
      self.symbol_instances = []

   @staticmethod
   def read (filepath):
      with open (filepath, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      root_node = parser.parse (content, filepath)

      return Root.parse (root_node)

   @staticmethod
   def parse (node):
      if not node: return None

      root = Root ()
      root.version = node.property ('version')
      root.generator = node.property ('generator')
      root.uuid = node.property ('uuid')
      root.paper = node.property ('paper')

      for lib_symbol_node in node.first_kind ('lib_symbols').filter_kind ('symbol'):
         root.lib_symbols.append (LibSymbol.parse (lib_symbol_node))

      for junction_node in node.filter_kind ('junction'):
         root.junctions.append (Junction.parse (junction_node))

      for wire_node in node.filter_kind ('wire'):
         root.wires.append (Wire.parse (wire_node))

      for global_label_node in node.filter_kind ('global_label'):
         root.global_labels.append (GlobalLabel.parse (global_label_node))

      for symbol_node in node.filter_kind ('symbol'):
         root.symbols.append (Symbol.parse (symbol_node))

      for sheet_node in node.filter_kind ('sheet'):
         root.sheets.append (Sheet.parse (sheet_node))

      sheet_instances_node = node.first_kind ('sheet_instances')
      if sheet_instances_node:
         for sheet_instance_node in sheet_instances_node.filter_kind ('path'):
            root.sheet_instances.append (SheetInstance.parse (sheet_instance_node))

      symbol_instances_node = node.first_kind ('symbol_instances')
      if symbol_instances_node:
         for symbol_instance_node in symbol_instances_node.filter_kind ('path'):
            root.symbol_instances.append (SymbolInstance.parse (symbol_instance_node))

      return root

   def write (self, filepath):
      root_node = self.generate ()
      writer = s_expression.Writer ()
      writer.write (root_node, filepath)

   def generate (self):
      root_node = s_expression.List.generate ('kicad_sch')
      root_node.add (s_expression.List.generate_property ('version', self.version))
      root_node.add (s_expression.List.generate_property ('generator', self.generator))
      root_node.add (s_expression.List.generate_property ('uuid', self.uuid))
      root_node.add (s_expression.List.generate_property ('paper', self.paper))

      lib_symbols_node = root_node.add (s_expression.List.generate ('lib_symbols'))
      for lib_symbol in self.lib_symbols:
         lib_symbols_node.add (lib_symbol.generate ())

      for junction in self.junctions:
         root_node.add (junction.generate ())

      for wire in self.wires:
         root_node.add (wire.generate ())

      for global_label in self.global_labels:
         root_node.add (global_label.generate ())

      for symbol in self.symbols:
         root_node.add (symbol.generate ())

      for sheet in self.sheets:
         root_node.add (sheet.generate ())

      sheet_instances_node = root_node.add (s_expression.List.generate ('sheet_instances'))
      for sheet_instance in self.sheet_instances:
         sheet_instances_node.add (sheet_instance.generate ())

      symbol_instances_node = root_node.add (s_expression.List.generate ('symbol_instances'))
      for symbol_instance in self.symbol_instances:
         symbol_instances_node.add (symbol_instance.generate ())

      return root_node



# -- At ----------------------------------------------------------------------

class At:
   def __init__ (self):
      self.x = None        # float
      self.y = None        # float
      self.rotation = None # float, degree

   @staticmethod
   def parse (node):
      if not node: return None

      at = At ()
      at.x = node.entities [1].value
      at.y = node.entities [2].value
      at.rotation = node.entities [3].value

      return at

   def generate (self):
      at_node = s_expression.List.generate ('at')
      at_node.add (s_expression.FloatLiteral (self.x))
      at_node.add (s_expression.FloatLiteral (self.y))
      at_node.add (s_expression.FloatLiteral (self.rotation))

      return at_node



# -- Xy ----------------------------------------------------------------------

class Xy:
   def __init__ (self):
      self.x = None        # float
      self.y = None        # float

   @staticmethod
   def parse (node):
      if not node: return None

      xy = Xy ()
      xy.x = node.entities [1].value
      xy.y = node.entities [2].value

      return xy

   def generate (self):
      xy_node = s_expression.List.generate ('xy')
      xy_node.add (s_expression.FloatLiteral (self.x))
      xy_node.add (s_expression.FloatLiteral (self.y))

      return xy_node

   def generate_with_alternate_name (self, name):
      xy_node = s_expression.List.generate (name)
      xy_node.add (s_expression.FloatLiteral (self.x))
      xy_node.add (s_expression.FloatLiteral (self.y))

      return xy_node


# -- Pts ----------------------------------------------------------------------

class Pts:
   def __init__ (self):
      self.items = [] # list of Xy

   @staticmethod
   def parse (node):
      if not node: return None

      pts = Pts ()
      for xy_node in node.filter_kind ('xy'):
         pts.items.append (Xy.parse (xy_node))

      return pts

   def generate (self):
      pts_node = s_expression.List.generate ('pts')
      for xy in self.items:
         pts_node.add (xy.generate ())

      return pts_node


# -- Color -------------------------------------------------------------------

class Color:
   def __init__ (self):
      self.r = None        # int
      self.g = None        # int
      self.b = None        # int
      self.a = None        # float, norm

   @staticmethod
   def parse (node):
      if not node: return None

      color = Color ()
      color.r = node.entities [1].value
      color.g = node.entities [2].value
      color.b = node.entities [3].value
      color.a = node.entities [4].value

      return color

   def generate (self):
      color_node = s_expression.List.generate ('color')
      color_node.add (s_expression.IntegerLiteral (self.r))
      color_node.add (s_expression.IntegerLiteral (self.g))
      color_node.add (s_expression.IntegerLiteral (self.b))
      color_node.add (s_expression.FloatLiteral (self.a))
      return color_node


# -- Stroke ------------------------------------------------------------------

class Stroke:
   def __init__ (self):
      self.width = None # float
      self.type = None  # str, eg. default
      self.color = Color ()

   @staticmethod
   def parse (node):
      if not node: return None

      stroke = Stroke ()
      stroke.width = node.property ('width')
      stroke.type = node.property ('type')
      stroke.color = Color.parse (node.first_kind ('color'))

      return stroke

   def generate (self):
      stroke_node = s_expression.List.generate ('stroke')
      stroke_node.add (s_expression.List.generate_property ('width', self.width))
      stroke_node.add (s_expression.List.generate_property_symbol ('type', self.type))
      stroke_node.add (self.color.generate ())
      return stroke_node


# -- Fill --------------------------------------------------------------------

class Fill:
   def __init__ (self):
      self.type = None  # str, eg. background, none

   @staticmethod
   def parse (node):
      if not node: return None

      fill = Fill ()
      fill.type = node.property ('type')

      return fill

   def generate (self):
      fill_node = s_expression.List.generate ('fill')
      fill_node.add (s_expression.List.generate_property_symbol ('type', self.type))
      return fill_node


# -- Polyline ----------------------------------------------------------------

class Polyline:
   def __init__ (self):
      self.pts = Pts ()
      self.stroke = Stroke ()
      self.fill = Fill ()

   @staticmethod
   def parse (node):
      if not node: return None

      polyline = Polyline ()
      polyline.pts = Pts.parse (node.first_kind ('pts'))
      polyline.stroke = Stroke.parse (node.first_kind ('stroke'))
      polyline.fill = Fill.parse (node.first_kind ('fill'))

      return polyline

   def generate (self):
      polyline_node = s_expression.List.generate ('polyline')
      polyline_node.add (self.pts.generate ())
      polyline_node.add (self.stroke.generate ())
      polyline_node.add (self.fill.generate ())
      return polyline_node



# -- Rectangle ---------------------------------------------------------------

class Rectangle:
   def __init__ (self):
      self.start = Xy ()
      self.end = Xy ()
      self.stroke = Stroke ()
      self.fill = Fill ()

   @staticmethod
   def parse (node):
      if not node: return None

      rectangle = Rectangle ()
      rectangle.start = Xy.parse (node.first_kind ('start'))
      rectangle.end = Xy.parse (node.first_kind ('end'))
      rectangle.stroke = Stroke.parse (node.first_kind ('stroke'))
      rectangle.fill = Fill.parse (node.first_kind ('fill'))

      return rectangle

   def generate (self):
      rectangle_node = s_expression.List.generate ('rectangle')
      rectangle_node.add (self.start.generate_with_alternate_name ('start'))
      rectangle_node.add (self.end.generate_with_alternate_name ('end'))
      rectangle_node.add (self.stroke.generate ())
      rectangle_node.add (self.fill.generate ())
      return rectangle_node


# -- Circle ------------------------------------------------------------------

class Circle:
   def __init__ (self):
      self.center = Xy ()
      self.radius = None   # float
      self.stroke = Stroke ()
      self.fill = Fill ()

   @staticmethod
   def parse (node):
      if not node: return None

      circle = Circle ()
      circle.center = Xy.parse (node.first_kind ('center'))
      circle.radius = node.property ('radius')
      circle.stroke = Stroke.parse (node.first_kind ('stroke'))
      circle.fill = Fill.parse (node.first_kind ('fill'))

      return circle

   def generate (self):
      circle_node = s_expression.List.generate ('circle')
      circle_node.add (self.center.generate_with_alternate_name ('center'))
      circle_node.add (s_expression.List.generate_property ('radius', self.radius))
      circle_node.add (self.stroke.generate ())
      circle_node.add (self.fill.generate ())
      return circle_node


# -- Effects -----------------------------------------------------------------

class Effects:
   def __init__ (self):
      self.font = Effects.Font ()
      self.justify = None   # str eg. 'left'
      self.hide = None      # boolean

   @staticmethod
   def parse (node):
      if not node: return None

      effects = Effects ()
      effects.font = Effects.Font.parse (node.first_kind ('font'))
      effects.justify = node.property ('justify')
      effects.hide = any (e.is_symbol and e.value == 'hide' for e in node.entities)

      return effects

   def generate (self):
      effects_node = s_expression.List.generate ('effects')
      effects_node.add (self.font.generate ())
      if self.justify:
         effects_node.add (s_expression.List.generate_property_symbol ('justify', self.justify))
      if self.hide:
         effects_node.add (s_expression.Symbol ('hide'))
      return effects_node


   class Font:
      def __init__ (self):
         self.size = None   # float, mm, written for both x,y

      @staticmethod
      def parse (node):
         if not node: return None

         font = Effects.Font ()
         font.size = node.property ('size')

         return font

      def generate (self):
         font_node = s_expression.List.generate ('font')
         size_node = font_node.add (s_expression.List.generate ('size'))
         size_node.add (s_expression.FloatLiteral (self.size))
         size_node.add (s_expression.FloatLiteral (self.size)) # twice
         return font_node


# -- Property ----------------------------------------------------------------

class Property:
   def __init__ (self):
      self.name = None  # str
      self.value = None # str
      self.id = None    # int
      self.at = At ()
      self.effects = None

   @staticmethod
   def parse (node):
      if not node: return None

      property = Property ()
      property.name = node.entities [1].value
      property.value = node.entities [2].value
      property.id = node.property ('id')
      property.at = At.parse (node.first_kind ('at'))
      property.effects = Effects.parse (node.first_kind ('effects'))

      return property

   def generate (self):
      property_node = s_expression.List.generate ('property')
      property_node.add (s_expression.StringLiteral (self.name))
      property_node.add (s_expression.StringLiteral (self.value))
      property_node.add (s_expression.List.generate_property ('id', self.id))
      property_node.add (self.at.generate ())
      if self.effects:
         property_node.add (self.effects.generate ())
      return property_node


# -- LibSymbol ---------------------------------------------------------------

class LibSymbol:
   def __init__ (self):
      self.name = None     # str
      self.power = None    # None or something
      self.pin_names = LibSymbol.PinNames ()
      self.in_bom = None   # boolean
      self.on_board = None # boolean
      self.properties = []
      self.symbols = []

   @staticmethod
   def parse (node):
      if not node: return None

      lib_symbol = LibSymbol ()
      lib_symbol.name = node.entities [1].value
      lib_symbol.power = node.first_kind ('power')
      lib_symbol.in_bom = node.property ('in_bom') == 'yes'
      lib_symbol.on_board = node.property ('on_board') == 'yes'

      lib_symbol.pin_names = LibSymbol.PinNames.parse (node.first_kind ('pin_names'))

      for property_node in node.filter_kind ('property'):
         lib_symbol.properties.append (Property.parse (property_node))

      for symbol_node in node.filter_kind ('symbol'):
         lib_symbol.symbols.append (LibSymbol.Symbol.parse (symbol_node))

      return lib_symbol

   def generate (self):
      lib_symbol_node = s_expression.List.generate ('symbol')
      lib_symbol_node.add (s_expression.StringLiteral (self.name))
      if self.power:
         lib_symbol_node.add (s_expression.List.generate ('power'))
      lib_symbol_node.add (self.pin_names.generate ())
      lib_symbol_node.add (s_expression.List.generate_property_symbol ('in_bom', 'yes' if self.in_bom else 'no'))
      lib_symbol_node.add (s_expression.List.generate_property_symbol ('on_board', 'yes' if self.on_board else 'no'))
      for property in self.properties:
         lib_symbol_node.add (property.generate ())
      for symbol in self.symbols:
         lib_symbol_node.add (symbol.generate ())
      return lib_symbol_node

   class PinNames:
      def __init__ (self):
         self.offset = None # float
         self.hide = None   # None or something

      @staticmethod
      def parse (node):
         if not node: return None

         pin_names = LibSymbol.PinNames ()
         pin_names.offset = node.property ('offset')
         pin_names.hide = any (e.is_symbol and e.value == 'hide' for e in node.entities)

         return pin_names

      def generate (self):
         pin_names_node = s_expression.List.generate ('pin_names')
         pin_names_node.add (s_expression.List.generate_property ('offset', self.offset))
         if self.hide:
            pin_names_node.add (s_expression.Symbol ('hide'))
         return pin_names_node

   class Symbol:
      def __init__ (self):
         self.name = None  # str
         self.shapes = []  # list of Rectangle, Cicle or Polyline
         self.pins = []    # list of LibSymbol.Symbol.Pin

      @staticmethod
      def parse (node):
         if not node: return None

         symbol = LibSymbol.Symbol ()
         symbol.name = node.entities [1].value

         for shape_node in node.filter_kinds (['rectangle', 'circle', 'polyline']):
            shape_kind = shape_node.entities [0].value
            if shape_kind == 'rectangle':
               symbol.shapes.append (Rectangle.parse (shape_node))
            elif shape_kind == 'circle':
               symbol.shapes.append (Circle.parse (shape_node))
            elif shape_kind == 'polyline':
               symbol.shapes.append (Polyline.parse (shape_node))
            else:
               assert False

         for pin_node in node.filter_kind ('pin'):
            symbol.pins.append (LibSymbol.Symbol.Pin.parse (pin_node))

         return symbol

      def generate (self):
         symbol_node = s_expression.List.generate ('symbol')
         symbol_node.add (s_expression.StringLiteral (self.name))
         for shape in self.shapes:
            symbol_node.add (shape.generate ())
         for pin in self.pins:
            symbol_node.add (pin.generate ())
         return symbol_node

      class Pin:
         def __init__ (self):
            self.electrical_type = None   # str eg. passive, power_in, etc.
            self.graphic_style = None     # str eg. line
            self.at = At ()
            self.length = None            # float
            self.hide = None              # boolean
            self.name = LibSymbol.Symbol.Pin.Name ()
            self.number = LibSymbol.Symbol.Pin.Number ()

         @staticmethod
         def parse (node):
            if not node: return None

            pin = LibSymbol.Symbol.Pin ()
            pin.electrical_type = node.entities [1].value
            pin.graphic_style = node.entities [2].value
            pin.at = At.parse (node.first_kind ('at'))
            pin.length = node.property ('length')
            pin.hide = any (e.is_symbol and e.value == 'hide' for e in node.entities)
            pin.name = LibSymbol.Symbol.Pin.Name.parse (node.first_kind ('name'))
            pin.number = LibSymbol.Symbol.Pin.Number.parse (node.first_kind ('number'))

            return pin

         def generate (self):
            pin_node = s_expression.List.generate ('pin')
            pin_node.add (s_expression.Symbol (self.electrical_type))
            pin_node.add (s_expression.Symbol (self.graphic_style))
            pin_node.add (self.at.generate ())
            pin_node.add (s_expression.List.generate_property ('length', self.length))
            if self.hide:
               pin_node.add (s_expression.Symbol ('hide'))
            pin_node.add (self.name.generate ())
            pin_node.add (self.number.generate ())
            return pin_node

         class Name:
            def __init__ (self):
               self.value = None   # str eg. ~
               self.effects = Effects ()

            @staticmethod
            def parse (node):
               if not node: return None

               name = LibSymbol.Symbol.Pin.Name ()
               name.value = node.entities [1].value
               name.effects = Effects.parse (node.first_kind ('effects'))

               return name

            def generate (self):
               name_node = s_expression.List.generate ('name')
               name_node.add (s_expression.StringLiteral (self.value))
               name_node.add (self.effects.generate ())
               return name_node

         class Number:
            def __init__ (self):
               self.value = None   # str eg. IN
               self.effects = Effects ()

            @staticmethod
            def parse (node):
               if not node: return None

               number = LibSymbol.Symbol.Pin.Number ()
               number.value = node.entities [1].value
               number.effects = Effects.parse (node.first_kind ('effects'))

               return number

            def generate (self):
               number_node = s_expression.List.generate ('number')
               number_node.add (s_expression.StringLiteral (self.value))
               number_node.add (self.effects.generate ())
               return number_node


# -- Junction ----------------------------------------------------------------

class Junction:
   def __init__ (self):
      self.at = Xy ()
      self.diameter = None # float
      color = Color ()
      self.uuid = None     # str eg. '0241e922-798f-4f95-bb3e-5bdf47696699'

   @staticmethod
   def parse (node):
      if not node: return None

      junction = Junction ()
      junction.at = Xy.parse (node.first_kind ('at'))
      junction.diameter = node.property ('diameter')
      junction.color = Color.parse (node.first_kind ('color'))
      junction.uuid = node.property ('uuid')

      return junction

   def generate (self):
      junction_node = s_expression.List.generate ('junction')
      junction_node.add (self.Xy.generate_with_alternate_name ('at'))
      junction_node.add (s_expression.List.generate_property ('diameter', self.diameter))
      junction_node.add (self.color.generate ())
      junction_node.add (s_expression.List.generate_property ('uuid', self.uuid))
      return junction_node


# -- Wire --------------------------------------------------------------------

class Wire:
   def __init__ (self):
      self.pts = Pts ()
      self.stroke = Stroke ()
      self.uuid = None     # str eg. '0241e922-798f-4f95-bb3e-5bdf47696699'

   @staticmethod
   def parse (node):
      if not node: return None

      wire = Wire ()
      wire.pts = Pts.parse (node.first_kind ('pts'))
      wire.stroke = Stroke.parse (node.first_kind ('stroke'))
      wire.uuid = node.property ('uuid')

      return wire

   def generate (self):
      wire_node = s_expression.List.generate ('wire')
      wire_node.add (self.pts.generate ())
      wire_node.add (self.stroke.generate ())
      wire_node.add (s_expression.List.generate_property ('uuid', self.uuid))
      return wire_node


# -- GlobalLabel -------------------------------------------------------------

class GlobalLabel:
   def __init__ (self):
      self.name = None  # str eg. IN
      self.shape = None # str eg. input
      self.at = At ()
      self.fields_autoplaced = None   # None or something
      self.effects = Effects ()
      self.uuid = None     # str eg. '0241e922-798f-4f95-bb3e-5bdf47696699'
      self.property = Property ()

   @staticmethod
   def parse (node):
      if not node: return None

      global_label = GlobalLabel ()
      global_label.name = node.entities [1].value
      global_label.shape = node.property ('shape')
      global_label.at = At.parse (node.first_kind ('at'))
      global_label.fields_autoplaced = node.first_kind ('fields_autoplaced')
      global_label.effects = Effects.parse (node.first_kind ('effects'))
      global_label.uuid = node.property ('uuid')
      global_label.property = Property.parse (node.first_kind ('property'))

      return global_label

   def generate (self):
      global_label_node = s_expression.List.generate ('global_label')
      global_label_node.add (s_expression.StringLiteral (self.name))
      global_label_node.add (s_expression.List.generate_property_symbol ('shape', self.shape))
      global_label_node.add (self.at.generate ())
      if self.fields_autoplaced:
         global_label_node.add (s_expression.List.generate ('fields_autoplaced'))
      global_label_node.add (self.effects.generate ())
      global_label_node.add (s_expression.List.generate_property ('uuid', self.uuid))
      global_label_node.add (self.property.generate ())
      return global_label_node


# -- Symbol ------------------------------------------------------------------

class Symbol:
   def __init__ (self):
      self.lib_id = None   # str eg. "Device:R_POT"
      self.at = At ()
      self.mirror = None   # str eg. x
      self.unit = None     # integer 1-based
      self.in_bom = None   # boolean
      self.on_board = None # boolean
      self.uuid = None     # str eg. '00000000-0000-0000-0000-00005fcae65b'
      self.properties = []
      self.pins = []

   @staticmethod
   def parse (node):
      if not node: return None

      symbol = Symbol ()
      symbol.lib_id = node.property ('lib_id')
      symbol.at = At.parse (node.first_kind ('at'))
      symbol.mirror = node.property ('mirror')
      symbol.unit = node.property ('unit')
      symbol.in_bom = node.property ('in_bom') == 'yes'
      symbol.on_board = node.property ('on_board') == 'yes'
      symbol.uuid = node.property ('uuid')

      for property_node in node.filter_kind ('property'):
         symbol.properties.append (Property.parse (property_node))

      for pin_node in node.filter_kind ('pin'):
         symbol.pins.append (Symbol.Pin.parse (pin_node))

      return symbol

   def generate (self):
      symbol_node = s_expression.List.generate ('symbol')
      symbol_node.add (s_expression.List.generate_property ('lib_id', '"%s"' % self.lib_id))
      symbol_node.add (self.at.generate ())
      if self.mirror:
         symbol_node.add (s_expression.List.generate_property_symbol ('mirror', self.mirror))
      symbol_node.add (s_expression.List.generate_property ('unit', self.unit))
      symbol_node.add (s_expression.List.generate_property_symbol ('in_bom', 'yes' if self.in_bom else 'no'))
      symbol_node.add (s_expression.List.generate_property_symbol ('on_board', 'yes' if self.on_board else 'no'))
      symbol_node.add (s_expression.List.generate_property ('uuid', self.uuid))
      for property in self.properties:
         symbol_node.add (property.generate ())
      for pin in self.pins:
         symbol_node.add (pin.generate ())
      return symbol_node

   def property (self, name):
      matches = [e for e in self.properties if e.name == name]
      match = next (iter (matches), None)
      return match.value if match else None

   def set_property (self, name, value):
      matches = [e for e in self.properties if e.name == name]
      match = next (iter (matches), None)
      match.value = value

   class Pin:
      def __init__ (self):
         self.name = None  # str eg. 1
         self.uuid = None  # str eg. dbe2d61e-6998-405a-a020-ebdfdb42a92a

      @staticmethod
      def parse (node):
         if not node: return None

         pin = Symbol.Pin ()
         pin.name = node.entities [1].value
         pin.uuid = node.property ('uuid')

         return pin

      def generate (self):
         pin_node = s_expression.List.generate ('pin')
         pin_node.add (s_expression.StringLiteral (self.name))
         pin_node.add (s_expression.List.generate_property ('uuid', self.uuid))
         return pin_node


# -- Sheet -------------------------------------------------------------------

class Sheet:
   def __init__ (self):
      self.at = Xy ()
      self.size = Xy ()
      self.fields_autoplaced = None   # None or something
      self.stroke = Stroke ()
      self.fill = Fill ()
      self.uuid = None     # str eg. '00000000-0000-0000-0000-00005fcae65b'
      self.properties = []
      self.pins = []

   @staticmethod
   def parse (node):
      if not node: return None

      sheet = Sheet ()
      sheet.at = Xy.parse (node.first_kind ('at'))
      sheet.size = Xy.parse (node.first_kind ('size'))
      sheet.fields_autoplaced = node.first_kind ('fields_autoplaced')
      sheet.stroke = Stroke.parse (node.first_kind ('stroke'))
      sheet.fill = Fill.parse (node.first_kind ('fill'))
      sheet.uuid = node.property ('uuid')

      for property_node in node.filter_kind ('property'):
         sheet.properties.append (Property.parse (property_node))

      for pin_node in node.filter_kind ('pin'):
         sheet.pins.append (Sheet.Pin.parse (pin_node))

      return sheet

   def generate (self):
      sheet_node = s_expression.List.generate ('sheet')
      sheet_node.add (self.at.generate_with_alternate_name ('at'))
      sheet_node.add (self.size.generate_with_alternate_name ('size'))
      if self.fields_autoplaced:
         sheet_node.add (s_expression.List.generate ('fields_autoplaced'))
      sheet_node.add (self.stroke.generate ())
      sheet_node.add (self.fill.generate ())
      sheet_node.add (s_expression.List.generate_property ('uuid', self.uuid))
      for property in self.properties:
         sheet_node.add (property.generate ())
      for pin in self.pins:
         sheet_node.add (pin.generate ())
      return sheet_node

   def property (self, name):
      matches = [e for e in self.properties if e.name == name]
      match = next (iter (matches), None)
      return match.value if match else None

   class Pin:
      def __init__ (self):
         self.name = None  # str eg. "GND"
         self.connection_type = None   # symbol eg. output
         self.at = At ()
         self.effects = Effects ()
         self.uuid = None  # str eg. dbe2d61e-6998-405a-a020-ebdfdb42a92a

      @staticmethod
      def parse (node):
         if not node: return None

         pin = Symbol.Pin ()
         pin.name = node.entities [1].value
         pin.connection_type = node.entities [2].value
         pin.at = At.parse (node.first_kind ('at'))
         pin.effects = Effects.parse (node.first_kind ('effects'))
         pin.uuid = node.property ('uuid')

         return pin

      def generate (self):
         pin_node = s_expression.List.generate ('pin')
         pin_node.add (s_expression.StringLiteral (self.name))
         pin_node.add (s_expression.Symbol (self.connection_type))
         pin_node.add (self.at.generate ())
         pin_node.add (self.effects.generate ())
         pin_node.add (s_expression.List.generate_property ('uuid', self.uuid))
         return pin_node


# -- SheetInstance -----------------------------------------------------------

class SheetInstance:
   def __init__ (self):
      self.path = None  # str eg. "/"
      self.page = None  # str eg. "1"

   @staticmethod
   def parse (node):
      if not node: return None

      sheet_instance = SheetInstance ()
      sheet_instance.path = node.entities [1].value
      sheet_instance.page = node.property ('page')

      return sheet_instance

   def generate (self):
      path_node = s_expression.List.generate ('path')
      path_node.add (s_expression.StringLiteral (self.path))
      path_node.add (s_expression.List.generate_property ('page', '"%s"' % self.page))
      return path_node


# -- SymbolInstance ----------------------------------------------------------

class SymbolInstance:
   def __init__ (self):
      self.path = None        # str eg. "/00000000-0000-0000-0000-00005fc9316d"
      self.reference = None   # str eg. "R4"
      self.unit = None        # integer, 1-based
      self.value = None       # str eg. 10k
      self.footprint = None   # str eg. "Resistor_SMD:R_0603_1608Metric"

   @staticmethod
   def parse (node):
      if not node: return None

      symbol_instance = SymbolInstance ()
      symbol_instance.path = node.entities [1].value
      symbol_instance.reference = node.property ('reference')
      symbol_instance.unit = node.property ('unit')
      symbol_instance.value = node.property ('value')
      symbol_instance.footprint = node.property ('footprint')

      return symbol_instance

   def generate (self):
      path_node = s_expression.List.generate ('path')
      path_node.add (s_expression.StringLiteral (self.path))
      path_node.add (s_expression.List.generate_property ('reference', '"%s"' % self.reference))
      path_node.add (s_expression.List.generate_property ('unit', self.unit))
      path_node.add (s_expression.List.generate_property ('value', '"%s"' % self.value))
      path_node.add (s_expression.List.generate_property ('footprint', '"%s"' % self.footprint))
      return path_node
