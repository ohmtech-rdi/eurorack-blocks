# multiplexer

## Description

This block allows to multiplex up to 8 3V3 value into a single value.

It is adapted from the [Mutable Instuments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).


## Usage

The number of actual Analog GPIOs on an MCU is always very limited, and one can quickly
have more controls and CVs on their panel than the number of available Analog GPIOs.

Multiplexing multiple signals to one signal allows to overcome this problem, at the expense
of a slower reading rate. Therefore it is suited for slowly varying signals such as the ones
delivered by a potentiometer or a button.

This block provides up to 8 3V3 signals multiplexing. Reading a particular input is done
by putting the address of the input as a number expressed in binary.

Since 1 Analog GPIO is needed for the signal, 3 General GPIOs for the address, to reach a total
of 8 inputs, when a traditional MCU has far more General GPIOs than analog GPIOs.

### Power

This modules needs to be connected to the `3V3A` and `GND` lines from the power block.

> On Daisy Seed, use the 3V3 Analog Power I/O on Pin 21, *not* the digital power.

All `GND` pins are internally connected in the block.

### Signals

The signal `OUT` is the mutliplexer output. It should be connected to any Analog GPIO of the
target MCU.

When using Daisy Seed as a development platform, see
[its pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w)
for details.

The signals from `IN0` to `IN7` are the inputs signals which would typically be connected to
a `pot` or `trim` block `OUT`.

Below is the `ADDR` to `IN#` relation table. Note that `C` is the most significant bit.

| IN# | ADDR (CBA) |
| --- | --- |
| IN0 | 000 |
| IN1 | 001 |
| IN2 | 010 |
| IN3 | 011 |
| IN4 | 100 |
| IN5 | 101 |
| IN6 | 110 |
| IN7 | 111 |

Multiple `multiplexer` can be used, for example for a module with 8 parameters,
one `multiplexer` for the 8 `pot`, and another for the 8 attenuverter `trim`.
In that case, note that the same 3 GPIO outputs address can be reused for both multiplexers.

When using a lot of `gate-in`, one could use this multiplexer as well. In that case the
block needs to be connected to the `3V3D` lines from the power block, and preferably a
non-analog GPIO of the target MCU.


## Design

<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
