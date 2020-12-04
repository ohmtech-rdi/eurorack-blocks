# audio-out-daisy

## Description

This block is a simple analog audio output active buffer and filter for the
[Daisy Seed](https://www.electro-smith.com/daisy/daisy) onboard codec.

It is adapted from the [Daisy Patch schematics](https://github.com/electro-smith/Hardware/tree/master/reference/daisy_patch),
except the op-amp second stage is left floating when no jack is connected,
as in [Mutable Instruments Warps design](https://mutable-instruments.net/modules/warps/downloads/warps_v30.pdf).


## Usage

This block provides a standard eurorack jack connector that is used for eurorack analog
audio output ±5V signals.

### Power

This modules needs to be connected to the `+12V`, `–12V` and `GND` lines from the eurorack
power bus connector.

All `GND` pins are internally connected in the block.

### Signal

The signal `IN` is the audio output signal from the Daisy Seed onboard
audio codec. It should be connected to either:
- `Audio Out 1` (pin 18),
- or `Audio Out 2` (pin 19).

See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details.


## Design

The daisy seed board has already a 10µF capacitor and 47kΩ resistor at the codec output to
form a passive DC block filter.

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
