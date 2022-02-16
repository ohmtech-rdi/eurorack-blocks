##############################################################################
#
#     project.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_ERBB_GENS = os.path.join (PATH_ROOT, 'build-system', 'erbb', 'generators')
PATH_ERBUI_GENS = os.path.join (PATH_ROOT, 'build-system', 'erbui', 'generators')



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
      template = self.replace_includes (template, module, path);
      template = self.replace_defines (template, module.defines)
      template = self.replace_bases (template, module, module.bases, path);
      template = self.replace_sources (template, module, module.sources, path)
      template = self.replace_actions (template, module, path)

      with open (path_cpp, 'w') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_includes (self, template, module, path):
      lines = ''

      if module.source_language == 'max':
         path_rel_root = os.path.relpath (PATH_ROOT, path)
         lines += '            \'%s/include/gen_dsp/gen_dsp.gypi\',\n' % path_rel_root

      return template.replace ('%           target_includes%', lines)


   #--------------------------------------------------------------------------

   def replace_defines (self, template, defines):
      lines = ''

      for define in defines:
         lines += '            \'%s=%s\',\n' % (defines.key, defines.value)

      return template.replace ('%           defines.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_bases (self, template, module, bases, path):
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

      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      if data_paths:
         lines += '            \'artifacts/plugin_generated_data.cpp\',\n'

      if module.source_language == 'max':
         lines += '            \'artifacts/%s_erbb.cpp\',\n' % module.name
         lines += '            \'artifacts/%s_erbui.cpp\',\n' % module.name
         lines += '            \'artifacts/%s.h\',\n' % module.name
         lines += '            \'artifacts/module_max_alt.cpp\',\n'
         lines += '            \'artifacts/module_max_alt.h\',\n'

      return template.replace ('%           sources.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_actions (self, template, module, path):
      lines = ''

      if module.source_language == 'max':
         lines += '            {\n'
         lines += '               \'action_name\': \'Transpile Max\',\n'
         lines += '               \'inputs\': [\n'
         lines += '                  \'<!(echo %s/max/code.py)\',\n' % PATH_ERBB_GENS
         lines += '                  \'<!(echo %s/max/code.py)\',\n' % PATH_ERBUI_GENS
         lines += '                  \'<!(echo artifacts/module_max.cpp)\',\n'
         lines += '                  \'<!(echo artifacts/module_max.h)\',\n'
         lines += '               ],\n'
         lines += '               \'outputs\': [\n'
         lines += '                  \'<!(echo artifacts/module_max_alt.cpp)\',\n'
         lines += '                  \'<!(echo artifacts/module_max_alt.h)\',\n'
         lines += '                  \'<!(echo artifacts/%s_erbb.cpp)\',\n' % module.name
         lines += '                  \'<!(echo artifacts/%s_erbui.cpp)\',\n' % module.name
         lines += '               ],\n'
         lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_max.py\' ],\n'
         lines += '            },\n'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Ui\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'<!(echo %s/ui/code.py)\',\n' % PATH_ERBUI_GENS
      lines += '                  \'<!(echo %s.erbui)\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'<!(echo artifacts/%sUi.h)\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_ui.py\' ],\n'
      lines += '            },\n'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile VcvRack\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'<!(echo %s/vcvrack/code.py)\',\n' % PATH_ERBUI_GENS
      lines += '                  \'<!(echo %s/vcvrack/manifest.py)\',\n' % PATH_ERBUI_GENS
      lines += '                  \'<!(echo %s/vcvrack/panel.py)\',\n' % PATH_ERBUI_GENS
      lines += '                  \'<!(echo %s.erbui)\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'<!(echo artifacts/panel_vcvrack.svg)\',\n'
      lines += '                  \'<!(echo artifacts/plugin_vcvrack.cpp)\',\n'
      lines += '                  \'<!(echo artifacts/plugin.json)\',\n'
      lines += '               ],\n'
      lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_vcvrack.py\' ],\n'
      lines += '            },\n'

      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      if data_paths:
         lines += '            {\n'
         lines += '               \'action_name\': \'Transpile Data\',\n'
         lines += '               \'inputs\': [\n'
         lines += '                  \'<!(echo %s/data/code.py)\',\n' % PATH_ERBB_GENS
         lines += '                  \'<!(echo %s.erbb)\',\n' % module.name
         for data_path in data_paths:
            lines += '                  \'<!(echo %s)\',\n' % data_path
         lines += '               ],\n'
         lines += '               \'outputs\': [\n'
         lines += '                  \'<!(echo artifacts/%sData.h)\',\n' % module.name
         lines += '                  \'<!(echo artifacts/plugin_generated_data.cpp)\',\n'
         lines += '               ],\n'
         lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_data.py\' ],\n'
         lines += '            },\n'

      return template.replace ('%           target_actions%', lines)
