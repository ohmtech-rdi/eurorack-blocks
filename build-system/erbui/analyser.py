##############################################################################
#
#     analyser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import re
from . import adapter
from . import ast
from . import error
from .generators.front_pcb import s_expression
from .analysers import style

import os
from difflib import get_close_matches

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')



class Analyser:

   def __init__ (self):
      self._cascade_index = 0

   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):
      assert global_namespace.is_global_namespace

      for module in global_namespace.modules:
         self.analyse_module (module)

      analyser_style = style.AnalyserStyle ()
      analyser_style.analyse (global_namespace)


   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      assert module.is_module

      self.analyse_board (module)

      if module.route == None:
         module.add (ast.Route (adapter.BuiltIn ('wire')))

      self.expand_pin_arrays (module)

      self.exclude_pins (module)

      self.set_auto_board_width (module)

      for control in module.controls:
         self.update_pools (module, control)

      for control in module.controls:
         self.allocate_pin (module, control)

      self.make_unused_pins (module)

      for control in module.controls:
         self.analyse_control (module, control)

      for alias in module.aliases:
         self.resolve_alias (module, alias)

      self.make_cascade_eval_list (module)

      self.resolve_module_faust_addresses (module)


   #--------------------------------------------------------------------------

   def analyse_board (self, module):
      assert module.is_module

      if module.super_identifier != None:
         module.add (ast.Board (module.super_identifier))
      elif module.board == None:
         module.add (ast.Board (adapter.IdentifierSynthesized ('default')))

      if not module.board.inline:
         module.board.load_builtin ()


   #--------------------------------------------------------------------------

   def expand_pin_arrays (self, module):
      pin_arrays = [e for e in module.board.entities if e.is_board_pin_array]
      for pin_array in pin_arrays:
         match = re.search (r'\d+$', pin_array.identifier.name)
         if match is None:
            err = error.Error ()
            err.add_error ("Pins cannot find range start in '%s'" % pin_array.identifier.name, pin_array.identifier)
            err.add_context (pin_array.identifier)
            raise err
         base = pin_array.identifier.name [: -len (match.group ())]
         start_range = int (match.group ())
         end_range = int (pin_array.end_range.value)

         for index in range (start_range, end_range + 1):
            board_pin = ast.BoardPin (adapter.IdentifierSynthesized ('%s%d' % (base, index)))
            board_pin.add (pin_array.accept)
            bind_str = eval ("f'%s'" % pin_array.bind.expression)
            board_pin.add (ast.BoardPinBind (ast.StringLiteral.synthesize (bind_str)))
            if pin_array.type_:
               board_pin.add (pin_array.type_)
            module.board.add (board_pin)


   #--------------------------------------------------------------------------

   def exclude_pins (self, module):
      epins = [e for e in module.entities if e.is_exclude_pins]
      for epin in epins:
         for name in epin.names:
            for pool in module.board.pools:
               pin = pool.find_pin (name)
               if pin != None:
                  pin.mark_unavailable ()


   #--------------------------------------------------------------------------

   def set_auto_board_width (self, module):
      if module.board.width == None:
         return # board doesn't support fixed width

      entities = [e for e in module.entities if e.is_width]
      if len (entities) == 0:
         module.add (module.board.width)


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

      pin_names = module.board.pin_names

      if pin.name not in pin_names:
         raise error.unknown_pin (pin, pin_names)


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
      control.add (cascade_from)
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

   def update_pools (self, module, control):
      if len (module.board.pools) == 0:
         return # board doesn't support auto pin allocation

      pins = [e for e in control.entities if e.is_pin]
      for pin in pins:
         self.remove_pools_pin (module, pin.name)

      pin_arrays = [e for e in control.entities if e.is_pin_array]
      for pin_array in pin_arrays:
         for pin_name in pin_array.names:
            self.remove_pools_pin (module, pin_name)


   #--------------------------------------------------------------------------

   def remove_pools_pin (self, module, pin_name):
      for pool in module.board.pools:
         pin = pool.find_pin (pin_name)
         if pin != None:
            pin.mark_unavailable ()


   #--------------------------------------------------------------------------

   def allocate_pin (self, module, control):
      if len (module.board.pools) == 0:
         return # board doesn't support auto pin allocation

      control_pools = module.board.kind (control.kind).pools.names

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
            pool = module.board.pool (pool_type).available_pins
            if len (pool) == 0:
               raise_pool_empty (pool_type)

            pool_pin = pool [0]
            pool_pin.mark_unavailable ()
            pin_identifier = pool_pin.identifier
            pin = ast.Pin (pin_identifier)
            control.add (pin)

      elif control.is_pin_multiple:
         pin_arrays = [e for e in control.entities if e.is_pin_array]
         nbr_pin_arrays = len (pin_arrays)

         if nbr_pin_arrays == 0:
            identifiers = []
            for pool_type in control_pools:
               pool = module.board.pool (pool_type).available_pins
               if len (pool) == 0:
                  raise_pool_empty (pool_type)

               pool_pin = pool [0]
               pool_pin.mark_unavailable ()
               pin_identifier = pool_pin.identifier
               identifiers.append (pin_identifier)

            pin_array = ast.Pins (identifiers)
            control.add (pin_array)


   #--------------------------------------------------------------------------

   def make_unused_pins (self, module):
      if len (module.board.pools) == 0:
         return # board doesn't support auto pin allocation

      module.unused_pins = []

      for pool in module.board.pools:
         for pin in pool.pins:
            if pin.available:
               # if it is still available at this stage, then it is not used
               module.unused_pins.append (pin.name)

      # add excluded pins (not available but unused as well)
      exclude_pinss = [e for e in module.entities if e.is_exclude_pins]
      for exclude_pins in exclude_pinss:
         module.unused_pins.extend (exclude_pins.names)



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
