##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



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

      board_to_class = {
         'kivu12': 'BoardKivu12',
      }

      board_class = board_to_class [module.board.name]

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
