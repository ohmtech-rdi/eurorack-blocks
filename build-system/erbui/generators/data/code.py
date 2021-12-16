##############################################################################
#
#     code.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

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
      path_template = os.path.join (PATH_THIS, 'code_template.h')
      path_cpp = os.path.join (path, '%sData.h' % module.name)

      with open (path_template, 'r') as file:
         template = file.read ()

      template = template.replace ('%module.name%', module.name)

      entities_content = self.generate_entities (module.entities)
      template = template.replace ('%entities%', entities_content)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def generate_entities (self, entities):
      content = ''

      for entity in entities:
         if entity.is_data:
            content += self.generate_data (entity)

      return content


   #--------------------------------------------------------------------------

   def generate_data (self, data):

      if data.data_type is None:
         return self.generate_data_raw (data)

      else:
         err = error.Error ()
         context = data.data_type.source_context
         err.add_error ("Undefined type '%s'" % context, context)
         err.add_context (context)
         raise err


   #--------------------------------------------------------------------------

   def generate_data_raw (self, data):

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
         content = 'static constexpr std::array <uint8_t, %d> %s = {' % (file_size, data.name);
         bytes = bytearray (file.read ())
         content += ', '.join (map (lambda byte: '0x' + format (byte, "02x"), bytes))
         content += '};\n'

      return content
