##############################################################################
#
#     ast.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
from . import adapter
from . import grammar

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')



# -- Node AST ----------------------------------------------------------------

class Node:
   def __init__ (self):
      self.parent = None
      self.extra_tokens = lambda: None

   @property
   def parent_scope (self):
      parent = self.parent
      if parent is not None:
         return parent if parent.is_scope else parent.parent_scope
      return None

   def source_context_part (self, part):
      # This method needs to be overloaded by subclasses
      assert False # pragma: no cover

   @property
   def is_literal (self): return isinstance (self, Literal)

   @property
   def is_float_literal (self): return isinstance (self, FloatLiteral)

   @property
   def is_string_literal (self): return isinstance (self, StringLiteral)

   @property
   def is_distance_literal (self): return isinstance (self, DistanceLiteral)

   @property
   def is_rotation_literal (self): return isinstance (self, RotationLiteral)

   @property
   def is_global_namespace (self): return isinstance (self, GlobalNamespace)

   @property
   def is_import (self): return isinstance (self, Import)

   @property
   def is_module (self): return isinstance (self, Module)

   @property
   def is_manufacturer_reference (self): return isinstance (self, ManufacturerReference)

   @property
   def is_board (self): return isinstance (self, Board)

   @property
   def is_board_class (self): return isinstance (self, BoardClass)

   @property
   def is_board_include (self): return isinstance (self, BoardInclude)

   @property
   def is_board_pcb (self): return isinstance (self, BoardPcb)

   @property
   def is_board_net (self): return isinstance (self, BoardNet)

   @property
   def is_board_pin (self): return isinstance (self, BoardPin)

   @property
   def is_board_pin_accept (self): return isinstance (self, BoardPinAccept)

   @property
   def is_board_pin_bind (self): return isinstance (self, BoardPinBind)

   @property
   def is_board_pin_type (self): return isinstance (self, BoardPinType)

   @property
   def is_board_pin_array (self): return isinstance (self, BoardPinArray)

   @property
   def is_board_kind (self): return isinstance (self, BoardKind)

   @property
   def is_board_kind_pools (self): return isinstance (self, BoardKindPools)

   @property
   def is_board_pool (self): return isinstance (self, BoardPool)

   @property
   def is_board_pool_pin (self): return isinstance (self, BoardPoolPin)

   @property
   def is_width (self): return isinstance (self, Width)

   @property
   def is_material (self): return isinstance (self, Material)

   @property
   def is_route (self): return isinstance (self, Route)

   @property
   def is_header (self): return isinstance (self, Header)

   @property
   def is_footer (self): return isinstance (self, Footer)

   @property
   def is_module_faust (self): return isinstance (self, ModuleFaust)

   @property
   def is_module_faust_init (self): return isinstance (self, ModuleFaustInit)

   @property
   def is_faust_address (self): return isinstance (self, FaustAddress)

   @property
   def is_faust_value (self): return isinstance (self, FaustValue)

   @property
   def is_faust_property (self): return isinstance (self, FaustProperty)

   @property
   def is_faust_bind (self): return isinstance (self, FaustBind)

   @property
   def is_control_faust (self): return isinstance (self, ControlFaust)

   @property
   def is_control_faust_init (self): return isinstance (self, ControlFaustInit)

   @property
   def is_control (self): return isinstance (self, Control)

   @property
   def is_alias (self): return isinstance (self, Alias)

   @property
   def is_mode (self): return isinstance (self, Mode)

   @property
   def is_style (self): return isinstance (self, Style)

   @property
   def is_label (self): return isinstance (self, Label)

   @property
   def is_sticker (self): return isinstance (self, Sticker)

   @property
   def is_exclude_pins (self): return isinstance (self, ExcludePins)

   @property
   def is_pin (self): return isinstance (self, Pin)

   @property
   def is_pin_array (self): return isinstance (self, Pins)

   @property
   def is_cascade_to (self): return isinstance (self, CascadeTo)

   @property
   def is_cascade_from (self): return isinstance (self, CascadeFrom)

   @property
   def is_positioning (self): return isinstance (self, Positioning)

   @property
   def is_position (self): return isinstance (self, Position)

   @property
   def is_rotation (self): return isinstance (self, Rotation)

   @property
   def is_offset (self): return isinstance (self, Offset)

   @property
   def is_file (self): return isinstance (self, File)

   @property
   def is_image (self): return isinstance (self, Image)

   @property
   def is_line (self): return isinstance (self, Line)

   @property
   def is_manufacturer (self): return isinstance (self, Manufacturer)

   @property
   def is_generator (self): return isinstance (self, Generator)

   @property
   def is_generator_arg_string (self): return isinstance (self, GeneratorArgString)

   @property
   def is_generator_arg_dict (self): return isinstance (self, GeneratorArgDict)

   @property
   def is_generator_arg_dict_item (self): return isinstance (self, GeneratorArgDictItem)

   @property
   def is_generator_arg (self): return self.is_generator_arg_string or self.is_generator_arg_dict

   @property
   def is_manufacturer_control (self): return isinstance (self, ManufacturerControl)

   @property
   def is_manufacturer_control_parts (self): return isinstance (self, ManufacturerControlParts)



# -- Scope -------------------------------------------------------------------

