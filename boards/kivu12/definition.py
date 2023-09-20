##############################################################################
#
#     definition.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'class': 'erb::BoardKivu12',
   'include': 'BoardKivu12.h',
   'pcb': 'hardware/kivu12.kicad_pcb',
   'sch': 'hardware/kivu12.kicad_sch',
   'width': 12, # hp
   'pins': {

      #--- Bottom Header

      'CI1': {
         'accept': ['CvIn'],
         'bind': 'ci(0)',
         'header': 'ZZ2',
      },
      'CI2': {
         'accept': ['CvIn'],
         'bind': 'ci(1)',
         'header': 'ZZ2',
      },
      'CI3': {
         'accept': ['CvIn'],
         'bind': 'ci(2)',
         'header': 'ZZ2',
      },
      'CI4': {
         'accept': ['CvIn'],
         'bind': 'ci(3)',
         'header': 'ZZ2',
      },
      'CI5': {
         'accept': ['CvIn'],
         'bind': 'ci(4)',
         'header': 'ZZ2',
      },
      'CI6': {
         'accept': ['CvIn'],
         'bind': 'ci(5)',
         'header': 'ZZ2',
      },
      'CI7': {
         'accept': ['CvIn'],
         'bind': 'ci(6)',
         'header': 'ZZ2',
      },
      'CI8': {
         'accept': ['CvIn'],
         'bind': 'ci(7)',
         'header': 'ZZ2',
      },
      'CO1': {
         'accept': ['CvOut'],
         'bind': 'co(0)',
         'header': 'ZZ5',
      },
      'CO2': {
         'accept': ['CvOut'],
         'bind': 'co(1)',
         'header': 'ZZ5',
      },
      'GO1': {
         'accept': ['GateOut'],
         'bind': 'go(0)',
         'header': 'ZZ5',
      },
      'GO2': {
         'accept': ['GateOut'],
         'bind': 'go(1)',
         'header': 'ZZ5',
      },
      'AI1': {
         'accept': ['AudioIn'],
         'bind': 'ai(0)',
         'header': 'ZZ5',
      },
      'AI2': {
         'accept': ['AudioIn'],
         'bind': 'ai(1)',
         'header': 'ZZ5',
      },
      'AO1': {
         'accept': ['AudioOut'],
         'bind': 'ao(0)',
         'header': 'ZZ5',
      },
      'AO2': {
         'accept': ['AudioOut'],
         'bind': 'ao(1)',
         'header': 'ZZ5',
      },

      #--- Top Header

      'L1': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(0)',
         'header': 'ZZ4',
      },
      'L2': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(1)',
         'header': 'ZZ4',
      },
      'L3': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(2)',
         'header': 'ZZ4',
      },
      'L4': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(3)',
         'header': 'ZZ4',
      },
      'L5': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(4)',
         'header': 'ZZ4',
      },
      'L6': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(5)',
         'header': 'ZZ4',
      },
      'L7': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(6)',
         'header': 'ZZ4',
      },
      'L8': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(7)',
         'header': 'ZZ4',
      },
      'L9': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(8)',
         'header': 'ZZ12',
      },
      'L10': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(9)',
         'header': 'ZZ12',
      },
      'L11': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(10)',
         'header': 'ZZ12',
      },
      'L12': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(11)',
         'header': 'ZZ12',
      },
      'L13': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(12)',
         'header': 'ZZ12',
      },
      'L14': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(13)',
         'header': 'ZZ12',
      },
      'L15': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(14)',
         'header': 'ZZ12',
      },
      'L16': {
         'type': 'pwm',
         'accept': ['Led', 'LedBi', 'LedRgb'],
         'bind': 'l(15)',
         'header': 'ZZ12',
      },

      #--- Left Header

      'P1': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(0)',
         'header': 'ZZ1',
      },
      'P2': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(1)',
         'header': 'ZZ1',
      },
      'P3': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(2)',
         'header': 'ZZ1',
      },
      'P4': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(3)',
         'header': 'ZZ1',
      },
      'P5': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(4)',
         'header': 'ZZ1',
      },
      'P6': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(5)',
         'header': 'ZZ1',
      },
      'P7': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(6)',
         'header': 'ZZ1',
      },
      'P8': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(7)',
         'header': 'ZZ1',
      },
      'P9': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(8)',
         'header': 'ZZ1',
      },
      'P10': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(9)',
         'header': 'ZZ1',
      },
      'P11': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(10)',
         'header': 'ZZ1',
      },
      'P12': {
         'accept': ['Pot', 'Trim'],
         'bind': 'p(11)',
         'header': 'ZZ1',
      },

      #--- Right Header

      'B1': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(0)',
         'header': 'ZZ3',
      },
      'B2': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(1)',
         'header': 'ZZ3',
      },
      'B3': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(2)',
         'header': 'ZZ3',
      },
      'B4': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(3)',
         'header': 'ZZ3',
      },
      'B5': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(4)',
         'header': 'ZZ3',
      },
      'B6': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(5)',
         'header': 'ZZ3',
      },
      'B7': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(6)',
         'header': 'ZZ3',
      },
      'B8': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(7)',
         'header': 'ZZ3',
      },
      'B9': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(8)',
         'header': 'ZZ7',
      },
      'B10': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(9)',
         'header': 'ZZ7',
      },
      'B11': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(10)',
         'header': 'ZZ7',
      },
      'B12': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(11)',
         'header': 'ZZ7',
      },
      'B13': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(12)',
         'header': 'ZZ7',
      },
      'B14': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(13)',
         'header': 'ZZ7',
      },
      'B15': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(14)',
         'header': 'ZZ7',
      },
      'B16': {
         'accept': ['Button', 'Encoder', 'GateIn', 'Switch'],
         'bind': 'b(15)',
         'header': 'ZZ7',
      },
   },
   'kinds': {
      'CvIn': {'pools': ['CI']},
      'CvOut': {'pools': ['CO']},
      'GateOut': {'pools': ['GO']},
      'AudioIn': {'pools': ['AI']},
      'AudioOut': {'pools': ['AO']},
      'Led': {'pools': ['L']},
      'LedBi': {'pools': ['L', 'L']},
      'LedRgb': {'pools': ['L', 'L', 'L']},
      'Pot': {'pools': ['P']},
      'Trim': {'pools': ['P']},
      'Button': {'pools': ['B']},
      'Encoder': {'pools': ['B', 'B']},
      'GateIn': {'pools': ['B']},
      'Switch': {'pools': ['B', 'B']},
   },
   'pools': {
      'CI': ['CI1', 'CI2', 'CI3', 'CI4', 'CI5', 'CI6', 'CI7', 'CI8'],
      'CO': ['CO1', 'CO2'],
      'GO': ['GO1', 'GO2'],
      'AI': ['AI1', 'AI2'],
      'AO': ['AO1', 'AO2'],
      'L': ['L1', 'L2', 'L3', 'L4', 'L5', 'L6', 'L7', 'L8', 'L9', 'L10', 'L11', 'L12', 'L13', 'L14', 'L15', 'L16'],
      'P': ['P1', 'P2', 'P3', 'P4', 'P5', 'P6', 'P7', 'P8', 'P9', 'P10', 'P11', 'P12'],
      'B': ['B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7', 'B8', 'B9', 'B10', 'B11', 'B12', 'B13', 'B14', 'B15', 'B16'],
   },
   'headers': [
      'ZZ1', 'ZZ2', 'ZZ3', 'ZZ4', 'ZZ5', 'ZZ7', 'ZZ12',
   ],
}
