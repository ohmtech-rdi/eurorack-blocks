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

      if control.kind in ['Pot', 'Trim', 'CvIn', 'CvOut']:
         if control.mode is None:
            if control.kind in ['Pot', 'Trim']:
               control_type = '%s <erb::FloatRange::Normalized>' % control.kind
            elif control.kind in ['CvIn', 'CvOut']:
               control_type = '%s <erb::FloatRange::Bipolar>' % control.kind

         elif control.mode.is_normalized:
            control_type = '%s <erb::FloatRange::Normalized>' % control.kind

         elif control.mode.is_bipolar:
            control_type = '%s <erb::FloatRange::Bipolar>' % control.kind

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
         control_type = control.erb_class

      else:
         control_type = control.kind

      if control.is_pin_single:
         args =  'board.%s' % module.board.pin (control.pin.name).bind.expression
      elif control.is_pin_multiple:
         args = ', '.join (map (lambda name: 'board.%s' % module.board.pin (name).bind.expression, control.pins.names))

      if control.kind == 'GateOut' or control.kind.startswith ('Led'):
         args += ', board.clock ()'

      source_code = '   erb::%s %s { %s };\n' % (control_type, control.name, args)

      return source_code


   #--------------------------------------------------------------------------

   def generate_alias (self, alias):

      source_code = '   decltype (%s) & %s { %s };\n' % (alias.reference.name, alias.name, alias.reference.name)

      return source_code
