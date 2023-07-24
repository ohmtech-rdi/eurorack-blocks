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
      path_template = os.path.join (PATH_THIS, 'code_template.cpp')
      path_cpp = os.path.join (path, 'perf', 'main.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)
      template = self.replace_board_preprocess (template, module.entities);
      template = self.replace_board_postprocess (template, module.entities);
      template = self.replace_controls_preprocess (template, module.entities);
      template = self.replace_controls_postprocess (template, module.entities);

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_board_preprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control and entity.is_input:
            for sub_entity in entity.entities:
               if sub_entity.is_pin:
                  lines += '      module.ui.board.impl_preprocess (BoardType::%s);\n' % sub_entity.name
               elif sub_entity.is_pin_array:
                  for name in sub_entity.names:
                     lines += '      module.ui.board.impl_preprocess (BoardType::%s);\n' % name


      return template.replace ('%     board_preprocess%', lines)


   #--------------------------------------------------------------------------

   def replace_board_postprocess (self, template, entities):
      lines = ''

      board_type = 'decltype (module.ui.board)'

      for entity in entities:
         if entity.is_control and entity.is_output:
            for sub_entity in entity.entities:
               if sub_entity.is_pin:
                  lines += '      module.ui.board.impl_postprocess (BoardType::%s);\n' % sub_entity.name
               elif sub_entity.is_pin_array:
                  for name in sub_entity.names:
                     lines += '      module.ui.board.impl_postprocess (BoardType::%s);\n' % name


      return template.replace ('%     board_postprocess%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_preprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '      module.ui.%s.impl_preprocess ();\n' % entity.name

      return template.replace ('%     controls_preprocess%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_postprocess (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control:
            lines += '      module.ui.%s.impl_postprocess ();\n' % entity.name

      return template.replace ('%     controls_postprocess%', lines)