class Scope (Node):
   def __init__ (self):
      super (Scope, self).__init__ ()
      self.entities = []

   def add (self, entity_or_entities):
      if isinstance (entity_or_entities, list):
         entities = entity_or_entities
         for entity in entities:
            self.add (entity)

      else:
         entity = entity_or_entities
         assert entity not in self.entities
         entity.parent = self
         self.entities.append (entity)



# -- Literals ----------------------------------------------------------------

class Literal (Node):
   def __init__ (self, literal):
      super (Literal, self).__init__ ()
      self.literal = literal

   @property
   def source_context (self):
      return self.source_context_part ('full')

   def source_context_part (self, part):
      if part == 'full':
         return adapter.SourceContext.from_token (self.literal)

      return super (Literal, self).source_context_part (part) # pragma: no cover


class StringLiteral (Literal):
   def __init__ (self, literal):
      assert isinstance (literal, adapter.Literal)
      super (StringLiteral, self).__init__ (literal)

   @staticmethod
   def synthesize (value):
      literal = adapter.LiteralSynthesized ('"%s"' % value)
      return StringLiteral (literal)

   @property
   def value (self): return str (self.literal.value.strip ('"'))



class IntegerLiteral (Literal):
   def __init__ (self, literal):
      assert isinstance (literal, adapter.Literal)
      super (IntegerLiteral, self).__init__ (literal)

   @property
   def value (self): return int (self.literal.value)


class FloatLiteral (Literal):
   def __init__ (self, literal):
      assert isinstance (literal, adapter.Literal)
      super (FloatLiteral, self).__init__ (literal)

   @property
   def value (self): return float (self.literal.value)


class DistanceLiteral (Literal):
   def __init__ (self, literal, unit):
      assert isinstance (literal, adapter.Literal)
      super (DistanceLiteral, self).__init__ (literal)
      self.unit = unit

   @staticmethod
   def synthesize (value, unit):
      literal = adapter.LiteralSynthesized ('%s%s' % (value, unit))
      return DistanceLiteral (literal, unit)

   @property
   def value (self): return float (self.literal.value [:-2])

   @property
   def mm (self):
      if self.unit == 'mm':
         return self.value
      elif self.unit == 'cm':
         return self.value * 10.0
      elif self.unit == 'hp':
         return self.value * 5.08
      else:
         assert (False)

   @property
   def pt (self):
      return self.mm * 72.0 / 25.4



class RotationLiteral (Literal):
   def __init__ (self, literal, unit):
      assert isinstance (literal, adapter.Literal)
      super (RotationLiteral, self).__init__ (literal)
      self.unit = unit

   @property
   def value (self):
      if self.unit == '°':
         return -float (self.literal.value [:-1])
      elif self.unit == '°ccw':
         return float (self.literal.value [:-4])
      elif self.unit == '°cw':
         return -float (self.literal.value [:-3])
      else:
         assert (False)

   @property
   def degree (self):
      return self.value

   @property
   def degree_top_down (self):
      return 360 - self.degree



# -- GlobalNamespace ---------------------------------------------------------

class GlobalNamespace (Scope):
   def __init__ (self):
      super (GlobalNamespace, self).__init__ ()

   @property
   def imports (self):
      entities = [e for e in self.entities if e.is_import]
      return entities

   @property
   def modules (self):
      entities = [e for e in self.entities if e.is_module]
      return entities

   @property
   def manufacturers (self):
      entities = [e for e in self.entities if e.is_manufacturer]
      return entities


# -- Import ------------------------------------------------------------------

class Import (Node):
   def __init__ (self, filepath, literal):
      assert isinstance (filepath, str)
      assert isinstance (literal, StringLiteral)
      super (Import, self).__init__ ()
      self.filepath = filepath
      self.literal = literal

   @staticmethod
   def typename (): return 'import'

   @property
   def path (self):
      return self.filepath

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.literal.literal)

      return super (Import, self).source_context_part (part) # pragma: no cover


# -- Module ------------------------------------------------------------------

class Module (Scope):
   def __init__ (self, identifier, super_identifier):
      assert isinstance (identifier, adapter.Identifier)
      assert super_identifier is None or isinstance (super_identifier, adapter.Identifier)
      super (Module, self).__init__ ()
      self.identifier = identifier
      self.super_identifier = super_identifier
      self.cascade_eval_list = []
      self.unused_pins = []
      self.faust_addresses = {}

   @staticmethod
   def typename (): return 'module'

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)
      elif part == 'extends':
         return adapter.SourceContext.from_token (self.super_identifier)

      return super (Module, self).source_context_part (part) # pragma: no cover

   @property
   def manufacturer_reference (self):
      entities = [e for e in self.entities if e.is_manufacturer_reference]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def board (self):
      entities = [e for e in self.entities if e.is_board]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def width (self):
      entities = [e for e in self.entities if e.is_width]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def material (self):
      entities = [e for e in self.entities if e.is_material]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def route (self):
      entities = [e for e in self.entities if e.is_route]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def header (self):
      entities = [e for e in self.entities if e.is_header]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def footer (self):
      entities = [e for e in self.entities if e.is_footer]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def images (self):
      entities = [e for e in self.entities if e.is_image]
      return entities

   @property
   def labels (self):
      entities = [e for e in self.entities if e.is_label]
      return entities

   @property
   def stickers (self):
      entities = [e for e in self.entities if e.is_sticker]
      return entities

   @property
   def lines (self):
      entities = [e for e in self.entities if e.is_line]
      return entities

   @property
   def controls (self):
      entities = [e for e in self.entities if e.is_control]
      return entities

   @property
   def aliases (self):
      entities = [e for e in self.entities if e.is_alias]
      return entities


