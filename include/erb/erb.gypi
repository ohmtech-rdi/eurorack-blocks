##############################################################################
#
#     erb.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'targets' : [
      {
         'target_name': 'erb',
         'type': 'static_library',

         'defines': [
            'erb_BUFFER_SIZE=48',
            'erb_SAMPLE_RATE=48014',
         ],

         'sources': [
            'AudioIn.h',
            'AudioOut.h',
            'Button.h',
            'CvIn.h',
            'GateIn.h',
            'GateOut.h',
            'Led.h',
            'LedBi.h',
            'LedRgb.h',
            'Pot.h',
            'SdramObject.h',
            'SdramObject.hpp',
            'Switch.h',

            'def.h',
            'erb.h',
            'module_init.h',

            '../../src/AudioIn.cpp',
            '../../src/AudioOut.cpp',
            '../../src/Button.cpp',
            '../../src/CvIn.cpp',
            '../../src/GateIn.cpp',
            '../../src/GateOut.cpp',
            '../../src/Led.cpp',
            '../../src/LedBi.cpp',
            '../../src/LedRgb.cpp',
            '../../src/Pot.cpp',
            '../../src/Switch.cpp',
         ],

         'include_dirs': [
            '..',
         ],
      },

      {
         'target_name': 'erb-daisy',
         'type': 'static_library',

         'dependencies': [ 'libdaisy' ],

         'defines': [
            'erb_TARGET_DAISY',
         ],

         'sources': [
            # headers
            'SdramObject.h',
            'SdramObject.hpp',
            'def.h',
            'erb.h',
            'module_init.h',

            'daisy/DaisyAdcChannels.h',
            'daisy/DaisyAnalogControlBase.h',
            'daisy/DaisyAudioInDaisy.h',
            'daisy/DaisyAudioOutDaisy.h',
            'daisy/DaisyButton.h',
            'daisy/DaisyConstants.h',
            'daisy/DaisyCvIn.h',
            'daisy/DaisyGateIn.h',
            'daisy/DaisyGateOut.h',
            'daisy/DaisyLed.h',
            'daisy/DaisyLedBi.h',
            'daisy/DaisyLedRgb.h',
            'daisy/DaisyModule.h',
            'daisy/DaisyModule.hpp',
            'daisy/DaisyModuleListener.h',
            'daisy/DaisyModuleListeners.h',
            'daisy/DaisyMultiplexer.h',
            'daisy/DaisyPins.h',
            'daisy/DaisyPot.h',
            'daisy/DaisySwitch.h',

            'detail/Animation.h',
            'detail/Animation.hpp',
            'detail/Debounce.h',

            # sources
            '../../src/daisy/DaisyAdcChannels.cpp',
            '../../src/daisy/DaisyAnalogControlBase.cpp',
            '../../src/daisy/DaisyAudioInDaisy.cpp',
            '../../src/daisy/DaisyAudioOutDaisy.cpp',
            '../../src/daisy/DaisyButton.cpp',
            '../../src/daisy/DaisyCvIn.cpp',
            '../../src/daisy/DaisyGateIn.cpp',
            '../../src/daisy/DaisyGateOut.cpp',
            '../../src/daisy/DaisyLed.cpp',
            '../../src/daisy/DaisyLedBi.cpp',
            '../../src/daisy/DaisyLedRgb.cpp',
            '../../src/daisy/DaisyModule.cpp',
            '../../src/daisy/DaisyModuleListeners.cpp',
            '../../src/daisy/DaisyMultiplexer.cpp',
            '../../src/daisy/DaisyPot.cpp',
            '../../src/daisy/DaisySwitch.cpp',

            '../../src/detail/Animation.cpp',
            '../../src/detail/Debounce.cpp',
         ],

         'include_dirs': [
            '..',
         ],

         'direct_dependent_settings': {
            'defines': [
               'erb_TARGET_DAISY',
            ],

            'include_dirs': [
               '..',
            ],

            'sources': [
               '<!(echo artifacts/main_daisy.cpp)',
            ],
         },

         'export_dependent_settings': [
            'libdaisy',
         ],
      },
      {
         'target_name': 'erb-vcvrack',
         'type': 'static_library',

         'defines': [
            'erb_TARGET_VCV_RACK',
         ],

         'sources': [
            # headers
            'SdramObject.h',
            'SdramObject.hpp',
            'def.h',
            'erb.h',
            'module_init.h',

            'vcvrack/VcvAudioInDaisy.h',
            'vcvrack/VcvAudioOutDaisy.h',
            'vcvrack/VcvButton.h',
            'vcvrack/VcvConstants.h',
            'vcvrack/VcvCvIn.h',
            'vcvrack/VcvGateIn.h',
            'vcvrack/VcvGateOut.h',
            'vcvrack/VcvInputBase.h',
            'vcvrack/VcvLed.h',
            'vcvrack/VcvLedBi.h',
            'vcvrack/VcvLedRgb.h',
            'vcvrack/VcvLightBase.h',
            'vcvrack/VcvModule.h',
            'vcvrack/VcvModule.hpp',
            'vcvrack/VcvModuleListener.h',
            'vcvrack/VcvModuleListeners.h',
            'vcvrack/VcvMultiplexer.h',
            'vcvrack/VcvOutputBase.h',
            'vcvrack/VcvParamBase.h',
            'vcvrack/VcvPins.h',
            'vcvrack/VcvPot.h',
            'vcvrack/VcvSwitch.h',
            'vcvrack/VcvWidgets.h',

            'detail/Animation.h',
            'detail/Animation.hpp',
            'detail/Debounce.h',

            # sources
            '../../src/vcvrack/VcvAudioInDaisy.cpp',
            '../../src/vcvrack/VcvAudioOutDaisy.cpp',
            '../../src/vcvrack/VcvButton.cpp',
            '../../src/vcvrack/VcvCvIn.cpp',
            '../../src/vcvrack/VcvGateIn.cpp',
            '../../src/vcvrack/VcvGateOut.cpp',
            '../../src/vcvrack/VcvInputBase.cpp',
            '../../src/vcvrack/VcvLed.cpp',
            '../../src/vcvrack/VcvLedBi.cpp',
            '../../src/vcvrack/VcvLedRgb.cpp',
            '../../src/vcvrack/VcvLightBase.cpp',
            '../../src/vcvrack/VcvModule.cpp',
            '../../src/vcvrack/VcvModuleListeners.cpp',
            '../../src/vcvrack/VcvMultiplexer.cpp',
            '../../src/vcvrack/VcvOutputBase.cpp',
            '../../src/vcvrack/VcvParamBase.cpp',
            '../../src/vcvrack/VcvPot.cpp',
            '../../src/vcvrack/VcvSwitch.cpp',

            '../../src/detail/Animation.cpp',
            '../../src/detail/Debounce.cpp',
         ],

         'xcode_settings':
         {
            'WARNING_CFLAGS': [
               '-Wno-shadow-field-in-constructor',
               '-Wno-float-conversion',
               '-Wno-documentation-unknown-command',
               '-Wno-documentation',
               '-Wno-old-style-cast',
               '-Wno-zero-as-null-pointer-constant',
               '-Wno-reserved-id-macro',
               '-Wno-gnu-anonymous-struct',
               '-Wno-nested-anon-types',
               '-Wno-double-promotion',
               '-Wno-shadow',
               '-Wno-conversion',
               '-Wno-unused-parameter',
               '-Wno-inconsistent-missing-destructor-override',
               '-Wno-global-constructors',
               '-Wno-cast-align',
               '-Wno-cast-qual',
               '-Wno-vla',
               '-Wno-vla-extension',
               '-Wno-header-hygiene',
            ],
         },

         'cflags': [
            '-fPIC',
         ],

         'include_dirs': [
            '..',
            '../../submodules/vcv-rack-sdk/include',
            '../../submodules/vcv-rack-sdk/dep/include',
         ],

         'direct_dependent_settings': {
            'defines': [
               'erb_TARGET_VCV_RACK',
            ],

            'sources': [
               '<!(echo artifacts/plugin_vcvrack.cpp)',
            ],

            'xcode_settings':
            {
               'WARNING_CFLAGS': [
                  '-Wno-shadow-field-in-constructor',
                  '-Wno-float-conversion',
                  '-Wno-documentation-unknown-command',
                  '-Wno-documentation',
                  '-Wno-old-style-cast',
                  '-Wno-zero-as-null-pointer-constant',
                  '-Wno-reserved-id-macro',
                  '-Wno-gnu-anonymous-struct',
                  '-Wno-nested-anon-types',
                  '-Wno-double-promotion',
                  '-Wno-shadow',
                  '-Wno-conversion',
                  '-Wno-unused-parameter',
                  '-Wno-inconsistent-missing-destructor-override',
                  '-Wno-global-constructors',
                  '-Wno-cast-align',
                  '-Wno-cast-qual',
                  '-Wno-vla',
                  '-Wno-vla-extension',
                  '-Wno-header-hygiene',
               ],

               'OTHER_LDFLAGS': [
                  '-undefined dynamic_lookup',
               ],

               'EXECUTABLE_PREFIX': '',
               'PRODUCT_NAME': 'plugin',
            },

            'cflags': [
               '-fPIC',
            ],

            'include_dirs': [
               '..',
               '../../submodules/vcv-rack-sdk/include',
               '../../submodules/vcv-rack-sdk/dep/include',
            ],

            'rules': [
               {
                  'rule_name': 'Transpile Erbui',
                  'extension': 'erbui',
                  'outputs': [
                     '<!(echo artifacts/deploy_vcvrack.py)',
                     '<!(echo artifacts/panel_vcvrack.svg)',
                     '<!(echo artifacts/plugin_vcvrack.cpp)',
                     '<!(echo artifacts/plugin.json)',
                  ],
                  'action': [ 'python3', 'artifacts/generate_vcvrack.py', '<(RULE_INPUT_PATH)' ],
               },
            ],

            'copies': [
               {
                  'destination': '<(PRODUCT_DIR)',
                  'files': [
                     '<!(echo artifacts/plugin.json)',
                  ],
               },
               {
                  'destination': '<(PRODUCT_DIR)/res',
                  'files': [
                     'vcvrack/resource/rogan.6ps.svg',
                     'vcvrack/resource/rogan.5ps.svg',
                     'vcvrack/resource/rogan.3ps.svg',
                     'vcvrack/resource/rogan.2ps.svg',
                     'vcvrack/resource/rogan.1ps.svg',
                     'vcvrack/resource/songhuei.9mm.svg',
                     'vcvrack/resource/thonk.pj398sm.knurled.svg',
                     'vcvrack/resource/thonk.pj398sm.hex.svg',
                     'vcvrack/resource/dailywell.2ms.1.svg',
                     'vcvrack/resource/dailywell.2ms.2.svg',
                     'vcvrack/resource/dailywell.2ms.3.svg',

                     '<!(echo artifacts/panel_vcvrack.svg)',
                  ],
               },
            ],

            'postbuilds': [
               {
                  'postbuild_name': 'Copy to VCV Rack plug-ins folder',
                  'action': [
                     'python3', 'artifacts/deploy_vcvrack.py'
                  ],
               },
            ],
         },
      },
   ],
}
