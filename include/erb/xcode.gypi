##############################################################################
#
#     xcode.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'target_defaults': {
      'configurations':
      {
         'Debug':
         {
            'xcode_settings':
            {
               'GCC_OPTIMIZATION_LEVEL': '0', # -O0
               'SWIFT_OPTIMIZATION_LEVEL': '-Onone',
            },
         },

         'Release':
         {
            'xcode_settings':
            {
               'GCC_OPTIMIZATION_LEVEL': 's', # -Os
               'SWIFT_OPTIMIZATION_LEVEL': '-O',
               'SWIFT_COMPILATION_MODE': 'wholemodule',
            },
         },
      },
      'xcode_settings':
      {
         'ARCHS': ['$(ARCHS_STANDARD)'],
         'ONLY_ACTIVE_ARCH': 'YES',
         'MACOSX_DEPLOYMENT_TARGET': '10.15',

         'CLANG_CXX_LANGUAGE_STANDARD': 'c++2a',
         'CLANG_CXX_LIBRARY': 'libc++',
         'WARNING_CFLAGS': [
            '-Wno-c++98-compat',
            '-Wno-c++98-compat-pedantic',
            '-Wno-c99-extensions',
            '-Wno-padded',
            '-Wno-weak-vtables',
            '-Wno-float-equal',
         ],
      },
   },
}
