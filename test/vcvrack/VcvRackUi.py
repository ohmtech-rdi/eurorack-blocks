##############################################################################
#
#     VcvRackUi.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'modules': [
      {
         'name': 'VcvRack',
         'width': '24hp', # 121.92mm
         'material': { 'name': 'aluminum' },
         'header': {
            'labels': [{ 'text': 'VCVRACK TEST' }],
         },
         'footer': {
            'labels': [{ 'text': 'Erb Tests' }],
         },

         'lines': [
            [{ 'x': '0mm', 'y': '0mm' }, { 'x': '12hp', 'y': '10mm' }],

            [{ 'x': '0mm', 'y': '20mm' }, { 'x': '20mm', 'y': '20mm' }],
            [{ 'x': '10mm', 'y': '10mm' }, { 'x': '10mm', 'y': '30mm' }],
         ],

         'controls': [
            {
               'type': 'AudioInDaisy',
               'property': 'audio_in',
               'position': { 'x': '10mm', 'y': '20mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'AudioInDaisy',
               'property': 'audio_in2',
               'position': { 'x': '30mm', 'y': '20mm' },
               'style': 'thonk.pj398sm.hex',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'AudioOutDaisy',
               'property': 'audio_out',
               'position': { 'x': '50mm', 'y': '20mm' },
               'style': 'thonk.pj398sm.hex',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'Button',
               'property': 'button',
               'position': { 'x': '70mm', 'y': '20mm' },
               'style': 'tl1105',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'CvIn',
               'property': 'cv_in',
               'position': { 'x': '90mm', 'y': '20mm' },
               'style': 'thonk.pj398sm.hex',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'GateIn',
               'property': 'gate_in',
               'position': { 'x': '110mm', 'y': '20mm' },
               'style': 'thonk.pj398sm.hex',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'GateOut',
               'property': 'gate_out',
               'position': { 'x': '10mm', 'y': '40mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'Led',
               'property': 'led',
               'position': { 'x': '30mm', 'y': '40mm' },
               'style': 'led.3mm.red',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'LedBi',
               'property': 'led_bi',
               'position': { 'x': '50mm', 'y': '40mm' },
               'style': 'led.3mm.green_red',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'Pot',
               'property': 'pot',
               'position': { 'x': '70mm', 'y': '40mm' },
               'style': 'rogan.1ps',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'Switch',
               'property': 'switch_',
               'position': { 'x': '90mm', 'y': '40mm' },
               'style': 'dailywell.2ms1',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'Trim',
               'property': 'trim',
               'position': { 'x': '110mm', 'y': '40mm' },
               'style': 'songhuei.9mm',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': 'B', 'positioning': 'bottom' }
               ],
            },

            {
               'type': 'Pot',
               'property': 'rogan_6ps',
               'position': { 'x': '20mm', 'y': '65mm' },
               'style': 'rogan.6ps',
               'labels': [{ 'text': 'rogan.6ps', 'positioning': 'bottom' }],
            },
            {
               'type': 'Pot',
               'property': 'rogan_5ps',
               'position': { 'x': '50mm', 'y': '65mm' },
               'style': 'rogan.5ps',
               'labels': [{ 'text': 'rogan.5ps', 'positioning': 'bottom' }],
            },
            {
               'type': 'Pot',
               'property': 'rogan_3ps',
               'position': { 'x': '73mm', 'y': '65mm' },
               'style': 'rogan.3ps',
               'labels': [{ 'text': 'rogan.3ps', 'positioning': 'bottom' }],
            },
            {
               'type': 'Pot',
               'property': 'rogan_2ps',
               'position': { 'x': '93mm', 'y': '65mm' },
               'style': 'rogan.2ps',
               'labels': [{ 'text': 'rogan.2ps', 'positioning': 'bottom' }],
            },
            {
               'type': 'Pot',
               'property': 'rogan_1ps',
               'position': { 'x': '110mm', 'y': '65mm' },
               'style': 'rogan.1ps',
               'labels': [{ 'text': 'rogan.1ps', 'positioning': 'bottom' }],
            },

            {
               'type': 'Switch',
               'property': 'dailywell_2ms1',
               'position': { 'x': '10mm', 'y': '90mm' },
               'style': 'dailywell.2ms1',
               'labels': [{ 'text': 'dailywell.2ms1', 'positioning': 'bottom' }],
            },
            {
               'type': 'Switch',
               'property': 'dailywell_2ms3',
               'position': { 'x': '30mm', 'y': '90mm' },
               'style': 'dailywell.2ms3',
               'labels': [{ 'text': 'dailywell.2ms3', 'positioning': 'bottom' }],
            },

            {
               'type': 'Led',
               'property': 'led_3mm_red',
               'position': { 'x': '52mm', 'y': '85mm' },
               'style': 'led.3mm.red',
               'labels': [{ 'text': 'led.3mm.red', 'positioning': 'bottom' }],
            },
            {
               'type': 'Led',
               'property': 'led_3mm_green',
               'position': { 'x': '79mm', 'y': '85mm' },
               'style': 'led.3mm.green',
               'labels': [{ 'text': 'led.3mm.green', 'positioning': 'bottom' }],
            },
            {
               'type': 'Led',
               'property': 'led_3mm_yellow',
               'position': { 'x': '52mm', 'y': '95mm' },
               'style': 'led.3mm.yellow',
               'labels': [{ 'text': 'led.3mm.yellow', 'positioning': 'bottom' }],
            },
            {
               'type': 'LedBi',
               'property': 'led_3mm_green_red',
               'position': { 'x': '79mm', 'y': '95mm' },
               'style': 'led.3mm.green_red',
               'labels': [{ 'text': 'led.3mm.green_red', 'positioning': 'bottom' }],
            },

            {
               'type': 'Button',
               'property': 'tl1105',
               'position': { 'x': '95mm', 'y': '85mm' },
               'style': 'tl1105',
               'labels': [{ 'text': 'tl1105', 'positioning': 'bottom' }],
            },
            {
               'type': 'Button',
               'property': 'ck_d6_black',
               'position': { 'x': '110mm', 'y': '85mm' },
               'style': 'ck.d6.black',
               'labels': [{ 'text': 'ck.d6.black', 'positioning': 'bottom' }],
            },

            {
               'type': 'Switch',
               'property': 'dailywell_2ms1_90ccw',
               'position': { 'x': '10mm', 'y': '110mm' },
               'style': 'dailywell.2ms1',
               'rotation': '90°CCW',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': '90CCW', 'positioning': 'bottom' }
               ],
            },
            {
               'type': 'Switch',
               'property': 'dailywell_2ms1_m90cw',
               'position': { 'x': '30mm', 'y': '110mm' },
               'style': 'dailywell.2ms1',
               'rotation': '90°CW',
               'labels': [
                  { 'text': 'L', 'positioning': 'left' },
                  { 'text': 'T', 'positioning': 'top' },
                  { 'text': 'R', 'positioning': 'right' },
                  { 'text': '90CW', 'positioning': 'bottom' }
               ],
            },

            {
               'type': 'CvIn',
               'property': 'thonk_pj398sm_knurled',
               'position': { 'x': '55mm', 'y': '110mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'thonk.pj398sm.knurled', 'positioning': 'bottom' }],
            },
            {
               'type': 'CvIn',
               'property': 'thonk_pj398sm_hex',
               'position': { 'x': '85mm', 'y': '110mm' },
               'style': 'thonk.pj398sm.hex',
               'labels': [{ 'text': 'thonk.pj398sm.hex', 'positioning': 'bottom' }],
            },
         ]
      },
   ],
}
