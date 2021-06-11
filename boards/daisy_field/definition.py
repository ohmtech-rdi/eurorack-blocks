##############################################################################
#
#     definition.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'class': 'BoardDaisyField',
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

      'CO1': {
         'accept': ['CvOut'],
         'bind': 'dac(0)',
      },
      'CO2': {
         'accept': ['CvOut'],
         'bind': 'dac(1)',
      },

      'GI': {
         'accept': ['GateIn'],
         'bind': 'gpi(0)',
      },

      'GO': {
         'accept': ['GateOut'],
         'bind': 'gpo(0)',
      },

      'L1': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(2)',
      },
      'L2': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(3)',
      },
      'L3': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(4)',
      },
      'L4': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(5)',
      },
      'L5': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(6)',
      },
      'L6': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(7)',
      },
      'L7': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(8)',
      },
      'L8': {
         'type': 'pwm',
         'accept': ['Led'],
         'bind': 'dac(9)',
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
      'P5': {
         'accept': ['Pot'],
         'bind': 'adc(8)',
      },
      'P6': {
         'accept': ['Pot'],
         'bind': 'adc(9)',
      },
      'P7': {
         'accept': ['Pot'],
         'bind': 'adc(10)',
      },
      'P8': {
         'accept': ['Pot'],
         'bind': 'adc(11)',
      },

      'B1': {
         'accept': ['Button'],
         'bind': 'gpi(1)',
      },
      'B2': {
         'accept': ['Button'],
         'bind': 'gpi(2)',
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
