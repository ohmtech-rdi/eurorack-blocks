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
      path_cpp = os.path.join (path, 'calibration', 'calibrator.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)
      template = self.replace_board_preprocess (template, module);
      template = self.replace_controls_calibrate (template, module);

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_board_preprocess (self, template, module):
      lines = ''

      for control in module.controls:
         if control.kind == 'CvIn':
            lines += '      module_ui.board.impl_preprocess (BoardType::%s);\n' % control.pin.name

      return template.replace ('%     board_preprocess%', lines)


   #--------------------------------------------------------------------------

   def replace_controls_calibrate (self, template, module):
      lines = ''

      cv_in_pool = module.board.kind ('CvIn').pools.names [0]
      cv_ins = module.board.pool (cv_in_pool).pin_names

      for control in module.controls:
         if control.kind == 'CvIn':
            cv_in_index = cv_ins.index (control.pin.name)
            lines += '   data.cv_ins [%d] = calibrate (module_ui, module_ui.%s, "%s");\n' % (cv_in_index, control.name, control.name)

      return template.replace ('%  controls_calibrate%', lines)
