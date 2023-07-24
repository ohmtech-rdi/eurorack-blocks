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
      self.generate_module_action (path, module, 'perf')
      self.generate_module_action (path, module, 'ui')
      self.generate_module_action (path, module, 'vcvrack')
      self.generate_module_action (path, module, 'data')
      self.generate_module_action (path, module, 'vcvrack_install')

      if module.source_language == 'max':
         self.generate_module_action (path, module, 'max')

      if module.source_language == 'faust':
         self.generate_module_action (path, module, 'faust')



   #--------------------------------------------------------------------------

   def generate_module_action (self, path, module, action):
      path_template = os.path.join (PATH_THIS, 'action_%s_template.py' % action)
      path_actions = os.path.join (path, 'artifacts', 'actions')
      path_py = os.path.join (path_actions, 'action_%s.py' % action)

      if not os.path.exists (path_actions):
         os.makedirs (path_actions)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      template = template.replace ('%PATH_ROOT%', PATH_ROOT.replace ('\\', '/'))
      template = template.replace ('%PATH_PROJECT%', os.path.abspath (path).replace ('\\', '/'))
      template = template.replace ('%module.name%', module.name)

      with open (path_py, 'w', encoding='utf-8') as file:
         file.write (template)
