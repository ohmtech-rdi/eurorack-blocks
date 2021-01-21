# switch

## Description

This block is a simple switch. It can be used with 2 or 3 positions switches.


## Usage

This block provides a switch compatible with
[SPDT](https://en.wikipedia.org/wiki/Switch#Contact_terminology) On-On or On-Off-On.

It uses two GPIOs for each On state. In the case of the 3 position switch, the Off position
is detected when the two other GPIOs are low.

### Power

This module needs to be connected to the `3V3D` and `GND` lines from the power block.

> On Daisy Seed, use the 3V3 Digital Power on Pin 38, *not* the analog power. 

All `GND` pins are internally connected in the block.

### Signal

The signals `OUT0` and `OUT1` are the switch signal. It should be connected to any GPIO of the
target MCU, **preferably non-analog** GPIOs.

Those two pins will need to be **configured in pull-down mode** in software.

When using Daisy Seed as a development platform, see
[its pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details. The Daisy Seed has a total of 31 GPIOs, only 12 of which are analog.


## Design

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