# -- ManufacturerReference ---------------------------------------------------

class ManufacturerReference (Node):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (ManufacturerReference, self).__init__ ()
      self.identifier = identifier

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)
      elif part == 'reference':
         return adapter.SourceContext.from_token (self.identifier)

      return super (ManufacturerReference, self).source_context_part (part) # pragma: no cover


# -- Board -------------------------------------------------------------------

class Board (Scope):
   def __init__ (self, identifier):
      if identifier != None:
         assert isinstance (identifier, adapter.Identifier)
      super (Board, self).__init__ ()
      self.identifier = identifier

   def load_builtin (self):
      path_definition = os.path.join (PATH_BOARDS, self.identifier.name, 'definition.py')
      board_path = os.path.dirname (path_definition)

      try:
         file = open (path_definition, 'r', encoding='utf-8')
      except OSError:
         err = error.Error ()
         context = self.source_context
         err.add_error ("Undefined board '%s'" % context, context)
         err.add_context (context)
         raise err

      with file:
         board_def = eval (file.read ())

      self.add (BoardClass (StringLiteral.synthesize (board_def ['class'])))

      board_include_path = os.path.join (board_path, board_def ['include'])
      self.add (BoardInclude (board_include_path, StringLiteral.synthesize (board_def ['include'])))

      if 'pcb' in board_def:
         board_pcb_path = os.path.join (board_path, board_def ['pcb'])
         self.add (BoardPcb (board_pcb_path, StringLiteral.synthesize (board_def ['pcb'])))

      if 'net' in board_def:
         board_net_path = os.path.join (board_path, board_def ['net'])
         self.add (BoardNet (board_net_path, StringLiteral.synthesize (board_def ['net'])))

      if 'width' in board_def:
         self.add (Width (DistanceLiteral.synthesize (board_def ['width'], 'hp')))

      pins_def = board_def ['pins']
      for pin_name in pins_def:
         board_pin = BoardPin (adapter.IdentifierSynthesized (pin_name))
         pin_desc = pins_def [pin_name]
         board_pin.add (BoardPinAccept (list (map (lambda x: adapter.BuiltIn (x), pin_desc ['accept']))))
         board_pin.add (BoardPinBind (StringLiteral.synthesize (pin_desc ['bind'])))
         if 'type' in pin_desc:
            board_pin.add (BoardPinType (adapter.BuiltIn (pin_desc ['type'])))
         self.add (board_pin)

      if 'kinds' in board_def:
         kinds_def = board_def ['kinds']
         for kind_name in kinds_def:
            board_kind = BoardKind (adapter.BuiltIn (kind_name))
            kind_desc = kinds_def [kind_name]
            board_kind.add (BoardKindPools (list (map (lambda x: adapter.IdentifierSynthesized (x), kind_desc ['pools']))))
            self.add (board_kind)

      if 'pools' in board_def:
         pools_def = board_def ['pools']
         for pool_name in pools_def:
            board_pool = BoardPool (adapter.IdentifierSynthesized (pool_name))
            pin_arr = pools_def [pool_name]
            for pin in pin_arr:
               board_pool.add (BoardPoolPin (adapter.IdentifierSynthesized (pin)))
            self.add (board_pool)


   @property
   def inline (self): return self.identifier == None

   @property
   def name (self): return self.identifier.name

   @property
   def class_ (self):
      entities = [e for e in self.entities if e.is_board_class]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def include (self):
      entities = [e for e in self.entities if e.is_board_include]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def pcb (self):
      entities = [e for e in self.entities if e.is_board_pcb]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def net (self):
      entities = [e for e in self.entities if e.is_board_net]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def width (self):
      entities = [e for e in self.entities if e.is_width]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   def pin (self, name):
      entities = [e for e in self.entities if e.is_board_pin and e.name == name]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def pins (self):
      entities = [e for e in self.entities if e.is_board_pin]
      return entities

   @property
   def pin_names (self):
      names = [e.name for e in self.entities if e.is_board_pin]
      return names

   @property
   def kinds (self):
      entities = [e for e in self.entities if e.is_board_kind]
      return entities

   def kind (self, name):
      entities = [e for e in self.entities if e.is_board_kind and e.name == name]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def pools (self):
      entities = [e for e in self.entities if e.is_board_pool]
      return entities

   def pool (self, name):
      entities = [e for e in self.entities if e.is_board_pool and e.name == name]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)

      return super (Board, self).source_context_part (part) # pragma: no cover


# -- BoardClass --------------------------------------------------------------

class BoardClass (Node):
   def __init__ (self, string_literal):
      assert isinstance (string_literal, StringLiteral)
      super (BoardClass, self).__init__ ()
      self.string_literal = string_literal

   @property
   def name (self): return self.string_literal.value


