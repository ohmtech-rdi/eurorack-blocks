##############################################################################
#
#     xcode.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import fileinput
import os
import platform
import random
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))

sys.path.insert (0, os.path.join (PATH_ROOT, 'submodules', 'gyp-next', 'pylib'))
import gyp



class Xcode:
   def __init__ (self):
      pass


   #--------------------------------------------------------------------------

   def generate (self, path, root):
      path_artifacts = os.path.join (path, 'artifacts')

      module = root.modules [0]

      gyp_args = [
         '--depth=.',
         '--generator-output=%s' % path_artifacts,
      ]

      cwd = os.getcwd ()
      os.chdir (path)
      gyp.main (gyp_args + ['project_vcvrack.gyp'])
      os.chdir (cwd)

      project_path = os.path.join (path_artifacts, 'project_vcvrack.xcodeproj')

      file = os.path.join (project_path, 'project.pbxproj')

      for line in fileinput.input (file, inplace = 1):
         print (line, end = '')

         if 'BuildIndependentTargetsInParallel' in line:
            print ('\t\t\t\tLastUpgradeCheck = 2000;')

      path_template = os.path.join (PATH_THIS, 'xcscheme_template')
      path_xcschemes = os.path.join (project_path, 'xcshareddata', 'xcschemes')
      path_xcscheme = os.path.join (path_xcschemes, '%s.xcscheme' % module.name)

      if not os.path.exists (path_xcschemes):
         os.makedirs (path_xcschemes)

      with open (path_template, 'r', encoding='utf-8') as file:
         template = file.read ()

      rack_path = ''
      if os.path.exists ('/Applications/VCV Rack 2 Pro.app/Contents/MacOS/Rack'):
         rack_path = '/Applications/VCV Rack 2 Pro.app'
      elif os.path.exists ('/Applications/VCV Rack 2 Free.app/Contents/MacOS/Rack'):
         rack_path = '/Applications/VCV Rack 2 Free.app'
      else:
         print ('\033[33mwarning:\033[0m can\'t find VCV Rack executable')

      identifier = ''.join (random.choice ('0123456789ABCDEF') for n in range (24))

      template = template.replace ('%module.name%', module.name)
      template = template.replace ('%identifier%', identifier)
      template = template.replace ('%rack.path%', rack_path)

      with open (path_xcscheme, 'w', encoding='utf-8') as file:
         file.write (template)
