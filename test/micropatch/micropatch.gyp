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

   'conditions': [
      ['OS=="daisy"', {
         'targets' : [
            {
               'target_name': 'micropatch',

               'includes': [
                  'micropatch-src.gypi',
                  '../../include/erb/erb-daisy.gypi',
               ],
            },
         ],
      },{
         'targets' : [
            {
               'target_name': 'micropatch',

               'includes': [
                  'micropatch-src.gypi',
                  '../../include/erb/erb-vcvrack.gypi',
               ],
            },
         ],
      }],
   ],
}
