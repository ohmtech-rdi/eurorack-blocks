##############################################################################
#
#     drop.gyp
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
         'target_name': 'drop-daisy',
         'type': 'executable',

         'dependencies': [ 'erb-daisy' ],

         'sources': [
            'main.cpp',

            'DropDsp.cpp',
            'DropDsp.h',
            'DropModule.cpp',
            'DropModule.h',
         ],
      },

      {
         'target_name': 'drop-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'erb-vcvrack' ],

         'sources': [
            'DropPluginVcv.cpp',

            'DropDsp.cpp',
            'DropDsp.h',
            'DropModule.cpp',
            'DropModule.h',
         ],

         'copies': [
            {
               'destination': '<(PRODUCT_DIR)/res',
               'files': [
                  'DropGuiVcv.svg',
               ],
            },
         ],
      },
   ],
}
