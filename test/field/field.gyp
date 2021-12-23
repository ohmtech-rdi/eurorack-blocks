##############################################################################
#
#     field.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
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

         'dependencies': [ 'field', 'erb-daisy' ],
      },

      {
         'target_name': 'field-vcvrack',

         'dependencies': [ 'field', 'erb-vcvrack' ],
      },
   ],
}
