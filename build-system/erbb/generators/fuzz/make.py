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
         self.generate_module (path, module, root.strict)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module, strict):
      path_template = os.path.join (PATH_THIS, 'Makefile_template')
      path_fuzz = os.path.join (path, 'artifacts', 'fuzz')
      path_makefile = os.path.join (path_fuzz, 'Makefile')

      if not os.path.exists (path_fuzz):
         os.makedirs (path_fuzz)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_root = os.path.relpath (PATH_ROOT, path_fuzz)
      path_libdaisy = os.path.relpath (PATH_LIBDAISY, path_fuzz)

      if module.section.name == 'flash':
         lds_path = os.path.join (PATH_LIBDAISY, 'core', 'STM32H750IB_flash.lds')
      elif module.section.name == 'qspi':
         lds_path = os.path.join (PATH_LIBDAISY, 'core', 'STM32H750IB_qspi.lds')
      elif module.section.name == 'sram':
         lds_path = os.path.join (PATH_ERBB_GENS, 'linker', 'STM32H750IB_sram_ramd2.lds')
      else:
         assert False

      path_lds = os.path.relpath (lds_path, path_fuzz)

      template = template.replace ('%module.name%', module.name)
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
      template = self.replace_warnings (template, strict)
      template = self.replace_defines (template, module, module.defines)
      template = self.replace_bases (template, module, module.bases, path_fuzz);
      template = self.replace_sources (template, module, module.sources, path_fuzz)
      template = self.replace_actions (template, module, path_fuzz)

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

   def replace_bases (self, template, module, bases, path_fuzz):
      lines = ''

      lines += 'FLAGS += -I../..\n'

      if module.source_language == 'max':
         path_gen_dsp = os.path.join (PATH_ROOT, 'include', 'gen_dsp')
         lines += 'FLAGS += -I%s\n' % os.path.relpath (path_gen_dsp, path_fuzz).replace ('\\', '/')
         lines += 'FLAGS += -I..\n'

      elif module.source_language == 'faust':
         lines += 'FLAGS += -I..\n'

      for base in bases:
         path_base = os.path.relpath (base.path, path_fuzz)
         lines += 'FLAGS += -I%s\n' % path_base.replace ('\\', '/')

      return template.replace ('%bases.entities%', lines)


   #--------------------------------------------------------------------------

   def replace_sources (self, template, module, sources, path_fuzz):
      lines = ''

      source_paths = self.include_sources_erb (module)

      def add_source_path (path):
         source_paths.append (os.path.abspath (path))

      add_source_path (os.path.join (path_fuzz, 'main.cpp'))

      for source in sources:
         for file in source.files:
            if file.path.endswith ('.cpp'):
               add_source_path (file.path)

      has_data = False

      for resource in module.resources:
         if resource.datas:
            has_data = True

      if has_data:
         add_source_path (os.path.join (path_fuzz, '../plugin_generated_data.cpp'))

      if module.source_language == 'max':
         add_source_path (os.path.join (path_fuzz, '../%s_erbb.cpp' % module.name))
         add_source_path (os.path.join (path_fuzz, '../%s_erbui.cpp' % module.name))
         add_source_path (os.path.join (path_fuzz, '../module_max_alt.cpp'))

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

      use_fatfs = False
      for define in module.defines:
         if define.key == 'erb_USE_FATFS' and define.value == '1':
            use_fatfs = True

      source_extra_paths = []
      source_extra_paths.append (os.path.abspath (os.path.join (PATH_LIBDAISY, 'core', 'startup_stm32h750xx.c')))
      cmsis_dsp_src_path = os.path.abspath (os.path.join (PATH_LIBDAISY, 'Drivers', 'CMSIS', 'DSP', 'Source'))
      source_extra_paths.append (os.path.join (cmsis_dsp_src_path, 'CommonTables', 'arm_common_tables.c'))
      source_extra_paths.append (os.path.join (cmsis_dsp_src_path, 'FastMathFunctions', 'arm_cos_f32.c'))
      source_extra_paths.append (os.path.join (cmsis_dsp_src_path, 'FastMathFunctions', 'arm_sin_f32.c'))
      if use_fatfs:
         fatfs_src_path = os.path.abspath (os.path.join (PATH_LIBDAISY, 'Middlewares', 'Third_Party', 'FatFs', 'src'))
         source_extra_paths.append (os.path.join (fatfs_src_path, 'diskio.c'))
         source_extra_paths.append (os.path.join (fatfs_src_path, 'ff.c'))
         source_extra_paths.append (os.path.join (fatfs_src_path, 'ff_gen_drv.c'))
         source_extra_paths.append (os.path.join (fatfs_src_path, 'option', 'ccsbcs.c'))

      objects = ' '.join (map (lambda x: object_name (x), source_paths))
      objects += ' ' + ' '.join (map (lambda x: object_name (x), source_extra_paths))
      lines += '$(CONFIGURATION)/$(TARGET).elf: %s\n' % objects
      lines += '\t@echo "LINK $(CONFIGURATION)/$(TARGET).elf"\n'
      lines += '\t@$(CXX) -o $@ $^ $(LDFLAGS)\n\n'

      for source_extra_path in source_extra_paths:
         rel_path = os.path.relpath (source_extra_path, path_fuzz)
         lines += '%s: %s Makefile | $(CONFIGURATION) $(ACTIONS)\n' % (object_name (source_extra_path), rel_path.replace ('\\', '/'))
         lines += '\t@echo "CC %s"\n' % rel_path.replace ('\\', '/').replace ('../', '')
         lines += '\t@mkdir -p $(@D)\n'
         lines += '\t@$(CC) -MMD -MP $(CFLAGS) -Wno-pedantic -Wno-missing-attributes -c -o $@ %s\n\n' % rel_path.replace ('\\', '/')
         lines += '-include %s\n\n' % dep_name (source_extra_path)

      for source_path in source_paths:
         rel_path = os.path.relpath (source_path, path_fuzz)
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

   def replace_actions (self, template, module, path_fuzz):
      lines = ''
      lines += self.replace_actions_max (module, path_fuzz)
      lines += self.replace_actions_faust (module, path_fuzz)
      lines += self.replace_actions_ui (module, path_fuzz)
      lines += self.replace_actions_fuzz (module, path_fuzz)
      lines += self.replace_actions_data (module, path_fuzz)

      return template.replace ('%target_actions%', lines)


   #--------------------------------------------------------------------------

   def replace_actions_max (self, module, path_fuzz):
      if module.source_language != 'max':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_fuzz)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_fuzz)

      inputs = os.path.join (path_erbb_gens, 'max', 'code.py').replace ('\\', '/') + ' '
      inputs += os.path.join (path_erbui_gens, 'max', 'code.py').replace ('\\', '/') + ' '
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
      lines += '\t@%s ../actions/action_max.py\n\n' % sys.executable.replace ('\\', '/')
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_faust (self, module, path_fuzz):
      if module.source_language != 'faust':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_fuzz)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_fuzz)

      inputs = os.path.join (path_erbb_gens, 'faust', 'code.py').replace ('\\', '/') + ' '
      inputs += os.path.join (path_erbui_gens, 'faust', 'code.py').replace ('\\', '/') + ' '
      inputs += '../../%s.dsp' % module.name

      outputs = '../module_faust.h' + ' '
      outputs += '../%s_erbb.hpp' % module.name + ' '
      outputs += '../%s_erbui.hpp' % module.name + ' '
      outputs += '../%s.h' % module.name

      lines += '%s:  ACTION_FAUST\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_FAUST: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION Faust"\n'
      lines += '\t@%s ../actions/action_faust.py\n\n' % sys.executable.replace ('\\', '/')
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_ui (self, module, path_fuzz):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_fuzz)

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

   def replace_actions_fuzz (self, module, path_fuzz):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path_fuzz)

      inputs = os.path.join (path_erbui_gens, 'fuzz', 'code.py').replace ('\\', '/') + ' '
      inputs += '../../%s.erbui' % module.name

      outputs = 'main.cpp'

      lines += '%s:  ACTION_DAISY\n' % outputs
      lines += '\t@:\n'
      lines += 'ACTION_DAISY: %s Makefile | $(CONFIGURATION)\n' % inputs
      lines += '\t@echo "ACTION Daisy"\n'
      lines += '\t@%s ../actions/action_fuzz.py\n\n' % sys.executable.replace ('\\', '/')
      lines += 'ACTIONS += %s\n\n' % outputs

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_data (self, module, path_fuzz):
      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      lines = ''

      if data_paths:
         path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path_fuzz)

         inputs = os.path.join (path_erbb_gens, 'data', 'code.py').replace ('\\', '/') + ' '
         inputs += '../../%s.erbb' % module.name + ' '

         for data_path in data_paths:
            inputs += '%s' % os.path.relpath (data_path, path_fuzz).replace ('\\', '/') + ' '

         outputs = '../%sData.h' % module.name + ' '
         outputs += '../plugin_generated_data.cpp'

         lines += '%s:  ACTION_DATA\n' % outputs
         lines += '\t@:\n'
         lines += 'ACTION_DATA: %s Makefile | $(CONFIGURATION)\n' % inputs
         lines += '\t@echo "ACTION Data"\n'
         lines += '\t@%s ../actions/action_data.py\n\n' % sys.executable.replace ('\\', '/')
         lines += 'ACTIONS += %s\n\n' % outputs

      return lines
