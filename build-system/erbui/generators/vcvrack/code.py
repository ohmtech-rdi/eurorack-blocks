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

      with open (path_template, 'r') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      template = self.replace_config_controls_bind (module.entities);

      controls_content = self.generate_controls (module.entities)
      template = template.replace ('%  controls%', controls_content)

      controls_preprocess = self.generate_controls_preprocess (module.entities)
      template = template.replace ('%     controls_preprocess%', controls_preprocess)

      controls_postprocess = self.generate_controls_postprocess (module.entities)
      template = template.replace ('%     controls_postprocess%', controls_postprocess)

      controls_config = self.generate_controls_config (module.entities)
      template = template.replace ('%  controls_config%', controls_config)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_config_controls_bind (self, entities):
      nbr_params = 0
      nbr_inputs = 0
      nbr_outputs = 0
      nbr_lights = 0

      controls_bind_config = ''

      for entity in entities:
         if entity.is_control:
            category = self.control_kind_to_vcv_category (control)

            if category == 'Param':
               min_val = -1.f if control.mode.is_bipolar else 0.f
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'params', nbr_params)
               controls_bind_config += '   configParam (%d, %f, 1.f, 0.f);\n' % (nbr_params, min_val)
               nbr_params += 1

            elif category == 'Input':
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'inputs', nbr_inputs)
               nbr_inputs += 1

            elif category == 'Output':
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'outputs', nbr_outputs)
               nbr_outputs += 1

            elif category == 'Light':
               controls_bind_config += '   module.ui.board.impl_bind (module.ui.%s, %s [%d]);\n' % (control.name, 'lights', nbr_lights)
               nbr_lights += 1

      template = template.replace ('%module.nbr_params%', nbr_params)
      template = template.replace ('%module.nbr_inputs%', nbr_inputs)
      template = template.replace ('%module.nbr_outputs%', nbr_outputs)
      template = template.replace ('%module.nbr_lights%', nbr_lights)

      template = template.replace ('%  module.controls.bind+config%', controls_bind_config)


   #--------------------------------------------------------------------------

   def generate_controls_config (self, entities):
      content = ''

      for entity in entities:
         if entity.is_control:
            content += self.generate_control_config (entity)
         elif entity.is_multiplexer:
            for control in entity.controls:
               content += self.generate_control_config (control)

      return content


   #--------------------------------------------------------------------------

   def generate_control_config (self, control):
      source_code = ''

      if control.style.is_dailywell_2ms3:
         source_code = '      if (i == module.ui.%s.index ()) { max_value = 2.f; }\n' % control.name

      return source_code


   #--------------------------------------------------------------------------

   def generate_controls_preprocess (self, entities):
      content = ''

      def generate_line (control):
         return '      module.ui.%s.impl_preprocess ();\n' % control.name

      for entity in entities:
         if entity.is_control:
            content += generate_line (entity)
         elif entity.is_multiplexer:
            for control in entity.controls:
               content += generate_line (control)

      return content


   #--------------------------------------------------------------------------

   def generate_controls_postprocess (self, entities):
      content = ''

      def generate_line (control):
         return '      module.ui.%s.impl_postprocess ();\n' % control.name

      for entity in entities:
         if entity.is_control:
            content += generate_line (entity)
         elif entity.is_multiplexer:
            for control in entity.controls:
               content += generate_line (control)

      return content


   #--------------------------------------------------------------------------

   def generate_controls (self, entities):
      content = ''

      for entity in entities:
         if entity.is_control:
            content += self.generate_control (entity)
         elif entity.is_multiplexer:
            for control in entity.controls:
               content += self.generate_control (control)

      return content


   #--------------------------------------------------------------------------

   def generate_control (self, control):

      category = self.control_kind_to_vcv_category (control)

      func_category = category
      if func_category == 'Light':
         func_category = 'Child'

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

      widget = style_widget_map [control.style.name]

      if control.style.is_dailywell_2ms:
         if control.rotation is None:
            rotation = 0
         else:
            rotation = control.rotation.degree_top_down % 360
         widget += ' <%d>' % rotation

      source_code = ''
      source_code += '   add%s (create%sCentered <%s> (mm2px (Vec (%f, %f)), module_, module_->module.ui.board.impl_to_vcv_index (module_->module.ui.%s.impl_data ())));\n' % (
         func_category, category, widget, control.position.x.mm, control.position.y.mm, control.name
      )
      if control.style.is_dailywell_2ms3:
         source_code += '   module_->module.ui.%s.set_3_position ();\n' % control.name
      source_code += '\n'

      return source_code


   #--------------------------------------------------------------------------

   def control_kind_to_vcv_category (self, control):
      kind_category_map = {
         'AudioIn': 'Input',
         'AudioOut': 'Output',
         'Button': 'Param',
         'CvIn': 'Input',
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


