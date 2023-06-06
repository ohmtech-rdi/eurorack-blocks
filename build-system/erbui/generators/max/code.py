##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import json
import math
import os
import subprocess
import sys

from ... import error

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BUILD_SYSTEM = os.path.join (PATH_ROOT, 'build-system')
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_PY3_PACKAGES = os.path.join (PATH_TOOLCHAIN, 'python3-packages')

sys.path.insert (0, PATH_PY3_PACKAGES)
from soundfile import SoundFile


class Code:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):

      try:
         file_def = open (os.path.join (path, 'module_max_def.py'), 'r', encoding='utf-8')

      except OSError:
         # gen code is not generated yet
         return

      with file_def:
         module_max_def = eval (file_def.read ())

      self.analyse_audio_inputs (module_max_def, module)
      self.analyse_audio_outputs (module_max_def, module)

      self.generate_module_definition (path, module, module_max_def)


   #--------------------------------------------------------------------------

   def analyse_audio_inputs (self, module_max_def, module):
      audio_inputs = [e for e in module.controls if e.kind == 'AudioIn']
      audio_inputs_nbr = len (audio_inputs)
      max_audio_inputs_nbr = module_max_def ['nbr_inputs']

      if max_audio_inputs_nbr != audio_inputs_nbr:
         err = error.Error ()
         context = module.source_context
         err.add_error ("Wrong number of audio inputs: expected %d, got %d" % (max_audio_inputs_nbr, audio_inputs_nbr), context)
         err.add_context (context)
         err.add_hint ("Please make sure your gen~ patch and erbui file define the same number of audio inputs", context)
         raise err


   #--------------------------------------------------------------------------

   def analyse_audio_outputs (self, module_max_def, module):
      audio_outputs = [e for e in module.controls if e.kind == 'AudioOut']
      audio_outputs_nbr = len (audio_outputs)
      max_audio_outputs_nbr = module_max_def ['nbr_outputs']

      if max_audio_outputs_nbr != audio_outputs_nbr:
         err = error.Error ()
         context = module_erbui.source_context
         err.add_error ("Wrong number of audio outputs: expected %d, got %d" % (max_audio_outputs_nbr, audio_outputs_nbr), context)
         err.add_context (context)
         err.add_hint ("Please make sure your gen~ patch and erbui file define the same number of audio outputs", context)
         raise err


   #--------------------------------------------------------------------------

   def generate_module_definition (self, path, module, module_max_def):
      path_template = os.path.join (PATH_THIS, 'code_template.cpp')
      path_output = os.path.join (path, '%s_erbui.cpp' % module.name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%  module.audio_inputs%', self.generate_module_definition_audio_inputs (module))
      template = template.replace ('%  module.audio_outputs%', self.generate_module_definition_audio_outputs (module))
      template = template.replace ('%  state.set_param%', self.generate_module_definition_set_param (module, module_max_def))
      template = template.replace ('%  ui.param = state.m_param%', self.generate_module_definition_get_param (module, module_max_def))

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_module_definition_audio_inputs (self, module):
      audio_inputs = [e for e in module.controls if e.kind == 'AudioIn']
      if audio_inputs:
         return '      ' + ', '.join (map (lambda x: '&ui.%s [0]' % x.name, audio_inputs))
      else:
         return '      &silence [0]' # gen needs always at least 1 input


   #--------------------------------------------------------------------------

   def generate_module_definition_audio_outputs (self, module):
      audio_outputs = [e for e in module.controls if e.kind == 'AudioOut']
      if audio_outputs:
         return '      ' + ', '.join (map (lambda x: '&ui.%s [0]' % x.name, audio_outputs))
      else:
         return '      nullptr' # avoid zero-size array with unused dummy value


   #--------------------------------------------------------------------------

   def generate_module_definition_set_param (self, module, module_max_def):
      lines = ''

      for control in module.controls:
         if control.kind in ['Button', 'CvIn', 'GateIn', 'Pot', 'Switch', 'Trim']:
            if control.name in module_max_def ['params']:
               param_val = self.make_mapping_input (
                  control, None,
                  module_max_def ['params'][control.name]['min'],
                  module_max_def ['params'][control.name]['max']
               )
               lines += '   state.set_%s (%s);\n' % (control.name, param_val)


      return lines


   #--------------------------------------------------------------------------

   def make_mapping_input (self, control, property, min_val, max_val):
      cpp_name = 'ui.' + (control.name if property is None else control.name + '.' + property)
      preconditioning = cpp_name
      if control is None:
         pass
      elif control.kind in ['Button']:
         preconditioning = '(%s.held () ? 1.f : 0.f)' % cpp_name
      elif control.kind in ['GateIn']:
         preconditioning = '(bool (%s) ? 1.f : 0.f)' % cpp_name
      elif control.kind in ['Switch']:
         preconditioning = '(%s.position_first () ? 0.f : (%s.position_center () ? 0.5f : 1.f))' % (cpp_name, cpp_name)
      elif control.mode is not None and control.mode.is_bipolar:
         preconditioning = '((%s + 1.f) * 0.5f)' % cpp_name

      mult = max_val - min_val
      offset = min_val

      return '%ff + %ff * %s' % (offset, mult, preconditioning)


   #--------------------------------------------------------------------------

   def generate_module_definition_get_param (self, module, module_max_def):
      lines = ''

      for control in module.controls:
         if control.kind in ['CvOut', 'GateOut', 'Led']:
            if control.name in module_max_def ['histories'] and 'internal' in module_max_def ['histories'][control.name]:
               cpp_name = 'ui.' + control.name
               state_name = module_max_def ['histories'][control.name]['internal']
               state_expr = self.make_mapping_output (control, state_name)
               lines += '   %s = %s;\n' % (cpp_name, state_expr)
            else:
               print ('\033[33mwarning:\033[0m non mapped %s %s' % (control.kind, control.name))

         elif control.kind in ['LedBi']:
            for property_ in ['r', 'g']:
               max_name = control.name + '_' + property_
               if max_name in module_max_def ['histories'] and 'internal' in module_max_def ['histories'][max_name]:
                  cpp_name = 'ui.' + control.name + '.' + property_
                  state_name = module_max_def ['histories'][max_name]['internal']
                  lines += '   %s = state.%s;\n' % (cpp_name, state_name)
               else:
                  print ('\033[33mwarning:\033[0m non mapped %s %s' % (control.kind, max_name))

         elif control.kind in ['LedRgb']:
            for property_ in ['r', 'g', 'b']:
               max_name = control.name + '_' + property_
               if max_name in module_max_def ['histories'] and 'internal' in module_max_def ['histories'][max_name]:
                  cpp_name = 'ui.' + control.name + '.' + property_
                  state_name = module_max_def ['histories'][max_name]['internal']
                  lines += '   %s = state.%s;\n' % (cpp_name, state_name)
               else:
                  print ('\033[33mwarning:\033[0m non mapped %s %s' % (control.kind, max_name))

      return lines


   #--------------------------------------------------------------------------

   def make_mapping_output (self, control, state_name):
      cpp_name = 'state.' + state_name
      preconditioning = cpp_name
      if control is None:
         pass
      elif control.kind in ['GateOut']:
         preconditioning = '(%s > 0.5f)' % cpp_name

      return preconditioning


   #--------------------------------------------------------------------------

   def find_control (self, module, name):
      for control in module.controls:
         if control.name == name:
            return control

      return None