# -- BoardInclude ------------------------------------------------------------

class BoardInclude (Node):
   def __init__ (self, filepath, string_literal):
      assert isinstance (filepath, str)
      assert isinstance (string_literal, StringLiteral)
      super (BoardInclude, self).__init__ ()
      self.filepath = filepath
      self.string_literal = string_literal

   @property
   def path (self): return self.filepath


# -- BoardPcb ----------------------------------------------------------------

class BoardPcb (Node):
   def __init__ (self, filepath, string_literal):
      assert isinstance (filepath, str)
      assert isinstance (string_literal, StringLiteral)
      super (BoardPcb, self).__init__ ()
      self.filepath = filepath
      self.string_literal = string_literal

   @property
   def path (self): return self.filepath


# -- BoardNet ----------------------------------------------------------------

class BoardNet (Node):
   def __init__ (self, filepath, string_literal):
      assert isinstance (filepath, str)
      assert isinstance (string_literal, StringLiteral)
      super (BoardNet, self).__init__ ()
      self.filepath = filepath
      self.string_literal = string_literal

   @property
   def path (self): return self.filepath


# -- BoardPin ----------------------------------------------------------------

class BoardPin (Scope):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (BoardPin, self).__init__ ()
      self.identifier = identifier

   @property
   def name (self): return self.identifier.name

   @property
   def accept (self):
      entities = [e for e in self.entities if e.is_board_pin_accept]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def bind (self):
      entities = [e for e in self.entities if e.is_board_pin_bind]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def type_ (self):
      entities = [e for e in self.entities if e.is_board_pin_type]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None


# -- BoardPinArray -----------------------------------------------------------

class BoardPinArray (Scope):
   def __init__ (self, identifier, end_range):
      assert isinstance (identifier, adapter.Identifier)
      assert isinstance (end_range, IntegerLiteral)
      super (BoardPinArray, self).__init__ ()
      self.identifier = identifier
      self.end_range = end_range

   @property
   def accept (self):
      entities = [e for e in self.entities if e.is_board_pin_accept]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def bind (self):
      entities = [e for e in self.entities if e.is_board_pin_bind]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def type_ (self):
      entities = [e for e in self.entities if e.is_board_pin_type]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None


# -- BoardPinAccept ----------------------------------------------------------

class BoardPinAccept (Node):
   def __init__ (self, keywords):
      assert isinstance (keywords, list)
      super (BoardPinAccept, self).__init__ ()
      self.keywords = keywords

   @property
   def kinds (self): return [k.value for k in self.keywords]


# -- BoardPinBind ------------------------------------------------------------

class BoardPinBind (Node):
   def __init__ (self, string_literal):
      assert isinstance (string_literal, StringLiteral)
      super (BoardPinBind, self).__init__ ()
      self.string_literal = string_literal

   @property
   def expression (self): return self.string_literal.value


# -- BoardPinType ------------------------------------------------------------

class BoardPinType (Node):
   def __init__ (self, keyword):
      assert isinstance (keyword, adapter.Keyword)
      super (BoardPinType, self).__init__ ()
      self.keyword = keyword

   @property
   def name (self): return self.keyword.value


# -- BoardKind ---------------------------------------------------------------

class BoardKind (Scope):
   def __init__ (self, keyword):
      assert isinstance (keyword, adapter.Keyword)
      super (BoardKind, self).__init__ ()
      self.keyword = keyword

   @property
   def name (self): return self.keyword.value

   @property
   def pools (self):
      entities = [e for e in self.entities if e.is_board_kind_pools]
      assert (len (entities) == 1)
      return entities [0]


# -- BoardKindPools ----------------------------------------------------------

class BoardKindPools (Node):
   def __init__ (self, identifiers):
      assert isinstance (identifiers, list)
      super (BoardKindPools, self).__init__ ()
      self.identifiers = identifiers

   @property
   def names (self): return [ ident.name for ident in self.identifiers ]


# -- BoardPool ---------------------------------------------------------------

class BoardPool (Scope):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (BoardPool, self).__init__ ()
      self.identifier = identifier

   @property
   def name (self): return self.identifier.name

   @property
   def pins (self):
      entities = [e for e in self.entities if e.is_board_pool_pin]
      assert (len (entities) >= 1)
      return entities

   @property
   def pin_names (self):
      names = [e.name for e in self.entities if e.is_board_pool_pin]
      assert (len (names) >= 1)
      return names

   def find_pin (self, name):
      pins = [e for e in self.entities if e.is_board_pool_pin and e.name == name ]
      assert len (pins) <= 1
      if pins:
         return pins [0]
      else:
         return None

   def has_pin (self, name):
      names = [e.name for e in self.entities if e.is_board_pool_pin]
      return name in names

   @property
   def available_pins (self):
      entities = [e for e in self.entities if e.is_board_pool_pin and e.available]
      return entities


# -- BoardPoolPin ------------------------------------------------------------

class BoardPoolPin (Node):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (BoardPoolPin, self).__init__ ()
      self.identifier = identifier
      self.is_available = True

   @property
   def name (self): return self.identifier.name

   def mark_unavailable (self):
      self.is_available = False

   @property
   def available (self): return self.is_available



# -- Material ----------------------------------------------------------------

