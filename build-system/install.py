#!/usr/bin/env python3
#
#     install.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

from __future__ import print_function
import os
import platform
import sys
import subprocess

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)



##############################################################################

if __name__ == '__main__':
   try:
      init_path = os.path.join (PATH_THIS, 'init.sh')

      if platform.system () == 'Darwin':
         profile_path = '~/.bash_profile'

      elif platform.system () == 'Linux':
         profile_path = '~/.bash_profile'

      else:
         print ('Platform %s not supported' % platform.system ())
         sys.exit (1)


      # Add source init.sh to profile
      subprocess.check_call ('echo "" >> %s' % profile_path, shell=True)
      subprocess.check_call (
         'echo "# Setting PATH for Eurorack-blocks/Erbb" >> %s' % profile_path,
         shell=True
      )
      subprocess.check_call (
         'echo "source %s" >> %s' % (init_path, profile_path),
         shell=True
      )

   except subprocess.CalledProcessError as error:
      print ('Configure command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit (1)
