# Design

This design is adapted from the [Mutable Instuments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).

## Schematic

<p align="center"><img src="./schematic.png"></p>

At rest, the [SPST-NO](https://en.wikipedia.org/wiki/Push_switch) switch `SW1` is in
normally-opened position and `OUT` is floating. When the button is pressed, `OUT` goes to
ground.

Therefore, on the MCU side, the pin needs to be configured in pull-up mode. The value
read for the GPIO is then inverted, and inversion must be done in software.

The `Button` class takes care of all those constraints automatically.

The Daisy Seed has a total of 31 GPIOs, only 12 of which are analog, so it is better to use
a non-analog GPIO to leave room for blocks which require an analog GPIO, such as
`cv-in` or `pot`.


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).


## BOM

This block uses a
[switch](https://www.digikey.de/product-detail/en/e-switch/TL1105SPF250Q/EG1862-ND/271559)
which would be fitted to a
[cap](https://www.digikey.de/product-detail/en/e-switch/1RBLK/EG1882-ND/271579)
in the final design.


## Generating Production Files

The gerber files and the BOM in `csv` format can be produced by running the block `build.py`
script. It requires to be launched with the Python KiCad bundled executable.
The files are generated in the `artifacts` block directory.

When using macOS and KiCad is installed in the usual `/Applications` directory, the
`build.py` script can be runned directly from the shell, as the shebang line will automatically
select the right version of Python to run.


## Implementation

The button will bounce when pressing or releasing the button. The signal as seen by the GPIO
looks like the following oscilloscope capture.

<img src="https://www.eejournal.com/wp-content/uploads/2020/01/MM-200122-912x912.png" width="490">

> Oscilloscope capture
> [by Max Maxfield for EE Journal](https://www.eejournal.com/article/ultimate-guide-to-switch-debounce-part-1/).

The signal needs to be "debounced", and a sliding window debounce algorithm was
implemented. It is adapted from the
[Mutable Instruments Tides switch driver](https://github.com/pichenettes/eurorack/blob/master/tides2/drivers/switches.cc#L66).
