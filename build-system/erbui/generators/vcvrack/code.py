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

      if module.format.is_1590bb2_portrait or module.format.is_1590dd_landscape:
         template = template.replace ('%add_screws%', 'false')
      else:
         template = template.replace ('%add_screws%', 'true')

      template = self.replace_config_controls_bind (template, module.entities);
      template = self.replace_normalling_process (template, module.normalling_eval_list);
      template = self.replace_controls_preprocess (template, module.entities);
      template = self.replace_controls_postprocess (template, module.entities);
      template = self.replace_controls_widget (template, module, module.entities);
      template = self.replace_has_midi_input (template, module, module.entities);

      with open (path_cpp, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_config_controls_bind (self, template, entities):
      index_param = 0
      index_input = 0
      index_output = 0
      index_light = 0

      bind_config = ''

      for entity in entities:
         if entity.is_control:
            control = entity

            if control.kind in ['Button', 'Encoder', 'EncoderButton', 'Pot', 'Switch', 'Trim']:
               control.vcv_param_index = index_param
               bind_config +=  '   {\n'
               bind_config += f'      module.ui.board.impl_bind (module.ui.{control.name}, params [{index_param}]);\n'
               bind_config += f'      const float val_min = decltype (module.ui.{control.name})::ValueMin;\n'
               bind_config += f'      const float val_max = decltype (module.ui.{control.name})::ValueMax;\n'
               bind_config +=  '      const float val_default = (val_min + val_max) * 0.5f;\n'
               bind_config += f'      configParam ({index_param}, val_min, val_max, val_default, "{control.name}");\n'
               bind_config +=  '   }\n\n'
               index_param += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioIn', 'CvIn', 'GateIn']:
               control.vcv_input_index = index_input
               bind_config +=  '   {\n'
               bind_config += f'      module.ui.board.impl_bind (module.ui.{control.name}, inputs [{index_input}]);\n'
               bind_config += f'      configInput ({index_input}, "{control.name}");\n'
               bind_config +=  '   }\n\n'
               index_input += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioStereoIn']:
               control.vcv_input_index = index_input
               bind_config +=  '   {\n'
               bind_config += f'      module.ui.board.impl_bind (module.ui.{control.name}, inputs [{index_input}]);\n'
               bind_config += f'      configInput ({index_input+0}, "{control.name}.left");\n'
               bind_config += f'      configInput ({index_input+1}, "{control.name}.right");\n'
               bind_config +=  '   }\n\n'
               index_input += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioOut', 'CvOut', 'GateOut']:
               control.vcv_output_index = index_output
               bind_config +=  '   {\n'
               bind_config += f'      module.ui.board.impl_bind (module.ui.{control.name}, outputs [{index_output}]);\n'
               bind_config += f'      configOutput ({index_output}, "{control.name}");\n'
               bind_config +=  '   }\n\n'
               index_output += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioStereoOut']:
               control.vcv_output_index = index_output
               bind_config +=  '   {\n'
               bind_config += f'      module.ui.board.impl_bind (module.ui.{control.name}, outputs [{index_output}]);\n'
               bind_config += f'      configOutput ({index_output+0}, "{control.name}.left");\n'
               bind_config += f'      configOutput ({index_output+1}, "{control.name}.right");\n'
               bind_config +=  '   }\n\n'
               index_output += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['Led', 'LedBi', 'LedRgb']:
               control.vcv_light_index = index_light
               bind_config +=  '   {\n'
               bind_config += f'      module.ui.board.impl_bind (module.ui.{control.name}, lights [{index_light}]);\n'
               bind_config += f'      configLight ({index_light}, "{control.name}");\n'
               bind_config +=  '   }\n\n'
               index_light += self.control_kind_to_vcv_id_count (control)

      template = template.replace ('%module.nbr_params%', str (index_param))
      template = template.replace ('%module.nbr_inputs%', str (index_input))
      template = template.replace ('%module.nbr_outputs%', str (index_output))
      template = template.replace ('%module.nbr_lights%', str (index_light))

      template = template.replace ('%  module.controls.bind+config%', bind_config)

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
      index_param = 0
      index_input = 0
      index_output = 0
      index_light = 0

      offset_x = 0.0
      offset_y = 0.0

      if module.format.is_1590bb2_portrait:
         offset_x = 6.34
         offset_y = 9.0
      elif module.format.is_1590dd_landscape:
         offset_x = 2.52
         offset_y = 8.5

      for entity in entities:
         if entity.is_control:
            control = entity

            if control.rotation is None:
               rotation = 0
            else:
               rotation = control.rotation.degree_top_down % 360

            rotation_rad = rotation * 2.0 * math.pi / 360.0
            x = control.position.x.mm + offset_x
            y = control.position.y.mm + offset_y
            simulator_class = control.args ['simulator_class']

            if control.kind in ['Button', 'Encoder', 'EncoderButton', 'Pot', 'Switch', 'Trim']:
               lines +=  '   {\n'
               lines += f'      auto control_ptr = createParamCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_, {index_param});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      addParam (control_ptr);\n'
               lines +=  '   }\n'
               index_param += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioIn', 'CvIn', 'GateIn']:
               lines +=  '   {\n'
               lines += f'      auto control_ptr = createInputCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_, {index_input});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      addInput (control_ptr);\n'
               lines +=  '   }\n'
               index_input += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioStereoIn']:
               lines +=  '   {\n'
               lines += f'      auto control_ptr = erb::createInputStereoCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_, {index_input});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      addChild (control_ptr);\n'
               lines +=  '   }\n'
               index_input += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioOut', 'CvOut', 'GateOut']:
               lines +=  '   {\n'
               lines += f'      auto control_ptr = createOutputCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_, {index_output});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      addOutput (control_ptr);\n'
               lines +=  '   }\n'
               index_output += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['AudioStereoOut']:
               lines +=  '   {\n'
               lines += f'      auto control_ptr = erb::createOutputStereoCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_, {index_output});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      addChild (control_ptr);\n'
               lines +=  '   }\n'
               index_output += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['Led', 'LedBi', 'LedRgb']:
               lines +=  '   {\n'
               lines += f'      auto control_ptr = createLightCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_, {index_light});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      add_child_auto (control_ptr);\n'
               lines +=  '   }\n'
               index_light += self.control_kind_to_vcv_id_count (control)

            elif control.kind in ['Display']:
               lines +=  '   if (module_ptr != nullptr)\n'
               lines +=  '   {\n'
               lines += f'      auto control_ptr = erb::createWidgetCentered <{simulator_class}> (mm2px (Vec ({x}f, {y}f)), module_ptr->module_uptr->ui.{control.name});\n'
               lines += f'      control_ptr->rotate ({rotation_rad}f);\n'
               lines +=  '      addChild (control_ptr);\n'
               lines +=  '   }\n'

            lines += '\n'

      return template.replace ('%  controls_widget%', lines)


   #--------------------------------------------------------------------------

   def replace_has_midi_input (self, template, module, entities):

      midi_inputs = [e for e in entities if e.is_control and e.kind == 'MidiIn']
      if len (midi_inputs) > 0:
         template = template.replace ('%has_midi_input%', 'true')
      else:
         template = template.replace ('%has_midi_input%', 'false')

      return template



   #--------------------------------------------------------------------------

   def control_kind_to_vcv_id_count (self, control):
      kind_vcv_id_count_map = {
         'AudioIn': 1,
         'AudioOut': 1,
         'AudioStereoIn': 2,
         'AudioStereoOut': 2,
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