class Material (Node):
   def __init__ (self, keyword_type, keyword_color):
      assert isinstance (keyword_type, adapter.Keyword)
      if keyword_color is not None:
         assert isinstance (keyword_color, adapter.Keyword)
      super (Material, self).__init__ ()
      self.keyword_type = keyword_type
      self.keyword_color = keyword_color

   @staticmethod
   def typename (): return 'material'

   @property
   def type (self): return self.keyword_type.value

   @property
   def color (self): return self.keyword_color.value if self.keyword_color is not None else 'natural'

   @property
   def is_light (self):
      return self.is_aluminum_natural or self.is_brushed_aluminum_natural or self.is_aluminum_coated_white

   @property
   def is_dark (self):
      return self.is_aluminum_black or self.is_brushed_aluminum_black or self.is_aluminum_coated_black

   @property
   def is_aluminum_natural (self):
      return self.type == 'aluminum' and self.color == 'natural'

   @property
   def is_aluminum_black (self):
      return self.type == 'aluminum' and self.color == 'black'

   @property
   def is_brushed_aluminum_natural (self):
      return self.type == 'brushed_aluminum' and self.color == 'natural'

   @property
   def is_brushed_aluminum_black (self):
      return self.type == 'brushed_aluminum' and self.color == 'black'

   @property
   def is_aluminum_coated_white (self):
      return self.type == 'aluminum_coated' and self.color == 'white'

   @property
   def is_aluminum_coated_black (self):
      return self.type == 'aluminum_coated' and self.color == 'black'


# -- Route -------------------------------------------------------------------

class Route (Node):
   def __init__ (self, keyword_mode):
      assert isinstance (keyword_mode, adapter.Keyword)
      super (Route, self).__init__ ()
      self.keyword_mode = keyword_mode

   @staticmethod
   def typename (): return 'route'

   @property
   def mode (self): return self.keyword_mode.value

   @property
   def is_manual (self):
      return self.mode == 'manual'

   @property
   def is_wire (self):
      return self.mode == 'wire'


# -- Header ------------------------------------------------------------------

class Header (Scope):
   def __init__ (self):
      super (Header, self).__init__ ()

   @staticmethod
   def typename (): return 'header'

   @property
   def labels (self):
      entities = [e for e in self.entities if e.is_label]
      return entities

   @property
   def stickers (self):
      entities = [e for e in self.entities if e.is_sticker]
      return entities

   @property
   def images (self):
      entities = [e for e in self.entities if e.is_image]
      return entities


# -- Footer ------------------------------------------------------------------

class Footer (Scope):
   def __init__ (self):
      super (Footer, self).__init__ ()

   @staticmethod
   def typename (): return 'footer'

   @property
   def labels (self):
      entities = [e for e in self.entities if e.is_label]
      return entities

   @property
   def stickers (self):
      entities = [e for e in self.entities if e.is_sticker]
      return entities

   @property
   def images (self):
      entities = [e for e in self.entities if e.is_image]
      return entities


# -- ModuleFaust ------------------------------------------------------------

class ModuleFaust (Scope):
   def __init__ (self):
      super (ModuleFaust, self).__init__ ()

   @staticmethod
   def typename (): return 'faust'

   @property
   def inits (self):
      entities = [e for e in self.entities if e.is_module_faust_init]
      return entities


# -- ModuleFaustInit ---------------------------------------------------------

class ModuleFaustInit (Scope):
   def __init__ (self):
      super (ModuleFaustInit, self).__init__ ()

   @staticmethod
   def typename (): return 'init'

   @property
   def address (self):
      entities = [e for e in self.entities if e.is_faust_address]
      assert len (entities) == 1
      return entities [0]

   @property
   def value (self):
      entities = [e for e in self.entities if e.is_faust_value]
      assert len (entities) == 1
      return entities [0]


# -- FaustBind ---------------------------------------------------------------

class FaustBind (Scope):
   def __init__ (self):
      super (FaustBind, self).__init__ ()

   @staticmethod
   def typename (): return 'bind'

   @property
   def address (self):
      entities = [e for e in self.entities if e.is_faust_address]
      assert len (entities) == 1
      return entities [0]

   @property
   def property_ (self):
      entities = [e for e in self.entities if e.is_faust_property]
      assert len (entities) <= 1
      if entities:
         return entities [0]
      else:
         return None


# -- FaustAddress ------------------------------------------------------------

class FaustAddress (Node):
   def __init__ (self, path):
      assert isinstance (path, StringLiteral)
      super (FaustAddress, self).__init__ ()
      self.literal_path = path

   @staticmethod
   def typename (): return 'address'

   @property
   def path (self): return self.literal_path.value

   @property
   def source_context (self):
      return self.source_context_part ('path')

   def source_context_part (self, part):
      if part == 'path':
         return adapter.SourceContext.from_token (self.literal_path)

      return super (FaustAddress, self).source_context_part (part) # pragma: no cover


# -- FaustValue --------------------------------------------------------------

