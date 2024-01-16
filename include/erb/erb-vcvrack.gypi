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
      'vcvrack/ModuleBoard.h',
      'vcvrack/VcvWidgets.h',

      # sources
      '../../src/vcvrack/BoardGeneric.cpp',
      '../../src/vcvrack/ModuleBoard.cpp',
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
            'vcvrack/resource/sifam.dbn151.white.svg',
            'vcvrack/resource/sifam.drn111.white.svg',
            'vcvrack/resource/thonk.pj398sm.knurled.svg',
            'vcvrack/resource/thonk.pj398sm.hex.svg',
            'vcvrack/resource/Rogan1S_bg.svg',
            'vcvrack/resource/Rogan1S.svg',
            'vcvrack/resource/Rogan1SBlack_fg.svg',
            'vcvrack/resource/Rogan1SWhite_fg.svg',
            'vcvrack/resource/Rogan2S_bg.svg',
            'vcvrack/resource/Rogan2SBlack_fg.svg',
            'vcvrack/resource/Rogan3SWhite_fg.svg',
            'vcvrack/resource/Rogan3SWhite.svg',
            'vcvrack/resource/Rogan5PSWhite_fg.svg',
            'vcvrack/resource/Rogan5PSWhite.svg',
            'vcvrack/resource/dailywell.2ms.1.svg',
            'vcvrack/resource/dailywell.2ms.2.svg',
            'vcvrack/resource/dailywell.2ms.3.svg',
            'vcvrack/resource/pedal.jack.svg',
            'vcvrack/resource/pedal.footswitch.0.svg',
            'vcvrack/resource/pedal.footswitch.1.svg',
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
