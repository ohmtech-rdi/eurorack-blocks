#!/usr/bin/env python3

import os
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
sys.path.insert (0, os.path.dirname (PATH_THIS))
import completion

if __name__ == '__main__':
   if 'ERBB_COMPLETION_FISH' in os.environ:
      print ('\n'.join (completion.complete (os.environ ['COMP_LINE'], add_description=True)))
   else:
      print ('COMPREPLY=(%s)' % ' '.join (completion.complete (os.environ ['COMP_LINE'])))
