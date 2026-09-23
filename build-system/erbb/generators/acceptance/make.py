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
PATH_BUILD_SYSTEM = os.path.join (PATH_ROOT, 'build-system')
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
      if not module.acceptances: return

      path_template = os.path.join (PATH_THIS, 'Makefile_template')
      path_acceptance = os.path.join (path, 'artifacts', 'acceptance')
      path_makefile = os.path.join (path_acceptance, 'Makefile')

      if not os.path.exists (path_acceptance):
         os.makedirs (path_acceptance)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_root = os.path.relpath (PATH_ROOT, path_acceptance)

      if platform.system () == 'Darwin':
         if platform.machine () == 'x86_64':
            arch = 'ARCH_MAC := 1\nARCH_OS := mac\nARCH_CPU := x64\nARCH_NAME := mac-x64'
            cxx = 'CXX = arch -x86_64 clang'
         elif platform.machine () == 'arm64':
            arch = 'ARCH_MAC := 1\nARCH_OS := mac\nARCH_CPU := arm64\nARCH_NAME := mac-arm64'
            cxx = 'CXX = arch -arm64 clang'
         else:
            sys.exit (1)

      elif platform.system () == 'Linux':
         arch = 'ARCH_LIN := 1\nARCH_OS := lin\nARCH_CPU := x64\nARCH_NAME := lin-x64'
         cxx = '' # default

      elif platform.system () == 'Windows':
         PATH_GPP = os.path.join (PATH_BUILD_SYSTEM, 'toolchain', 'msys2_mingw64', 'bin', 'g++.exe')
         path_cxx = os.path.relpath (PATH_GPP, path_acceptance)
         arch = 'ARCH_WIN := 1\nARCH_OS := win\nARCH_WIN_64 := 1\nBITS := 64\nARCH_CPU := x64\nARCH_NAME := win-x64'
         cxx = 'CXX = %s' % path_cxx.replace ('\\', '/')

      project_path = os.path.abspath (path).replace ('\\', '/').rstrip ('/')

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%define_PATH_ROOT%', 'PATH_ROOT ?= %s' % path_root.replace ('\\', '/'))
      template = template.replace ('%define_ARCH%', arch)
      template = template.replace ('%define_CXX%', cxx)
      template = template.replace ('%define_PROJECT_PATH%', 'FLAGS += -Derb_PROJECT_PATH=\\"%s\\"' % project_path)
      template = self.replace_warnings (template, strict)
      template = self.replace_defines (template, module, module.defines)
      template = self.replace_bases (template, module, module.bases, path_acceptance)
      template = self.replace_blocks_all (template, module)
      template = self.replace_sources (template, module, module.sources, path_acceptance)
      template = self.replace_actions (template, module, path_acceptance)

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

      define_map = {
         'erb_BUFFER_SIZE': '48',
         'erb_SAMPLE_RATE': '48014',
         'erb_USE_FATFS': '0',
      }

      for define in defines:
         define_map [define.key] = define.value.replace ('"', '\\"')

      for key, value in define_map.items ():
         lines += 'FLAGS += -D%s=%s\n' % (key, value)

      return template.replace ('%defines.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_bases (self, template, module, bases, path_acceptance):
      lines = ''

      lines += 'FLAGS += -I../..\n'

      if self.use_fatfs (module):
         path_fatfs = os.path.join (PATH_LIBDAISY, 'Middlewares', 'Third_Party', 'FatFs', 'src')
         lines += 'FLAGS += -I%s\n' % os.path.relpath (path_fatfs, path_acceptance).replace ('\\', '/')
         path_daisy_src_sys = os.path.join (PATH_LIBDAISY, 'src', 'sys')
         lines += 'FLAGS += -I%s\n' % os.path.relpath (path_daisy_src_sys, path_acceptance).replace ('\\', '/')
         path_daisy_src = os.path.join (PATH_LIBDAISY, 'src')
         lines += 'FLAGS += -I%s\n' % os.path.relpath (path_daisy_src, path_acceptance).replace ('\\', '/')

      for base in bases:
         path_base = os.path.relpath (base.path, path_acceptance)
         lines += 'FLAGS += -I%s\n' % path_base.replace ('\\', '/')

      return template.replace ('%bases.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_blocks_all (self, template, module):
      names = [acceptance.name for acceptance in module.acceptances]

      lines = ''
      lines += 'all: %s\n\n' % ' '.join (names)

      for name in names:
         lines += '%s: $(CONFIGURATION)/%s\n' % (name, name)

      lines += '\n.PHONY: all %s\n' % ' '.join (names)

      return template.replace ('%blocks.all%', lines)


   #--------------------------------------------------------------------------

   def use_fatfs (self, module):
      for define in module.defines:
         if define.key == 'erb_USE_FATFS' and define.value == '1':
            return True

      return False


   #--------------------------------------------------------------------------

   def replace_sources (self, template, module, sources, path_acceptance):
      lines = ''

      def object_name (path):
         if platform.system () == 'Windows':
            return '$(CONFIGURATION)' + path [path.find (':') + 1:].replace ('\\', '/') + '.o'
         else:
            return '$(CONFIGURATION)' + path + '.o'

      def dep_name (path):
         if platform.system () == 'Windows':
            return '$(CONFIGURATION)' + path [path.find (':') + 1:].replace ('\\', '/') + '.d'
         else:
            return '$(CONFIGURATION)' + path + '.d'

      module_paths = self.include_sources_erb (module)

      for source in sources:
         for file in source.files:
            if file.path.endswith ('.cpp'):
               module_paths.append (os.path.abspath (file.path))

      has_data = False

      for resource in module.resources:
         if resource.datas:
            has_data = True

      if has_data:
         module_paths.append (os.path.abspath (os.path.join (path_acceptance, '../plugin_generated_data.cpp')))

      module_c_paths = []

      if self.use_fatfs (module):
         fatfs_src_path = os.path.abspath (os.path.join (PATH_LIBDAISY, 'Middlewares', 'Third_Party', 'FatFs', 'src'))
         module_c_paths.append (os.path.join (fatfs_src_path, 'diskio.c'))
         module_c_paths.append (os.path.join (fatfs_src_path, 'ff.c'))
         module_c_paths.append (os.path.join (fatfs_src_path, 'ff_gen_drv.c'))
         module_c_paths.append (os.path.join (fatfs_src_path, 'option', 'ccsbcs.c'))

      module_objects = ' '.join (map (object_name, module_paths + module_c_paths))

      # One executable per block
      block_paths = []

      for acceptance in module.acceptances:
         paths = [os.path.abspath (file.path) for file in acceptance.files if file.path.endswith ('.cpp')]
         block_paths.extend (paths)

         objects = ' '.join (map (object_name, paths))
         lines += '$(CONFIGURATION)/%s: %s %s\n' % (acceptance.name, module_objects, objects)
         lines += '\t@echo "LINK %s"\n' % acceptance.name
         lines += '\t@$(CXX) -o $@ $^ $(LDFLAGS)\n\n'

      for c_path in module_c_paths:
         rel_path = os.path.relpath (c_path, path_acceptance)
         lines += '%s: %s Makefile | $(CONFIGURATION) $(ACTIONS)\n' % (object_name (c_path), rel_path.replace ('\\', '/'))
         lines += '\t@echo "CC %s"\n' % rel_path.replace ('\\', '/').replace ('../', '')
         lines += '\t@mkdir -p $(@D)\n'
         lines += '\t@$(CC) -MMD -MP $(CFLAGS) -Wno-pedantic -Wno-ignored-attributes -c -o $@ %s\n\n' % rel_path.replace ('\\', '/')
         lines += '-include %s\n\n' % dep_name (c_path)

      for source_path in module_paths + block_paths:
         rel_path = os.path.relpath (source_path, path_acceptance)
         lines += '%s: %s Makefile | $(CONFIGURATION) $(ACTIONS)\n' % (object_name (source_path), rel_path.replace ('\\', '/'))
         lines += '\t@echo "CXX %s"\n' % rel_path.replace ('\\', '/').replace ('../', '')
         lines += '\t@mkdir -p $(@D)\n'
         lines += '\t@$(CXX) -MMD -MP $(CXXFLAGS) -c -o $@ %s\n\n' % rel_path.replace ('\\', '/')
         lines += '-include %s\n\n' % dep_name (source_path)

      return template.replace ('%sources%', lines)


   #--------------------------------------------------------------------------

   def include_sources_erb (self, module):
      sources = []

      sources.extend (self.include_gyp_sources (
         os.path.join (PATH_ROOT, 'include', 'erb', 'erb-src.gypi')
      ))

      sources.extend (self.include_gyp_sources (
         os.path.join (PATH_ROOT, 'include', 'erb', 'erb-rig.gypi')
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

   def replace_actions (self, template, module, path_acceptance):
      lines = ''
      lines += self.replace_actions_ui (module, path_acceptance)
      lines += self.replace_actions_data (module, path_acceptance)

      return template.replace ('%target_actions%', lines)


   #--------------------------------------------------------------------------

   def replace_actions_ui (self, module, path_acceptance):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_acceptance)

      inputs = os.path.join (path_erbui_gens, 'ui', 'code.py').replace ('\\', '/') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = '../%sUi.h' % module.name

      lines += '%s:  ACTION_UI\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_UI: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION UI"\n'
      lines += '\t@%s ../actions/action_ui.py\n\n' % sys.executable.replace ('\\', '/')
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_data (self, module, path_acceptance):
      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      lines = ''

      if data_paths:
         path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_acceptance)

         inputs = os.path.join (path_erbb_gens, 'data', 'code.py').replace ('\\', '/') + ' '
         inputs += '../../%s.erbb' % module.name + ' '

         for data_path in data_paths:
            inputs += '%s' % os.path.relpath (data_path, path_acceptance).replace ('\\', '/') + ' '

         outputs = '../%sData.h' % module.name + ' '
         outputs += '../plugin_generated_data.cpp'

         lines += '%s:  ACTION_DATA\n' % outputs
         lines += '\t@:\n'
         lines += 'ACTION_DATA: %s Makefile | $(CONFIGURATION)\n' % inputs
         lines += '\t@echo "ACTION Data"\n'
         lines += '\t@%s ../actions/action_data.py\n\n' % sys.executable.replace ('\\', '/')
         lines += 'ACTIONS += %s\n\n' % outputs

      return lines
