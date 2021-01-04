##############################################################################
#
#     test.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'includes': [
      '../../eurorack-blocks.gypi',
   ],

   'targets' : [
      {
         'target_name': 'test',
         'type': 'executable',

         'dependencies': [ 'erb' ],

         'sources': [
            'main.cpp',
         ],
      },
   ],
}
