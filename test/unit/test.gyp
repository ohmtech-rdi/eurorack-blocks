##############################################################################
#
#     test.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'conditions': [
      ['OS=="mac"', {
         'includes': [
            'xcode.gypi',
         ],
      }],

      ['OS=="linux"', {
         'includes': [
            'linux.gypi',
         ],
      }],
   ],

   'targets' : [
      {
         'target_name': 'test',
         'type': 'executable',

         'include_dirs': [
            '.',
            '../../include',
         ],

         'sources': [
            'main.cpp',
            'test.h',

            '../../include/erb/detail/Debounce.h',
            '../../src/detail/Debounce.cpp',

            'TestDebounce.cpp',
            'TestDebounce.h',
         ],
      },
   ],
}
