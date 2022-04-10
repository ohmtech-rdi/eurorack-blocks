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
               elif control.parts [0] == 'dailywell.2ms3':
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

            widget = self.control_to_widget (control)

            if control.parts [0].startswith ('dailywell.2ms'):
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
               nbr_lights += control.nbr_pins

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

   def control_to_widget (self, control):
      for part in control.parts:
         widget = self.control_part_to_widget (part)
         if widget is not None:
            return widget

      assert False


   #--------------------------------------------------------------------------

   def control_part_to_widget (self, part):
      if part == 'thonk.pj398sm.nut.hex':
         return 'erb::ThonkPj398SmHex'

      elif part == 'thonk.pj398sm.nut.knurled':
         return 'erb::ThonkPj398SmKnurled'

      elif part.startswith ('rogan.6ps'):
         return 'erb::AlphaPot <erb::Rogan6Ps>'

      elif part.startswith ('rogan.5ps'):
         return 'erb::AlphaPot <erb::Rogan5Ps>'

      elif part.startswith ('rogan.3ps'):
         return 'erb::AlphaPot <erb::Rogan3Ps>'

      elif part.startswith ('rogan.2ps'):
         return 'erb::AlphaPot <erb::Rogan2Ps>'

      elif part.startswith ('rogan.1ps'):
         return 'erb::AlphaPot <erb::Rogan1Ps>'

      elif part.startswith ('rogan.2s.black'):
         return 'erb::AlphaPot <erb::Rogan2SBlack>'

      elif part.startswith ('rogan.1s.black'):
         return 'erb::AlphaPot <erb::Rogan1SBlack>'

      elif part.startswith ('rogan.1s'):
         return 'erb::AlphaPot <erb::Rogan1S>'

      elif part.startswith ('songhuei.9mm'):
         return 'erb::SongHuei9'

      elif part == 'sifam.c151.white':
         return 'erb::AlphaPot <erb::SifamDbn151>'

      elif part == 'sifam.c111.white':
         return 'erb::AlphaPot <erb::SifamDrn111>'

      elif part == 'dailywell.2ms1':
         return 'erb::Dailywell2Ms1'

      elif part == 'dailywell.2ms3':
         return 'erb::Dailywell2Ms3'

      elif part == 'led.tht.3mm.red':
         return 'MediumLight <RedLight>'

      elif part == 'led.tht.3mm.green':
         return 'MediumLight <GreenLight>'

      elif part == 'led.tht.3mm.yellow':
         return 'MediumLight <YellowLight>'

      elif part == 'led.tht.3mm.orange':
         return 'MediumLight <YellowLight>' # orange is missing

      elif part == 'led.tht.3mm.green_red':
         return 'MediumLight <GreenRedLight>'

      elif part == 'led.smt.3mm.rgb':
         return 'MediumLight <RedGreenBlueLight>'

      elif part == 'ck.d6r.black':
         return 'CKD6'

      elif part == '1rblk':
         return 'TL1105'

      else:
         return None
