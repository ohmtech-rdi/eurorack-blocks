##############################################################################
#
#     project.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



class Project:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'project_template.gyp')
      path_cpp = os.path.join (path, 'project_vcvrack.gyp')

      with open (path_template, 'r') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%PATH_ROOT%', path_rel_root)
      template = self.replace_defines (template, module.defines);
      template = self.replace_bases (template, module.bases);
      template = self.replace_sources (template, module, module.sources, path);

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_defines (self, template, defines):
      lines = ''

      for define in defines:
         lines += '            \'%s=%s\',\n' % (defines.key, defines.value)

      return template.replace ('%           defines.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_bases (self, template, bases):
      lines = ''

      for base in bases:
         base_path = os.path.normpath (base.path)
         lines += '            \'%s\',\n' % base_path

      return template.replace ('%           bases.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_sources (self, template, module, sources, path):
      lines = ''

      for source in sources:
         for file in source.files:
            file_path = os.path.relpath (file.path, path)
            lines += '            \'%s\',\n' % file_path

      lines += '            \'%s.erbb\',\n' % module.name

      lines += '            \'artifacts/%sUi.h\',\n' % module.name
      lines += '            \'artifacts/%sData.h\',\n' % module.name

      if module.source_language == 'faust':
         lines += '            \'artifacts/%s.h\',\n' % module.name
         lines += '            \'artifacts/%s.hpp\',\n' % module.name
         lines += '            \'artifacts/module_faust.h\',\n'

      return template.replace ('%           sources.entities%', lines)
