##############################################################################
#
#     analyser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from . import adapter
from . import ast
from . import error

import os
from difflib import get_close_matches

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')



class Analyser:

   def __init__ (self):
      self._board_definition = {}
      self._used_pins = {} # map from physical pin number to declaration
      self._cascade_index = 0

   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):
      assert global_namespace.is_global_namespace

      for module in global_namespace.modules:
         self.analyse_module (module)

   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      assert module.is_module

      self._board_definition = self.load_board_definition (module)

      self.set_auto_board_width (module)

      for control in module.controls:
         self.update_pools (control)

      for control in module.controls:
         self.allocate_pin (control)

      self.make_unused_pins (module)

      for control in module.controls:
         self.analyse_control (module, control)

      for alias in module.aliases:
         self.resolve_alias (module, alias)

      self.make_cascade_eval_list (module)

      self.resolve_module_faust_addresses (module)


   #--------------------------------------------------------------------------

   def set_auto_board_width (self, module):
      if 'width' not in self._board_definition:
         return # board doesn't support fixed width

      board_width = self._board_definition ['width']

      def generate_literal (value):
         node = lambda: None
         node.value = value
         node.position = None
         return adapter.Literal (None, node)

      entities = [e for e in module.entities if e.is_width]
      if len (entities) == 0:
         literal = generate_literal ('%shp' % board_width)
         distance_literal = ast.DistanceLiteral (literal, 'hp')
         width = ast.Width (distance_literal)
         module.entities.append (width)


   #--------------------------------------------------------------------------

   def analyse_control (self, module, control):
      assert control.is_control

      if control.is_pin_single:
         pins = [e for e in control.entities if e.is_pin]
         nbr_pins = len (pins)

         if nbr_pins == 0:
            raise error.missing_required (control, ast.Pin)
         elif nbr_pins > 1:
            raise error.multiple_definition (control, pins)

         pin = pins [0]
         self.analyse_pin (module, control, pin)

      elif control.is_pin_multiple:
         pin_arrays = [e for e in control.entities if e.is_pin_array]
         nbr_pin_arrays = len (pin_arrays)

         if nbr_pin_arrays == 0:
            raise error.missing_required (control, ast.Pins)
         elif nbr_pin_arrays > 1:
            raise error.multiple_definition (control, pin_arrays)

         pin_array = pin_arrays [0]

         if len (pin_array.pins) != control.nbr_pins:
            control_name = control.source_context_part ('name')
            kind = control.typename ()
            err = error.Error ()
            err.add_error ("'%s' has the wrong number of pins for kind '%s'" % (control.name, kind), control_name)
            err.add_context (control_name)
            context = adapter.SourceContext.from_token_range (
               pin_array.identifiers [0],
               pin_array.identifiers [-1],
            )
            err.add_note ("%d instead of %d" % (len (pin_array.pins), control.nbr_pins), context)
            err.add_context (context)
            raise err

         self.analyse_pins (module, control, pin_array)

      if control.cascade_to is not None:
         self.resolve_cascade (module, control, control.cascade_to)

      self.resolve_control_faust_addresses (module, control)


   #--------------------------------------------------------------------------

   def analyse_pin (self, module, control, pin):
      assert pin.is_pin

      pins = self._board_definition ['pins'];

      if pin.name not in pins.keys ():
         raise error.unknown_pin (pin, pins.keys ())

      pin_description = pins [pin.name]

      if 'physical.location' in pin_description:
         hw_pin = pin_description ['physical.location']

         if hw_pin in self._used_pins:
            raise error.already_used_pin (pin, self._used_pins [hw_pin])

         self._used_pins [hw_pin] = pin

   #--------------------------------------------------------------------------

   def analyse_pins (self, module, control, pin_array):
      for pin in pin_array.pins:
         self.analyse_pin (module, control, pin)


   #--------------------------------------------------------------------------

   def resolve_alias (self, module, alias):
      control = None

      for entity in module.entities:
         if entity.is_control:
            if alias.identifier_reference.name == entity.name:
               control = entity

      if control is None:
         possible_tokens = []
         for entity in module.entities:
            if entity.is_control:
               possible_tokens.append (entity.identifier_name)

         def make_dict (fun, iterable):
            return dict (zip (map (fun, iterable), iterable))

         possible_names = make_dict (lambda x: x.value, possible_tokens)
         matches = get_close_matches (alias.identifier_reference.name, possible_names.keys ())

         fixit_decl_tokens = [possible_names [match_name] for match_name in matches]
         fixit_decls_sc = [adapter.SourceContext.from_token (f) for f in fixit_decl_tokens]

         raise error.undefined_reference (alias, fixit_decls_sc)

      alias.reference = control


   #--------------------------------------------------------------------------

   def resolve_cascade (self, module, control_from, cascade_to):
      control = None

      for entity in module.entities:
         if entity.is_control:
            if cascade_to.identifier.name == entity.name:
               control = entity

      if control is None:
         possible_tokens = []
         for entity in module.entities:
            if entity.is_control:
               possible_tokens.append (entity.identifier_name)

         def make_dict (fun, iterable):
            return dict (zip (map (fun, iterable), iterable))

         possible_names = make_dict (lambda x: x.value, possible_tokens)
         matches = get_close_matches (cascade_to.identifier.name, possible_names.keys ())

         fixit_decl_tokens = [possible_names [match_name] for match_name in matches]
         fixit_decls_sc = [adapter.SourceContext.from_token (f) for f in fixit_decl_tokens]

         raise error.undefined_reference (cascade_to, fixit_decls_sc)

      cascade_to.reference = control
      cascade_to.index = self._cascade_index
      cascade_from = ast.CascadeFrom ()
      cascade_from.reference = control_from
      cascade_from.index = self._cascade_index
      control.entities.append (cascade_from)
      self._cascade_index += 1


   #--------------------------------------------------------------------------

   def resolve_module_faust_addresses (self, module):
      assert module.is_module

      faust_entities = [e for e in module.entities if e.is_module_faust]
      nbr_faust = len (faust_entities)

      if nbr_faust > 1:
         raise error.multiple_definition (control, faust_entities)

      if nbr_faust == 1:
         faust = faust_entities [0]
         inits = [e for e in faust.entities if e.is_module_faust_init]
         for init in inits:
            object = lambda: None
            object.control = None
            object.property = None
            object.qualified = None
            object.value = init.value.value
            module.faust_addresses [init.address.path] = object


   #--------------------------------------------------------------------------

   def resolve_control_faust_addresses (self, module, control):
      assert control.is_control

      faust_entities = [e for e in control.entities if e.is_control_faust]
      nbr_faust = len (faust_entities)

      if nbr_faust == 0:
         properties = control.compound_properties
         faust = ast.ControlFaust ()
         if len (properties) == 0:
            bind = ast.FaustBind ()
            address_value = '/' + module.name + '/' + control.name
            address = ast.FaustAddress (ast.StringLiteral.synthesize (address_value))
            bind.add (address)
            faust.add (bind)
         else:
            for property in properties:
               bind = ast.FaustBind ()
               address_value = '/' + module.name + '/' + control.name + '.' + property
               address = ast.FaustAddress (ast.StringLiteral.synthesize (address_value))
               bind.add (address)
               faust.add (bind)
         control.add (faust)
      elif nbr_faust == 1:
         faust = faust_entities [0]
         binds = [e for e in faust.entities if e.is_faust_bind]
         for bind in binds:
            addresses = [e for e in bind.entities if e.is_faust_address]
            nbr_addresses = len (addresses)
            if nbr_addresses == 0:
               raise error.missing_required (bind, ast.FaustAddress)
            elif nbr_addresses > 1:
               raise error.multiple_definition (bind, addresses)

            address = addresses [0]

            faust_properties = [e for e in bind.entities if e.is_faust_property]
            nbr_faust_properties = len (faust_properties)

            if nbr_faust_properties > 1:
               raise error.multiple_definition (bind, faust_properties)

            properties = control.compound_properties
            if not properties:
               if nbr_faust_properties == 1:
                  faust_property = faust_properties [0]
                  err = error.Error ()
                  selector = faust_property.source_context_part ('name')
                  err.add_error ("Unknown property '%s'" % faust_property, faust_property)
                  err.add_context (faust_property)
                  raise error
            else:
               if nbr_faust_properties == 0:
                  raise error.missing_required (bind, ast.FaustProperty)
               faust_property = faust_properties [0]
               if not faust_property.name in control.compound_properties:
                  err = error.Error ()
                  selector = faust_property.source_context_part ('name')
                  err.add_error ("Unknown property '%s'" % faust_property, faust_property)
                  err.add_context (faust_property)
                  raise error
      else:
         raise error.multiple_definition (control, faust_entities)

      faust_entities = [e for e in control.entities if e.is_control_faust]
      faust = faust_entities [0]
      binds = [e for e in faust.entities if e.is_faust_bind]
      for bind in binds:
         suffix = '.' + bind.property_ if bind.property_ is not None else ''
         object = lambda: None
         object.control = control
         object.property = bind.property_
         object.qualified = control.name + suffix
         object.value = None
         module.faust_addresses [bind.address.path] = object

