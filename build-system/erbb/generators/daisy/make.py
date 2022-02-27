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
PATH_LIBDAISY = os.path.join (PATH_ROOT, 'submodules', 'libDaisy')



class Make:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module, root.strict)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module, strict):
      path_template = os.path.join (PATH_THIS, 'Makefile_template')
      path_daisy = os.path.join (path, 'artifacts', 'daisy')
      path_makefile = os.path.join (path_daisy, 'Makefile')

      if not os.path.exists (path_daisy):
         os.makedirs (path_daisy)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_root = os.path.relpath (PATH_ROOT, path_daisy)
      path_libdaisy = os.path.relpath (PATH_LIBDAISY, path_daisy)

      if module.section.name == 'flash':
         lds_path = os.path.join (PATH_LIBDAISY, 'core', 'STM32H750IB_flash.lds')
      elif module.section.name == 'qspi':
         lds_path = os.path.join (PATH_LIBDAISY, 'core', 'STM32H750IB_qspi.lds')
      else:
         assert False

      path_lds = os.path.relpath (lds_path, path_daisy)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%define_PATH_ROOT%', 'PATH_ROOT ?= %s' % path_root)
      template = template.replace ('%define_PATH_LIBDAISY%', 'LIBDAISY_DIR ?= %s' % path_libdaisy)
      template = template.replace ('%LDS_PATH%', path_lds)
      template = self.replace_warnings (template, strict)
      template = self.replace_defines (template, module, module.defines)
      template = self.replace_bases (template, module, module.bases, path_daisy);
      template = self.replace_sources (template, module, module.sources, path_daisy)
      template = self.replace_actions (template, module, path_daisy)

      with open (path_makefile, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_warnings (self, template, strict):
      lines = ''

      if strict:
         lines += 'FLAGS += -Wall -Wextra -Wpedantic -Werror\n'

      return template.replace ('%warnings%', lines)


   #--------------------------------------------------------------------------

   def replace_defines (self, template, module, defines):
      lines = ''

      if module.section.name != 'flash':
         lines += 'FLAGS += -DBOOT_APP=1\n'

      if module.source_language == 'max':
         lines += 'FLAGS += -DGENLIB_USE_FLOAT32\n'
         lines += 'FLAGS += -DGENLIB_NO_JSON\n'
         lines += 'FLAGS += -DGEN_NO_STDLIB\n'

      for define in defines:
         lines += 'FLAGS += -D%s=%s\n' % (defines.key, defines.value)

      return template.replace ('%defines.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_bases (self, template, module, bases, path_daisy):
      lines = ''

      lines += 'FLAGS += -I../..\n'

      if module.source_language == 'max':
         path_gen_dsp = os.path.join (PATH_ROOT, 'include', 'gen_dsp')
         lines += 'FLAGS += -I%s\n' % os.path.relpath (path_gen_dsp, path_daisy)

      for base in bases:
         path_base = os.path.relpath (base.path, path_daisy)
         lines += 'FLAGS += -I%s\n' % path_base

      return template.replace ('%bases.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_sources (self, template, module, sources, path_daisy):
      lines = ''

      source_paths = self.include_sources_erb (module)

      def add_source_path (path):
         source_paths.append (os.path.abspath (path))

      add_source_path (os.path.join (path_daisy, '../main_daisy.cpp'))

      for source in sources:
         for file in source.files:
            if file.path.endswith ('.cpp'):
               add_source_path (file.path)

      has_data = False

      for resource in module.resources:
         if resource.datas:
            has_data = True

      if has_data:
         add_source_path (os.path.join (path_daisy, '../plugin_generated_data.cpp'))

      if module.source_language == 'max':
         add_source_path (os.path.join (path_daisy, '../%s_erbb.cpp' % module.name))
         add_source_path (os.path.join (path_daisy, '../%s_erbui.cpp' % module.name))
         add_source_path (os.path.join (path_daisy, '../module_max_alt.cpp'))

      def object_name (path):
         return '$(CONFIGURATION)' + path + '.o'

      def dep_name (path):
         return '$(CONFIGURATION)' + path + '.d'

      source_path_startup = os.path.abspath (os.path.join (PATH_LIBDAISY, 'core', 'startup_stm32h750xx.c'))

      objects = ' '.join (map (lambda x: object_name (x), source_paths))
      objects += ' ' + object_name (source_path_startup)
      lines += '$(CONFIGURATION)/$(TARGET).elf: %s\n' % objects
      lines += '\t@echo "LINK $(CONFIGURATION)/$(TARGET).elf"\n'
      lines += '\t@$(CXX) -o $@ $^ $(LDFLAGS)\n\n'

      rel_path = os.path.relpath (source_path_startup, path_daisy)
      lines += '%s: %s Makefile | $(CONFIGURATION) $(ACTIONS)\n' % (object_name (source_path_startup), rel_path)
      lines += '\t@echo "CC %s"\n' % rel_path.replace ('../', '')
      lines += '\t@mkdir -p $(@D)\n'
      lines += '\t@$(CC) -MMD -MP $(CFLAGS) -Wno-pedantic -Wno-missing-attributes -c -o $@ %s\n\n' % rel_path
      lines += '-include %s\n\n' % dep_name (source_path_startup)

      for source_path in source_paths:
         rel_path = os.path.relpath (source_path, path_daisy)
         lines += '%s: %s Makefile | $(CONFIGURATION) $(ACTIONS)\n' % (object_name (source_path), rel_path)
         lines += '\t@echo "CXX %s"\n' % rel_path.replace ('../', '')
         lines += '\t@mkdir -p $(@D)\n'
         lines += '\t@$(CXX) -MMD -MP $(CXXFLAGS) -c -o $@ %s\n\n' % rel_path
         lines += '-include %s\n\n' % dep_name (source_path)

      return template.replace ('%sources%', lines)


   #--------------------------------------------------------------------------

   def include_sources_erb (self, module):
      sources = []

      sources.extend (self.include_gyp_sources (
         os.path.join (PATH_ROOT, 'include', 'erb', 'erb-src.gypi')
      ))

      sources.extend (self.include_gyp_sources (
         os.path.join (PATH_ROOT, 'include', 'erb', 'erb-daisy.gypi')
      ))

      if module.source_language == 'max':
         sources.extend (self.include_gyp_sources (
            os.path.join (PATH_ROOT, 'include', 'gen_dsp', 'gen_dsp.gypi')
         ))

      return sources


   #--------------------------------------------------------------------------

   def include_gyp_sources (self, path_gyp_file):
      sources = []

      with open (path_gyp_file, 'r', encoding='utf-8') as f:
         gyp_dict = eval (f.read ())

      gyp_sources = gyp_dict ['sources']
      path_gyp_dir = os.path.dirname (path_gyp_file)

      for source in gyp_sources:
         if source.endswith ('.cpp'):
            sources.append (os.path.abspath (os.path.join (path_gyp_dir, source)))

      return sources


   #--------------------------------------------------------------------------

   def replace_actions (self, template, module, path_daisy):
      lines = ''
      lines += self.replace_actions_max (module, path_daisy)
      lines += self.replace_actions_faust (module, path_daisy)
      lines += self.replace_actions_ui (module, path_daisy)
      lines += self.replace_actions_daisy (module, path_daisy)
      lines += self.replace_actions_data (module, path_daisy)

      return template.replace ('%target_actions%', lines)


   #--------------------------------------------------------------------------

   def replace_actions_max (self, module, path_daisy):
      if module.source_language != 'max':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_daisy)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_daisy)

      inputs = os.path.join (path_erbb_gens, 'max', 'code.py') + ' '
      inputs += os.path.join (path_erbui_gens, 'max', 'code.py') + ' '
      inputs += '../module_max.cpp' + ' '
      inputs += '../module_max.h'

      outputs = '../module_max_alt.cpp' + ' '
      outputs += '../module_max_alt.h' + ' '
      outputs += '../%s_erbb.cpp' % module.name + ' '
      outputs += '../%s_erbui.cpp' % module.name + ' '
      outputs += '../%s.h' % module.name

      lines += '%s:  ACTION_MAX\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_MAX: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION Max"\n'
      lines += '\t@%s ../actions/action_max.py\n\n' % sys.executable
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_faust (self, module, path_daisy):
      if module.source_language != 'faust':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_daisy)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_daisy)

      inputs = os.path.join (path_erbb_gens, 'faust', 'code.py') + ' '
      inputs += os.path.join (path_erbui_gens, 'faust', 'code.py') + ' '
      inputs += '../../%s.dsp' % module.name

      outputs = '../module_faust.h' + ' '
      outputs += '../%s_erbb.hpp' % module.name + ' '
      outputs += '../%s_erbui.hpp' % module.name + ' '
      outputs += '../%s.h' % module.name

      lines += '%s:  ACTION_FAUST\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_FAUST: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION Faust"\n'
      lines += '\t@%s ../actions/action_faust.py\n\n' % sys.executable
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_ui (self, module, path_daisy):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_daisy)

      inputs = os.path.join (path_erbui_gens, 'ui', 'code.py') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = '../%sUi.h' % module.name

      lines += '%s:  ACTION_UI\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_UI: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION UI"\n'
      lines += '\t@%s ../actions/action_ui.py\n\n' % sys.executable
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_daisy (self, module, path_daisy):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_daisy)

      inputs = os.path.join (path_erbui_gens, 'daisy', 'code.py') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = '../main_daisy.cpp'

      lines += '%s:  ACTION_DAISY\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_DAISY: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION Daisy"\n'
      lines += '\t@%s ../actions/action_daisy.py\n\n' % sys.executable
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_data (self, module, path_daisy):
      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      lines = ''

      if data_paths:
         path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_daisy)

         inputs = os.path.join (path_erbb_gens, 'data', 'code.py') + ' '
         inputs += '../../%s.erbb' % module.name + ' '

         for data_path in data_paths:
            inputs += '%s' % os.path.relpath (data_path, path_daisy) + ' '

         outputs = '../%sData.h' % module.name + ' '
         outputs += '../plugin_generated_data.cpp'

         lines += '%s:  ACTION_DATA\n' % outputs
         lines += '\t@:\n'
         lines += 'ACTION_DATA: %s Makefile | $(CONFIGURATION)\n' % inputs
         lines += '\t@echo "ACTION Data"\n'
         lines += '\t@%s ../actions/action_data.py\n\n' % sys.executable
         lines += 'ACTIONS += %s\n\n' % outputs

      return lines
