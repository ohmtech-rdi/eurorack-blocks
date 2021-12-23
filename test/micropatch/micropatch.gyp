##############################################################################
#
#     micropatch.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
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

         'dependencies': [ 'micropatch', 'erb-daisy' ],
      },

      {
         'target_name': 'micropatch-vcvrack',

         'dependencies': [ 'micropatch', 'erb-vcvrack' ],
      },
   ],
}
