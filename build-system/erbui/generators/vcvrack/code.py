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

      controls_content = self.generate_controls (module.entities)
      template = template.replace ('%controls%', controls_content)

      controls_config = self.generate_controls_config (module.entities)
      template = template.replace ('%controls_config%', controls_config)

      with open (path_cpp, 'w') as file:
         file.write (template)


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

      type_func_category_map = {
         'AudioInDaisy': 'Input',
         'AudioOutDaisy': 'Output',
         'Button': 'Param',
         'CvIn': 'Input',
         'GateIn': 'Input',
         'GateOut': 'Output',
         'Led': 'Child',
         'LedBi': 'Child',
         'LedRgb': 'Child',
         'Pot': 'Param',
         'Switch': 'Param',
         'Trim': 'Param',
      }

      func_category = type_func_category_map [control.kind]

      type_category_map = {
         'AudioInDaisy': 'Input',
         'AudioOutDaisy': 'Output',
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

      category = type_category_map [control.kind]

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
      source_code += '   // Type mismatch between module and gui code\n'
      source_code += '   static_assert (std::is_same <decltype (module_->module.ui.%s), erb::%s>::value, "");\n' % (
         control.name, control.kind
      )
      source_code += '   add%s (create%sCentered <%s> (mm2px (Vec (%f, %f)), module_, module_->module.ui.%s.index ()));\n' % (
         func_category, category, widget, control.position.x.mm, control.position.y.mm, control.name
      )
      if control.style.is_dailywell_2ms3:
         source_code += '   module_->module.ui.%s.set_3_position ();\n' % control.name
      source_code += '\n'

      return source_code


