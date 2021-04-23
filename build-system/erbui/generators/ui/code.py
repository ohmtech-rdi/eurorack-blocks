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

      template = template.replace ('%module.name%', module.name)

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

      return content


   #--------------------------------------------------------------------------

   def generate_control (self, control):

      source_code = '   erb::%s %s { module' % (control.kind, control.name)

      if control.is_pin_single:
         source_code += ', erb::' + control.pin.name
      elif control.is_pin_multiple:
         source_code += ', erb::' + ', erb::'.join (control.pins.names)

      if control.kind == 'Pot' or control.kind == 'Trim':
         if control.mode is None or control.mode.is_normalized:
            source_code += ', erb::%s::Mode::Normalized' % control.kind
         elif control.mode.is_bipolar:
            source_code += ', erb::%s::Mode::Bipolar' % control.kind

      source_code += ' };\n'

      return source_code


   #--------------------------------------------------------------------------

   def generate_multiplexer (self, multiplexer):

      source_code = '   erb::Multiplexer %s { module' % multiplexer.name
      source_code += ', erb::' + ', erb::'.join (multiplexer.pins.names)
      source_code += ' };\n'

      for control in multiplexer.controls:
         source_code += self.generate_control (control)

      return source_code
