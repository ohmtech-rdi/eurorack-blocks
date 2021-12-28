##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
from soundfile import SoundFile

from ... import error

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')



class Code:
   def __init__ (self):
      self._board_definition = {}


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      self.generate_module_declaration (path, module)
      self.generate_module_definition (path, module)


   #--------------------------------------------------------------------------

   def generate_module_declaration (self, path, module):
      path_template = os.path.join (PATH_THIS, 'code_template.h')
      path_cpp = os.path.join (path, '%sData.h' % module.name)

      with open (path_template, 'r') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      entities_content = self.generate_declaration_entities (module.entities)
      template = template.replace ('%entities%', entities_content)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_declaration_entities (self, entities):
      content = ''

      for entity in entities:
         if entity.is_data:
            content += self.generate_declaration_data (entity)

      return content


   #--------------------------------------------------------------------------

   def generate_declaration_data (self, data):

      if data.data_type is None:
         return self.generate_declaration_data_raw (data)

      elif data.data_type.name == 'AudioSample':
         return self.generate_declaration_data_audio_sample (data)

      else:
         err = error.Error ()
         context = data.data_type.source_context
         err.add_error ("Undefined type '%s'" % context, context)
         err.add_context (context)
         raise err


   #--------------------------------------------------------------------------

   def generate_declaration_data_raw (self, data):

      try:
         file = open (data.file.file, 'rb')

      except OSError:
         err = error.Error ()
         context = data.file.source_context
         err.add_error ("File '%s' not found" % context, context)
         err.add_context (context)
         raise err

      with file:
         file.seek (0, os.SEEK_END)
         file_size = file.tell ()
         file.seek (0, os.SEEK_SET)
         content = '   static const std::array <uint8_t, %d> %s;\n' % (file_size, data.name);

      return content


   #--------------------------------------------------------------------------

   def generate_declaration_data_audio_sample (self, data):

      try:
         file = SoundFile (data.file.file)

      except OSError:
         err = error.Error ()
         context = data.file.source_context
         err.add_error ("File '%s' not found" % context, context)
         err.add_context (context)
         raise err

      with file:
         samples = file.read ()
         content = '   static const erb::AudioSample <float, %d, %d> %s;\n' % (file.frames, file.channels, data.name);

      return content


   #--------------------------------------------------------------------------

   def generate_module_definition (self, path, module):
      path_template = os.path.join (PATH_THIS, 'code_template.cpp')
      path_cpp = os.path.join (path, 'plugin_generated_data.cpp')

      with open (path_template, 'r') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      entities_content = self.generate_definition_entities (module, module.entities)
      template = template.replace ('%entities%', entities_content)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_definition_entities (self, module, entities):
      content = ''

      for entity in entities:
         if entity.is_data:
            content += self.generate_definition_data (module, entity)

      return content


   #--------------------------------------------------------------------------

   def generate_definition_data (self, module, data):

      if data.data_type is None:
         return self.generate_definition_data_raw (module, data)

      elif data.data_type.name == 'AudioSample':
         return self.generate_definition_data_audio_sample (module, data)

      else:
         err = error.Error ()
         context = data.data_type.source_context
         err.add_error ("Undefined type '%s'" % context, context)
         err.add_context (context)
         raise err


   #--------------------------------------------------------------------------

   def generate_definition_data_raw (self, module, data):

      try:
         file = open (data.file.file, 'rb')

      except OSError:
         err = error.Error ()
         context = data.file.source_context
         err.add_error ("File '%s' not found" % context, context)
         err.add_context (context)
         raise err

      with file:
         file.seek (0, os.SEEK_END)
         file_size = file.tell ()
         file.seek (0, os.SEEK_SET)
         content = 'const std::array <uint8_t, %d> %sData::%s = {' % (file_size, module.name, data.name);
         bytes = bytearray (file.read ())
         content += ', '.join (map (lambda byte: '0x' + format (byte, "02x"), bytes))
         content += '};\n'

      return content


   #--------------------------------------------------------------------------

   def generate_definition_data_audio_sample (self, module, data):

      try:
         file = SoundFile (data.file.file)

      except OSError:
         err = error.Error ()
         context = data.file.source_context
         err.add_error ("File '%s' not found" % context, context)
         err.add_context (context)
         raise err

      with file:
         samples = file.read ()
         content = 'const erb::AudioSample <float, %d, %d> %sData::%s = {\n' % (file.frames, file.channels, module.name, data.name);
         content += '   .sample_rate = %f,\n' % file.samplerate;
         content += '   .channels = {{\n';
         if file.channels == 1:
            content += '      {{';
            content += ', '.join (map (lambda frame: float.hex(frame), samples))
            content += '}},\n';
         else:
            for c in range (file.channels):
               content += '      {{';
               content += ', '.join (map (lambda frame: float.hex(frame [c]), samples))
               content += '}},\n';
         content += '   }}\n';
         content += '};\n'

      return content
