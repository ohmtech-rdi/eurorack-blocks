##############################################################################
#
#     diy-manual.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'generators': [
      { 'id': 'front_panel/dxf' },
      { 'id': 'front_panel/pdf' },
      { 'id': 'front_pcb/kicad_pcb' },
      {
         'id': 'front_pcb/bom',
         'args': {
            'line_format': '{references};{Description};{Remarks};{quantity};{Dist};{DistPartNumber};{DistLink}\n',
            'header_map': {
               'references': 'References',
               'Description': 'Description',
               'Remarks': 'Remarks',
               'Dist': 'Distributor',
               'DistPartNumber': 'Distributor Part Number',
               'DistLink': 'Distributor Part URL',
               'quantity': 'Quantity'
            },
            'include_non_empty': '{Dist}',
            'projection': '{DistPartNumber};{Description}',
         }
      }
   ],
   'controls': {
      'AudioIn': [
         { 'styles': { 'thonk.pj398sm.knurled' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.knurled'] },
         { 'styles': { 'thonk.pj398sm.hex' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.hex'] },
      ],
      'AudioOut': [
         { 'styles': { 'thonk.pj398sm.knurled' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.knurled'] },
         { 'styles': { 'thonk.pj398sm.hex' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.hex'] },
      ],
      'Button' : [
         { 'styles': { 'tl1105' }, 'parts': ['tl1105.manual', '1rblk'] },
         { 'styles': { 'ck.d6r.black' }, 'parts': ['ck.d6r.black.manual'] },
      ],
      'CvIn': [
         { 'styles': { 'thonk.pj398sm.knurled' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.knurled'] },
         { 'styles': { 'thonk.pj398sm.hex' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.hex'] },
      ],
      'CvOut': [
         { 'styles': { 'thonk.pj398sm.knurled' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.knurled'] },
         { 'styles': { 'thonk.pj398sm.hex' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.hex'] },
      ],
      'GateIn': [
         { 'styles': { 'thonk.pj398sm.knurled' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.knurled'] },
         { 'styles': { 'thonk.pj398sm.hex' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.hex'] },
      ],
      'GateOut': [
         { 'styles': { 'thonk.pj398sm.knurled' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.knurled'] },
         { 'styles': { 'thonk.pj398sm.hex' }, 'parts': ['thonk.pj398sm.manual', 'thonk.pj398sm.hex'] },
      ],
      'Led': [
         { 'styles': { 'led.3mm.red' }, 'parts': ['led.3mm.red.manual'] },
         { 'styles': { 'led.3mm.green' }, 'parts': ['led.3mm.green.manual'] },
         { 'styles': { 'led.3mm.yellow' }, 'parts': ['led.3mm.yellow.manual'] },
         { 'styles': { 'led.3mm.orange' }, 'parts': ['led.3mm.orange.manual'] },
      ],
      'LedBi': [
         { 'styles': { 'led.3mm.green_red' }, 'parts': ['led.3mm.bi.green_red.manual'] },
      ],
      'LedRgb': [
         { 'styles': { 'led.3mm.rgb' }, 'parts': ['led.3mm.rgb.manual'] },
      ],
      'Pot': [
         { 'styles': { 'rogan.2ps' }, 'parts': ['alpha.9mm.manual', 'rogan.2ps'] },
         { 'styles': { 'rogan.3ps' }, 'parts': ['alpha.9mm.manual', 'rogan.3ps'] },
         { 'styles': { 'rogan.1ps' }, 'parts': ['alpha.9mm.manual', 'rogan.1ps'] },
         { 'styles': { 'rogan.6ps' }, 'parts': ['alpha.9mm.manual', 'rogan.6ps'] },
         { 'styles': { 'rogan.5ps' }, 'parts': ['alpha.9mm.manual', 'rogan.5ps'] },
         { 'styles': { 'sifam.drn111.white' }, 'parts': ['alpha.9mm.manual', 'sifam.drn111.white'] },
         { 'styles': { 'sifam.dbn151.white' }, 'parts': ['alpha.9mm.manual', 'sifam.dbn151.white'] },
      ],
      'Switch': [
         { 'styles': { 'dailywell.2ms1' }, 'parts': ['dailywell.2ms1.manual'] },
         { 'styles': { 'dailywell.2ms3' }, 'parts': ['dailywell.2ms3.manual'] },
      ],
      'Trim': [
         { 'styles': { 'songhuei.9mm' }, 'parts': ['songhuei.9mm.manual'] },
      ],
   },
}
