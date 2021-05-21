##############################################################################
#
#     documentation.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'targets' : [
      {
         'target_name': 'documentation',
         'type': 'none',

         'sources': [
            'README.md',

            'controls/README.md',
            'controls/AudioIn.md',
            'controls/AudioOut.md',
            'controls/Button.md',
            'controls/CvIn.md',
            'controls/CvOut.md',
            'controls/GateIn.md',
            'controls/GateOut.md',
            'controls/Led.md',
            'controls/LedBi.md',
            'controls/LedRgb.md',
            'controls/Pot.md',
            'controls/Switch.md',
            'controls/Trim.md',

            'language/lexical.md',
            'language/grammar.md',
         ],
      },
   ],
}
