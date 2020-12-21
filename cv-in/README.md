# cv-in

## Description

This block is a simple analog CV input active buffer and filter 3V3 MCU Analog GPIOs.

It is adapted from the [Mutable Instuments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).


## Usage

This block provides a standard eurorack jack connector that is used for eurorack analog
CV input signals. Because of the range of possible signals, this module is designed to
take a ±8V range to cover every usage cases.

### Power

This modules needs to be connected to the `3V3A` and `GND` lines from the power block.

> On Daisy Seed, use the 3V3 Analog Power I/O on Pin 21, *not* the digital power.

All `GND` pins are internally connected in the block.

### Signal

The signal `OUT` is the CV input signal. It should be connected to any Analog GPIO of the
target MCU.

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

Each block contains a voltage reference. This decision was made to ease prototyping, as drawing
more current from the voltage reference needs the voltage reference associated resistor to be
adjusted at the right value.

A voltage reference component is relatively an expensive component, so one would just put one
in the final design, with the appropriate resistor value.

Because the signal is inverted, it needs to be **inverted in software**:

```
// Normalised floating point value has seen by the analog GPIO
float cv_inv = my_module.get_cv_value (DaisySeed::Pin15);

// Value as expected by the user
float cv = 1.f - cv_inv;
```

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
