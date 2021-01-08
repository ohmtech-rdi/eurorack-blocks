# eurorack-blocks

[![License: CC BY-SA 4.0](https://licensebuttons.net/l/by-sa/4.0/80x15.png)](https://creativecommons.org/licenses/by-sa/4.0/)

This repository contains all the build material to manufacture "eurorack blocks": small PCBs
that can be used on a breadboard, and provide atomic typical eurorack features such
as power, CV, gates, pots and leds.


## Manifest

This project aims at simplifying eurorack development by providing atomic building blocks
for each eurorack basic features.

The full manifest can be read [here](manifest.md).


## Requirements

### Software

Building and deploying the tests requires:

- The `gcc` ARM toolchain,
- The `dfu-util` firmware downloader,
- The `ninja` build system.

To do so, follow the instructions from the Daisy wiki:

- [Installing on macOS](https://github.com/electro-smith/DaisyWiki/wiki/1b.-Installing-the-Toolchain-on-Mac)
- [Installing on Windows](https://github.com/electro-smith/DaisyWiki/wiki/1c.-Installing-the-Toolchain-on-Windows)
- [Installing on Linux](https://github.com/electro-smith/DaisyWiki/wiki/1d.-Installing-the-Toolchain-on-Linux)

> Note: Installing `make` on macOS might not be required if Xcode is installed. If `brew` returns
> an error, try `brew install armmbed/formulae/arm-none-eabi-gcc dfu-util` instead.

A pre-built package of `ninja` can be installed with your favorite package manager by
following the directions described [here](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

Every other build dependencies can be found in the submodules of this repository, so make
sure to update the submodules, as described below.

### Hardware

Producing the PCBs gerbers requires:

- [Kicad 5.1.9](http://kicad-pcb.org/download/)


## Cloning

This repository contains submodules:

    git clone git@github.com:ohmtech-rdi/eurorack-blocks.git
    git submodule update --init --recursive


## Testing

Almost each block contain a `test` folder with a minimal implementation to show usage
of the block on the software side. To build and deploy the test:

    $ python configure.py

This will create an `artifacts` folder with everything needed to build.

    $ python build.py
    ninja: Entering directory `/Users/raf/dev/eurorack-blocks/audio-out-daisy/test/artifacts/out/Release'
    [10/10] LINK test
    OBJCOPY

This will create the binary file to upload to the Daisy seed. It is the `test.bin` file output in the
`artifacts/out/Release` build directory.

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

Follow the onscreen instructions and this will download the `test.bin` firmware to the
Daisy Seed when it is connected to USB. The error 74 reported from `dfu-util` can be safely
ignored.

Alternatively, if `dfu-util` does not work properly on the target platform,
one may use the [Daisy Web Programmer](https://electro-smith.github.io/Programmer/)
instead.


## Structure

All blocks have their own directory. The `submodules` folder contains `git` submodules
used in that repository. Additionally the `include` and `src` folder contains the software
support for the each blocks. Finally this repository contains a small `build-system` to
configure, build and deploy the tests.

```
eurorack-blocks/
   audio-in-daisy/
   audio-out-daisy/
   build-system/
   button/
   cv-in/
   gate-in/
   gate-out/
   include/
   kits/
   multiplexer/
   led/
   led-bi/
   pot/
   power-bus/
   regulator-daisy/
   slider/
   src/
   submodules/
      kcgen/
      kicad-libs/
   switch/
   trim/
```

### `audio-in-daisy`

[`audio-in-daisy`](./audio-in-daisy/) is an audio input block, meant to be used directly with [Daisy Seed](https://www.electro-smith.com/daisy/daisy) on pins 16 and 17.

### `audio-out-daisy`

[`audio-out-daisy`](./audio-out-daisy/) is an audio output block, meant to be used directly with [Daisy Seed](https://www.electro-smith.com/daisy/daisy) on pins 18 and 19.

### `button`

[`button`](./button/) is a trigger button.

### `cv-in`

[`cv-in`](./cv-in/) is a CV input block compatible with 3V3 MCU GPIOs.

### `gate-in`

[`gate-in`](./gate-in/) is a gate input block compatible with 3V3 MCU GPIOs.

### `gate-out`

[`gate-out`](./gate-out/) is a gate output block compatible with 3V3 MCU GPIOs.

### `include`

[`include`](./include/) contains the software implementation of the blocks.

### `kits`

[`kits`](./kits/) contains panelized blocks standard kits.

### `led`

[`led`](./led/) is a monochromatic LED compatible with 3V3 MCU GPIOs.

### `led-bi`

[`led-bi`](./led-bi/) is a dichromatic LED compatible with 3V3 MCU GPIOs.

### `multiplexer`

[`multiplexer`](./multiplexer/) is a multiplexer block compatible with 3V3 MCU GPIOs.

### `pot`

[`pot`](./pot/) is a potentiometer block compatible with 3V3 MCU GPIOs.

### `power-bus`

[`power-bus`](./power-bus/) is a eurorack compatible power bus.

### `regulator-daisy`

[`regulator-daisy`](./regulator-daisy/) is a voltage regulator compatible with the Daisy Seed.

### `slider`

[`slider`](./slider/) is a slider potentiometer block compatible with 3V3 MCU GPIOs.

### `src`

[`src`](./src/) contains the software implementation of the blocks.

### `switch`

[`switch`](./switch/) is a 2 or 3 positions toggle switch.

### `trim`

[`trim`](./trim/) is a trim potentiometer block compatible with 3V3 MCU GPIOs.

### `kcgen`

`kcgen` is a Kicad gerber and BOM automatic generator.

### `kicad-libs`

`kicad-libs` is a symbol and footprint library for Kicad, containing components like
the standard Thonk jack connector.
