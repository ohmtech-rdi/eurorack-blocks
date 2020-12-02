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
