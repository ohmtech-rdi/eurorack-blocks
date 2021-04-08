# Design

This design is adapted from the
[Mutable Instuments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).


## Schematic

### Overview

This provides a standard potentiometer.

<p align="center"><img src="./schematic.png"></p>

### Smoothing

A 100nF capacitance is used to smooth slightly the potentiometer value to remove noise.

The `OUT` value is inverted:
- When the potentiometer is in the leftmost position, `OUT` is 3V3,
- When the potentiometer is in the rightmost position, `OUT` is 0V.

This allows to follow the same design as the `CvIn` class.

### Software Implementation Considerations

Because the signal `OUT` is inverted, it needs to be inverted in software.

The `Pot` class takes care of all those constraints automatically.


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).


## BOM

The pots from Thonk do not come with knobs.

The knobs to use are shaft D, such as:
- [Rogan-style D shaft knobs](https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/),
- [Davies 1900-style D shaft knobs](https://www.thonk.co.uk/shop/1900h-d/).

> Note: be sure to order D shaft and **not** T18!


## Generating Production Files

The gerber files and the BOM in `csv` format can be produced by running the block `build.py`
script. It requires to be launched with the Python KiCad bundled executable.
The files are generated in the `artifacts` block directory.

When using macOS and KiCad is installed in the usual `/Applications` directory, the
`build.py` script can be runned directly from the shell, as the shebang line will automatically
select the right version of Python to run.


## Implementation

When `Module::run` is called, all `Pot` configurations are retrieved to configure the
ADC converter, as the convertion time of the ADC is quite long and wouldn't fit real-time
constraints. The convertion result is stored in an address the `Pot` class is lazily monitoring.
