##############################################################################
#
#     kivu12.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'includes': [
      '../../eurorack-blocks.gypi',
   ],

   'targets' : [
      {
         'target_name': 'kivu12',
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'Kivu12.cpp',
               'Kivu12.h',
               'Kivu12.erbui',
            ],

            'include_dirs': [
               '..',
            ],
         },
      },

      {
         'target_name': 'kivu12-daisy',
         'type': 'executable',

         'dependencies': [ 'kivu12', 'erb-daisy' ],
      },

      {
         'target_name': 'kivu12-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'kivu12', 'erb-vcvrack' ],
      },
   ],
}