class FaustValue (Node):
   def __init__ (self, value):
      assert isinstance (value, FloatLiteral)
      super (FaustValue, self).__init__ ()
      self.literal_value = value

   @staticmethod
   def typename (): return 'value'

   @property
   def value (self): return self.literal_value.value

   @property
   def source_context (self):
      return self.source_context_part ('value')

   def source_context_part (self, part):
      if part == 'value':
         return adapter.SourceContext.from_token (self.literal_value)

      return super (FaustValue, self).source_context_part (part) # pragma: no cover


# -- FaustProperty -----------------------------------------------------------

class FaustProperty (Node):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (FaustProperty, self).__init__ ()
      self.identifier = identifier

   @staticmethod
   def typename (): return 'property'

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)

      return super (FaustProperty, self).source_context_part (part) # pragma: no cover


# -- Alias -------------------------------------------------------------------

class Alias (Node):
   def __init__ (self, name, reference):
      assert isinstance (name, adapter.Identifier)
      assert isinstance (reference, adapter.Identifier)
      super (Alias, self).__init__ ()
      self.identifier_name = name
      self.identifier_reference = reference
      self.reference = None

   @staticmethod
   def typename (): return 'alias'

   @property
   def name (self): return self.identifier_name.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier_name)
      elif part == 'reference':
         return adapter.SourceContext.from_token (self.identifier_reference)

      return super (Alias, self).source_context_part (part) # pragma: no cover


# -- ExcludePins -------------------------------------------------------------

class ExcludePins (Node):
   def __init__ (self, identifiers):
      assert isinstance (identifiers, list)
      super (ExcludePins, self).__init__ ()
      self.identifiers = identifiers
      self.pins = [ Pin (ident) for ident in identifiers]

   @staticmethod
   def typename (): return 'exclude'

   @property
   def names (self): return [ ident.name for ident in self.identifiers ]


# -- ControlFaust ------------------------------------------------------------

class ControlFaust (Scope):
   def __init__ (self):
      super (ControlFaust, self).__init__ ()

   @staticmethod
   def typename (): return 'faust'

   @property
   def binds (self):
      entities = [e for e in self.entities if e.is_faust_bind]
      return entities

   @property
   def inits (self):
      entities = [e for e in self.entities if e.is_control_faust_init]
      return entities


# -- ControlFaustInit --------------------------------------------------------

class ControlFaustInit (Scope):
   def __init__ (self):
      super (ControlFaustInit, self).__init__ ()

   @staticmethod
   def typename (): return 'init'

   @property
   def address (self):
      entities = [e for e in self.entities if e.is_faust_address]
      assert len (entities) == 1
      return entities [0]

   @property
   def property_ (self):
      entities = [e for e in self.entities if e.is_faust_property]
      assert len (entities) <= 1
      if entities:
         return entities [0]
      else:
         return None

   @property
   def value (self):
      entities = [e for e in self.entities if e.is_faust_value]
      assert len (entities) == 1
      return entities [0]


# -- Control -----------------------------------------------------------------

class Control (Scope):
   class Part:
      def __init__ (self, pcb, net):
         self.pcb = pcb
         self.net = net

   def __init__ (self, identifier_name, keyword_kind):
      assert isinstance (identifier_name, adapter.Identifier)
      assert isinstance (keyword_kind, adapter.Keyword)
      super (Control, self).__init__ ()
      self.identifier_name = identifier_name
      self.keyword_kind = keyword_kind
      self.parts = []

   @staticmethod
   def typename (): return 'control'

   @property
   def name (self): return self.identifier_name.name

   @property
   def kind (self): return self.keyword_kind.value

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier_name)

      if part == 'kind':
         return adapter.SourceContext.from_token (self.identifier_kind)

      return super (Control, self).source_context_part (part) # pragma: no cover

   @property
   def faust (self):
      entities = [e for e in self.entities if e.is_control_faust]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def mode (self):
      entities = [e for e in self.entities if e.is_mode]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def position (self):
      entities = [e for e in self.entities if e.is_position]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def style (self):
      entities = [e for e in self.entities if e.is_style]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def rotation (self):
      entities = [e for e in self.entities if e.is_rotation]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def labels (self):
      entities = [e for e in self.entities if e.is_label]
      return entities

   @property
   def stickers (self):
      entities = [e for e in self.entities if e.is_sticker]
      return entities

   @property
   def is_pin_single (self):
      return not self.is_pin_multiple

   @property
   def pin (self):
      entities = [e for e in self.entities if e.is_pin]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def is_pin_multiple (self):
      return self.kind == 'Switch' or self.kind == 'LedBi' or self.kind == 'LedRgb'

   @property
   def pins (self):
      entities = [e for e in self.entities if e.is_pin_array]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def nbr_pins (self):
      if self.kind == 'Switch':
         return 2
      elif self.kind == 'LedBi':
         return 2
      elif self.kind == 'LedRgb':
         return 3
      else:
         return 1

   @property
   def cascade_to (self):
      entities = [e for e in self.entities if e.is_cascade_to]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def cascade_from (self):
      entities = [e for e in self.entities if e.is_cascade_from]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def compound_properties (self):
      if self.kind in ['AudioIn', 'AudioOut', 'Button', 'CvIn', 'CvOut', 'GateIn', 'GateOut', 'Led', 'Pot', 'Switch', 'Trim']:
         return []
      elif self.kind == 'LedBi':
         return ['r', 'g']
      elif self.kind == 'LedRgb':
         return ['r', 'g', 'b']
      else:
         assert False

   @property
   def is_input (self):
      return self.kind in ['AudioIn', 'Button', 'CvIn', 'GateIn', 'Pot', 'Switch', 'Trim']

   @property
   def is_output (self):
      return self.kind in ['AudioOut', 'CvOut','GateOut', 'Led', 'LedBi', 'LedRgb']

   @property
   def is_kind_in (self):
      return self.kind in ['AudioIn', 'CvIn', 'GateIn']

   @property
   def is_kind_out (self):
      return self.kind in ['AudioOut', 'CvOut', 'GateOut']


