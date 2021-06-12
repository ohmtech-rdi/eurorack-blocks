##############################################################################
#
#     definition.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'class': 'BoardKivu12',
   'pins': {

      #--- Bottom Header

      'CI1': {
         'accept': ['CvIn'],
         'bind': 'ci(0)',
      },
      'CI2': {
         'accept': ['CvIn'],
         'bind': 'ci(1)',
      },
      'CI3': {
         'accept': ['CvIn'],
         'bind': 'ci(2)',
      },
      'CI4': {
         'accept': ['CvIn'],
         'bind': 'ci(3)',
      },
      'CI5': {
         'accept': ['CvIn'],
         'bind': 'ci(4)',
      },
      'CI6': {
         'accept': ['CvIn'],
         'bind': 'ci(5)',
      },
      'CI7': {
         'accept': ['CvIn'],
         'bind': 'ci(6)',
      },
      'CI8': {
         'accept': ['CvIn'],
         'bind': 'ci(7)',
      },
      'CO1': {
         'accept': ['CvOut'],
         'bind': 'co(0)',
      },
      'CO2': {
         'accept': ['CvOut'],
         'bind': 'co(1)',
      },
      'GO1': {
         'accept': ['GateOut'],
         'bind': 'go(0)',
      },
      'GO2': {
         'accept': ['GateOut'],
         'bind': 'go(1)',
      },
      'AI1': {
         'accept': ['AudioIn'],
         'bind': 'ai(0)',
      },
      'AI2': {
         'accept': ['AudioIn'],
         'bind': 'ai(1)',
      },
      'AO1': {
         'accept': ['AudioOut'],
         'bind': 'ao(0)',
      },
      'AO2': {
         'accept': ['AudioOut'],
         'bind': 'ao(1)',
      },

      #--- Top Header

      'L1': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(0)',
      },
      'L2': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(1)',
      },
      'L3': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(2)',
      },
      'L4': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(3)',
      },
      'L5': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(4)',
      },
      'L6': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(5)',
      },
      'L7': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(6)',
      },
      'L8': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(7)',
      },
      'L9': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(8)',
      },
      'L10': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(9)',
      },
      'L11': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(10)',
      },
      'L12': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(11)',
      },
      'L13': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(12)',
      },
      'L14': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(13)',
      },
      'L15': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(14)',
      },
      'L16': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(15)',
      },
      'L17': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(16)',
      },
      'L18': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(17)',
      },
      'L19': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(18)',
      },
      'L20': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(19)',
      },

      #--- Left Header

      'P1': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(0)',
      },
      'P2': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(1)',
      },
      'P3': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(2)',
      },
      'P4': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(3)',
      },
      'P5': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(4)',
      },
      'P6': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(5)',
      },
      'P7': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(6)',
      },
      'P8': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(7)',
      },
      'P9': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(8)',
      },
      'P10': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(9)',
      },
      'P11': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(10)',
      },
      'P12': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(11)',
      },

      #--- Right Header

      'B1': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(0)',
      },
      'B2': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(1)',
      },
      'B3': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(2)',
      },
      'B4': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(3)',
      },
      'B5': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(4)',
      },
      'B6': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(5)',
      },
      'B7': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(6)',
      },
      'B8': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(7)',
      },
      'B9': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(8)',
      },
      'B10': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(9)',
      },
      'B11': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(10)',
      },
      'B12': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(11)',
      },
      'B13': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(12)',
      },
      'B14': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(13)',
      },
      'B15': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(14)',
      },
      'B16': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'b(15)',
      },
   }
}
