##############################################################################
#
#     micropatch.gyp
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
         'target_name': 'micropatch',
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'Micropatch.cpp',
               'Micropatch.h',
               'Micropatch.erbui',
            ],

            'include_dirs': [
               '..',
            ],
         },
      },

      {
         'target_name': 'micropatch-daisy',
         'type': 'executable',

         'dependencies': [ 'micropatch', 'erb-daisy' ],
      },

      {
         'target_name': 'micropatch-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'micropatch', 'erb-vcvrack' ],
      },
   ],
}