#      inits = [e for e in faust.entities if e.is_control_faust_init]
#      for init in inits:
#         suffix = '.' + init.property_ if init.property_ is not None else ''
#         object = lambda: None
#         object.control = control
#         object.property = init.property_
#         object.qualified = control.name + suffix
#         object.value = init.value
#         module.faust_addresses [init.address.path] = object
#

   #--------------------------------------------------------------------------

   def load_board_definition (self, module):
      module_board = 'daisy_seed' if module.board is None else module.board.name

      path_definition = os.path.join (PATH_BOARDS, module_board, 'definition.py')

      try:
         file = open (path_definition, 'r')
      except OSError:
         err = error.Error ()
         context = module.board.source_context
         err.add_error ("Undefined board '%s'" % context, context)
         err.add_context (context)
         raise err

      with file:
         board_definition = eval (file.read ())

      return board_definition


   #--------------------------------------------------------------------------

   def update_pools (self, control):
      if 'pools' not in self._board_definition:
         return # board doesn't support auto pin allocation

      pins = [e for e in control.entities if e.is_pin]
      for pin in pins:
         self.remove_pools_pin (pin.name)

      pin_arrays = [e for e in control.entities if e.is_pin_array]
      for pin_array in pin_arrays:
         for pin_name in pin_array.names:
            self.remove_pools_pin (pin_name)


   #--------------------------------------------------------------------------

   def remove_pools_pin (self, pin_name):
      pools = self._board_definition ['pools']
      for key, value in pools.items ():
         if pin_name in value:
            value.remove (pin_name)


   #--------------------------------------------------------------------------

   def allocate_pin (self, control):
      if 'pools' not in self._board_definition:
         return # board doesn't support auto pin allocation

      pools = self._board_definition ['pools']
      control_pools = self._board_definition ['kinds'][control.kind]['pools']

      def generate_identifier (name):
         node = lambda: None
         node.value = name
         node.position = None
         return adapter.Identifier (None, node)

      def raise_pool_empty (pool_type):
         err = error.Error ()
         context = control.source_context
         err.add_error ("No more pin of type %s" % pool_type, context)
         err.add_context (context)
         raise err

      if control.is_pin_single:
         pins = [e for e in control.entities if e.is_pin]
         nbr_pins = len (pins)

         if nbr_pins == 0:
            pool_type = control_pools [0]
            pool = pools [pool_type]
            if len (pool) == 0:
               raise_pool_empty (pool_type)

            pin_name = pool.pop (0)
            pin = ast.Pin (generate_identifier (pin_name))
            control.entities.append (pin)

      elif control.is_pin_multiple:
         pin_arrays = [e for e in control.entities if e.is_pin_array]
         nbr_pin_arrays = len (pin_arrays)

         if nbr_pin_arrays == 0:
            identifiers = []
            for pool_type in control_pools:
               pool = pools [pool_type]
               if len (pool) == 0:
                  raise_pool_empty (pool_type)

               pin_name = pool.pop (0)
               identifiers.append (generate_identifier (pin_name))

            pin_array = ast.Pins (identifiers)
            control.entities.append (pin_array)


   #--------------------------------------------------------------------------

   def make_unused_pins (self, module):
      if 'pools' not in self._board_definition:
         return # board doesn't support auto pin allocation

      module.unused_pins = []
      pools = self._board_definition ['pools']
      for key, value in pools.items ():
         module.unused_pins.extend (value)


   #--------------------------------------------------------------------------

   def make_cascade_eval_list (self, module):
      for control in module.controls:
         if control.is_kind_in:
            self.visit_cascade (module, control)


   #--------------------------------------------------------------------------

   def visit_cascade (self, module, control):
      if self.is_cascade_visited (control):
         return

      if self.is_cascade_visiting (control):
         err = error.Error ()
         context = module.source_context
         err.add_error ("Cascade loop", context)
         err.add_context (context)
         raise err

      self.mark_cascade_visiting (control)

      if control.cascade_to is not None:
         control_next = control.cascade_to.reference
         self.visit_cascade (module, control_next)

      self.remove_cascade_visiting (control)
      self.mark_cascade_visited (control)
      module.cascade_eval_list.insert (0, control)


   #--------------------------------------------------------------------------

   def mark_cascade_visiting (self, control):
      setattr (control, '_cascade_visiting', None)


   #--------------------------------------------------------------------------

   def remove_cascade_visiting (self, control):
      delattr (control, '_cascade_visiting')


   #--------------------------------------------------------------------------

   def is_cascade_visiting (self, control):
      return hasattr (control, '_cascade_visiting')


   #--------------------------------------------------------------------------

   def mark_cascade_visited (self, control):
      setattr (control, '_cascade_visited', None)


   #--------------------------------------------------------------------------

   def is_cascade_visited (self, control):
      return hasattr (control, '_cascade_visited')
