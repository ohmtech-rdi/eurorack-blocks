#!/usr/bin/env python3

import os
import sys

def main ():
   comp_line = os.environ ['COMP_LINE']
   comp_cword = os.environ ['COMP_CWORD']

   def complete (choices, start):
      replies = [x for x in choices if x.startswith (start)]
      print ('COMPREPLY=(%s)' % ' '.join (replies))

   if comp_cword == '1':
      words = comp_line.split (' ')
      command = words [1]
      choices = ['setup', 'init', 'configure', 'build', 'install', 'bootloader', 'max', 'faust']
      complete (choices, command)

   elif comp_cword == '2':
      words = comp_line.split (' ')
      command = words [1]
      option = words [2]
      if command == 'build':
         choices = ['daisy', 'gerber', 'hardware', 'simulator']
         complete (choices, option)

      elif command == 'install':
         choices = ['openocd', 'dfu']
         complete (choices, option)

      elif command == 'max':
         choices = ['init']
         complete (choices, option)

      elif command == 'faust':
         choices = ['init']
         complete (choices, option)

      else:
         print ('COMPREPLY=()')

   elif comp_cword == '3':
      words = comp_line.split (' ')
      command = words [1]
      option = words [2]
      option2 = words [3]
      if command == 'build' and option in ['daisy', 'simulator']:
         choices = ['debug', 'release']
         complete (choices, option2)

      elif command == 'install':
         choices = ['debug', 'release']
         complete (choices, option2)

      else:
         print ('COMPREPLY=()')

   else:
      print ('COMPREPLY=()')



#--------------------------------------------------------------------------

if __name__ == '__main__':
   sys.exit (main ())
