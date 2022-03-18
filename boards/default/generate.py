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
Name : generate_definition
==============================================================================
"""

def generate_definition ():

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
   content += "   'class': 'erb::BoardDefault',\n"
   content += "   'include': 'BoardDefault.h',\n"
   content += "   'pcb': 'default.kicad_pcb',\n"
   content += "   'width': 12, # hp\n"
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



"""
==============================================================================
Name : generate_pcb
==============================================================================
"""

def generate_pcb ():

   nbr_digital_input = 128
   nbr_analog_input = 128
   nbr_audio_input = 4
   nbr_digital_output = 128
   nbr_analog_output = 128
   nbr_audio_output = 4

   net_index = 3

   kicad_template_pcb = os.path.join (PATH_THIS, 'default_template.kicad_pcb')
   with open (kicad_template_pcb, 'r', encoding='utf-8') as file:
      content = file.read ()

   nets = ''

   for i in range (nbr_digital_input):
      nets += '  (net %d "Net-(DII%d-Pad1)")\n' % (net_index, (i + 1))
      net_index += 1

   for i in range (nbr_analog_input):
      nets += '  (net %d "Net-(ANI%d-Pad1)")\n' % (net_index, (i + 1))
      net_index += 1

   for i in range (nbr_audio_input):
      nets += '  (net %d "Net-(AUI%d-Pad1)")\n' % (net_index, (i + 1))
      net_index += 1

   for i in range (nbr_digital_output):
      nets += '  (net %d "Net-(DIO%d-Pad1)")\n' % (net_index, (i + 1))
      net_index += 1

   for i in range (nbr_analog_output):
      nets += '  (net %d "Net-(ANO%d-Pad1)")\n' % (net_index, (i + 1))
      net_index += 1

   for i in range (nbr_audio_output):
      nets += '  (net %d "Net-(AUO%d-Pad1)")\n' % (net_index, (i + 1))
      net_index += 1

   content = content.replace ('  %nets%\n', nets)

   kicad_pcb = os.path.join (PATH_THIS, 'default.kicad_pcb')
   with open (kicad_pcb, 'w', encoding='utf-8') as file:
      file.write (content)



"""
==============================================================================
Name : generate
==============================================================================
"""

def generate ():
   generate_definition ()
   generate_pcb ()



##############################################################################

if __name__ == '__main__':
   sys.exit (generate ())
