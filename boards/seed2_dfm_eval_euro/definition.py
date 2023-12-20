##############################################################################
#
#     definition.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'class': 'erb::BoardSeed2DfmEvalEuro',
   'include': 'BoardSeed2DfmEvalEuro.h',
   'pins': {
      'CI1': {
         'accept': ['CvIn'],
         'bind': 'adc(0)',
      },
      'CI2': {
         'accept': ['CvIn'],
         'bind': 'adc(1)',
      },
      'CI3': {
         'accept': ['CvIn'],
         'bind': 'adc(2)',
      },

      'CO1': {
         'accept': ['CvOut'],
         'bind': 'dac(0)',
      },

      'CO2': {
         'accept': ['CvOut'],
         'bind': 'dac(1)',
      },

      'GI1': {
         'accept': ['GateIn'],
         'bind': 'gpi(0)',
      },

      'P1': {
         'accept': ['Pot'],
         'bind': 'adc(3)',
      },
      'P2': {
         'accept': ['Pot'],
         'bind': 'adc(4)',
      },
      'P3': {
         'accept': ['Pot'],
         'bind': 'adc(5)',
      },
      'P4': {
         'accept': ['Pot'],
         'bind': 'adc(6)',
      },

      'B1': {
         'accept': ['Button'],
         'bind': 'gpi(1)',
      },

      'B2': {
         'accept': ['Switch'],
         'bind': 'gpi(2)',
      },
      'B3': {
         'accept': ['Switch'],
         'bind': 'gpi(3)',
      },

      'B4': {
         'accept': ['EncoderButton'],
         'bind': 'gpi(4)',
      },
      'B5': {
         'accept': ['EncoderButton'],
         'bind': 'gpi(5)',
      },
      'B6': {
         'accept': ['EncoderButton'],
         'bind': 'gpi(6)',
      },

      'AI1': {
         'accept': ['AudioIn'],
         'bind': 'audioin(0)',
      },
      'AI2': {
         'accept': ['AudioIn'],
         'bind': 'audioin(1)',
      },
      'AI3': {
         'accept': ['AudioIn'],
         'bind': 'audioin(2)',
      },
      'AI4': {
         'accept': ['AudioIn'],
         'bind': 'audioin(3)',
      },

      'AO1': {
         'accept': ['AudioOut'],
         'bind': 'audioout(0)',
      },
      'AO2': {
         'accept': ['AudioOut'],
         'bind': 'audioout(1)',
      },
      'AO3': {
         'accept': ['AudioOut'],
         'bind': 'audioout(2)',
      },
      'AO4': {
         'accept': ['AudioOut'],
         'bind': 'audioout(3)',
      },

      'OLED1': {
         'accept': ['Display'],
         'bind': 'oled()',
      },
   }
}
