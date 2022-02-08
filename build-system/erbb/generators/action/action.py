##############################################################################
#
#     project.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



class Action:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      self.generate_module_action (path, module, 'daisy')
      self.generate_module_action (path, module, 'ui')
      self.generate_module_action (path, module, 'vcvrack')



   #--------------------------------------------------------------------------

   def generate_module_action (self, path, module, action):
      path_template = os.path.join (PATH_THIS, 'action_%s_template.py' % action)
      path_py = os.path.join (path, 'artifacts', 'action_%s.py' % action)

      with open (path_template, 'r') as file:
         template = file.read ()

      path_rel_root = os.path.relpath (PATH_ROOT, path)
      template = template.replace ('%PATH_ROOT%', path_rel_root)

      with open (path_py, 'w') as file:
         file.write (template)
