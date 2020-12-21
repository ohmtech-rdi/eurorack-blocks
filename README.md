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

Producing the PCBs gerbers requires:

- [Kicad 5](http://kicad-pcb.org/download/)


## Cloning

This repository contains submodules

    git clone git@github.com:ohmtech/eurorack-blocks.git
    git submodule update --init --recursive


## Structure

All blocks have their own directory. The `submodules` folder contains `git` submodules
used in that repository.

```
eurorack-blocks/
   audio-in-daisy/
   audio-out-daisy/
   cv-in/
   gate-in/
   multiplexer/
   pot/
   power-bus/
   submodules/
      kcgen/
      kicad-libs/
```

### `audio-in-daisy`

[`audio-in-daisy`](./audio-in-daisy/) is an audio input block, meant to be used directly with [Daisy Seed](https://www.electro-smith.com/daisy/daisy) on pins 16 and 17.

### `audio-out-daisy`

[`audio-out-daisy`](./audio-out-daisy/) is an audio output block, meant to be used directly with [Daisy Seed](https://www.electro-smith.com/daisy/daisy) on pins 18 and 19.

### `cv-in`

[`cv-in`](./cv-in/) is a CV input block compatible with 3V3 MCU GPIOs.

### `gate-in`

[`gate-in`](./gate-in/) is a gate input block compatible with 3V3 MCU GPIOs.

### `multiplexer`

[`multiplexer`](./multiplexer/) is a multiplexer block compatible with 3V3 MCU GPIOs.

### `pot`

[`pot`](./pot/) is a potentiometer block compatible with 3V3 MCU GPIOs.

### `power-bus`

[`power-bus`](./power-bus/) is a eurorack compatible power bus.

### `kcgen`

`kcgen` is a Kicad gerber and BOM automatic generator.

### `kicad-libs`

`kicad-libs` is a symbol and footprint library for Kicad, containing components like
the standard Thonk jack connector.
