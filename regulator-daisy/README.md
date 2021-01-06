# regulator-daisy

## Description

This block is a simple voltage regulator aim to power the Daisy Seed.
Its design is detailed [here](./documentation/design.md).


## Connecting

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally,
- This block needs its `+12R` to be connected to the `+12R` of the `power-bus`,
- The pin `+5VD` is the regulated output.
   It needs to be connected to the Daisy Seed `VIN` (Pin 39)
   See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.

The Daisy Seed `DGND` (Pin 40) needs to be connected to `AGND` (Pin 20). Both needs to
be connected to `GND`.

> ⚠️ Not connecting `DGND` to `AGND` on the Daisy Seed [may **destroy it**](https://forum.electro-smith.com/t/externally-powering-the-seed/826) ⚠️ 
