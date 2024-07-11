##############################################################################
#
#     project.py
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



class Project:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module, root.strict)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module, strict):
      path_template = os.path.join (PATH_THIS, 'project_template.gyp')
      path_cpp = os.path.join (path, 'project_vcvrack.gyp')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%PATH_ROOT%', path_rel_root)
      template = self.replace_includes (template, module, path);
      template = self.replace_xcode_settings (template, strict);
      template = self.replace_cflags (template, strict);
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

   def replace_xcode_settings (self, template, strict):
      lines = ''

      if platform.system () == 'Darwin' and strict:
         lines += '         \'xcode_settings\':\n'
         lines += '         {\n'
         lines += '            \'GCC_TREAT_WARNINGS_AS_ERRORS\': \'YES\',\n'
         lines += '            \'SWIFT_TREAT_WARNINGS_AS_ERRORS\': \'YES\',\n'
         lines += '\n'
         lines += '            \'CLANG_WARN__DUPLICATE_METHOD_MATCH\': \'YES\',\n'
         lines += '            \'CLANG_WARN__EXIT_TIME_DESTRUCTORS\': \'YES\',\n'
         lines += '            \'CLANG_WARN_ASSIGN_ENUM\': \'YES\',\n'
         lines += '            \'CLANG_WARN_BOOL_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_CONSTANT_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_CXX0X_EXTENSIONS\': \'YES\',\n'
         lines += '            \'CLANG_WARN_DOCUMENTATION_COMMENTS\': \'YES\',\n'
         lines += '            \'CLANG_WARN_EMPTY_BODY\': \'YES\',\n'
         lines += '            \'CLANG_WARN_ENUM_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_IMPLICIT_SIGN_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_INT_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_SUSPICIOUS_IMPLICIT_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_UNREACHABLE_CODE\': \'YES\',\n'
         lines += '            \'CLANG_WARN_FLOAT_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_NON_LITERAL_NULL_CONVERSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_INFINITE_RECURSION\': \'YES\',\n'
         lines += '            \'CLANG_WARN_SEMICOLON_BEFORE_METHOD_BODY\': \'YES\',\n'
         lines += '            \'CLANG_WARN_COMMA\': \'YES\',\n'
         lines += '            \'CLANG_WARN_PRAGMA_PACK\': \'YES\',\n'
         lines += '            \'CLANG_WARN_UNGUARDED_AVAILABILITY\': \'YES\',\n'
         lines += '            \'CLANG_WARN_VEXING_PARSE\': \'YES\',\n'
         lines += '            \'CLANG_WARN_DELETE_NON_VIRTUAL_DTOR\': \'YES\',\n'
         lines += '            \'CLANG_WARN_RANGE_LOOP_ANALYSIS\': \'YES\',\n'
         lines += '            \'CLANG_WARN_SUSPICIOUS_MOVE\': \'YES\',\n'
         lines += '\n'
         lines += '            \'GCC_TREAT_IMPLICIT_FUNCTION_DECLARATIONS_AS_ERRORS\': \'YES\',\n'
         lines += '            \'GCC_TREAT_INCOMPATIBLE_POINTER_TYPE_WARNINGS_AS_ERRORS\': \'YES\',\n'
         lines += '            \'GCC_WARN_64_TO_32_BIT_CONVERSION\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_DEPRECATED_FUNCTIONS\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_INVALID_OFFSETOF_MACRO\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_MISSING_NEWLINE\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_MISSING_PROTOTYPES\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_POINTER_SIGNEDNESS\': \'YES\',\n'
         lines += '            \'GCC_WARN_ABOUT_RETURN_TYPE\': \'YES\',\n'
         lines += '            \'GCC_WARN_ALLOW_INCOMPLETE_PROTOCOL\': \'YES\',\n'
         lines += '            \'GCC_WARN_CHECK_SWITCH_STATEMENTS\': \'YES\',\n'
         lines += '            \'GCC_WARN_FOUR_CHARACTER_CONSTANTS\': \'YES\',\n'
         lines += '            \'GCC_WARN_HIDDEN_VIRTUAL_FUNCTIONS\': \'YES\',\n'
         lines += '            \'GCC_WARN_INITIALIZER_NOT_FULLY_BRACKETED\': \'YES\',\n'
         lines += '            \'GCC_WARN_MISSING_PARENTHESES\': \'YES\',\n'
         lines += '            \'GCC_WARN_MULTIPLE_DEFINITION_TYPES_FOR_SELECTOR\': \'YES\',\n'
         lines += '            \'GCC_WARN_NON_VIRTUAL_DESTRUCTOR\': \'YES\',\n'
         lines += '            \'GCC_WARN_PEDANTIC\': \'YES\',\n'
         lines += '            \'GCC_WARN_SHADOW\': \'YES\',\n'
         lines += '            \'GCC_WARN_SIGN_COMPARE\': \'YES\',\n'
         lines += '            \'GCC_WARN_STRICT_SELECTOR_MATCH\': \'YES\',\n'
         lines += '            \'GCC_WARN_TYPECHECK_CALLS_TO_PRINTF\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNDECLARED_SELECTOR\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNINITIALIZED_AUTOS\': \'YES_AGGRESSIVE\',\n'
         lines += '            \'GCC_WARN_UNKNOWN_PRAGMAS\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNUSED_FUNCTION\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNUSED_LABEL\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNUSED_PARAMETER\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNUSED_VALUE\': \'YES\',\n'
         lines += '            \'GCC_WARN_UNUSED_VARIABLE\': \'YES\',\n'
         lines += '\n'

         # There is no way to disable it (since it's in VCV Rack SDK headers).
         # So don't turn it on now.
         #lines += '            \'RUN_CLANG_STATIC_ANALYZER\': \'YES\',\n'
         #lines += '            \'CLANG_STATIC_ANALYZER_MODE\': \'deep\',\n'
         #lines += '            \'CLANG_ANALYZER_NONNULL\': \'YES\',\n'
         #lines += '            \'CLANG_ANALYZER_USE_AFTER_MOVE\': \'YES\',\n'
         #lines += '\n'

         lines += '            \'WARNING_CFLAGS\': [\n'
         lines += '               \'-Weverything\',\n'
         lines += '            ],\n'
         lines += '         },\n'

      return template.replace ('%        xcode_settings%', lines)


   #--------------------------------------------------------------------------

   def replace_cflags (self, template, strict):
      lines = ''

      if platform.system () == 'Linux' and strict:
         lines += '            \'-Wall\',\n'
         lines += '            \'-Wextra\',\n'
         lines += '            \'-Wpedantic\',\n'
         lines += '            \'-Werror\',\n'

      return template.replace ('%           cflags%', lines)


   #--------------------------------------------------------------------------

   def replace_defines (self, template, defines):
      lines = ''

      define_map = {
         'erb_BUFFER_SIZE': '48',
         'erb_SAMPLE_RATE': '48014',
         'erb_MIDI_MESSAGE_SIZE': '128',
      }

      for define in defines:
         define_map [define.key] = define.value

      for key, value in define_map.items ():
         lines += '            \'%s=%s\',\n' % (key, value)

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
      lines += self.replace_actions_max (module, path)
      lines += self.replace_actions_faust (module, path)
      lines += self.replace_actions_ui (module, path)
      lines += self.replace_actions_vcvrack (module, path)
      lines += self.replace_actions_data (module, path)

      return template.replace ('%           target_actions%', lines)


   #--------------------------------------------------------------------------

   def replace_actions_max (self, module, path):
      if module.source_language != 'max':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path)
      python_path = sys.executable
      action_path = 'artifacts/actions/action_max.py'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Max\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'%s/max/code.py\',\n' % path_erbb_gens
      lines += '                  \'%s/max/code.py\',\n' % path_erbui_gens
      lines += '                  \'artifacts/module_max.cpp\',\n'
      lines += '                  \'artifacts/module_max.h\',\n'
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'artifacts/module_max_alt.cpp\',\n'
      lines += '                  \'artifacts/module_max_alt.h\',\n'
      lines += '                  \'artifacts/%s_erbb.cpp\',\n' % module.name
      lines += '                  \'artifacts/%s_erbui.cpp\',\n' % module.name
      lines += '                  \'artifacts/%s.h\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'action\': [ \'%s\', \'%s\' ],\n' % (python_path, action_path)
      lines += '            },\n'

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_faust (self, module, path):
      if module.source_language != 'faust':
         return ''

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path)
      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path)
      python_path = sys.executable
      action_path = 'artifacts/actions/action_faust.py'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Faust\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'%s/faust/code.py\',\n' % path_erbb_gens
      lines += '                  \'%s/faust/code.py\',\n' % path_erbui_gens
      lines += '                  \'%s.dsp\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'artifacts/%s.h\',\n' % module.name
      lines += '                  \'artifacts/%s_erbb.hpp\',\n' % module.name
      lines += '                  \'artifacts/%s_erbui.hpp\',\n' % module.name
      lines += '                  \'artifacts/module_faust.h\',\n'
      lines += '               ],\n'
      lines += '               \'action\': [ \'%s\', \'%s\' ],\n' % (python_path, action_path)
      lines += '            },\n'

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_ui (self, module, path):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path)
      python_path = sys.executable
      action_path = 'artifacts/actions/action_ui.py'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile Ui\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'%s/ui/code.py\',\n' % path_erbui_gens
      lines += '                  \'%s.erbui\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'artifacts/%sUi.h\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'action\': [ \'%s\', \'%s\' ],\n' % (python_path, action_path)
      lines += '            },\n'

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_vcvrack (self, module, path):
      lines = ''

      path_erbui_gens = os.path.relpath (PATH_ERBUI_GENS, path)
      python_path = sys.executable
      action_path = 'artifacts/actions/action_vcvrack.py'

      lines += '            {\n'
      lines += '               \'action_name\': \'Transpile VcvRack\',\n'
      lines += '               \'inputs\': [\n'
      lines += '                  \'%s/vcvrack/code.py\',\n' % path_erbui_gens
      lines += '                  \'%s/vcvrack/manifest.py\',\n' % path_erbui_gens
      lines += '                  \'%s/vcvrack/panel.py\',\n' % path_erbui_gens
      lines += '                  \'%s.erbui\',\n' % module.name
      lines += '               ],\n'
      lines += '               \'outputs\': [\n'
      lines += '                  \'artifacts/panel_vcvrack.svg\',\n'
      lines += '                  \'artifacts/plugin_vcvrack.cpp\',\n'
      lines += '                  \'artifacts/plugin.json\',\n'
      lines += '               ],\n'
      lines += '               \'action\': [ \'%s\', \'%s\' ],\n' % (python_path, action_path)
      lines += '            },\n'

      return lines


   #--------------------------------------------------------------------------

   def replace_actions_data (self, module, path):
      data_paths = []

      for resource in module.resources:
         for data in resource.datas:
            data_paths.append (data.file.path)

      lines = ''

      path_erbb_gens = os.path.relpath (PATH_ERBB_GENS, path)
      python_path = sys.executable
      action_path = 'artifacts/actions/action_data.py'

      if data_paths:
         lines += '            {\n'
         lines += '               \'action_name\': \'Transpile Data\',\n'
         lines += '               \'inputs\': [\n'
         lines += '                  \'%s/data/code.py\',\n' % path_erbb_gens
         lines += '                  \'%s.erbb\',\n' % module.name
         for data_path in data_paths:
            lines += '                  \'%s\',\n' % data_path
         lines += '               ],\n'
         lines += '               \'outputs\': [\n'
         lines += '                  \'artifacts/%sData.h\',\n' % module.name
         lines += '                  \'artifacts/plugin_generated_data.cpp\',\n'
         lines += '               ],\n'
         lines += '               \'action\': [ \'%s\', \'%s\' ],\n' % (python_path, action_path)
         lines += '            },\n'

      return lines
