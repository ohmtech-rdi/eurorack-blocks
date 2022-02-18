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
               'target_name': 'erb-daisy',
               'type': 'static_library',
               'includes': [ '../../include/erb/erb-daisy.gypi' ],
            },
            {
               'target_name': 'audio-in-daisy',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'audio-in-daisy.cpp' ],
            },

            {
               'target_name': 'audio-out-daisy',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'audio-out-daisy.cpp' ],
            },

            {
               'target_name': 'button',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'button.cpp' ],
            },

            {
               'target_name': 'cv-in',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'cv-in.cpp' ],
            },

            {
               'target_name': 'cv-in2',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'cv-in2.cpp' ],
            },

            {
               'target_name': 'gate-in',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'gate-in.cpp' ],
            },

            {
               'target_name': 'gate-out',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'gate-out.cpp' ],
            },

            {
               'target_name': 'led-rgb',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'led-rgb.cpp' ],
            },

            {
               'target_name': 'led-bi',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'led-bi.cpp' ],
            },

            {
               'target_name': 'led',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'led.cpp' ],
            },

            {
               'target_name': 'pot',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'pot.cpp' ],
            },

            {
               'target_name': 'switch',
               'type': 'executable',
               'dependencies': [ 'erb-daisy' ],
               'sources': [ 'switch.cpp' ],
            },
         ],
      },{
         'targets' : [
            {
               'target_name': 'erb-vcvrack',
               'type': 'static_library',
               'includes': [ '../../include/erb/erb-vcvrack.gypi' ],
            },
            {
               'target_name': 'audio-in-daisy',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'audio-in-daisy.cpp' ],
            },

            {
               'target_name': 'audio-out-daisy',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'audio-out-daisy.cpp' ],
            },

            {
               'target_name': 'button',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'button.cpp' ],
            },

            {
               'target_name': 'cv-in',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'cv-in.cpp' ],
            },

            {
               'target_name': 'cv-in2',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'cv-in2.cpp' ],
            },

            {
               'target_name': 'gate-in',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'gate-in.cpp' ],
            },

            {
               'target_name': 'gate-out',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'gate-out.cpp' ],
            },

            {
               'target_name': 'led-rgb',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'led-rgb.cpp' ],
            },

            {
               'target_name': 'led-bi',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'led-bi.cpp' ],
            },

            {
               'target_name': 'led',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'led.cpp' ],
            },

            {
               'target_name': 'pot',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'pot.cpp' ],
            },

            {
               'target_name': 'switch',
               'type': 'executable',
               'dependencies': [ 'erb-vcvrack' ],
               'sources': [ 'switch.cpp' ],
            },
         ],
      }],
   ],
}
