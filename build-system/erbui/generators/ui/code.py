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
      self._board_definition = {}
      self._board_path = None


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

      self._board_definition, self._board_path = self.load_board_definition (module)
      board_class = self._board_definition ['class']
      board_include = self._board_definition ['include']

      include_path = os.path.join (self._board_path, board_include)
      include_path = os.path.relpath (include_path, os.path.dirname (path))

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%module.board.include.path%', include_path)
      template = template.replace ('%type(module.board)%', board_class)

      entities_content = self.generate_entities (module.entities)
      template = template.replace ('%entities%', entities_content)

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_entities (self, entities):
      content = ''

      for entity in entities:
         if entity.is_control:
            content += self.generate_control (entity)

      for entity in entities:
         if entity.is_alias:
            content += self.generate_alias (entity)

      return content


   #--------------------------------------------------------------------------

   def generate_control (self, control):

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

         pin_type = self._board_definition ['pins'][pin_name]['type']
         if pin_type == 'gpio':
            control_type = '%s <erb::PinType::Gpio>' % control.kind
         elif pin_type == 'pwm':
            control_type = '%s <erb::PinType::Pwm>' % control.kind
         elif pin_type == 'dac':
            control_type = '%s <erb::PinType::Dac>' % control.kind

      elif control.kind in ['Switch']:
         if control.style.is_dailywell_2ms1:
            control_type = '%s <2>' % control.kind
         elif control.style.is_dailywell_2ms3:
            control_type = '%s <3>' % control.kind

      else:
         control_type = control.kind

      def pin_name (name):
         pin_desc = self._board_definition ['pins'][name]
         if control.is_input:
            if 'bind.input' in pin_desc:
               return pin_desc ['bind.input']
            else:
               return pin_desc ['bind']
         else:
            if 'bind.output' in pin_desc:
               return pin_desc ['bind.output']
            else:
               return pin_desc ['bind']

      if control.is_pin_single:
         args =  'board.%s' % pin_name (control.pin.name)
      elif control.is_pin_multiple:
         args = ', '.join (map (lambda name: 'board.%s' % pin_name (name), control.pins.names))

      if control.kind == 'GateOut' or control.kind.startswith ('Led'):
         args += ', board.clock ()'

      source_code = '   erb::%s %s { %s };\n' % (control_type, control.name, args)

      return source_code


   #--------------------------------------------------------------------------

   def generate_alias (self, alias):

      source_code = '   decltype (%s) & %s { %s };\n' % (alias.reference.name, alias.name, alias.reference.name)

      return source_code


   #--------------------------------------------------------------------------

   def load_board_definition (self, module):

      module_board = 'default' if module.board is None else module.board.name

      path_definition = os.path.join (PATH_BOARDS, module_board, 'definition.py')

      try:
         file = open (path_definition, 'r', encoding='utf-8')
      except OSError:
         err = error.Error ()
         context = module.board.source_context
         err.add_error ("Undefined board '%s'" % context, context)
         err.add_context (context)
         raise err

      with file:
         board_definition = eval (file.read ())

      board_path = os.path.dirname (path_definition)

      return (board_definition, board_path)
