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

   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):
      assert global_namespace.is_global_namespace

      for module in global_namespace.modules:
         self.analyse_module (module)

   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      assert module.is_module

      self._board_definition = self.load_board_definition (module)

      for control in module.controls:
         self.analyse_control (module, control)

      for alias in module.aliases:
         self.resolve_alias (module, alias)

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
