# led-bi

## Description

This block is a simple dichromatic green/red LED.

It is adapted from the Mutable Instuments
[Frames](https://mutable-instruments.net/modules/frames/downloads/frames_v03.pdf) and
[Tides](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf) and
schematics.


## Usage

This block provides a two-color LED.

### Power

This block needs to be connected to `GND`.

### Signal

The signal `ING` and `INR` are the LED Red and Green signals.
It should be connected to any GPIO of the target MCU, **preferably non-analog** GPIOs.

When using Daisy Seed as a development platform, see
[its pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details. The Daisy Seed has a total of 31 GPIOs, only 12 of which are analog.


## Design

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
