##############################################################################
#
#     linux.gypi
#     Copyright (c) 2020 Raphael DINGE
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
            ],
         },

         'Release':
         {
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

         '-Wno-multichar', # gcc support : diagnostic ignored is buggy for this warning
      ],

      'cflags_cc': [
         '-std=c++1z',
      ],
   },
}
