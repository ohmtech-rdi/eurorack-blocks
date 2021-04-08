##############################################################################
#
#     test.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'variables': {
      'erbb_flash_lds': '../../../../submodules/libDaisy/core/STM32H750IB_flash.lds',
   },

   'includes': [
      '../eurorack-blocks.gypi',
   ],

   'targets' : [
      {
         'target_name': 'audio-in-daisy',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'audio-in-daisy.cpp' ],
      },

      {
         'target_name': 'audio-out-daisy',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'audio-out-daisy.cpp' ],
      },

      {
         'target_name': 'button',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'button.cpp' ],
      },

      {
         'target_name': 'cv-in',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'cv-in.cpp' ],
      },

      {
         'target_name': 'cv-in2',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'cv-in2.cpp' ],
      },

      {
         'target_name': 'gate-in',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'gate-in.cpp' ],
      },

      {
         'target_name': 'gate-out',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'gate-out.cpp' ],
      },

      {
         'target_name': 'led-bi',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'led-bi.cpp' ],
      },

      {
         'target_name': 'led',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'led.cpp' ],
      },

      {
         'target_name': 'multiplexer',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'multiplexer.cpp' ],
      },

      {
         'target_name': 'pot',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'pot.cpp' ],
      },

      {
         'target_name': 'switch',
         'type': 'executable',
         'dependencies': [ 'erb' ],
         'sources': [ 'switch.cpp' ],
      },
   ],
}
