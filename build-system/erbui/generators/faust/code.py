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

from ... import error

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))


class FaustDsp:
   def __init__ (self):
      self.nbr_inputs = 0
      self.nbr_outputs = 0
      self.widgets = []


class FaustWidget:
   def __init__ (self, type_, address, min_val, max_val, scale):
      self.type_ = type_
      self.address = address
      self.scale = scale

      if scale == 'linear':
         base_min = min_val
         base_max = max_val
      elif scale == 'log':
         # using non-denormal float to avoid denormal rounding to zero
         base_min = math.log (max (1.17549e-38, min_val))
         base_max = math.log (max (1.17549e-38, max_val))
      elif scale == 'exp':
         try:
            base_min = min (math.exp (min_val), 3.402823e+38)
         except OverflowError:
            base_min = 3.402823e+38
         try:
            base_max = min (math.exp (max_val), 3.402823e+38)
         except OverflowError:
            base_max = 3.402823e+38

      self.mult = base_max - base_min
      self.offset = base_min

      if base_max == base_min:
         self.inv_mult = 0
         self.inv_offset = 0.5
      else:
         self.inv_mult = 1.0 / (base_max - base_min)
         self.inv_offset = - base_min / (base_max - base_min)


   def make_mapping_input (self, control, name):
      preconditioning = name
      if control is None:
         pass
      elif control.kind in ['Button']:
         preconditioning = 'float (%s.pressed ())' % name
      elif control.kind in ['Encoder']:
         preconditioning = 'float (int (%s))' % name
      elif control.kind in ['Switch']:
         preconditioning = '(%s.position_first () ? 0.f : (%s.position_center () ? 0.5f : 1.f))' % (name, name)

      lerp = '(%ff + %ff * %s)' % (self.offset, self.mult, preconditioning)

      if self.scale == 'linear':
         return '(%s)' % lerp
      elif self.scale == 'log':
         return 'std::exp (%s)' % lerp
      elif self.scale == 'exp':
         return 'std::log (%s)' % lerp
      else:
         assert False

      return preconditioning

   def make_mapping_output (self, control, name):
      if self.scale == 'linear':
         preconditioning = name
      elif self.scale == 'log':
         preconditioning = 'std::log (std::max (%s, std::numeric_limits <float>::min ()))' % name
      elif self.scale == 'exp':
         preconditioning = 'std::min (std::exp (%s), std::numeric_limits <float>::max ())' % name

      return '(%ff + %ff * %s)' % (self.inv_offset, self.inv_mult, preconditioning)


