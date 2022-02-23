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

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%PATH_ROOT%', path_rel_root)
      template = self.replace_includes (template, module, path);
      template = self.replace_defines (template, module.defines)
      template = self.replace_bases (template, module, module.bases, path);
      template = self.replace_sources (template, module, module.sources, path)
      template = self.replace_actions (template, module, path)

      with open (path_cpp, 'w', encoding='utf-8') as file:
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

      if module.source_language == 'faust':
         lines += '            \'artifacts/%s_erbb.hpp\',\n' % module.name
         lines += '            \'artifacts/%s_erbui.hpp\',\n' % module.name
         lines += '            \'artifacts/%s.h\',\n' % module.name
         lines += '            \'artifacts/module_faust.h\',\n'

      return template.replace ('%           sources.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_actions (self, template, module, path):
      lines = ''

      path_rel_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path)
      path_rel_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path)

      if module.source_language == 'max':
         lines += '            {\n'
         lines += '               \'action_name\': \'Transpile Max\',\n'
         lines += '               \'inputs\': [\n'
         lines += '                  \'%s/max/code.py\',\n' % path_rel_erbb_gens
         lines += '                  \'%s/max/code.py\',\n' % path_rel_erbui_gens
         lines += '                  \'artifacts/module_max.cpp\',\n'
         lines += '                  \'artifacts/module_max.h\',\n'
         lines += '               ],\n'
         lines += '               \'outputs\': [\n'
         lines += '                  \'artifacts/module_max_alt.cpp\',\n'
         lines += '                  \'artifacts/module_max_alt.h\',\n'
         lines += '                  \'artifacts/%s_erbb.cpp\',\n' % module.name
         lines += '                  \'artifacts/%s_erbui.cpp\',\n' % module.name
         lines += '               ],\n'
         lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_max.py\' ],\n'
         lines += '            },\n'

      if module.source_language == 'faust':
         lines += '            {\n'
         lines += '               \'action_name\': \'Transpile Faust\',\n'
         lines += '               \'inputs\': [\n'
         lines += '                  \'%s/faust/code.py\',\n' % path_rel_erbb_gens
         lines += '                  \'%s/faust/code.py\',\n' % path_rel_erbui_gens
         lines += '                  \'%s.dsp\',\n' % module.name
         lines += '               ],\n'
         lines += '               \'outputs\': [\n'
         lines += '                  \'artifacts/%s.h\',\n' % module.name
         lines += '                  \'artifacts/%s_erbb.hpp\',\n' % module.name
         lines += '                  \'artifacts/%s_erbui.hpp\',\n' % module.name
         lines += '                  \'artifacts/module_faust.h\',\n'
         lines += '               ],\n'
         lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_faust.py\' ],\n'
         lines += '            },\n'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Ui\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'%s/ui/code.py\',\n' % path_rel_erbui_gens
      lines += '                  \'%s.erbui\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'artifacts/%sUi.h\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_ui.py\' ],\n'
      lines += '            },\n'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile VcvRack\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'%s/vcvrack/code.py\',\n' % path_rel_erbui_gens
      lines += '                  \'%s/vcvrack/manifest.py\',\n' % path_rel_erbui_gens
      lines += '                  \'%s/vcvrack/panel.py\',\n' % path_rel_erbui_gens
      lines += '                  \'%s.erbui\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'artifacts/panel_vcvrack.svg\',\n'
      lines += '                  \'artifacts/plugin_vcvrack.cpp\',\n'
      lines += '                  \'artifacts/plugin.json\',\n'
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
         lines += '                  \'%s/data/code.py\',\n' % path_rel_erbb_gens
         lines += '                  \'%s.erbb\',\n' % module.name
         for data_path in data_paths:
            lines += '                  \'%s\',\n' % data_path
         lines += '               ],\n'
         lines += '               \'outputs\': [\n'
         lines += '                  \'artifacts/%sData.h\',\n' % module.name
         lines += '                  \'artifacts/plugin_generated_data.cpp\',\n'
         lines += '               ],\n'
         lines += '               \'action\': [ \'<!(which python3)\', \'artifacts/actions/action_data.py\' ],\n'
         lines += '            },\n'

      return template.replace ('%           target_actions%', lines)
