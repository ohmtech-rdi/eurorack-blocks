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
      path_cpp = os.path.join (path, 'project_daisy.gyp')

      with open (path_template, 'r') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%PATH_ROOT%', path_rel_root)
      template = self.replace_boot_option (template, module);
      template = self.replace_section (template, module);
      template = self.replace_defines (template, module.defines)
      template = self.replace_bases (template, module.bases)
      template = self.replace_sources (template, module, module.sources, path)
      template = self.replace_actions (template, module, path)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_boot_option (self, template, module):

      boot_option = ''

      if module.section.name != 'flash':
         boot_option = '\'BOOT_APP=1\''

      return template.replace ('%boot.option%', boot_option)


   #--------------------------------------------------------------------------

   def replace_section (self, template, module):
      daisy_core = os.path.join (PATH_ROOT, 'submodules', 'libDaisy', 'core')

      if module.section.name == 'flash':
         lds_path = os.path.join (daisy_core, 'STM32H750IB_flash.lds')
      elif module.section.name == 'qspi':
         lds_path = os.path.join (daisy_core, 'STM32H750IB_qspi.lds')
      else:
         assert False

      return template.replace ('%module.section%', lds_path)


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

      return template.replace ('%           sources.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_actions (self, template, module, path):
      lines = ''

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Ui\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'<!(echo %s.erbui)\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'<!(echo artifacts/%sUi.h)\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/action_ui.py\' ],\n'
      lines += '            },\n'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Daisy\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'<!(echo %s.erbui)\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'<!(echo artifacts/main_daisy.cpp)\',\n'
      lines += '               ],\n'
      lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/action_daisy.py\' ],\n'
      lines += '            },\n'

      return template.replace ('%           target_actions%', lines)
