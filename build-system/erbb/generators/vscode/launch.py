##############################################################################
#
#     launch.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



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

      template = template.replace ('%executable_release%', file_elf_release)
      template = template.replace ('%executable_debug%', file_elf_debug)
      template = template.replace ('%svd_file%', file_svd)

      with open (path_dst, 'w', encoding='utf-8') as file:
         file.write (template)