# -- Mode --------------------------------------------------------------------

class Mode (Node):
   def __init__ (self, keyword_name):
      assert isinstance (keyword_name, adapter.Keyword)
      super (Mode, self).__init__ ()
      self.keyword_name = keyword_name

   @staticmethod
   def typename (): return 'mode'

   @property
   def name (self): return self.keyword_name.value

   @property
   def is_normalized (self): return self.name == 'normalized'

   @property
   def is_bipolar (self): return self.name == 'bipolar'


# -- Style -------------------------------------------------------------------

class Style (Scope):
   def __init__ (self, keyword_names):
      assert isinstance (keyword_names, list)
      super (Style, self).__init__ ()
      self.keyword_names = keyword_names

   @staticmethod
   def typename (): return 'style'


# -- Label -------------------------------------------------------------------

class Label (Scope):
   def __init__ (self, literal):
      assert isinstance (literal, StringLiteral)
      super (Label, self).__init__ ()
      self.literal = literal

   @staticmethod
   def typename (): return 'label'

   @property
   def text (self):
      return self.literal.value

   @property
   def positioning (self):
      entities = [e for e in self.entities if e.is_positioning]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def position (self):
      entities = [e for e in self.entities if e.is_position]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def offset (self):
      entities = [e for e in self.entities if e.is_offset]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None



# -- Sticker -------------------------------------------------------------------

class Sticker (Scope):
   def __init__ (self, literal):
      assert isinstance (literal, StringLiteral)
      super (Sticker, self).__init__ ()
      self.literal = literal

   @staticmethod
   def typename (): return 'sticker'

   @property
   def text (self):
      return self.literal.value

   @property
   def positioning (self):
      entities = [e for e in self.entities if e.is_positioning]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def position (self):
      entities = [e for e in self.entities if e.is_position]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None

   @property
   def offset (self):
      entities = [e for e in self.entities if e.is_offset]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None



# -- Pin ---------------------------------------------------------------------

class Pin (Node):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (Pin, self).__init__ ()
      self.identifier = identifier

   @staticmethod
   def typename (): return 'pin'

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)

      return super (Pin, self).source_context_part (part) # pragma: no cover



# -- Pins --------------------------------------------------------------------

class Pins (Node):
   def __init__ (self, identifiers):
      assert isinstance (identifiers, list)
      super (Pins, self).__init__ ()
      self.identifiers = identifiers
      self.pins = [ Pin (ident) for ident in identifiers]

   @staticmethod
   def typename (): return 'pins'

   @property
   def names (self): return [ ident.name for ident in self.identifiers ]



# -- CascadeTo ---------------------------------------------------------------

class CascadeTo (Node):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (CascadeTo, self).__init__ ()
      self.identifier = identifier
      self.reference = None
      self.index = 0

   @staticmethod
   def typename (): return 'cascade_to'

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)

      return super (CascadeTo, self).source_context_part (part) # pragma: no cover



# -- CascadeFrom -------------------------------------------------------------

class CascadeFrom (Node):
   def __init__ (self):
      super (CascadeFrom, self).__init__ ()
      self.reference = None
      self.index = 0

   @staticmethod
   def typename (): return 'cascade_from'



# -- Width ------------------------------------------------------------------

class Width (Node):
   def __init__ (self, literal):
      assert isinstance (literal, DistanceLiteral)
      super (Width, self).__init__ ()
      self.literal = literal

   @staticmethod
   def typename (): return 'width'

   @property
   def mm (self):
      return self.literal.mm

   @property
   def pt (self):
      return self.literal.pt



# -- Positioning -------------------------------------------------------------

class Positioning (Node):
   def __init__ (self, keyword_positioning):
      assert isinstance (keyword_positioning, adapter.Keyword)
      super (Positioning, self).__init__ ()
      self.keyword_positioning = keyword_positioning

   @staticmethod
   def typename (): return 'positioning'

   @property
   def is_center (self):
      return self.keyword_positioning.value == 'center'

   @property
   def is_left (self):
      return self.keyword_positioning.value == 'left'

   @property
   def is_top (self):
      return self.keyword_positioning.value == 'top'

   @property
   def is_right (self):
      return self.keyword_positioning.value == 'right'

   @property
   def is_bottom (self):
      return self.keyword_positioning.value == 'bottom'



# -- Position ----------------------------------------------------------------

class Position (Node):
   def __init__ (self, literal_x, literal_y):
      assert isinstance (literal_x, DistanceLiteral)
      assert isinstance (literal_y, DistanceLiteral)
      super (Position, self).__init__ ()
      self.literal_x = literal_x
      self.literal_y = literal_y

   @staticmethod
   def typename (): return 'position'

   @property
   def x (self):
      return self.literal_x

   @property
   def y (self):
      return self.literal_y



