#!/usr/bin/env python3
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
import os
import sys



##############################################################################

if sys.version_info < (3, 7):
   print ('This script requires python 3.7 or greater.', file = sys.stderr)
   sys.exit (1)

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))



"""
==============================================================================
Name : generate
==============================================================================
"""

def generate ():

   nbr_digital_input = 128
   nbr_analog_input = 128
   nbr_audio_input = 4
   nbr_digital_output = 128
   nbr_analog_output = 128
   nbr_audio_output = 4

   content = ""
   content += "##############################################################################\n"
   content += "#\n"
   content += "#     definition.py\n"
   content += "#     Copyright (c) 2020 Raphael DINGE\n"
   content += "#\n"
   content += "#Tab=3########################################################################\n\n\n"
   content += "{\n"
   content += "   'class': 'erb::BoardMega',\n"
   content += "   'simulator': 'simulator/BoardMega.h',\n"
   content += "   'firmware': '',\n"
   content += "   'width': 42, # hp\n"
   content += "   'pins': {\n"

   for i in range (nbr_digital_input):
      content += "      'DII%d': {\n" % (i + 1)
      content += "         'accept': ['Button', 'GateIn', 'Switch'],\n"
      content += "         'bind': 'dii(%d)',\n" % i
      content += "      },\n"

   for i in range (nbr_analog_input):
      content += "      'ANI%d': {\n" % (i + 1)
      content += "         'accept': ['CvIn', 'Pot', 'Trim'],\n"
      content += "         'bind': 'ani(%d)',\n" % i
      content += "      },\n"

   for i in range (nbr_audio_input):
      content += "      'AUI%d': {\n" % (i + 1)
      content += "         'accept': ['AudioIn'],\n"
      content += "         'bind': 'aui(%d)',\n" % i
      content += "      },\n"

   for i in range (nbr_digital_output):
      content += "      'DIO%d': {\n" % (i + 1)
      content += "         'accept': ['GateOut'],\n"
      content += "         'bind': 'dio(%d)',\n" % i
      content += "      },\n"

   for i in range (nbr_analog_output):
      content += "      'ANO%d': {\n" % (i + 1)
      content += "         'type': 'pwm', # Led*\n"
      content += "         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],\n"
      content += "         'bind': 'ano(%d)',\n" % i
      content += "      },\n"

   for i in range (nbr_audio_output):
      content += "      'AUO%d': {\n" % (i + 1)
      content += "         'accept': ['AudioOut'],\n"
      content += "         'bind': 'auo(%d)',\n" % i
      content += "      },\n"

   content += "   },\n"

   content += "   'kinds': {\n"
   content += "      'CvIn': {'pools': ['ANI']},\n"
   content += "      'CvOut': {'pools': ['ANO']},\n"
   content += "      'GateOut': {'pools': ['DIO']},\n"
   content += "      'AudioIn': {'pools': ['AUI']},\n"
   content += "      'AudioOut': {'pools': ['AUO']},\n"
   content += "      'Led': {'pools': ['ANO']},\n"
   content += "      'LedBi': {'pools': ['ANO', 'ANO']},\n"
   content += "      'LedRgb': {'pools': ['ANO', 'ANO', 'ANO']},\n"
   content += "      'Pot': {'pools': ['ANI']},\n"
   content += "      'Trim': {'pools': ['ANI']},\n"
   content += "      'Button': {'pools': ['DII']},\n"
   content += "      'GateIn': {'pools': ['DII']},\n"
   content += "      'Switch': {'pools': ['DII', 'DII']},\n"
   content += "   },\n"

   content += "   'pools': {\n"

   content += "      'DII': [%s],\n" % ', '.join (map (lambda x: "'DII%d'" % (x + 1), range (nbr_digital_input)))
   content += "      'ANI': [%s],\n" % ', '.join (map (lambda x: "'ANI%d'" % (x + 1), range (nbr_analog_input)))
   content += "      'AUI': [%s],\n" % ', '.join (map (lambda x: "'AUI%d'" % (x + 1), range (nbr_audio_input)))
   content += "      'DIO': [%s],\n" % ', '.join (map (lambda x: "'DIO%d'" % (x + 1), range (nbr_digital_output)))
   content += "      'ANO': [%s],\n" % ', '.join (map (lambda x: "'ANO%d'" % (x + 1), range (nbr_analog_output)))
   content += "      'AUO': [%s],\n" % ', '.join (map (lambda x: "'AUO%d'" % (x + 1), range (nbr_audio_output)))

   content += "   },\n"
   content += "}\n"

   definition_py = os.path.join (PATH_THIS, 'definition.py')
   with open (definition_py, 'w', encoding='utf-8') as file:
      file.write (content)



##############################################################################

if __name__ == '__main__':
   sys.exit (generate ())
