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
      self.generate_file (path, module, 'code_template.h', 'acceptance_glue.h')
      self.generate_file (path, module, 'code_template.cpp', 'acceptance_glue.cpp')


   #--------------------------------------------------------------------------

   def generate_file (self, path, module, template_name, output_name):
      path_template = os.path.join (PATH_THIS, template_name)
      path_output = os.path.join (path, output_name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)
      template = self.replace_normalling_preprocess (template, module.normalling_eval_list)
      template = self.replace_controls_preprocess (template, module.entities)
      template = self.replace_controls_postprocess (template, module.entities)
      template = self.replace_controls_name (template, module.entities)

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_normalling_preprocess (self, template, controls):
      lines = ''

      for control in controls:
         if control.normalling_from is None:
            continue
         if control.normalling_from.is_nothing:
            continue
         elif control.normalling_from.is_board_pin:
            lines += '   module.ui.board.impl_apply_normalling (module.ui.%s.impl_data, module.ui.board.%s);\n' % (control.name, control.normalling_from.reference.bind.expression)
         elif control.normalling_from.is_control:
            reference = control.normalling_from.reference
            if reference.kind != control.kind:
               raise Exception ("normalling of '%s' from '%s': %s to %s" % (control.name, reference.name, reference.kind, control.kind))
            lines += '   module.ui.board.impl_apply_normalling (module.ui.%s.impl_data, module.ui.%s.impl_data);\n' % (control.name, reference.name)
         else:
            assert False

      return template.replace ('%  normalling_preprocess%\n', lines)


   #--------------------------------------------------------------------------

   def replace_controls_preprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '   module.ui.%s.impl_preprocess ();\n' % entity.name

      return template.replace ('%  controls_preprocess%\n', lines)


   #--------------------------------------------------------------------------

   def replace_controls_postprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '   module.ui.%s.impl_postprocess ();\n' % entity.name

      return template.replace ('%  controls_postprocess%\n', lines)


   #--------------------------------------------------------------------------

   def replace_controls_name (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '   if (control_ptr == &module.ui.%s) return "%s";\n' % (entity.name, entity.name)

      return template.replace ('%  controls_name%\n', lines)
