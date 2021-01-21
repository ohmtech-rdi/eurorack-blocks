# gate-in

## Description

This block is a simple 3V3 gate input.

It is adapted from the [Mutable Instruments Marbles schematics](https://mutable-instruments.net/modules/marbles/downloads/marbles_v70.pdf).


## Usage

This block provides a standard eurorack jack connector that is used for eurorack gate input
+5V signals.

### Power

This module needs to be connected to the `3V3D` and `GND` lines from the power block.

> When using Daisy Seed, use the 3V3 Digital Power I/O on Pin 38, *not* the analog power. 

All `GND` pins are internally connected in the block.

### Signal

The signal `OUT` is the gate signal. It should be connected to any GPIO of the target MCU,
**preferably non-analog** GPIOs.

When using Daisy Seed as a development platform, see
[its pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details. The Daisy Seed has a total of 31 GPIOs, only 12 of which are analog.

### Jack detection

When the jack is connected, the signal send on `NOP` will flow through the components
and reach `OUT`. This can be used to detect if a jack is present by sending a random
signal on `NOP` and correlating it with `OUT` in software.

This method is used often in Mutable Instruments modules and is explained
[here](https://forum.mutable-instruments.net/t/plaits-normalization-probe/14358/2).
Its implementation can be found
[here](https://github.com/pichenettes/eurorack/blob/master/plaits/ui.cc#L368).

Jack detection allows, from a user experience point of view, to dissociate a non-connected
jack from a connected jack at `GND` level.

If this feature is not required, connect `NOP` to `GND`.


## Design

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
