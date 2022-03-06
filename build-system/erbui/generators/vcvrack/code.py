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
      path_cpp = os.path.join (path, 'plugin_vcvrack.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      template = self.replace_config_controls_bind (template, module.entities);
      template = self.replace_cascade_process (template, module.cascade_eval_list);
      template = self.replace_controls_preprocess (template, module.entities);
      template = self.replace_controls_postprocess (template, module.entities);
      template = self.replace_controls_widget (template, module.entities);

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

            if category == 'Param':
               if control.mode is not None and control.mode.is_bipolar:
                  min_val = -1
                  max_val = 1
               elif control.mode is not None and control.mode.is_pitch:
                  min_val = 0
                  max_val = 10
               elif control.style.is_dailywell_2ms3:
                  min_val = 0
                  max_val = 2
               else:
                  min_val = 0
                  max_val = 1

               control.vcv_param_index = nbr_params
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'params', nbr_params)
               controls_bind_config += '   configParam (%d, %f, %f, 0.f);\n\n' % (nbr_params, min_val, max_val)
               nbr_params += 1

            elif category == 'Input':
               control.vcv_input_index = nbr_inputs
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'inputs', nbr_inputs)
               nbr_inputs += 1

            elif category == 'Output':
               control.vcv_output_index = nbr_outputs
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'outputs', nbr_outputs)
               nbr_outputs += 1

            elif category == 'Light':
               control.vcv_light_index = nbr_lights
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'lights', nbr_lights)
               nbr_lights += control.nbr_pins

      template = template.replace ('%module.nbr_params%', str (nbr_params))
      template = template.replace ('%module.nbr_inputs%', str (nbr_inputs))
      template = template.replace ('%module.nbr_outputs%', str (nbr_outputs))
      template = template.replace ('%module.nbr_lights%', str (nbr_lights))

      template = template.replace ('%  module.controls.bind+config%', controls_bind_config)

      return template


   #--------------------------------------------------------------------------

   def replace_cascade_process (self, template, controls):
      lines = ''

      for control in controls:
         if control.cascade_from is not None:
            lines += '   if (!inputs [%d].isConnected ())\n' % control.vcv_input_index
            lines += '   {\n'
            lines += '      inputs [%d].setVoltage (inputs [%d].getVoltage ());\n' % (control.vcv_input_index, control.cascade_from.reference.vcv_input_index)
            lines += '   }\n'

      return template.replace ('%  cascade_process%', lines)


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

   def replace_controls_widget (self, template, entities):
      lines = ''
      nbr_params = 0
      nbr_inputs = 0
      nbr_outputs = 0
      nbr_lights = 0

      for entity in entities:
         if entity.is_control:
            control = entity
            category = self.control_kind_to_vcv_category (control)

            func_category = category
            if func_category == 'Light':
               func_category = 'Child'

            widget = self.control_style_to_widget (control)

            if control.style.is_dailywell_2ms:
               if control.rotation is None:
                  rotation = 0
               else:
                  rotation = control.rotation.degree_top_down % 360
               widget += ' <%d>' % rotation

            if category == 'Param':
               index = nbr_params
               nbr_params += 1

            elif category == 'Input':
               index = nbr_inputs
               nbr_inputs += 1

            elif category == 'Output':
               index = nbr_outputs
               nbr_outputs += 1

            elif category == 'Light':
               index = nbr_lights
               nbr_lights += 1

            lines += '   add%s (create%sCentered <%s> (mm2px (Vec (%ff, %ff)), module_, %d));\n' % (
               func_category, category, widget, control.position.x.mm, control.position.y.mm, index
            )
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

   def control_style_to_widget (self, control):
      style_widget_map = {
         'rogan.6ps': 'erb::Rogan6Ps',
         'rogan.5ps': 'erb::Rogan5Ps',
         'rogan.3ps': 'erb::Rogan3Ps',
         'rogan.2ps': 'erb::Rogan2Ps',
         'rogan.1ps': 'erb::Rogan1Ps',
         'songhuei.9mm': 'erb::SongHuei9',
         'dailywell.2ms1': 'erb::Dailywell2Ms1',
         'dailywell.2ms3': 'erb::Dailywell2Ms3',
         'led.3mm.red': 'MediumLight <RedLight>',
         'led.3mm.green': 'MediumLight <GreenLight>',
         'led.3mm.yellow': 'MediumLight <YellowLight>',
         'led.3mm.orange': 'MediumLight <YellowLight>', # orange is missing
         'led.3mm.green_red': 'MediumLight <GreenRedLight>',
         'led.3mm.rgb': 'MediumLight <RedGreenBlueLight>',
         'thonk.pj398sm.knurled': 'erb::ThonkPj398SmKnurled',
         'thonk.pj398sm.hex': 'erb::ThonkPj398SmHex',
         'ck.d6r.black': 'CKD6',
         'tl1105': 'TL1105',
      }

      return style_widget_map [control.style.name]