class Code:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      faust_dsp_json = os.path.join (path, '%s.dsp.json' % module.name)

      with open (faust_dsp_json, 'r', encoding='utf-8') as f:
         faust_json = json.load (f)

      faust_dsp = self.generate_faust_dsp (faust_json)

      self.analyse_audio_inputs (faust_dsp, module)
      self.analyse_audio_outputs (faust_dsp, module)

      self.generate_module_definition (path, faust_dsp, module)


   #--------------------------------------------------------------------------

   def generate_faust_dsp (self, faust_json):
      faust_dsp = FaustDsp ()
      faust_dsp.nbr_inputs = faust_json ['inputs']
      faust_dsp.nbr_outputs = faust_json ['outputs']
      faust_dsp.widgets = self.generate_faust_dsp_fetch_items (faust_json ['ui'])

      return faust_dsp


   #--------------------------------------------------------------------------

   def generate_faust_dsp_fetch_items (self, node):
      items = []
      for item in node:
         if item ['type'] in ['vgroup', 'hgroup', 'tgroup']:
            items.extend (self.generate_faust_dsp_fetch_items (item ['items']))
         else:
            min = 0.0
            if 'min' in item:
               min = item ['min']
            max = 1.0
            if 'max' in item:
               max = item ['max']
            scale = 'linear'
            if 'meta' in item:
               meta = item ['meta'] # !!! array, not dict
               for sub_item in meta:
                  if 'scale' in sub_item:
                     scale = sub_item ['scale']
            widget = FaustWidget (item ['type'], item ['address'], min, max, scale)
            items.append (widget)
      return items


   #--------------------------------------------------------------------------

   def analyse_audio_inputs (self, faust_dsp, module):
      audio_inputs = [e for e in module.controls if e.kind == 'AudioIn']
      audio_inputs_nbr = len (audio_inputs)

      if faust_dsp.nbr_inputs != audio_inputs_nbr:
         err = error.Error ()
         context = module.source_context
         err.add_error ("Wrong number of inputs: expected %d, got %d" % (faust_dsp.nbr_inputs, audio_inputs_nbr), context)
         err.add_context (context)
         raise err


   #--------------------------------------------------------------------------

   def analyse_audio_outputs (self, faust_dsp, module):
      audio_outputs = [e for e in module.controls if e.kind == 'AudioOut']
      audio_outputs_nbr = len (audio_outputs)

      if faust_dsp.nbr_outputs != audio_outputs_nbr:
         err = error.Error ()
         context = module.source_context
         err.add_error ("Wrong number of outputs: expected %d, got %d" % (faust_dsp.nbr_outputs, audio_outputs_nbr), context)
         err.add_context (context)
         raise err


   #--------------------------------------------------------------------------

   def generate_module_definition (self, path, faust_dsp, module):
      path_template = os.path.join (PATH_THIS, 'code_template.hpp')
      path_output = os.path.join (path, '%s_erbui.hpp' % module.name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%  module.audio_inputs%', self.generate_module_definition_audio_inputs (module))
      template = template.replace ('%  module.audio_outputs%', self.generate_module_definition_audio_outputs (module))
      template = template.replace ('%  module.ui_input_entities%', self.generate_module_definition_ui_inputs (faust_dsp, module))
      template = template.replace ('%  module.ui_output_entities%', self.generate_module_definition_ui_outputs (faust_dsp, module))

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_module_definition_audio_inputs (self, module):
      audio_inputs = [e for e in module.controls if e.kind == 'AudioIn']
      if audio_inputs:
         return '      ' + ', '.join (map (lambda x: '&ui.%s [0]' % x.name, audio_inputs))
      else:
         return '      nullptr' # avoid zero-size array with unused dummy value


   #--------------------------------------------------------------------------

   def generate_module_definition_audio_outputs (self, module):
      audio_outputs = [e for e in module.controls if e.kind == 'AudioOut']
      if audio_outputs:
         return '      ' + ', '.join (map (lambda x: '&ui.%s [0]' % x.name, audio_outputs))
      else:
         return '      nullptr' # avoid zero-size array with unused dummy value


   #--------------------------------------------------------------------------

   def generate_module_definition_ui_inputs (self, faust_dsp, module):
      content = ''
      for index, widget in enumerate (faust_dsp.widgets):
         if widget.type_ in ['button', 'checkbox', 'hslider', 'vslider', 'nentry']:
            if widget.address in module.faust_addresses:
               address_object = module.faust_addresses [widget.address]
               if address_object.qualified is not None:
                  qualified_name = address_object.qualified
                  content += '   *module.adapter.parameters [%d] = %s;\n' % (index, widget.make_mapping_input (address_object.control, 'module.ui.' + qualified_name))
               elif address_object.value is not None:
                  content += '   *module.adapter.parameters [%d] = %ff;\n' % (index, address_object.value)
               else:
                  assert False
            else:
               print ('\033[33mwarning:\033[0m non mapped %s %s' % (widget.type_, widget.address))
      return content


   #--------------------------------------------------------------------------

   def generate_module_definition_ui_outputs (self, faust_dsp, module):
      content = ''
      for index, widget in enumerate (faust_dsp.widgets):
         if widget.type_ in ['hbargraph', 'vbargraph']:
            if widget.address in module.faust_addresses:
               address_object = module.faust_addresses [widget.address]
               assert address_object.qualified is not None
               qualified_name = address_object.qualified
               if address_object.value:
                  content += '   %s = %ff;\n' % ('module.ui.' + qualified_name, address_object.value)
               else:
                  content += '   module.ui.%s = %s;\n' % (qualified_name, widget.make_mapping_output (address_object.control, '*module.adapter.parameters [%d]'% index))
            else:
               print ('\033[33mwarning:\033[0m non mapped %s %s' % (widget.type_, widget.address))

      for control in module.controls:
         if control.faust:
            for init in control.faust.inits:
               qualified_name = control.name
               if init.property_:
                  qualified_name += '.' + init.property_.name
               content += '   %s = %ff;\n' % ('module.ui.' + qualified_name, init.value.value)


      return content
