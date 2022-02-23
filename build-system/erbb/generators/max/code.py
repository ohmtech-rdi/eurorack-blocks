##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import json
import math
import os
import re
import subprocess
from soundfile import SoundFile

from ... import error

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))


class Code:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      if module.source_language != 'max': return

      maxpat = self.make_maxpat (path, module)

      self.generate_module_declaration (path, module)
      self.generate_module_definition (path, module)
      self.generate_max_declaration (path, module, maxpat)
      self.generate_max_definition (path, module)


   #--------------------------------------------------------------------------

   def generate_module_declaration (self, path, module):
      path_template = os.path.join (PATH_THIS, 'code_template.h')
      path_output = os.path.join (path, '%s.h' % module.name)

      has_data = False

      for resources in module.resources:
         for data in resources.datas:
            has_data = True

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)
      if has_data:
         template = template.replace ('%include module.nameData.h%', '#include "%sData.h"' % module.name)
         template = template.replace ('%  module.nameData data;%', '   %sData data;' % module.name)
      else:
         template = template.replace ('%include module.nameData.h%', '')
         template = template.replace ('%  module.nameData data;%', '')

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_module_definition (self, path, module):
      path_template = os.path.join (PATH_THIS, 'code_template.cpp')
      path_output = os.path.join (path, '%s_erbb.cpp' % module.name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%  state.set_data%', self.generate_data_definition (path, module))

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_data_definition (self, path, module):
      lines = ''

      for resources in module.resources:
         for data in resources.datas:
            if data.type_ is None:
               pass
            elif data.type_ == 'AudioSample':
               lines += '   {\n'
               lines += '      auto adapter = MaxErbDataAdapter { .frames = data.%s.frames.size (), .channels = data.%s.frames [0].channels.size (), .data = &data.%s.frames [0].channels [0] };\n' % (data.name, data.name, data.name)
               lines += '      state.set_%s (&adapter);\n' % data.name
               lines += '   }\n'

      return lines;


   #--------------------------------------------------------------------------

   def generate_max_declaration (self, path, module, maxpat):
      path_template = os.path.join (PATH_THIS, 'module_max_template.h')
      path_output = os.path.join (path, 'module_max_alt.h')
      path_input = os.path.join (path, 'module_max.cpp')
      module_max_def = os.path.join (path, 'module_max_def.py')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      try:
         file_input = open (path_input, 'r', encoding='utf-8')

      except OSError:
         print ('warning: No gen code found. Please open %s.maxpat and save it to generate gen code.' % (module.name), file=sys.stderr)
         return

      with file_input:
         max_cpp = file_input.read ()

      marker_begin = 'typedef struct State {\n'
      marker_end = '} State;\n'

      index_begin = max_cpp.find (marker_begin)
      assert index_begin != None

      index_end = max_cpp.find (marker_end, index_begin)
      assert index_end != None
      index_end += len (marker_end)

      state_def = max_cpp [index_begin:index_end]

      for history_key, history_value in maxpat ['histories'].items ():
         if history_key [-1].isdigit ():
            print ('warning: %s ends with a digit, which is not supported. Add a character to solve that.' % history_key, file=sys.stderr)
         else:
            cpp_expr = '^\\tt_sample m_%s_([0-9]+);$' % history_key
            pattern = re.compile (cpp_expr, re.M)
            s = pattern.search (state_def)
            if s:
               internal_name = s.group () [len ('\tt_sample '):-1]
               maxpat ['histories'][history_key] = {'internal': internal_name}
            else:
               print ('warning: Output %s not mapped.' % history_key, file=sys.stderr)


      with open (module_max_def, 'w', encoding='utf-8') as file:
         file.write (str (maxpat))

      template = template.replace ('%typedef struct State%', state_def)

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_max_definition (self, path, module):
      path_template = os.path.join (PATH_THIS, 'module_max_template.cpp')
      path_output = os.path.join (path, 'module_max_alt.cpp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def make_maxpat (self, path, module):
      for sources in module.sources:
         for file in sources.files:
            filename, file_extension = os.path.splitext (file.path)
            if file_extension == '.maxpat':
               maxpat_path = file.path

      with open (maxpat_path, 'r', encoding='utf-8') as f:
         max_json = json.load (f)

      return self.make_maxpat_patcher (max_json)


   #--------------------------------------------------------------------------

   def make_maxpat_patcher (self, max_json):
      patcher = max_json ['patcher']
      boxes = patcher ['boxes']
      for box_elem in boxes:
         box = box_elem ['box']
         if 'patcher' in box:
            sub_patcher = box ['patcher']
            if 'classnamespace' in sub_patcher and sub_patcher ['classnamespace'] == 'dsp.gen':
               gen_boxes = sub_patcher ['boxes']
               return self.make_maxpat_dspgen (gen_boxes)


   #--------------------------------------------------------------------------

   def make_maxpat_dspgen (self, boxes):
      ret = {
         'nbr_inputs': 0,
         'nbr_outputs': 0,
         'params': {},
         'histories': {},
      }
      for box_elem in boxes:
         box = box_elem ['box']
         if 'text' in box:
            text = box ['text']
            tokens = text.split (' ')
            op = tokens [0]
            if op == 'in':
               input_nbr = int (tokens [1])
               ret ['nbr_inputs'] = max (ret ['nbr_inputs'], input_nbr)
            elif op == 'out':
               output_nbr = int (tokens [1])
               ret ['nbr_outputs'] = max (ret ['nbr_outputs'], output_nbr)
            elif op in ['param', 'Param']:
               if len (tokens) >= 2:
                  min_val = 0.0
                  max_val = 1.0
                  for index, token in enumerate (tokens):
                     if token == '@min':
                        min_val = float (tokens [index + 1])
                     elif token == '@max':
                        max_val = float (tokens [index + 1])
                  param = {tokens [1] : {'min': min_val, 'max': max_val}}
                  ret ['params'].update (param)
            elif op == 'history':
               if len (tokens) >= 2:
                  history = {tokens [1] : {}}
                  ret ['histories'].update (history)

      return ret
