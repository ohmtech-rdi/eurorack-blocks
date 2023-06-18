##############################################################################
#
#     xcode.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import fileinput
import os
import platform
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
