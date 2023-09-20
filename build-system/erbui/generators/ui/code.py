##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')



class Code:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'code_template.h')
      path_cpp = os.path.join (path, '%sUi.h' % module.name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      include_path = os.path.relpath (module.board.include.path, os.path.dirname (path))

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%module.board.include.path%', include_path)
      template = template.replace ('%type(module.board)%', module.board.class_.name)

      entities_content = self.generate_entities (module, module.entities)
      template = template.replace ('%entities%', entities_content)

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_entities (self, module, entities):
      content = ''

      for entity in entities:
         if entity.is_control:
            content += self.generate_control (module, entity)

      for entity in entities:
         if entity.is_alias:
            content += self.generate_alias (entity)

      return content


   #--------------------------------------------------------------------------

   def generate_control (self, module, control):

      if control.kind in ['Pot', 'Trim', 'CvOut']:
         if control.mode is None:
            if control.kind in ['Pot', 'Trim']:
               control_type = '%s <erb::FloatRange::Normalized>' % control.kind
            elif control.kind in ['CvOut']:
               control_type = '%s <erb::FloatRange::Bipolar>' % control.kind

         elif control.mode.is_normalized:
            control_type = '%s <erb::FloatRange::Normalized>' % control.kind

         elif control.mode.is_bipolar:
            control_type = '%s <erb::FloatRange::Bipolar>' % control.kind

      elif control.kind in ['CvIn']:
         if control.mode is None: # default
            range = 'erb::FloatRange::Bipolar'
         elif control.mode.is_normalized:
            range = 'erb::FloatRange::Normalized'
         elif control.mode.is_bipolar:
            range = 'erb::FloatRange::Bipolar'

         if control.normalling_from is not None and control.normalling_from.is_nothing:
            base_control = 'CvInJackDetection'
         else:
            base_control = 'CvIn'

         control_type = '%s <%s>' % (base_control, range)

      elif control.kind in ['GateIn', 'AudioIn']:
         if control.normalling_from is not None and control.normalling_from.is_nothing:
            control_type = '%sJackDetection' % control.kind
         else:
            control_type = control.kind

      elif control.kind in ['Led', 'LedBi', 'LedRgb']:
         if control.kind == 'Led':
            pin_name = control.pin.name
         else:
            pin_name = control.pins.names [0]

         pin_type = module.board.pin (pin_name).type_.name
         if pin_type == 'gpio':
            control_type = '%s <erb::PinType::Gpio>' % control.kind
         elif pin_type == 'pwm':
            control_type = '%s <erb::PinType::Pwm>' % control.kind
         elif pin_type == 'dac':
            control_type = '%s <erb::PinType::Dac>' % control.kind

      elif control.kind in ['Switch']:
         nbr_positions = self.get_nbr_positions (control)
         control_type = '%s <%s>' % (control.kind, nbr_positions)

      elif control.kind in ['Display']:
         display_size = self.get_display_size (control)
         control_type = '%s <%s>' % (
            control.kind,
            'erb::FormatSsd130x <%s, %s>' % display_size
         )

      else:
         control_type = control.kind

      if control.is_pin_single:
         args =  'board.%s' % module.board.pin (control.pin.name).bind.expression
      elif control.is_pin_multiple:
         args = ', '.join (map (lambda name: 'board.%s' % module.board.pin (name).bind.expression, control.pins.names))

      if control.kind == 'GateOut' or control.kind.startswith ('Led'):
         args += ', board.clock ()'

      if control.kind in ['AudioIn', 'CvIn', 'GateIn'] and control.normalling_from is not None and control.normalling_from.is_nothing:
         args += ', board.npr ()'

      source_code = '   erb::%s %s { %s };\n' % (control_type, control.name, args)

      return source_code


   #--------------------------------------------------------------------------

   def get_nbr_positions (self, control):
      for part in control.parts:
         for symbol in part.sch.symbols:
            nbr_positions_field = symbol.property ('NbrPositions')
            if nbr_positions_field is not None:
               return nbr_positions_field

      assert False


   #--------------------------------------------------------------------------

   def get_display_size (self, control):
      for part in control.parts:
         for symbol in part.sch.symbols:
            display_width_field = symbol.property ('DisplayWidth')
            display_height_field = symbol.property ('DisplayHeight')
            if display_width_field is not None:
               return (display_width_field, display_height_field)

      assert False


   #--------------------------------------------------------------------------

   def generate_alias (self, alias):

      source_code = '   decltype (%s) & %s { %s };\n' % (alias.reference.name, alias.name, alias.reference.name)

      return source_code
