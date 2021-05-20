##############################################################################
#
#     field.gyp
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
         'target_name': 'field',
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'Field.cpp',
               'Field.h',
               'Field.erbui',
            ],

            'include_dirs': [
               '..',
            ],
         },
      },

      {
         'target_name': 'field-daisy',
         'type': 'executable',

         'dependencies': [ 'field', 'erb-daisy' ],
      },

      {
         'target_name': 'field-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'field', 'erb-vcvrack' ],
      },
   ],
}
