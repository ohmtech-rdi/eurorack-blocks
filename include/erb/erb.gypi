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

         'all_dependent_settings': {
            'defines': [
               'erb_BUFFER_SIZE=48',
               'erb_SAMPLE_RATE=48014',
            ],
         },

         'sources': [
            'AudioIn.h',
            'AudioIn.hpp',
            'AudioOut.h',
            'AudioOut.hpp',
            'Buffer.h',
            'Button.h',
            'Button.hpp',
            'CvIn.h',
            'CvIn.hpp',
            'FloatRange.h',
            'GateIn.h',
            'GateIn.hpp',
            'GateOut.h',
            'Led.h',
            'LedBi.h',
            'LedRgb.h',
            'Pot.h',
            'Pot.hpp',
            'SdramObject.h',
            'SdramObject.hpp',
            'Switch.h',
            'Switch.hpp',
            'def.h',
            'erb.h',
            'module_init.h',

            'detail/Animation.h',
            'detail/Animation.hpp',
            'detail/Clock.h',
            'detail/Clock.hpp',
            'detail/Debounce.h',
            'detail/DoubleBuffer.h',
            'detail/DoubleBuffer.hpp',
            'detail/GateGenerator.h',
            'detail/GateGenerator.hpp',
            'detail/fnc.h',
            'detail/fnc.hpp',

            '../../src/Button.cpp',
            '../../src/GateOut.cpp',
            '../../src/Led.cpp',
            '../../src/LedBi.cpp',
            '../../src/LedRgb.cpp',
         ],

         'include_dirs': [
            '..',
         ],
      },

      {
         'target_name': 'erb-daisy',
         'type': 'static_library',

         'dependencies': [ 'erb', 'libdaisy' ],

         'defines': [
            'erb_TARGET_DAISY',
         ],

         'sources': [
            'daisy/BoardDaisySeed.h',
            'daisy/BoardDaisySeed.hpp',
            'daisy/BoardKivu12.h',

            '../../src/daisy/BoardDaisySeed.cpp',
            '../../src/daisy/BoardKivu12.cpp',
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

         'dependencies': [ 'erb' ],

         'defines': [
            'erb_TARGET_VCV_RACK',
         ],

         'sources': [
            # headers
            'vcvrack/BoardGeneric.h',
            'vcvrack/BoardGeneric.hpp',
            'vcvrack/BoardKivu12.h',

            # sources
            '../../src/vcvrack/BoardGeneric.cpp',
            '../../src/vcvrack/BoardKivu12.cpp',
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
