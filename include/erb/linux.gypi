##############################################################################
#
#     linux.gypi
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################



{
   'target_defaults': {
      'configurations':
      {
         'Debug':
         {
            'cflags':
            [
               '-O0',
               '-g',
            ],
         },

         'Release':
         {
            'defines': [
               'NDEBUG=1',
            ],

            'cflags':
            [
               '-O3',
            ],
         },
      },

      'cflags': [
         '-fPIC',
         '-g',
      ],

      'cflags_c': [
         '-std=gnu11',
      ],

      'cflags_cc': [
         '-std=gnu++2a',
      ],
   },
}
