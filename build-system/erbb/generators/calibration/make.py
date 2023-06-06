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
PATH_BUILD_SYSTEM = os.path.join (PATH_ROOT, 'build-system')
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_ERBB_GENS = os.path.join (PATH_BUILD_SYSTEM, 'erbb', 'generators')
PATH_ERBUI_GENS = os.path.join (PATH_BUILD_SYSTEM, 'erbui', 'generators')
PATH_LIBDAISY = os.path.join (PATH_ROOT, 'submodules', 'libDaisy')



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
      path_configuration = os.path.join (path, 'artifacts', 'calibration')
      path_makefile = os.path.join (path_configuration, 'Makefile')

      if not os.path.exists (path_configuration):
         os.makedirs (path_configuration)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_root = os.path.relpath (PATH_ROOT, path_configuration)
      path_libdaisy = os.path.relpath (PATH_LIBDAISY, path_configuration)

      lds_path = os.path.join (PATH_LIBDAISY, 'core', 'STM32H750IB_flash.lds')
      path_lds = os.path.relpath (lds_path, path_configuration)

      template = template.replace ('%define_PATH_ROOT%', 'PATH_ROOT ?= %s' % path_root.replace ('\\', '/'))
      template = template.replace ('%define_PATH_LIBDAISY%', 'LIBDAISY_DIR ?= %s' % path_libdaisy.replace ('\\', '/'))

      if platform.system () == 'Darwin':
         PATH_ARM_BIN = os.path.join (PATH_TOOLCHAIN, 'gcc-arm-none-eabi-10.3-2021.10', 'bin')
         template = template.replace ('%define_CC%', 'CC = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-gcc'))
         template = template.replace ('%define_CXX%', 'CXX = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-g++'))
         template = template.replace ('%define_GDB%', 'GDB = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-gdb'))
         template = template.replace ('%define_AS%', 'AS = %s -x assembler-with-cpp' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-gcc'))
         template = template.replace ('%define_CP%', 'CP = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-objcopy'))
         template = template.replace ('%define_SZ%', 'SZ = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-size'))
         template = template.replace ('%define_HEX%', 'HEX = %s -O ihex' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-objcopy'))
         template = template.replace ('%define_BIN%', 'BIN = %s -O binary -S' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-objcopy'))

      elif platform.system () == 'Windows':
         PATH_ARM_BIN = os.path.join (PATH_TOOLCHAIN, 'gcc-arm-none-eabi-10.3-2021.10', 'bin')
         template = template.replace ('%define_CC%', 'CC = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-gcc').replace ('\\', '/'))
         template = template.replace ('%define_CXX%', 'CXX = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-g++').replace ('\\', '/'))
         template = template.replace ('%define_GDB%', 'GDB = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-gdb').replace ('\\', '/'))
         template = template.replace ('%define_AS%', 'AS = %s -x assembler-with-cpp' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-gcc').replace ('\\', '/'))
         template = template.replace ('%define_CP%', 'CP = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-objcopy').replace ('\\', '/'))
         template = template.replace ('%define_SZ%', 'SZ = %s' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-size').replace ('\\', '/'))
         template = template.replace ('%define_HEX%', 'HEX = %s -O ihex' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-objcopy').replace ('\\', '/'))
         template = template.replace ('%define_BIN%', 'BIN = %s -O binary -S' % os.path.join (PATH_ARM_BIN, 'arm-none-eabi-objcopy').replace ('\\', '/'))

      else:
         template = template.replace ('%define_CC%', 'CC = arm-none-eabi-gcc')
         template = template.replace ('%define_CXX%', 'CXX = arm-none-eabi-g++')
         template = template.replace ('%define_GDB%', 'GDB = arm-none-eabi-gdb')
         template = template.replace ('%define_AS%', 'AS = arm-none-eabi-gcc -x assembler-with-cpp')
         template = template.replace ('%define_CP%', 'CP = arm-none-eabi-objcopy')
         template = template.replace ('%define_SZ%', 'SZ = arm-none-eabi-size')
         template = template.replace ('%define_HEX%', 'HEX = arm-none-eabi-objcopy -O ihex')
         template = template.replace ('%define_BIN%', 'BIN = arm-none-eabi-objcopy -O binary -S')

      template = template.replace ('%LDS_PATH%', path_lds)
      template = self.replace_sources (template, module, module.sources, path_configuration)
      template = self.replace_actions (template, module, path_configuration)

      with open (path_makefile, 'w', encoding='utf-8') as file:
         file.write (template)


   #--------------------------------------------------------------------------

   def replace_sources (self, template, module, sources, path_configuration):
      lines = ''

      source_paths = self.include_sources_erb (module)

      def add_source_path (path):
         source_paths.append (os.path.abspath (path))

      add_source_path (os.path.join (path_configuration, 'calibrator.cpp'))

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

      source_extra_paths = []
      source_extra_paths.append (os.path.abspath (os.path.join (PATH_LIBDAISY, 'core', 'startup_stm32h750xx.c')))

      objects = ' '.join (map (lambda x: object_name (x), source_paths))
      objects += ' ' + ' '.join (map (lambda x: object_name (x), source_extra_paths))
      lines += '$(CONFIGURATION)/$(TARGET).elf: %s\n' % objects
      lines += '\t@echo "LINK $(CONFIGURATION)/$(TARGET).elf"\n'
      lines += '\t@$(CXX) -o $@ $^ $(LDFLAGS)\n\n'

      for source_extra_path in source_extra_paths:
         rel_path = os.path.relpath (source_extra_path, path_configuration)
         lines += '%s: %s Makefile | $(CONFIGURATION) $(ACTIONS)\n' % (object_name (source_extra_path), rel_path.replace ('\\', '/'))
         lines += '\t@echo "CC %s"\n' % rel_path.replace ('\\', '/').replace ('../', '')
         lines += '\t@mkdir -p $(@D)\n'
         lines += '\t@$(CC) -MMD -MP $(CFLAGS) -Wno-pedantic -Wno-missing-attributes -c -o $@ %s\n\n' % rel_path.replace ('\\', '/')
         lines += '-include %s\n\n' % dep_name (source_extra_path)

      for source_path in source_paths:
         rel_path = os.path.relpath (source_path, path_configuration)
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
         os.path.join (PATH_ROOT, 'include', 'erb', 'erb-daisy.gypi')
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

   def replace_actions (self, template, module, path_configuration):
      lines = ''
      lines += self.replace_actions_ui (module, path_configuration)
      lines += self.replace_actions_calibrator (module, path_configuration)

      return template.replace ('%target_actions%', lines)


   #--------------------------------------------------------------------------

   def replace_actions_ui (self, module, path_configuration):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_configuration)

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

   def replace_actions_calibrator (self, module, path_configuration):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_configuration)

      inputs = os.path.join (path_erbui_gens, 'calibrator', 'code.py').replace ('\\', '/') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = 'calibrator.cpp'

      lines += '%s:  ACTION_CALIBRATOR\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_CALIBRATOR: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION Calibrator"\n'
      lines += '\t@%s ../actions/action_calibrator.py\n\n' % sys.executable.replace ('\\', '/')
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines
