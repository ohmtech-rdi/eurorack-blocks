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
            'AdcChannels.h',
            'AnalogControlBase.h',
            'AudioInDaisy.h',
            'AudioOutDaisy.h',
            'Button.h',
            'Constants.h',
            'CvIn.h',
            'GateIn.h',
            'GateOut.h',
            'Led.h',
            'LedBi.h',
            'Module.h',
            'Module.hpp',
            'ModuleListener.h',
            'ModuleListeners.h',
            'Multiplexer.h',
            'Pins.h',
            'Pot.h',
            'Switch.h',

            'detail/Debounce.h',

            # sources
            '../../src/erb.cpp',
            '../../src/AdcChannels.cpp',
            '../../src/AnalogControlBase.cpp',
            '../../src/AudioInDaisy.cpp',
            '../../src/AudioOutDaisy.cpp',
            '../../src/Button.cpp',
            '../../src/CvIn.cpp',
            '../../src/GateIn.cpp',
            '../../src/GateOut.cpp',
            '../../src/Led.cpp',
            '../../src/LedBi.cpp',
            '../../src/Module.cpp',
            '../../src/ModuleListeners.cpp',
            '../../src/Multiplexer.cpp',
            '../../src/Pot.cpp',
            '../../src/Switch.cpp',

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
