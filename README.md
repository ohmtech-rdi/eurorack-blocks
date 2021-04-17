# eurorack-blocks

[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-sa/4.0/)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/Ubuntu%2020.04/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=Ubuntu%2020.04)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/macOS%2010.15/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=macOS%2010.15)

<img align="left" width="30%" src="./erb-logo.svg">

The `eurorack-blocks` project allows to develop your own custom Eurorack module for either
protoyping or fun in the comfort of your day-to-day IDE and debugging in a
[virtual Eurorack environment](https://vcvrack.com),
and when ready, to auto-magically generate all the needed files to manufacture
the eurorack module for you to use in a real Eurorack modular system.

`eurorack-blocks` is using [`Daisy Seed`](https://www.electro-smith.com/daisy/daisy),
an embedded platform for music, which uses
a 480 MHz ARM Cortex-M7 MCU, a High fidelity AKM stereo audio codec, 64MB of SDRAM,
and 8MB of flash memory.

The full project's manifest can be read [here](manifest.md).


```cpp
// Bypass.h

#include "erb/erb.h"

using namespace erb;

struct Bypass {
   Module module;
   AudioInDaisy audio_in { module, AudioInDaisyPinLeft };
   AudioOutDaisy audio_out { module, AudioOutDaisyPinLeft };

   void process () {
      audio_out = audio_in;
   }
};
```

<img align="right" width="15%" src="./samples/bypass/screenshot.png">

```erb
// Bypass.erbui

module Bypass {
   width 8hp
   material aluminum black
   header { label "BYPASS" }

   control audio_in AudioInDaisy {
      position 4hp, 40mm
      style thonk.pj398sm.knurled
      label "IN"
   }

   control audio_out AudioOutDaisy {
      position 4hp, 80mm
      style thonk.pj398sm.knurled
      label "OUT"
   }
}
```

```console
raf:bypass$ ./configure.py 👈 Generate IDE project and hardware files
raf:bypass$ ls artifacts/
-rw-r--r--  1 raf  staff  36914 Apr 17 09:03 bypass-preprocess.svg
-rw-r--r--  1 raf  staff  17228 Apr 17 09:03 bypass.dxf
-rw-r--r--  1 raf  staff   9066 Apr 17 09:03 bypass.pdf
-rw-r--r--  1 raf  staff  36560 Apr 17 09:03 bypass.svg
drwxr-xr-x  3 raf  staff     96 Apr 17 09:03 bypass.xcodeproj 👈 Xcode Project
-rw-r--r--  1 raf  staff   2009 Apr 17 09:03 deploy_vcvrack.py
drwxr-xr-x  4 raf  staff    128 Apr 17 09:03 out
-rw-r--r--  1 raf  staff    635 Apr 17 09:03 plugin.json
-rw-r--r--  1 raf  staff   8756 Apr 17 09:03 plugin_vcvrack.cpp
raf:bypass$ ./build.py 👈 Build the firmware
ninja: Entering directory `.../eurorack-blocks/samples/bypass/artifacts/out/Release'
[185/185] LINK bypass-daisy
OBJCOPY bypass-daisy
raf:bypass$ ./deploy.py 👈 Upload the firmware to your Daisy Seed
Enter the system bootloader by holding the BOOT button down,
and then pressing, and releasing the RESET button.
Press Enter to continue...
...
raf:bypass$
```


## Blocks

### Audio Signals

- [`audio-in-daisy`](./blocks/audio-in-daisy/documentation/) is an audio input block,
- [`audio-out-daisy`](./blocks/audio-out-daisy/documentation/) is an audio output block.

### Control Voltages

- [`cv-in`](./blocks/cv-in/documentation/) is a CV input block.

### Trigger, Gate and Clock Signals

- [`gate-in`](./blocks/gate-in/documentation/) is a gate input block,
- [`gate-out`](./blocks/gate-out/) is a gate output block.

### HID

- [`button`](./blocks/button/documentation/) is a trigger button,
- [`led`](./blocks/led/documentation/) is a monochromatic LED,
- [`led-bi`](./blocks/led-bi/documentation/) is a dichromatic LED,
- [`pot`](./blocks/pot/documentation/) is a potentiometer block,
- [`slider`](./blocks/slider/) is a slider potentiometer block,
- [`switch`](./blocks/switch/documentation/) is a 2 or 3 positions toggle switch,
- [`trim`](./blocks/trim/documentation/) is a trim potentiometer block.

### Utility

- [`multiplexer`](./blocks/multiplexer/documentation/) is a signal multiplexer block.


## Setting up

The eurorack-block project requires the following to be installed:

- The `python3` interpreter with minimum version 3.7,
- The `pip3` python package manager,
- [Kicad 5.1.9](http://kicad-pcb.org/download/),
- The [D-DIN Font](./include/erb/vcvrack/design/d-din) must be installed on the system.

> Note: Python 2 is not supported.

### macOS

- [Homebrew](https://brew.sh), up-to-date,
- [Xcode](https://developer.apple.com/xcode/), with minimum version 10 on macOS,
- [All the package dependencies](https://github.com/ohmtech-rdi/eurorack-blocks/blob/main/.github/workflows/macos_10_15.yml#L42-L47).

### Debian/Ubuntu

- [All the package dependencies](https://github.com/ohmtech-rdi/eurorack-blocks/blob/main/.github/workflows/ubuntu_20_04.yml#L42-L49).


## Cloning

This repository contains submodules:

    git clone git@github.com:ohmtech-rdi/eurorack-blocks.git
    git submodule update --init --recursive


## Sample Projects

Sample projects are a good place to start learning:

- [`bypass`](./samples/bypass/) is the example used above,
- [`drop`](./samples/drop/) shows the usage of almost every blocks.


## Structure

```
eurorack-blocks/
   blocks/
   build-system/
   include/
   src/
   submodules/
```

- [`blocks`](./blocks/) contains all the atomic blocks hardware for design validation, software tests and documentation,
- [`build-system`](./build-system/) contains the build system used to build and deploy
   the tests and samples,
- [`include`](./include/) contains the software implementation of the blocks,
- [`src`](./src/) contains the software implementation of the blocks,
- [`submodules`](./submodules/) contains the software dependencies as submodules.


## License

All files in this repository are provided with the CC BY-SA 4.0 license, **except**:

- The [D-DIN Font](./include/erb/vcvrack/design/d-din),
   under [SIL Open Font License](./include/erb/vcvrack/design/d-din/SIL%20Open%20Font%20License.txt),
- The [Arpeggio project](https://github.com/textX/Arpeggio), under the [MIT License](https://textx.github.io/Arpeggio/stable/about/license/).
