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
            'erb.h',
            'AdcChannels.h',
            'AnalogControlBase.h',
            'Button.h',
            'Control.h',
            'Controls.h',
            'CvIn.h',
            'GateIn.h',
            'GateOut.h',
            'Led.h',
            'LedBi.h',
            'Module.h',
            'Module.hpp',
            'Pins.h',
            'Pot.h',
            'Switch.h',

            # sources
            '../../src/erb.cpp',
            '../../src/AdcChannels.cpp',
            '../../src/AnalogControlBase.cpp',
            '../../src/Button.cpp',
            '../../src/Controls.cpp',
            '../../src/CvIn.cpp',
            '../../src/GateIn.cpp',
            '../../src/GateOut.cpp',
            '../../src/Led.cpp',
            '../../src/LedBi.cpp',
            '../../src/Module.cpp',
            '../../src/Pot.cpp',
            '../../src/Switch.cpp',
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
