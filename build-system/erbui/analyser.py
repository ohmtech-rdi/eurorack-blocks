##############################################################################
#
#     analyser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from . import adapter
from . import ast
from . import error

from difflib import get_close_matches



class Analyser:

   def __init__ (self):
      self._pin_names = []
      self._pin_out = {} # map from pin name to hardware number
      self._used_pins = {} # map from hardware number to declaration

   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):
      assert global_namespace.is_global_namespace

      for module in global_namespace.modules:
         self.analyse_module (module)

   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      assert module.is_module

      self.make_pin_names (module)
      self.make_pin_out (module)

      for control in module.controls:
         self.analyse_control (module, control)

      for multiplexer in module.multiplexers:
         self.analyse_multiplexer (module, multiplexer)

      for alias in module.aliases:
         self.resolve_alias (module, alias)

   #--------------------------------------------------------------------------

   def analyse_multiplexer (self, module, multiplexer):
      assert multiplexer.is_multiplexer

      for control in multiplexer.controls:
         self.analyse_control (multiplexer, control)

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

      if pin.name not in self._pin_names:
         raise error.unknown_pin (pin, self._pin_names)

      if pin.name in self._pin_out:
         hw_pin = self._pin_out [pin.name]

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
         elif entity.is_multiplexer:
            for subcontrol in entity.controls:
               if alias.identifier_reference.name == subcontrol.name:
                  control = subcontrol

      if control is None:
         possible_tokens = []
         for entity in module.entities:
            if entity.is_control:
               possible_tokens.append (entity.identifier_name)
            elif entity.is_multiplexer:
               for control in entity.controls:
                  possible_tokens.append (control.identifier_name)

         def make_dict (fun, iterable):
            return dict (zip (map (fun, iterable), iterable))

         possible_names = make_dict (lambda x: x.value, possible_tokens)
         matches = get_close_matches (alias.identifier_reference.name, possible_names.keys ())

         fixit_decl_tokens = [possible_names [match_name] for match_name in matches]
         fixit_decls_sc = [adapter.SourceContext.from_token (f) for f in fixit_decl_tokens]

         raise error.undefined_reference (alias, fixit_decls_sc)

      alias.reference = control


   #--------------------------------------------------------------------------

   def make_pin_names (self, module):
      self._pin_names = []

      for i in range (0, 31):
         self._pin_names.append ('Pin%d' % i)

      for i in range (0, 12):
         self._pin_names.append ('AdcPin%d' % i)

      for i in range (0, 8):
         self._pin_names.append ('MultiplexerPin%d' % i)

      self._pin_names.append ('AudioInPinLeft')
      self._pin_names.append ('AudioInPinRight')
      self._pin_names.append ('AudioInPin0')
      self._pin_names.append ('AudioInPin1')

      self._pin_names.append ('AudioOutPinLeft')
      self._pin_names.append ('AudioOutPinRight')
      self._pin_names.append ('AudioOutPin0')
      self._pin_names.append ('AudioOutPin1')

      self._pin_names.append ('PinNC')
      self._pin_names.append ('AdcPinNC')
      self._pin_names.append ('MultiplexerPinNC')
      self._pin_names.append ('AudioInPinNC')
      self._pin_names.append ('AudioOutPinNC')

   #--------------------------------------------------------------------------

   def make_pin_out (self, module):
      self._pin_out = {}

      for i in range (0, 15):
         self._pin_out ['Pin%d' % i] = i + 1

      self._pin_out ['AudioInPinLeft'] = 16
      self._pin_out ['AudioInPin0'] = 16
      self._pin_out ['AudioInPinRight'] = 17
      self._pin_out ['AudioInPin1'] = 17

      self._pin_out ['AudioOutPinLeft'] = 18
      self._pin_out ['AudioOutPin0'] = 18
      self._pin_out ['AudioOutPinRight'] = 19
      self._pin_out ['AudioOutPin1'] = 19

      for i in range (15, 31):
         self._pin_out ['Pin%d' % i] = i + 7

      for i in range (0, 11):
         self._pin_out ['AdcPin%d' % i] = i + 22

      self._pin_out ['AdcPin11'] = 35
