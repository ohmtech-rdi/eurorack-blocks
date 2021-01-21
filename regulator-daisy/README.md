# regulator-daisy

## Description

This block is a simple voltage regulator aim to power the Daisy Seed.

It is adapted from the [Mutable Instruments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).


## Usage

This block provides voltage regulation for the Daisy Seed input voltage. It delivers +5V and
up to 500mA.

### Power

This module needs to be connected to the `GND` and `+12R` lines from the `power-bus` module.

> Note this is the `+12R` line, **not** the `+12V` line of the `power-bus` module.

Then its `GND` needs to be connected to **both** `DGND` (Pin 40) and `AGND` (Pin 20) of the
Daisy Seed.

> ⚠️ Not connecting `DGND` to `AGND` on the Daisy Seed [may destroy it](https://forum.electro-smith.com/t/externally-powering-the-seed/826). 

Finally the `+5VD` line needs to be connected to the Daisy Seed `VIN` (Pin 39).

see
[Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details.


## Design

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
