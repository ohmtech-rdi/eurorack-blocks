#!/usr/bin/env python
#
#     deploy.py
#     Copyright (c) 2020 Raphael Dinge
#
#Tab=3########################################################################


##### IMPORT #################################################################

import os
import platform
import shutil
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))

if platform.system () == 'Darwin':
   PATH_VCV_PLUGINS = os.path.abspath (os.path.join (os.path.expanduser ("~"), 'Documents', 'Rack', 'plugins-v1'))

elif platform.system () == 'Linux':
   PATH_VCV_PLUGINS = os.path.abspath (os.path.join (os.path.expanduser ("~"), '.Rack', 'plugins-v1'))

PATH_VCV_PLUGIN = os.path.abspath (os.path.join (PATH_VCV_PLUGINS, 'Drop'))
PATH_VCV_PLUGIN_RES = os.path.abspath (os.path.join (PATH_VCV_PLUGIN, 'res'))
TARGET_BUILD_DIR = os.environ ['TARGET_BUILD_DIR']


##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      if not os.path.exists (PATH_VCV_PLUGIN):
         os.makedirs (PATH_VCV_PLUGIN)

      shutil.copyfile (
         os.path.join (TARGET_BUILD_DIR, 'plugin.dylib'),
         os.path.join (PATH_VCV_PLUGIN, 'plugin.dylib')
      )

      shutil.copyfile (
         os.path.join (TARGET_BUILD_DIR, 'plugin.json'),
         os.path.join (PATH_VCV_PLUGIN, 'plugin.json')
      )

      if os.path.exists (PATH_VCV_PLUGIN_RES):
         shutil.rmtree (PATH_VCV_PLUGIN_RES)

      shutil.copytree (
         os.path.join (TARGET_BUILD_DIR, 'res'),
         PATH_VCV_PLUGIN_RES
      )

   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Run command exited with %d' % error.returncode
      sys.exit (1)
