# audio-in-daisy

## Description

This block is a simple analog audio input active buffer and filter for the
[Daisy Seed](https://www.electro-smith.com/daisy/daisy) onboard codec.

It is adapted from the [Daisy Patch schematics](https://github.com/electro-smith/Hardware/tree/master/reference/daisy_patch).


## Usage

This block provides a standard eurorack jack connector that is used for eurorack analog
audio input ±5V signals.

### Power

This modules needs to be connected to the `+12V`, `–12V` and `GND` lines from the eurorack
power bus connector.

All `GND` pins are internally connected in the block.

### Signal

The signal `OUT` is the audio input signal filtered and adapted for the Daisy Seed onboard
audio codec. It should be connected to either:
- `Audio In 1` (pin 16),
- or `Audio In 2` (pin 17).

See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details.

### Normalisation pin

When the jack is connected, the signal send on `NOP` will flow through the components
and reach `OUT`. This can be used to:
- Use another input signal, typically duplicating a mono signal to a stereo signal,
- Detect if a jack is present.

The latter is used often in Mutable Instruments modules and is explained
[here](https://forum.mutable-instruments.net/t/plaits-normalization-probe/14358/2).
Its implementation can be found
[here](https://github.com/pichenettes/eurorack/blob/master/plaits/ui.cc#L368).

Jack detection allows, from a user experience point of view, to dissociate a non-connected
jack from a connected jack at `GND` level.

If this feature is not required, connect `NOP` to `GND`.


## Design

The daisy seed board has already a 10µF capacitor at the codec input as recommended by the
[AK4556 codec datasheet system design](https://www.akm.com/content/dam/documents/products/audio/audio-codec/ak4556vt/ak4556vt-en-datasheet.pdf)
in Figure 10, page 19.

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
