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
            'controls/Display.md',
            'controls/Encoder.md',
            'controls/EncoderButton.md',
            'controls/GateIn.md',
            'controls/GateOut.md',
            'controls/Led.md',
            'controls/LedBi.md',
            'controls/LedRgb.md',
            'controls/Pot.md',
            'controls/SdMmc.md',
            'controls/Switch.md',
            'controls/Trim.md',

            'getting-started/before.md',
            'getting-started/what.md',

            'starter-kit/intro.md',
            'starter-kit/kivu12.md',
            'starter-kit/demos.md',

            'setup/select.md',
            'setup/macos-cpp-xcode.md',
            'setup/macos-cpp-vscode.md',
            'setup/macos-cpp-cli.md',
            'setup/macos-max.md',
            'setup/macos-faust.md',
            'setup/windows-cpp-vscode.md',
            'setup/windows-cpp-cli.md',
            'setup/windows-max.md',
            'setup/windows-faust.md',
            'setup/linux-cpp-vscode.md',
            'setup/linux-cpp-cli.md',
            'setup/linux-faust.md',

            'guides/first.md',
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

            'faust/first.md',
            'faust/mapping.md',
            'faust/soundfile.md',

            'erbb/lexical.md',
            'erbb/grammar.md',

            'erbui/lexical.md',
            'erbui/grammar.md',
         ],
      },
   ],
}
