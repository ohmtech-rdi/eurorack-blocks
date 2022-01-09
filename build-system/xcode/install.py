#!/usr/bin/env python3
#
#     install.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

import os
import platform
import shutil
import sys



PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_XCODE = os.path.join (os.path.expanduser ('~'), 'Library', 'Developer', 'Xcode')
PATH_XCODE_PLUGINS = os.path.join (PATH_XCODE, 'Plug-ins')
PATH_XCODE_SPECS = os.path.join (PATH_XCODE, 'Specifications')


if __name__ == '__main__':

   if platform.system () != 'Darwin':
      print ('Unsupported platform', file=sys.stderr)
      sys.exit (1)

   if not os.path.exists (PATH_XCODE_PLUGINS):
      os.makedirs (PATH_XCODE_PLUGINS)

   if not os.path.exists (PATH_XCODE_SPECS):
      os.makedirs (PATH_XCODE_SPECS)

   print ('Copying Erbb.ideplugin')

   shutil.rmtree (os.path.join (PATH_XCODE_PLUGINS, 'Erbb.ideplugin'), ignore_errors = True)

   shutil.copytree (
      os.path.join (PATH_THIS, 'Erbb.ideplugin'),
      os.path.join (PATH_XCODE_PLUGINS, 'Erbb.ideplugin')
   )

   print ('Copying Erbb.xclangspec')

   shutil.copyfile (
      os.path.join (PATH_THIS, 'Erbb.xclangspec'),
      os.path.join (PATH_XCODE_SPECS, 'Erbb.xclangspec')
   )

   print ('Copying Erbui.ideplugin')

   shutil.rmtree (os.path.join (PATH_XCODE_PLUGINS, 'Erbui.ideplugin'), ignore_errors = True)

   shutil.copytree (
      os.path.join (PATH_THIS, 'Erbui.ideplugin'),
      os.path.join (PATH_XCODE_PLUGINS, 'Erbui.ideplugin')
   )

   print ('Copying Erbui.xclangspec')

   shutil.copyfile (
      os.path.join (PATH_THIS, 'Erbui.xclangspec'),
      os.path.join (PATH_XCODE_SPECS, 'Erbui.xclangspec')
   )
