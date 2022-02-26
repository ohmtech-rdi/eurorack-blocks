##############################################################################
#
#     make.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import platform
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_ERBB_GENS = os.path.join (PATH_ROOT, 'build-system', 'erbb', 'generators')
PATH_ERBUI_GENS = os.path.join (PATH_ROOT, 'build-system', 'erbui', 'generators')
PATH_RACK = os.path.join (PATH_ROOT, 'submodules', 'vcv-rack-sdk')



class Make:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'Makefile_template')
      path_simulator = os.path.join (path, 'artifacts', 'simulator')
      path_makefile = os.path.join (path_simulator, 'Makefile')

      if not os.path.exists (path_simulator):
         os.makedirs (path_simulator)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_root = os.path.relpath (PATH_ROOT, path_simulator)
      path_rack_dir = os.path.relpath (PATH_RACK, path_simulator)

      if platform.system () == 'Darwin':
         arch = 'ARCH_MAC := 1\nARCH := mac'
      elif platform.system () == 'Linux':
         arch = 'ARCH_LIN := 1\nARCH := lin'
      elif platform.system () == 'Windows':
         arch = 'ARCH_WIN := 1\nARCH := win\nARCH_WIN_64 := 1\nBITS := 64'

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%define_PATH_ROOT%', 'PATH_ROOT ?= %s' % path_root)
      template = template.replace ('%define_RACK_DIR%', 'RACK_DIR ?= %s' % path_rack_dir)
      template = template.replace ('%define_ARCH%', arch)
      template = self.replace_defines (template, module.defines)
      template = self.replace_bases (template, module, module.bases, path_simulator);
      template = self.replace_sources (template, module, module.sources, path_simulator)
      template = self.replace_actions (template, module, path_simulator)

      with open (path_makefile, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_defines (self, template, defines):
      lines = ''

      for define in defines:
         lines += 'FLAGS += -D%s=%s\n' % (defines.key, defines.value)

      return template.replace ('%defines.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_bases (self, template, module, bases, path_simulator):
      lines = ''

      for base in bases:
         path_base = os.path.relpath (base, path_simulator)
         lines += 'FLAGS += -I%s\n' % path_base

      return template.replace ('%bases.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_sources (self, template, module, sources, path_simulator):
      lines = ''

      source_paths = []

      def add_source_path (path):
         source_paths.append (os.path.abspath (path))

      add_source_path (os.path.join (PATH_ROOT, 'src', 'vcvrack', 'BoardGeneric.cpp'))
      add_source_path (os.path.join (PATH_ROOT, 'src', 'Button.cpp'))
      add_source_path (os.path.join (PATH_ROOT, 'src', 'GateOut.cpp'))
      add_source_path (os.path.join (PATH_ROOT, 'src', 'detail', 'Animation.cpp'))
      add_source_path (os.path.join (PATH_ROOT, 'src', 'detail', 'Debounce.cpp'))
      add_source_path (os.path.join (PATH_ROOT, 'src', 'detail', 'Sdram.cpp'))
      add_source_path (os.path.join (PATH_ROOT, 'src', 'detail', 'Sram.cpp'))

      add_source_path (os.path.join (path_simulator, '../plugin_vcvrack.cpp'))

      for source in sources:
         for file in source.files:
            if file.path.endswith ('.cpp'):
               add_source_path (file.path)

      has_data = False

      for resource in module.resources:
         if resource.datas:
            has_data = True

      if has_data:
         add_source_path (os.path.join (path_simulator, '../plugin_generated_data.cpp'))

      if module.source_language == 'max':
         add_source_path (os.path.join (path_simulator, '../artifacts/%s_erbb.cpp' % module.name))
         add_source_path (os.path.join (path_simulator, '../%s_erbui.cpp' % module.name))
         add_source_path (os.path.join (path_simulator, '../module_max_alt.cpp'))

      if module.source_language == 'faust':
         pass  # nothing

      def object_name (path):
         return '$(CONFIGURATION)' + path + '.o'

      lines += '$(TARGET): %s\n' % ' '.join (map (lambda x: object_name (x), source_paths))
      lines += '\t@echo "LINK $(TARGET)"\n'
      lines += '\t@$(CXX) -o $@ $^ $(LDFLAGS)\n\n'

      for source_path in source_paths:
         rel_path = os.path.relpath (source_path, path_simulator)
         lines += '%s: %s Makefile | $(CONFIGURATION)\n' % (object_name (source_path), rel_path)
         lines += '\t@echo "CXX %s"\n' % rel_path.replace ('../', '')
         lines += '\t@mkdir -p $(@D)\n'
         lines += '\t@$(CXX) -MMD -MP $(CXXFLAGS) -c -o $@ %s\n\n' % rel_path

      return template.replace ('%sources.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_actions (self, template, module, path_simulator):
      lines = ''
      lines += self.replace_actions_max (module, path_simulator)
      lines += self.replace_actions_faust (module, path_simulator)
      lines += self.replace_actions_ui (module, path_simulator)
      lines += self.replace_actions_vcvrack (module, path_simulator)
      lines += self.replace_actions_data (module, path_simulator)

      return template.replace ('%target_actions%', lines)


   #--------------------------------------------------------------------------

   def replace_actions_max (self, module, path_simulator):
      if module.source_language != 'max':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_simulator)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_simulator)

      inputs = os.path.join (path_erbb_gens, 'max', 'code.py') + ' '
      inputs += os.path.join (path_erbui_gens, 'max', 'code.py') + ' '
      inputs += '../module_max.cpp' + ' '
      inputs += '../module_max.h'

      outputs = '../module_max_alt.cpp' + ' '
      outputs += '../module_max_alt.h' + ' '
      outputs += '../%s_erbb.cpp' % module.name + ' '
      outputs += '../%s_erbui.cpp' % module.name + ' '
      outputs += '../%s.h' % module.name

      lines += '%s: %s Makefile | $(CONFIGURATION)\n' % (outputs, inputs)
      lines += '\t@echo "ACTION Max"\n'
      lines += '\t@%s ../actions/action_max.py\n\n' % sys.executable

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_faust (self, module, path_simulator):
      if module.source_language != 'faust':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_simulator)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_simulator)

      inputs = os.path.join (path_erbb_gens, 'faust', 'code.py') + ' '
      inputs += os.path.join (path_erbui_gens, 'faust', 'code.py') + ' '
      inputs += '../../%s.dsp' % module.name

      outputs = '../module_faust.h' + ' '
      outputs += '../%s_erbb.hpp' % module.name + ' '
      outputs += '../%s_erbui.hpp' % module.name + ' '
      outputs += '../%s.h' % module.name

      lines += '%s: %s Makefile | $(CONFIGURATION)\n' % (outputs, inputs)
      lines += '\t@echo "ACTION Faust"\n'
      lines += '\t@%s ../actions/action_faust.py\n\n' % sys.executable

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_ui (self, module, path_simulator):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_simulator)

      inputs = os.path.join (path_erbui_gens, 'ui', 'code.py') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = '../artifacts/%sUi.h' % module.name

      lines += '%s: %s Makefile | $(CONFIGURATION)\n' % (outputs, inputs)
      lines += '\t@echo "ACTION Ui"\n'
      lines += '\t@%s ../actions/action_ui.py\n\n' % sys.executable

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_vcvrack (self, module, path_simulator):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_simulator)

      inputs = os.path.join (path_erbui_gens, 'vcvrack', 'code.py') + ' '
      inputs += os.path.join (path_erbui_gens, 'vcvrack', 'manifest.py') + ' '
      inputs += os.path.join (path_erbui_gens, 'vcvrack', 'panel.py') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = '../panel_vcvrack.svg' + ' '
      outputs += '../plugin_vcvrack.cpp' + ' '
      outputs += '../plugin.json'

      lines += '%s: %s Makefile | $(CONFIGURATION)\n' % (outputs, inputs)
      lines += '\t@echo "ACTION VCV Rack"\n'
      lines += '\t@%s ../actions/action_vcvrack.py\n\n' % sys.executable

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_data (self, module, path_simulator):
      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      lines = ''

      if data_paths:
         path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_simulator)

         inputs = os.path.join (path_erbb_gens, 'data', 'code.py') + ' '
         inputs += '../../%s.erbb' % module.name

         for data_path in data_paths:
            inputs += '%s' % os.path.relpath (data_path, path_simulator)

         outputs = '../%sData.h' % module.name + ' '
         outputs += '../plugin_generated_data.cpp'

         lines += '%s: %s Makefile | $(CONFIGURATION)\n' % (outputs, inputs)
         lines += '\t@echo "ACTION Data"\n'
         lines += '\t@%s ../actions/action_data.py\n\n' % sys.executable

      return lines
