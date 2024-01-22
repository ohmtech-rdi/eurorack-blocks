##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
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
      path_cpp = os.path.join (path, 'plugin_vcvrack.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      if module.format.is_1590bb2_portrait:
         template = template.replace ('%add_screws%', 'false')
      else:
         template = template.replace ('%add_screws%', 'true')

      template = self.replace_config_controls_bind (template, module.entities);
      template = self.replace_normalling_process (template, module.normalling_eval_list);
      template = self.replace_controls_preprocess (template, module.entities);
      template = self.replace_controls_postprocess (template, module.entities);
      template = self.replace_controls_widget (template, module, module.entities);

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_config_controls_bind (self, template, entities):
      nbr_params = 0
      nbr_inputs = 0
      nbr_outputs = 0
      nbr_lights = 0

      controls_bind_config = ''

      for entity in entities:
         if entity.is_control:
            control = entity
            category = self.control_kind_to_vcv_category (control)
            nbr_ids = self.control_kind_to_vcv_id_count (control)

            if category == 'Param':
               control.vcv_param_index = nbr_params
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'params', nbr_params)
               controls_bind_config += '   configParam (%d, decltype (module.ui.%s)::ValueMin, decltype (module.ui.%s)::ValueMax, 0.5f * (decltype (module.ui.%s)::ValueMin + decltype (module.ui.%s)::ValueMax), "%s");\n\n' % (nbr_params, control.name, control.name, control.name, control.name, control.name)
               nbr_params += nbr_ids

            elif category == 'Input':
               control.vcv_input_index = nbr_inputs
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'inputs', nbr_inputs)
               controls_bind_config += '   configInput (%d, "%s");\n\n' % (nbr_inputs, control.name)
               nbr_inputs += nbr_ids

            elif category == 'Output':
               control.vcv_output_index = nbr_outputs
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'outputs', nbr_outputs)
               controls_bind_config += '   configOutput (%d, "%s");\n\n' % (nbr_outputs, control.name)
               nbr_outputs += nbr_ids

            elif category == 'Light':
               control.vcv_light_index = nbr_lights
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'lights', nbr_lights)
               controls_bind_config += '   configLight (%d, "%s");\n\n' % (nbr_lights, control.name)
               nbr_lights += nbr_ids

      template = template.replace ('%module.nbr_params%', str (nbr_params))
      template = template.replace ('%module.nbr_inputs%', str (nbr_inputs))
      template = template.replace ('%module.nbr_outputs%', str (nbr_outputs))
      template = template.replace ('%module.nbr_lights%', str (nbr_lights))

      template = template.replace ('%  module.controls.bind+config%', controls_bind_config)

      return template


   #--------------------------------------------------------------------------

   def replace_normalling_process (self, template, controls):
      lines = ''

      for control in controls:
         if control.normalling_from is not None:
            if not control.normalling_from.is_nothing:
               lines += '   if (!inputs [%d].isConnected ())\n' % control.vcv_input_index
               lines += '   {\n'
               lines += '      inputs [%d].setVoltage (inputs [%d].getVoltage ());\n' % (control.vcv_input_index, control.normalling_from.reference.vcv_input_index)
               lines += '   }\n'

      return template.replace ('%  normalling_process%', lines)


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

   def replace_controls_widget (self, template, module, entities):
      lines = ''
      nbr_params = 0
      nbr_inputs = 0
      nbr_outputs = 0
      nbr_lights = 0

      offset_x = 0.0
      offset_y = 0.0

      if module.format.is_1590bb2_portrait:
         offset_x = 6.34
         offset_y = 9.0

      for entity in entities:
         if entity.is_control:
            control = entity
            category = self.control_kind_to_vcv_category (control)
            nbr_ids = self.control_kind_to_vcv_id_count (control)

            func_category = category
            if func_category == 'Light':
               func_category = '_child_auto'

            if control.rotation is None:
               rotation = 0
            else:
               rotation = control.rotation.degree_top_down % 360

            rotation_rad = rotation * 2.0 * math.pi / 360.0

            if category == 'Param':
               index = nbr_params
               nbr_params += nbr_ids

            elif category == 'Input':
               index = nbr_inputs
               nbr_inputs += nbr_ids

            elif category == 'Output':
               index = nbr_outputs
               nbr_outputs += nbr_ids

            elif category == 'Light':
               index = nbr_lights
               nbr_lights += nbr_ids

            if category in ['Param', 'Input', 'Output', 'Light']:
               lines += '   {\n'
               lines += '      auto control_ptr = create%sCentered <%s> (mm2px (Vec (%ff, %ff)), module_, %d);\n' % (
                  category, control.simulator_class, control.position.x.mm + offset_x, control.position.y.mm + offset_y, index
               )
               lines += '      control_ptr->rotate (float (%f));\n' % rotation_rad
               lines += '      add%s (control_ptr);\n' % func_category
               lines += '   }\n'

            else:
               lines += '   if (module_ptr != nullptr)\n'
               lines += '   {\n'
               lines += '      auto control_ptr = erb::createWidgetCentered <%s> (mm2px (Vec (%ff, %ff)), module_ptr->module_uptr->ui.%s);\n' % (
                  control.simulator_class, control.position.x.mm + offset_x, control.position.y.mm + offset_y, control.name
               )
               lines += '      control_ptr->rotate (float (%f));\n' % rotation_rad
               lines += '      addChild (control_ptr);\n'
               lines += '   }\n'

            lines += '\n'

      return template.replace ('%  controls_widget%', lines)


   #--------------------------------------------------------------------------

   def control_kind_to_vcv_category (self, control):
      kind_category_map = {
         'AudioIn': 'Input',
         'AudioOut': 'Output',
         'Button': 'Param',
         'CvIn': 'Input',
         'CvOut': 'Output',
         'Display': None,
         'Encoder': 'Param',
         'EncoderButton': 'Param',
         'GateIn': 'Input',
         'GateOut': 'Output',
         'Led': 'Light',
         'LedBi': 'Light',
         'LedRgb': 'Light',
         'Pot': 'Param',
         'Switch': 'Param',
         'Trim': 'Param',
      }

      return kind_category_map [control.kind]


   #--------------------------------------------------------------------------

   def control_kind_to_vcv_id_count (self, control):
      kind_vcv_id_count_map = {
         'AudioIn': 1,
         'AudioOut': 1,
         'Button': 1,
         'CvIn': 1,
         'CvOut': 1,
         'Display': None,
         'Encoder': 1,
         'EncoderButton': 2,
         'GateIn': 1,
         'GateOut': 1,
         'Led': 1,
         'LedBi': 2,
         'LedRgb': 3,
         'Pot': 1,
         'Switch': 1,
         'Trim': 1,
      }

      return kind_vcv_id_count_map [control.kind]
