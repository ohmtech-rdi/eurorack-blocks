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

      for sheet_instance_node in node.first_kind ('sheet_instances').filter_kind ('path'):
         root.sheet_instances.append (SheetInstance.parse (sheet_instance_node))

      for symbol_instance_node in node.first_kind ('symbol_instances').filter_kind ('path'):
         root.symbol_instances.append (SymbolInstance.parse (symbol_instance_node))

      return root


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
      if (len (node.entities) >= 4):
         at.rotation = node.entities [3].value

      return at


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


   class Font:
      def __init__ (self):
         self.size = None   # float, mm, written for both x,y

      @staticmethod
      def parse (node):
         if not node: return None

         font = Effects.Font ()
         font.size = node.property ('size')

         return font


# -- Property ----------------------------------------------------------------

class Property:
   def __init__ (self):
      self.name = None  # str
      self.value = None # str
      self.id = None    # int
      self.at = At ()
      self.effects = Effects ()

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

   class Symbol:
      def __init__ (self):
         self.name = None  # str
         self.shapes = []  # list of Rectangle or Polyline
         self.pins = []    # list of LibSymbol.Symbol.Pin

      @staticmethod
      def parse (node):
         if not node: return None

         symbol = LibSymbol.Symbol ()
         symbol.name = node.entities [1].value

         for shape_node in node.filter_kinds (['rectangle', 'polyline']):
            shape_kind = shape_node.entities [0].value
            if shape_kind == 'rectangle':
               symbol.shapes.append (Rectangle.parse (shape_node))
            elif shape_kind == 'polyline':
               symbol.shapes.append (Polyline.parse (shape_node))
            else:
               assert False

         for pin_node in node.filter_kind ('pin'):
            symbol.pins.append (LibSymbol.Symbol.parse (pin_node))

      class Pin:
         def __init__ (self):
            self.electrical_type = None   # str eg. passive, power_in, etc.
            self.graphic_style = None     # str eg. line
            self.at = At ()
            self.length = None            # float
            self.name = LibSymbol.Symbol.Pin.Name ()
            self.number = LibSymbol.Symbol.Pin.Number ()

         @staticmethod
         def parse (node):
            if not node: return None

            pin = LibSymbol.Symbol.Pin ()
            pin.electrical_type = node.entities [1].value
            pin.graphic_style = node.entities [2].value
            pin.at.parse (node.first_kind ('at'))
            pin.length = node.property ('length')
            pin.name.parse (node.first_kind ('name'))
            pin.number.parse (node.first_kind ('number'))

            return pin

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


# -- Junction ----------------------------------------------------------------

class Junction:
   def __init__ (self):
      self.at = At ()
      self.diameter = None # float
      color = Color ()
      self.uuid = None     # str eg. '0241e922-798f-4f95-bb3e-5bdf47696699'

   @staticmethod
   def parse (node):
      if not node: return None

      junction = Junction ()
      junction.at = At.parse (node.first_kind ('at'))
      junction.diameter = node.property ('diameter')
      junction.color = Color.parse (node.first_kind ('color'))
      junction.uuid = node.property ('uuid')

      return junction


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
