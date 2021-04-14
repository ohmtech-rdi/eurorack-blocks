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
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'DropDsp.cpp',
               'DropDsp.h',
               'DropGui.py',
               'DropGui.erbui',
               'DropModule.cpp',
               'DropModule.h',
            ],
         },
      },

      {
         'target_name': 'drop-daisy',
         'type': 'executable',

         'dependencies': [ 'drop', 'erb-daisy' ],

         'sources': [
            'main.cpp',
         ],
      },

      {
         'target_name': 'drop-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'drop', 'erb-vcvrack' ],
      },
   ],
}
