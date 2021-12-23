##############################################################################
#
#     vcvrack.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'includes': [
      '../../eurorack-blocks.gypi',
   ],

   'targets' : [
      {
         'target_name': 'vcvrack',

         'dependencies': [ 'erb-vcvrack' ],

         'sources': [
            'VcvRack.cpp',
            'VcvRack.h',
            'VcvRack.erbui',
         ],
      },
   ],
}