# -- Offset ------------------------------------------------------------------

class Offset (Node):
   def __init__ (self, literal_x, literal_y):
      assert isinstance (literal_x, DistanceLiteral)
      assert isinstance (literal_y, DistanceLiteral)
      super (Offset, self).__init__ ()
      self.literal_x = literal_x
      self.literal_y = literal_y

   @staticmethod
   def typename (): return 'offset'

   @property
   def x (self):
      return self.literal_x

   @property
   def y (self):
      return self.literal_y



# -- Rotation ----------------------------------------------------------------

class Rotation (Node):
   def __init__ (self, literal):
      assert isinstance (literal, RotationLiteral)
      super (Rotation, self).__init__ ()
      self.literal = literal

   @staticmethod
   def typename (): return 'rotation'

   @property
   def degree (self):
      return self.literal.degree

   @property
   def degree_top_down (self):
      return self.literal.degree_top_down



# -- File --------------------------------------------------------------------

class File (Node):
   def __init__ (self, filepath, literal):
      assert isinstance (filepath, str)
      assert isinstance (literal, StringLiteral)
      super (File, self).__init__ ()
      self.filepath = filepath
      self.literal = literal

   @staticmethod
   def typename (): return 'file'

   @property
   def file (self):
      return self.filepath

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.literal.literal)

      return super (File, self).source_context_part (part) # pragma: no cover



# -- Image -------------------------------------------------------------------

class Image (Node):
   def __init__ (self, filepath):
      assert isinstance (filepath, StringLiteral) or isinstance (filepath, str)
      super (Image, self).__init__ ()
      self.filepath = filepath

   @staticmethod
   def typename (): return 'image'

   @property
   def file (self):
      if isinstance (self.filepath, StringLiteral):
         return self.filepath.value
      elif isinstance (self.filepath, str):
         return self.filepath



# -- Line --------------------------------------------------------------------

class Line (Scope):
   def __init__ (self):
      super (Line, self).__init__ ()

   @staticmethod
   def typename (): return 'line'

   @property
   def points (self):
      entities = [e for e in self.entities if e.is_position]
      return entities



# -- Manufacturer ------------------------------------------------------------

class Manufacturer (Scope):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (Manufacturer, self).__init__ ()
      self.identifier = identifier

   @staticmethod
   def typename (): return 'manufacturer'

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)

      return super (Manufacturer, self).source_context_part (part) # pragma: no cover

   @property
   def generators (self):
      entities = [e for e in self.entities if e.is_generator]
      return entities

   @property
   def controls (self):
      entities = [e for e in self.entities if e.is_manufacturer_control]
      return entities


# -- Generator ---------------------------------------------------------------

class Generator (Scope):
   def __init__ (self, name_string_literal):
      assert isinstance (name_string_literal, StringLiteral)
      super (Generator, self).__init__ ()
      self.name_string_literal = name_string_literal

   @property
   def name (self): return self.name_string_literal.value

   @property
   def args (self):
      entities = [e for e in self.entities if e.is_generator_arg]
      return entities


# -- GeneratorArgString ------------------------------------------------------

class GeneratorArgString (Scope):
   def __init__ (self, identifier, value_string_literal):
      assert isinstance (identifier, adapter.Identifier)
      assert isinstance (value_string_literal, StringLiteral)
      super (GeneratorArgString, self).__init__ ()
      self.identifier = identifier
      self.value_string_literal = value_string_literal

   @property
   def name (self): return self.identifier.name

   @property
   def value (self):
      return self.value_string_literal.value.replace ('\\n', '\n').replace ('\\t', '\t').replace ('\\"', '"')


# -- GeneratorArgDict --------------------------------------------------------

class GeneratorArgDict (Scope):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (GeneratorArgDict, self).__init__ ()
      self.identifier = identifier

   @property
   def name (self): return self.identifier.name

   @property
   def items (self):
      entities = [e for e in self.entities if e.is_generator_arg_string]
      return entities


# -- ManufacturerControl -----------------------------------------------------

class ManufacturerControl (Scope):
   def __init__ (self, kind_keyword_list):
      assert isinstance (kind_keyword_list, list)
      super (ManufacturerControl, self).__init__ ()
      self.kind_keyword_list = kind_keyword_list

   @property
   def kinds (self): return [e.value for e in self.kind_keyword_list]

   @property
   def style (self):
      entities = [e for e in self.entities if e.is_style]
      assert len (entities) == 1
      keyword_names = entities [0].keyword_names
      return {e.value for e in keyword_names}

   @property
   def parts (self):
      entities = [e for e in self.entities if e.is_manufacturer_control_parts]
      assert len (entities) == 1
      keyword_names = entities [0].keyword_names
      return [e.value for e in keyword_names]


# -- ManufacturerControlParts ------------------------------------------------

class ManufacturerControlParts (Scope):
   def __init__ (self, keyword_names):
      assert isinstance (keyword_names, list)
      super (ManufacturerControlParts, self).__init__ ()
      self.keyword_names = keyword_names

   @staticmethod
   def typename (): return 'parts'
