##############################################################################
#
#     launch.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import platform

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BUILD_SYSTEM = os.path.join (PATH_ROOT, 'build-system')



class Launch:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'launch_template.json')
      path_dst = os.path.join (path, '.vscode', 'launch.json')

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_artifacts = os.path.join (path, 'artifacts')
      file_elf_release = os.path.abspath (
         os.path.join (path_artifacts, 'daisy', 'Release', '%s.elf' % module.name)
      )
      file_elf_debug = os.path.abspath (
         os.path.join (path_artifacts, 'daisy', 'Debug', '%s.elf' % module.name)
      )
      file_svd = os.path.abspath (os.path.join (PATH_THIS, 'svd', 'STM32H750x.svd'))

      if platform.system () == 'Darwin':
         rack_path = ''
         if os.path.exists ('/Applications/VCV Rack 2 Pro.app/Contents/MacOS/Rack'):
            rack_path = '/Applications/VCV Rack 2 Pro.app/Contents/MacOS/Rack'
         elif os.path.exists ('/Applications/VCV Rack 2 Free.app/Contents/MacOS/Rack'):
            rack_path = '/Applications/VCV Rack 2 Free.app/Contents/MacOS/Rack'
         else:
            print ('\033[33mwarning:\033[0m can\'t find VCV Rack executable')

         os_launch_debug_config =  '         "osx": {\n'
         os_launch_debug_config += '            "MIMode": "lldb",\n'
         os_launch_debug_config += '            "program": "%s"\n' % rack_path
         os_launch_debug_config += '         }'

      elif platform.system () == 'Windows':
         rack_path = ''
         if os.path.exists ('C:/Program Files/VCV/Rack2Pro/Rack.exe'):
            rack_path = 'C:/Program Files/VCV/Rack2Pro/Rack.exe'
         elif os.path.exists ('C:/Program Files/VCV/Rack2Free/Rack.exe'):
            rack_path = 'C:/Program Files/VCV/Rack2Free/Rack.exe'
         else:
            print ('\033[33mwarning:\033[0m can\'t find VCV Rack executable')

         gdb_path = os.path.join (PATH_BUILD_SYSTEM, 'toolchain', 'msys2_mingw64', 'bin', 'gdb.exe')

         os_launch_debug_config =  '         "windows": {\n'
         os_launch_debug_config += '            "MIMode": "gdb",\n'
         os_launch_debug_config += '            "program": "%s",\n' % rack_path
         os_launch_debug_config += '            "miDebuggerPath": "%s"\n' % gdb_path.replace ('\\', '/')
         os_launch_debug_config += '         }'

      elif platform.system () == 'Linux':
         rack_path = ''
         print ('\033[33mwarning:\033[0m can\'t find VCV Rack executable')

         os_launch_debug_config =  '         "linux": {\n'
         os_launch_debug_config += '            "MIMode": "gdb",\n'
         os_launch_debug_config += '            "program": "%s"\n' % rack_path
         os_launch_debug_config += '         }'


      template = template.replace ('%executable_release%', file_elf_release.replace ('\\', '/'))
      template = template.replace ('%executable_debug%', file_elf_debug.replace ('\\', '/'))
      template = template.replace ('%svd_file%', file_svd.replace ('\\', '/'))
      template = template.replace ('%        os_launch_debug_config%', os_launch_debug_config)

      with open (path_dst, 'w', encoding='utf-8') as file:
         file.write (template)
