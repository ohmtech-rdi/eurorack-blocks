##############################################################################
#
#     bypass.gyp
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

   'targets' : [
      {
         'target_name': 'bypass',
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'Bypass.cpp',
               'Bypass.h',
               'Bypass.erbui',
            ],
         },
      },

      {
         'target_name': 'bypass-daisy',
         'type': 'executable',

         'dependencies': [ 'bypass', 'erb-daisy' ],

         'sources': [
            'main.cpp',
         ],
      },

      {
         'target_name': 'bypass-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'bypass', 'erb-vcvrack' ],

         'copies': [{
            'destination': '<(PRODUCT_DIR)/res',
            'files': [ 'artifacts/bypass.svg' ],
         }],
      },
   ],
}
