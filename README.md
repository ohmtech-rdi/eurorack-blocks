# eurorack-blocks

[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-sa/4.0/)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/Ubuntu%2018.04/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=Ubuntu%2018.04)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/Ubuntu%2020.04/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=Ubuntu%2020.04)
[<!--lint ignore no-dead-urls-->![GitHub Actions status | ohmtech-rdi/eurorack-blocks](https://github.com/ohmtech-rdi/eurorack-blocks/workflows/macOS%2010.15/badge.svg)](https://github.com/ohmtech-rdi/eurorack-blocks/actions?workflow=macOS%2010.15)

This repository contains all the build material to manufacture "eurorack blocks": small PCBs
that can be used on a breadboard, and provide atomic typical digital eurorack features such
as power, CV, gates, pots and leds.


## Manifest

This project aims at simplifying digital eurorack development by providing atomic building blocks
for each eurorack basic features.

The full manifest can be read [here](manifest.md).


## Blocks

### Audio Signals

- [`audio-in-daisy`](./audio-in-daisy/) is an audio input block,
- [`audio-out-daisy`](./audio-out-daisy/) is an audio output block.

### Control Voltages

- [`cv-in`](./cv-in/) is a CV input block.

### Trigger, Gate and Clock Signals

- [`gate-in`](./gate-in/) is a gate input block,
- [`gate-out`](./gate-out/) is a gate output block.

### HID

- [`button`](./button/) is a trigger button,
- [`led`](./led/) is a monochromatic LED,
- [`led-bi`](./led-bi/) is a dichromatic LED,
- [`pot`](./pot/) is a potentiometer block,
- [`slider`](./slider/) is a slider potentiometer block,
- [`switch`](./switch/) is a 2 or 3 positions toggle switch,
- [`trim`](./trim/) is a trim potentiometer block.

### Power

- [`power-bus`](./power-bus/) is a eurorack compatible power bus.
- [`regulator-daisy`](./regulator-daisy/) is a voltage regulator compatible with the Daisy Seed.

### Utility

- [`multiplexer`](./multiplexer/) is a signal multiplexer block.


## Kits

Blocks are packed into panels called "kits".
[`kits`](./kits/) contains panelized blocks standard kits.


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


## Structure

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
      libDaisy/
   switch/
   trim/
```

- All blocks have their own directory,
- [`build-system`](./build-system/) contains the build system used to build and deploy
   the tests and samples,
- [`include`](./include/) contains the software implementation of the blocks,
- [`src`](./src/) contains the software implementation of the blocks,
- [`kcgen`](https://github.com/ohmtech/kcgen) is a Kicad gerber and BOM automatic generator,
- [`kicad-libs`](https://github.com/ohmtech/kicad-libs) is a symbol and footprint library for Kicad,
   containing components like the standard Thonk jack connector,
- [`libDaisy`](https://github.com/electro-smith/libDaisy) is a hardware library
   for the Daisy audio platform.
