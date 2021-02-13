# Design

## Description

This design is adapted from the [Mutable Instruments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).


## Schematic

### Overview

This block provides voltage regulation for the Daisy Seed input voltage. It delivers +5V and
up to 500mA.

<p align="center"><img src="./schematic.png"></p>

Its schematic is following the
[recommended configuration](https://recom-power.com/pdf/Innoline/R-78E-0.5.pdf),
but with Mutable Instruments Tides component values.

One big advantage of the RECOM chip compared to a classic linear voltage regulator is
that it doesn't heat.

The delivered +5V fits in the [Daisy Seed `VIN` Range](https://github.com/electro-smith/Hardware/blob/master/reference/daisy_seed/Datasheet.md#electrical-characteristics).

The delivered 500mA is the same as the Digital Regulator in the
[Daisy Seed schematics](https://github.com/electro-smith/Hardware/blob/master/reference/daisy_seed/ES_Daisy_Seed_Rev4.pdf)
on page 1.


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).


## Generating Production Files

The gerber files and the BOM in `csv` format can be produced by running the block `build.py`
script. It requires to be launched with the Python KiCad bundled executable.
The files are generated in the `artifacts` block directory.

When using macOS and KiCad is installed in the usual `/Applications` directory, the
`build.py` script can be runned directly from the shell, as the shebang line will automatically
select the right version of Python to run.
