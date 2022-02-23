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

      if 'CI' in os.environ:
         profile_path = os.path.join (os.path.expanduser ('~'), '.bash_profile')

      else:
         shell = os.environ ['SHELL']

         if 'bash' in shell:
            profile_path = os.path.join (os.path.expanduser ('~'), '.bash_profile')

         elif 'zsh' in shell:
            profile_path = os.path.join (os.path.expanduser ('~'), '.zshrc')

         else:
            print ('Shell %s is not supported' % shell)
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
