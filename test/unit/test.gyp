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

         'defines': [
            'erb_TARGET_UNIT_TEST',
         ],

         'include_dirs': [
            '.',
            '../../include',
         ],

         'sources': [
            'main.cpp',
            'test.h',

            '../../include/erb/SdramObject.h',
            '../../include/erb/SdramObject.hpp',
            '../../include/erb/SdramPtr.h',
            '../../include/erb/SdramPtr.hpp',
            '../../include/erb/detail/Animation.h',
            '../../include/erb/detail/Animation.hpp',
            '../../include/erb/detail/Debounce.h',
            '../../include/erb/detail/MonotonicMemoryPool.h',
            '../../include/erb/detail/MonotonicMemoryPool.hpp',
            '../../include/erb/detail/Sdram.h',
            '../../include/erb/detail/Sdram.hpp',

            '../../src/detail/Animation.cpp',
            '../../src/detail/Debounce.cpp',
            '../../src/detail/Sdram.cpp',

            'TestAnimation.cpp',
            'TestAnimation.h',
            'TestDebounce.cpp',
            'TestDebounce.h',
            'TestSdramPtr.cpp',
            'TestSdramPtr.h',
         ],

         'ldflags': [
            '-pthread',
         ],
      },
   ],
}
