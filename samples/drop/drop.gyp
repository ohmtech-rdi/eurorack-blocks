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
         'target_name': 'drop',
         'type': 'executable',

         'dependencies': [ 'erb' ],

         'sources': [
            'main.cpp',

            'DropDsp.cpp',
            'DropDsp.h',
            'DropModule.cpp',
            'DropModule.h',
         ],
      },

      {
         'target_name': 'test',
         'type': 'executable',

         'sources': [
            'test.cpp',

            'DropDsp.cpp',
            'DropDsp.h',
         ],
      },
   ],
}
