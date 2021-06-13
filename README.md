# eurorack-blocks

[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-sa/4.0/)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/Ubuntu%2020.04/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=Ubuntu%2020.04)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/macOS%2010.15/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=macOS%2010.15)

<img align="left" width="30%" src="./erb-logo.svg">

The `eurorack-blocks` project allows to develop your own custom Eurorack module for either
prototyping or fun in the comfort of your day-to-day IDE and debugging in a
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

#include "artifacts/BypassUi.h"

struct Bypass {
   BypassUi ui;

   void process () {
      ui.audio_out = ui.audio_in;
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

   control audio_in AudioIn {
      position 4hp, 40mm
      style thonk.pj398sm.knurled
      label "IN"
   }

   control audio_out AudioOut {
      position 4hp, 80mm
      style thonk.pj398sm.knurled
      label "OUT"
   }
}
```

```console
raf:bypass$ ./configure.py 👈 Generate IDE project and hardware files
raf:bypass$ ls artifacts/
...
drwxr-xr-x  4 raf  staff    128 Apr 23 18:14 bypass.xcodeproj 👈 Xcode Project
...
raf:bypass$ ./build.py 👈 Build the firmware
ninja: Entering directory `.../eurorack-blocks/samples/bypass/artifacts/out/Release'
[185/185] LINK bypass-daisy
OBJCOPY bypass-daisy
raf:bypass$ ./deploy.py 👈 Upload the firmware
Enter the system bootloader by holding the BOOT button down,
and then pressing, and releasing the RESET button.
Press Enter to continue...
...
raf:bypass$
```


## Sample Projects

[<img align="right" height="200px" src="./samples/bypass/screenshot.png">](./samples/bypass/)
[<img align="right" height="200px" src="./samples/drop/screenshot.png">](./samples/drop/)
[<img align="right" height="200px" src="./samples/reverb/screenshot.png">](./samples/reverb/)

Sample projects are a good place to start learning:

- [`bypass`](./samples/bypass/) is the example used above,
- [`drop`](./samples/drop/) shows the usage of almost every blocks,
- [`reverb`](./samples/reverb/) illustrates how to utilize all the platform memory.


## Blocks

### Audio Signals

- [`AudioIn`](./documentation/controls/AudioIn.md) represents an audio input block,
- [`AudioOut`](./documentation/controls/AudioOut.md) represents an audio output block.

### Control Voltages

- [`CvIn`](./documentation/controls/CvIn.md) represents a CV input block,
- [`CvOut`](./documentation/controls/CvOut.md) represents a CV output block.

### Trigger, Gate and Clock Signals

- [`GateIn`](./documentation/controls/GateIn.md) represents a gate input block,
- [`GateOut`](./documentation/controls/GateOut.md) represents a gate output block.

### Human Interface Devices

- [`Button`](./documentation/controls/Button.md) represents a switch button,
- [`Led`](./documentation/controls/Led.md) represents a monochromatic LED,
- [`LedBi`](./documentation/controls/LedBi.md) represents a dichromatic LED,
- [`LedRgb`](./documentation/controls/LedRgb.md) represents a RGB LED,
- [`Pot`](./documentation/controls/Pot.md) represents a potentiometer block,
- [`Switch`](./documentation/controls/Switch.md) represents a 2 or 3 positions toggle switch,
- [`Trim`](./documentation/controls/Trim.md) represents a trim potentiometer block.


## Setting up

The eurorack-block project requires the following to be installed:

- The `python3` interpreter with minimum version 3.7,
- The `pip3` python package manager,

> Note: Python 2 is not supported.

### macOS

- [Homebrew](https://brew.sh), up-to-date,
- [Xcode](https://developer.apple.com/xcode/), with minimum version 10 on macOS,
- [All the package dependencies](.github/workflows/macos_10_15.yml#L43-L59).

### Debian/Ubuntu

- [All the package dependencies](.github/workflows/ubuntu_20_04.yml#L43-L61).

### STLink probe

The `STLINK-V3MINI` probe can optionally be used to streamline development iterations.
See instructions in its [documentation](./documentation/stlink/).


## Cloning

This repository contains submodules:

    git clone git@github.com:ohmtech-rdi/eurorack-blocks.git
    git submodule update --init --recursive


## Structure

```
eurorack-blocks/
   blocks/
   boards/
   build-system/
   include/
   src/
   submodules/
```

- [`blocks`](./blocks/) contains all the atomic blocks hardware for design validation and software tests,
- [`boards`](./blocks/) contains all the boards hardware to design with,
- [`build-system`](./build-system/) contains the build system used to build and deploy
   the tests and samples,
- [`include`](./include/) contains the software implementation of the blocks,
- [`src`](./src/) contains the software implementation of the blocks,
- [`submodules`](./submodules/) contains the software dependencies as submodules.


## License

All files in this repository, excluding `submodules/`, are provided with the CC BY-SA 4.0 license, **except**:

- The [D-DIN Font](./include/erb/vcvrack/design/d-din),
   under [SIL Open Font License](./include/erb/vcvrack/design/d-din/SIL%20Open%20Font%20License.txt),
- The [Indie Flower Font](./include/erb/vcvrack/design/indie-flower),
   under [SIL Open Font License](./include/erb/vcvrack/design/indie-flower/OFL.txt),
- The [Arpeggio project](https://github.com/textX/Arpeggio), under the [MIT License](https://textx.github.io/Arpeggio/stable/about/license/).
