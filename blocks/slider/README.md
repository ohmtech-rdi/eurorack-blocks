# slider

## Description

This block is a simple potentiometer and LED in a slider form factor.

It is adapted from the [Mutable Instuments Stages schematics](https://mutable-instruments.net/modules/stages/downloads/stages_v70.pdf).


## Soldering

Pin headers don't come with just one position. Instead of that, the BOM has 2-position
pin male headers that need to be broke into 2 pieces.


## Usage

This block provides a silder potentiometer with a red LED.

### Power

This modules needs to be connected to the `3V3A` and `GND` lines from the power block.

> On Daisy Seed, use the 3V3 Analog Power I/O on Pin 21, *not* the digital power.

All `GND` pins are internally connected in the block.

### Signal

The signal `IN` drives the LED. It should be connected to any GPIO of the
target MCU, **preferably non-analog** GPIOs.

The signal `OUT` is the potentiometer value. It should be connected to any Analog GPIO of the
target MCU.

When using Daisy Seed as a development platform, see
[its pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details. The Daisy Seed has a total of 31 GPIOs, only 12 of which are analog.


## Design

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
