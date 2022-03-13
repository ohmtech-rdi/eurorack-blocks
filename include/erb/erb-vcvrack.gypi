##############################################################################
#
#     erb-vcvrack.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'defines': [
      'erb_TARGET_VCV_RACK',
   ],

   'includes' : ['erb-src.gypi'],

   'sources': [
      # headers
      'vcvrack/BoardGeneric.h',
      'vcvrack/BoardGeneric.hpp',
      'vcvrack/VcvWidgets.h',

      # sources
      '../../src/vcvrack/BoardGeneric.cpp',
   ],

   'include_dirs': [
      '..',
      '../../submodules/vcv-rack-sdk/include',
      '../../submodules/vcv-rack-sdk/dep/include',
   ],

   'xcode_settings':
   {
      'OTHER_LDFLAGS': [
         '-undefined dynamic_lookup',
      ],

      'EXECUTABLE_PREFIX': '',
      'EXECUTABLE_EXTENSION': 'dylib',
      'PRODUCT_NAME': 'plugin',
   },

   'cflags': [
      '-fPIC',
   ],

   'cflags_cc': [
      '-fPIC',
   ],

   'copies': [
      {
         'destination': '<(PRODUCT_DIR)/res',
         'files': [
            'vcvrack/resource/rogan.6ps.svg',
            'vcvrack/resource/rogan.5ps.svg',
            'vcvrack/resource/rogan.3ps.svg',
            'vcvrack/resource/rogan.2ps.svg',
            'vcvrack/resource/rogan.1ps.svg',
            'vcvrack/resource/sifam.dbn151.white.svg',
            'vcvrack/resource/sifam.drn111.white.svg',
            'vcvrack/resource/songhuei.9mm.svg',
            'vcvrack/resource/thonk.pj398sm.knurled.svg',
            'vcvrack/resource/thonk.pj398sm.hex.svg',
            'vcvrack/resource/dailywell.2ms.1.svg',
            'vcvrack/resource/dailywell.2ms.2.svg',
            'vcvrack/resource/dailywell.2ms.3.svg',
         ],
      },
   ],

   'postbuilds': [
      {
         'postbuild_name': 'Copy to VCV Rack plug-ins folder',
         'action': [
            '<!(which python3)', 'artifacts/actions/action_vcvrack_install.py'
         ],
      },
   ],

   'direct_dependent_settings': {
      'defines': [
         'erb_TARGET_VCV_RACK',
      ],

      'include_dirs': [
         '..',
         '../../submodules/vcv-rack-sdk/include',
         '../../submodules/vcv-rack-sdk/dep/include',
      ],
   },
}
