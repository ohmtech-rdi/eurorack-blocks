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

   'conditions': [
      ['OS=="daisy"', {
         'targets' : [
            {
               'target_name': 'kivu12',

               'includes': [
                  'kivu12-src.gypi',
                  '../../include/erb/erb-daisy.gypi',
               ],
            },
         ],
      },{
         'targets' : [
            {
               'target_name': 'kivu12',

               'includes': [
                  'kivu12-src.gypi',
                  '../../include/erb/erb-vcvrack.gypi',
               ],
            },
         ],
      }],
   ],
}
