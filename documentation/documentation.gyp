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
            'index.md',

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

            'getting-started/before.md',
            'getting-started/first.md',
            'getting-started/setup.md',
            'getting-started/what.md',

            'starter-kit/requirements.md',
            'starter-kit/content.md',
            'starter-kit/kivu12.md',
            'starter-kit/drop.md',
            'starter-kit/frohmage.md',
            'starter-kit/testing.md',

            'guides/drop.md',
            'guides/kick.md',
            'guides/reverb.md',

            'diy/intro.md',
            'diy/board.md',
            'diy/drc.md',
            'diy/routing.md',
            'diy/order-assemble.md',

            'max/first.md',
            'max/ui.md',
            'max/setup.md',

            'faust/first.md',
            'faust/mapping.md',
            'faust/setup.md',
            'faust/soundfile.md',

            'erbb/lexical.md',
            'erbb/grammar.md',

            'erbui/lexical.md',
            'erbui/grammar.md',
         ],
      },
   ],
}
