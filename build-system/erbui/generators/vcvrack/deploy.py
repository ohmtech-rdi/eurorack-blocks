##############################################################################
#
#     deploy.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



class Deploy:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, name, path, root):
      for module in root.modules:
         self.generate_module (name, path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, name, path, module):
      path_artifacts = os.path.join (path, 'artifacts')
      path_template = os.path.join (PATH_THIS, 'deploy_template.py')
      path_py = os.path.join (path_artifacts, 'deploy_vcvrack.py')

      with open (path_template, 'r') as file:
         template = file.read ()

      template = template.replace ('%name%', name)
      template = template.replace ('%module.name%', module.name)

      with open (path_py, 'w') as file:
         file.write (template)
