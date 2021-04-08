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

         'dependencies': [ 'libdaisy' ],

         'sources': [
            # headers
            'def.h',
            'erb.h',

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
            'daisy/DaisyModule.h',
            'daisy/DaisyModule.hpp',
            'daisy/DaisyModuleListener.h',
            'daisy/DaisyModuleListeners.h',
            'daisy/DaisyMultiplexer.h',
            'daisy/DaisyPins.h',
            'daisy/DaisyPot.h',
            'daisy/DaisySwitch.h',

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
            '../../src/daisy/DaisyModule.cpp',
            '../../src/daisy/DaisyModuleListeners.cpp',
            '../../src/daisy/DaisyMultiplexer.cpp',
            '../../src/daisy/DaisyPot.cpp',
            '../../src/daisy/DaisySwitch.cpp',

            '../../src/detail/Debounce.cpp',
         ],

         'include_dirs': [
            '..',
         ],

         'direct_dependent_settings': {
            'include_dirs': [
               '..',
            ],
         },

         'export_dependent_settings': [
            'libdaisy',
         ],
      },
   ],
}
