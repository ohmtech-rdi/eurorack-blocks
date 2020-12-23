# Drop

`Drop` is a sample to illustrate a simple module, yet using quite some different eurorack blocks features.


## Overview

This module allows to make a typical "techno drop".

When active, the stereo input is either muted or goes through a high-pass filter. The latter cutoff frequency can be controlled with the `FREQ` pot, and can be used to selectively remove the drum kick frequencies.

When passive, it is just a bypass.

The transition from passive to active or active to passive is armed with the `ARM` button or gate. The actual transition only happens when the transition is armed and a `SYNC` trigger is received.

Typically, the `SYNC` gate input would be connected to a clock divider with appropriate reset, so that the `SYNC` is triggered only on beats or bars.


## Configuring

    $ python configure.py

This will create an `artifacts` folder with everything needed to build.


## Building

    $ python build.py
    ninja: Entering directory `/Users/raf/dev/eurorack-blocks/samples/drop/artifacts/out/Release'
    [10/10] LINK test
    OBJCOPY
    ...

This will create a binary file to upload to the Daisy seed. It is the `drop.bin` file
output in the `artifacts/out/Release` build directory.


## Deploying

    $ python deploy.py
    Enter the system bootloader by holding the BOOT button down,
    and then pressing, and releasing the RESET button.
    Press Enter to continue...
    Flashing...
    dfu-util 0.9
    [...]
    Downloading to address = 0x08000000, size = 36484
    Download   [=========================] 100%        36484 bytes
    Download done.
    File downloaded successfully
    dfu-util: Error during download get_status
    Run command exited with 74

Follow the onscreen instructions and this will download the `drop.bin` firmware to the
Daisy Seed when it is connected to USB.

The error 74 reported from `dfu-util` can be safely
ignored.

Alternatively, if `dfu-util` does not work properly on your computer,
one may use the [Daisy Web Programmer](https://electro-smith.github.io/Programmer/)
in the [Chrome](https://support.google.com/chrome/answer/95346) browser instead.
