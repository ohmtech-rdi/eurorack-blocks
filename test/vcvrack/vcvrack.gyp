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

         'sources': [
            'VcvRack.cpp',
            'VcvRack.h',
            'VcvRack.erbui',
         ],

         'includes': [
            '../../include/erb/erb-vcvrack.gypi',
         ],
      },
   ],
}
