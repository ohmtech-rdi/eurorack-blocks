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
from soundfile import SoundFile

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



class Code:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      if module.source_language != 'faust': return

      faust_dsp = None
      for sources in module.sources:
         for file in sources.files:
            filename, file_extension = os.path.splitext (file.path)
            if file_extension == '.dsp':
               faust_dsp = os.path.join (os.path.dirname (path), file.path)
               filename_dsp = filename

      faust_dsp_json = os.path.join (path, '%s.dsp.json' % filename_dsp)

      subprocess.check_call (
         [
            'faust',
            '-json',
            '--output-dir', '.',
            '--memory-manager',
            faust_dsp,
            '-o', 'module_faust.h'
         ],
         cwd = path
      )

      with open (faust_dsp_json, 'r', encoding='utf-8') as f:
         faust_json = json.load (f)

      faust_dsp = self.generate_faust_dsp (faust_json)

      self.generate_module_declaration (path, faust_dsp, module)
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

   def generate_module_declaration (self, path, faust_dsp, module):
      path_template = os.path.join (PATH_THIS, 'code_template.h')
      path_output = os.path.join (path, '%s.h' % module.name)

      has_data = False

      for resources in module.resources:
         for data in resources.datas:
            has_data = True

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      soundfile_widgets = [e for e in faust_dsp.widgets if e.type_ == 'soundfile']

      template = template.replace ('%module.name%', module.name)
      if has_data:
         template = template.replace ('%include module.nameData.h%', '#include "%sData.h"' % module.name)
         template = template.replace ('%  module.nameData data;%', '   %sData data;' % module.name)
      else:
         template = template.replace ('%include module.nameData.h%', '')
         template = template.replace ('%  module.nameData data;%', '')
      template = template.replace ('%faust.widgets.length%', str (len (faust_dsp.widgets)))
      template = template.replace ('%module.samples.length%', str (len (soundfile_widgets)))
      template = template.replace ('%     module.spl_adapters%', self.generate_module_declaration_spl_adapter (faust_dsp, module))
      template = template.replace ('%     module.samples%', self.generate_module_declaration_samples (faust_dsp, module))

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_module_declaration_spl_adapter (self, faust_dsp, module):
      content = ''
      for index, widget in enumerate (faust_dsp.widgets):
         if widget.type_ in ['soundfile']:
            if widget.address in module.faust_addresses:
               address_object = module.faust_addresses [widget.address]
               name = address_object.name
               try:
                  file = SoundFile (address_object.data.file.path)
               except OSError:
                  err = error.Error ()
                  context = address_object.data.file.source_context
                  err.add_error ("File '%s' not found" % context, context)
                  err.add_context (context)
                  raise err
               with file:
                  channels = ', '.join (map (lambda x: '&%sData::%s.channels [%d].samples [0]' % (module.name, name, x) , range (file.channels)))
                  content += '      {\n'
                  content += '         .channels = { %s },\n' % channels
                  content += '         .nbr_channels = %d,\n' % file.channels
                  content += '         .length = %d,\n' % file.frames
                  content += '         .sample_rate = %d\n' % file.samplerate
                  content += '      },\n'
            else:
               err = error.Error ()
               context = module.source_context
               err.add_error ("Soundfile '%s' is not mapped" % (widget.address), context)
               err.add_context (context)
               raise err
      return content


   #--------------------------------------------------------------------------

   def generate_module_declaration_samples (self, faust_dsp, module):
      content = ''
      for index, widget in enumerate (faust_dsp.widgets):
         if widget.type_ in ['soundfile']:
            address_object = module.faust_addresses [widget.address]
            name = address_object.name
            content += '      {\n'
            content += '         .fBuffers = const_cast <float **> (&spl_adapter [%d].channels [0]),\n' % index
            content += '         .fLength = &spl_adapter [%d].length,\n' % index
            content += '         .fSR = &spl_adapter [%d].sample_rate,\n' % index
            content += '         .fOffset = &offset_zero,\n'
            content += '         .fChannels = spl_adapter [%d].nbr_channels\n' % index
            content += '      },\n'
      return content


   #--------------------------------------------------------------------------

   def generate_module_definition (self, path, faust_dsp, module):
      path_template = os.path.join (PATH_THIS, 'code_template.hpp')
      path_output = os.path.join (path, '%s_erbb.hpp' % module.name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      with open (path_output, 'w', encoding='utf-8') as file:
         file.write (template)
