##############################################################################
#
#     test.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'variables': {
      'erbb_flash_lds': '../../../../../submodules/libDaisy/core/STM32H750IB_flash.lds',
   },

   'includes': [
      '../../eurorack-blocks.gypi',
   ],

   'conditions': [
      ['OS=="daisy"', {
         'targets' : [
            {
               'target_name': 'audio-in-daisy',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'audio-in-daisy.cpp' ],
            },

            {
               'target_name': 'audio-out-daisy',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'audio-out-daisy.cpp' ],
            },

            {
               'target_name': 'button',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'button.cpp' ],
            },

            {
               'target_name': 'cv-in',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'cv-in.cpp' ],
            },

            {
               'target_name': 'cv-in2',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'cv-in2.cpp' ],
            },

            {
               'target_name': 'gate-in',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'gate-in.cpp' ],
            },

            {
               'target_name': 'gate-out',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'gate-out.cpp' ],
            },

            {
               'target_name': 'led-rgb',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'led-rgb.cpp' ],
            },

            {
               'target_name': 'led-bi',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'led-bi.cpp' ],
            },

            {
               'target_name': 'led',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'led.cpp' ],
            },

            {
               'target_name': 'pot',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'pot.cpp' ],
            },

            {
               'target_name': 'switch',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
               'sources': [ 'switch.cpp' ],
            },
         ],
      },{
         'targets' : [
            {
               'target_name': 'audio-in-daisy',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'audio-in-daisy.cpp' ],
            },

            {
               'target_name': 'audio-out-daisy',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'audio-out-daisy.cpp' ],
            },

            {
               'target_name': 'button',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'button.cpp' ],
            },

            {
               'target_name': 'cv-in',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'cv-in.cpp' ],
            },

            {
               'target_name': 'cv-in2',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'cv-in2.cpp' ],
            },

            {
               'target_name': 'gate-in',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'gate-in.cpp' ],
            },

            {
               'target_name': 'gate-out',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'gate-out.cpp' ],
            },

            {
               'target_name': 'led-rgb',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'led-rgb.cpp' ],
            },

            {
               'target_name': 'led-bi',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'led-bi.cpp' ],
            },

            {
               'target_name': 'led',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'led.cpp' ],
            },

            {
               'target_name': 'pot',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'pot.cpp' ],
            },

            {
               'target_name': 'switch',
               'type': 'executable',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
               'sources': [ 'switch.cpp' ],
            },
         ],
      }],
   ],
}
