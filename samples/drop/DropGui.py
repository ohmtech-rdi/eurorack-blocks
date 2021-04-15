##############################################################################
#
#     DropGui.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'modules': [
      {
         'name': 'Drop',
         'width': '10hp',
         'material': { 'name': 'aluminum' },
         'header': {
            'labels': [{ 'text': 'DROP' }],
         },
         #'footer': {
         #   'labels': [{ 'text': 'Erb' }],
         #},

         'lines': [
            [{ 'x': '43.4mm', 'y': '83.7mm' }, { 'x': '43.4mm', 'y': '88.1mm' }],
            [{ 'x': '7.11mm', 'y': '80.7mm' }, { 'x': '7.11mm', 'y': '82.6mm' }],
            [{ 'x': '19.2mm', 'y': '80.7mm' }, { 'x': '19.2mm', 'y': '82.6mm' }],
         ],

         'controls': [
            {
               'type': 'Pot',
               'property': 'freq_pot',
               'position': { 'x': '25.3mm', 'y': '34mm' },
               'style': 'rogan.6ps',
               'labels': [{ 'text': 'FREQ', 'positioning': 'bottom' }],
            },
            {
               'type': 'Switch',
               'property': 'mute_hp',
               'position': { 'x': '25.3mm', 'y': '62mm' },
               'style': 'dailywell.2ms1',
               'rotation': '90°CCW',
               'labels': [
                  { 'text': 'MUTE', 'positioning': 'left' },
                  { 'text': 'HP', 'positioning': 'right' },
               ],
            },
            {
               'type': 'Trim',
               'property': 'freq_trim',
               'position': { 'x': '43.4mm', 'y': '75.3mm' },
               'style': 'songhuei.9mm',
               'labels': [{ 'text': '–/+', 'positioning': 'bottom' }],
            },
            {
               'type': 'Button',
               'property': 'sync_button',
               'position': { 'x': '7.11mm', 'y': '75.3mm' },
               'style': 'ck.d6.black',
            },
            {
               'type': 'Button',
               'property': 'arm_button',
               'position': { 'x': '19.2mm', 'y': '75.3mm' },
               'style': 'ck.d6.black',
            },
            {
               'type': 'Led',
               'property': 'sync_led',
               'position': { 'x': '7.11mm', 'y': '85mm' },
               'style': 'led.3mm.red',
            },
            {
               'type': 'GateIn',
               'property': 'sync_gate',
               'position': { 'x': '7.11mm', 'y': '96.5mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'SYNC', 'positioning': 'top' }],
            },
            {
               'type': 'Led',
               'property': 'arm_led',
               'position': { 'x': '19.2mm', 'y': '85mm' },
               'style': 'led.3mm.red',
            },
            {
               'type': 'GateIn',
               'property': 'arm_gate',
               'position': { 'x': '19.2mm', 'y': '96.5mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'ARM', 'positioning': 'top' }],
            },
            {
               'type': 'LedBi',
               'property': 'state_led',
               'position': { 'x': '31.3mm', 'y': '85mm' },
               'style': 'led.3mm.green_red',
            },
            {
               'type': 'GateOut',
               'property': 'state_gate',
               'position': { 'x': '31.3mm', 'y': '96.5mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'STATE', 'positioning': 'top' }],
            },
            {
               'type': 'CvIn',
               'property': 'freq_cv',
               'position': { 'x': '43.4mm', 'y': '96.5mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'FREQ', 'positioning': 'top' }],
            },
            {
               'type': 'AudioInDaisy',
               'property': 'audio_in_left',
               'position': { 'x': '7.11mm', 'y': '111mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'IN L', 'positioning': 'top' }],
            },
            {
               'type': 'AudioInDaisy',
               'property': 'audio_in_right',
               'position': { 'x': '19.2mm', 'y': '111mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'IN R', 'positioning': 'top' }],
            },
            {
               'type': 'AudioOutDaisy',
               'property': 'audio_out_left',
               'position': { 'x': '31.3mm', 'y': '111mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'OUT L', 'positioning': 'top' }],
            },
            {
               'type': 'AudioOutDaisy',
               'property': 'audio_out_right',
               'position': { 'x': '43.4mm', 'y': '111mm' },
               'style': 'thonk.pj398sm.knurled',
               'labels': [{ 'text': 'OUT R', 'positioning': 'top' }],
            },
         ]
      },
   ],
}
