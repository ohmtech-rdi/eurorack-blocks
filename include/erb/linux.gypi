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
            'defines': [
               'DEBUG=1',
            ],

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
               'RELEASE=1',
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

         '-Wall',
         '-Wextra',
         '-Wpedantic',
         '-Werror',
      ],

      'cflags_c': [
         '-std=gnu11',
      ],

      'cflags_cc': [
         '-std=gnu++2a',
      ],
   },
}
