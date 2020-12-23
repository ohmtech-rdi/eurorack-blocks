##############################################################################
#
#     eurorack-blocks.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'target_defaults': {
      'xcode_settings': {
         'CLANG_CXX_LANGUAGE_STANDARD': 'c++1y',
         'USE_HEADERMAP': 'NO',
         'WARNING_CFLAGS': [
            '-Wno-four-char-constants',
         ],
      },

      'cflags_cc': [
         '-std=c++14',
      ],

      'cflags': [
         '-Wno-multichar',
      ],
   },

   'includes': [
      './submodules/libdaisy.gypi',
   ],

   'conditions': [
      ['OS=="mac"', {
         'includes': [
            './include/erb/xcode.gypi',
         ],
      }],

      ['OS=="daisy"', {
         'includes': [
            './include/erb/daisy.gypi',
         ],
      }],
   ],
}
