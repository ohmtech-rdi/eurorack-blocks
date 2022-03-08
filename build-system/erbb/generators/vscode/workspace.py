##############################################################################
#
#     workspace.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



class Workspace:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      path_template = os.path.join (PATH_THIS, 'workspace_template.json')
      path_dst = os.path.join (path, 'artifacts', '%s.code-workspace' % module.name)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      path_artifacts = os.path.join (path, 'artifacts')

      paths = []
      paths.append (path)

      paths.append (os.path.join (PATH_ROOT, 'include', 'erb'))

      if module.source_language == 'max':
         paths.append (os.path.join (PATH_ROOT, 'include', 'gen_dsp'))

      for import_ in module.imports:
         paths.append (os.path.dirname (import_.path))

      lines = ',\n'.join (map (lambda path: '      { "path": "%s" }' % os.path.relpath (path, path_artifacts).replace ('\\', '/'), paths))
      template = template.replace ('%     folders%', lines)

      with open (path_dst, 'w', encoding='utf-8') as file:
         file.write (template)
