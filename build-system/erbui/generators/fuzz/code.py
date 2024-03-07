##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import random

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
      path_cpp = os.path.join (path, 'fuzz', 'main.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)
      template = self.replace_controls_context_decl (template, module.entities);
      template = self.replace_controls_context_process (template, module.entities);
      template = self.replace_board_preprocess (template, module.entities);
      template = self.replace_board_postprocess (template, module.entities);
      template = self.replace_controls_instrument (template, module.entities);
      template = self.replace_controls_preprocess (template, module.entities);
      template = self.replace_controls_postprocess (template, module.entities);
      template = self.replace_controls_check_audio (template, module.entities);

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_controls_context_decl (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control and entity.is_input:
            if entity.kind in ['AudioIn']:
               lines += '      Vco %s = { %f, %f };\n' % (entity.name, random.uniform (500.0, 600.0), random.uniform (0.01, 0.1))
            elif entity.kind in ['CvIn']:
               lines += '      Lfo %s = { %f, %f };\n' % (entity.name, random.uniform (10.0, 100.0), random.uniform (0.01, 0.1))
            elif entity.kind in ['Pot', 'Trim']:
               lines += '      Lfo %s = { %f, %f };\n' % (entity.name, random.uniform (0.1, 1.0), random.uniform (0.01, 0.1))
            elif entity.kind in ['Button']:
               lines += '      Lfo %s = { %f, %f };\n' % (entity.name, random.uniform (0.1, 1.0), random.uniform (0.01, 0.1))
            elif entity.kind in ['GateIn']:
               lines += '      Lfo %s = { %f, %f };\n' % (entity.name, random.uniform (10.0, 100.0), random.uniform (0.01, 0.1))
            elif entity.kind in ['Switch']:
               lines += '      Lfo %s_0 = { %f, %f };\n' % (entity.name, random.uniform (0.1, 1.0), random.uniform (0.01, 0.1))
               lines += '      Lfo %s_1 = { %f, %f };\n' % (entity.name, random.uniform (0.1, 1.0), random.uniform (0.01, 0.1))

      return template.replace ('%     controls_context_decl%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_context_process (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control and entity.is_input:
            if entity.kind in ['AudioIn']:
               lines += '      context.%s.process ();\n' % entity.name
            elif entity.kind in ['CvIn', 'Pot', 'Trim']:
               lines += '      context.%s.process ();\n' % entity.name
            elif entity.kind in ['Button', 'GateIn']:
               lines += '      context.%s.process ();\n' % entity.name
            elif entity.kind in ['Switch']:
               lines += '      context.%s_0.process ();\n' % entity.name
               lines += '      context.%s_1.process ();\n' % entity.name

      return template.replace ('%     controls_context_process%', lines)


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

   def replace_controls_instrument (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control and entity.is_input:
            if entity.kind in ['AudioIn']:
               lines += '      const_cast <erb::Buffer &> (module.ui.%s.impl_data) = context.%s;\n' % (entity.name, entity.name)
            elif entity.kind in ['CvIn', 'Pot', 'Trim']:
               lines += '      const_cast <float &> (module.ui.%s.impl_data) = context.%s;\n' % (entity.name, entity.name)
            elif entity.kind in ['Button', 'GateIn']:
               lines += '      const_cast <uint8_t &> (module.ui.%s.impl_data) = context.%s < 0.5f;\n' % (entity.name, entity.name)
            elif entity.kind in ['Switch']:
               lines += '      const_cast <uint8_t &> (module.ui.%s._0.impl_data) = context.%s_0 < 0.5f;\n' % (entity.name, entity.name)
               lines += '      const_cast <uint8_t &> (module.ui.%s._1.impl_data) = context.%s_1 < 0.5f;\n' % (entity.name, entity.name)

      return template.replace ('%     controls_instrument%', lines)


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


   #--------------------------------------------------------------------------

   def replace_controls_check_audio (self, template, entities):
      lines = ''

      for entity in entities:
         if entity.is_control and entity.is_output:
            if entity.kind in ['AudioOut']:
               lines += '      check_audio_buffer (module.ui.%s.impl_data);\n' % entity.name

      return template.replace ('%     controls_check_audio%', lines)


