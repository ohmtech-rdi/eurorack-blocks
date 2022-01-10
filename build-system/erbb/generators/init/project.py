##############################################################################
#
#     project.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))



class Project:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, name):
      self.generate_file (path, name, 'cpp')
      self.generate_file (path, name, 'h')
      self.generate_file (path, name, 'erbui')
      self.generate_file (path, name, 'erbb')


   #--------------------------------------------------------------------------

   def generate_file (self, path, name, extension):
      path_template = os.path.join (PATH_THIS, 'project_template.%s' % extension)
      path_output = os.path.join (path, '%s.%s' % (name, extension))

      with open (path_template, 'r') as file:
         template = file.read ()

      template = template.replace ('%Name%', name)

      with open (path_output, 'w') as file:
         file.write (template)
