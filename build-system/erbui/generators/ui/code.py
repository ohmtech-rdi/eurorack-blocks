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

      with open (path_template, 'r') as file:
         template = file.read ()

      board_class = self.module_board_to_class (module)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%type(module.board)%', board_class)

      entities_content = self.generate_entities (module.entities)
      template = template.replace ('%entities%', entities_content)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_entities (self, entities):
      content = ''

      for entity in entities:
         if entity.is_control:
            content += self.generate_control (entity)
         elif entity.is_multiplexer:
            content += self.generate_multiplexer (entity)

      for entity in entities:
         if entity.is_alias:
            content += self.generate_alias (entity)

      return content


   #--------------------------------------------------------------------------

   def generate_control (self, control):

      if control.kind == 'Pot' or control.kind == 'Trim' or control.kind == 'CvIn':
         if control.mode is None:
            if control.kind == 'Pot' or control.kind == 'Trim':
               control_type = '%s <erb::FloatRange::Normalized>' % control.kind
            elif control.kind == 'CvIn':
               control_type = '%s <erb::FloatRange::Bipolar>' % control.kind

         elif control.mode.is_normalized:
            control_type = '%s <erb::FloatRange::Normalized>' % control.kind

         elif control.mode.is_bipolar:
            control_type = '%s <erb::FloatRange::Bipolar>' % control.kind

      else:
         control_type = control.kind

      if control.is_pin_single:
         args =  'board.%s ()' % control.pin.name.lower ()
      elif control.is_pin_multiple:
         args = ', '.join (map (lambda name: 'board.%s ()' % name.lower (), control.pins.names))

      if control.kind == 'GateOut' or control.kind.startswith ('Led'):
         args += ', board.clock ()'

      source_code = '   erb::%s %s { %s };\n' % (control_type, control.name, args)

      return source_code


   #--------------------------------------------------------------------------

   def generate_multiplexer (self, multiplexer):

      source_code = '   erb::Multiplexer %s { module' % multiplexer.name
      source_code += ', erb::' + ', erb::'.join (multiplexer.pins.names)
      source_code += ' };\n'

      for control in multiplexer.controls:
         source_code += self.generate_control (control)

      return source_code


   #--------------------------------------------------------------------------

   def generate_alias (self, alias):

      source_code = '   erb::%s & %s { %s };\n' % (alias.reference.kind, alias.name, alias.reference.name)

      return source_code


   #--------------------------------------------------------------------------

   def module_board_to_class (self, module):

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

      return board_definition ['class']
