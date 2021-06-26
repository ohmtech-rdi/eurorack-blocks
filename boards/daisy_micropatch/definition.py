##############################################################################
#
#     definition.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'class': 'BoardDaisyMicropatch',
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
      'CI4': {
         'accept': ['CvIn'],
         'bind': 'adc(3)',
      },

      'CO': {
         'accept': ['CvOut'],
         'bind': 'dac(0)',
      },

      'GI1': {
         'accept': ['GateIn'],
         'bind': 'gpi(0)',
      },

      'GI2': {
         'accept': ['GateIn'],
         'bind': 'gpi(1)',
      },

      'GO1': {
         'accept': ['GateOut'],
         'bind': 'gpo(0)',
      },

      'GO2': {
         'accept': ['GateOut'],
         'bind': 'gpo(1)',
      },

      'L': {
         'type': 'dac',
         'accept': ['Led'],
         'bind': 'dac(1)',
      },

      'SD': {
         'type': 'sd',
         'accept': ['Sd'],
         'bind': 'sd()',
      },

      'P1': {
         'accept': ['Pot'],
         'bind': 'adc(4)',
      },
      'P2': {
         'accept': ['Pot'],
         'bind': 'adc(5)',
      },
      'P3': {
         'accept': ['Pot'],
         'bind': 'adc(6)',
      },
      'P4': {
         'accept': ['Pot'],
         'bind': 'adc(7)',
      },

      'B1': {
         'accept': ['Button'],
         'bind': 'gpi(2)',
      },

      'B2': {
         'accept': ['Switch'],
         'bind': 'gpi(3)',
      },
      'B3': {
         'accept': ['Switch'],
         'bind': 'gpi(4)',
      },

      'AI1': {
         'accept': ['AudioIn'],
         'bind': 'audioin(0)',
      },
      'AI2': {
         'accept': ['AudioIn'],
         'bind': 'audioin(1)',
      },

      'AO1': {
         'accept': ['AudioOut'],
         'bind': 'audioout(0)',
      },
      'AO2': {
         'accept': ['AudioOut'],
         'bind': 'audioout(1)',
      },
   }
}
