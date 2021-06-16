##############################################################################
#
#     erb.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'targets' : [
      {
         'target_name': 'erb-daisy',
         'type': 'static_library',

         'includes' : ['erb-src.gypi'],
         'dependencies': [ 'libdaisy' ],

         'defines': [
            'erb_TARGET_DAISY',
         ],

         'sources': [
            'daisy/AdcDaisy.h',
            'daisy/AdcDaisy.hpp',
            'daisy/BoardDaisyField.h',
            'daisy/BoardDaisyField.hpp',
            'daisy/BoardDaisyMicropatch.h',
            'daisy/BoardDaisyMicropatch.hpp',
            'daisy/BoardDaisySeed.h',
            'daisy/BoardDaisySeed.hpp',
            'daisy/BoardKivu12.h',
            'daisy/BoardKivu12.hpp',
            'daisy/DacDaisy.h',
            'daisy/DacDaisy.hpp',
            'daisy/GpioInputDaisy.h',
            'daisy/GpioInputDaisy.hpp',
            'daisy/GpioOutputDaisy.h',
            'daisy/GpioOutputDaisy.hpp',
            'daisy/SubmoduleDaisyPatchSm.h',
            'daisy/SubmoduleDaisyPatchSm.hpp',
            'daisy/SubmoduleDaisySeed.h',
            'daisy/SubmoduleDaisySeed.hpp',

            '../../src/daisy/BoardDaisyField.cpp',
            '../../src/daisy/BoardDaisyMicropatch.cpp',
            '../../src/daisy/BoardDaisySeed.cpp',
            '../../src/daisy/BoardKivu12.cpp',
            '../../src/daisy/SubmoduleDaisyPatchSm.cpp',
            '../../src/daisy/SubmoduleDaisySeed.cpp',
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

         'conditions': [['OS=="daisy"', {
            'type': 'none',
         },{
            'type': 'static_library',
         }]],

         'includes' : ['erb-src.gypi'],

         'defines': [
            'erb_TARGET_VCV_RACK',
         ],

         'sources': [
            # headers
            'vcvrack/BoardDaisyField.h',
            'vcvrack/BoardDaisyMicropatch.h',
            'vcvrack/BoardDaisySeed.h',
            'vcvrack/BoardGeneric.h',
            'vcvrack/BoardGeneric.hpp',
            'vcvrack/BoardKivu12.h',
            'vcvrack/VcvWidgets.h',

            # sources
            '../../src/vcvrack/BoardGeneric.cpp',
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

         'cflags_cc': [
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

            'cflags_cc': [
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
