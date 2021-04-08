# Design

This design is adapted from the
[Mutable Instruments Marbles schematics](https://mutable-instruments.net/modules/marbles/downloads/marbles_v70.pdf).


## Schematic

### Overview

This block provides a standard eurorack jack connector that is used for eurorack analog
gate input signals.
Because of the [range of possible signals](http://www.doepfer.de/a100_man/a100t_e.htm),
this module is designed to take a ±12V range to cover every possible cases.

The block is a NPN transistor that adapts to the 3V3 MCU Digital GPIOs.

<p align="center"><img src="./schematic.png"></p>

### Input

The input is a jack connector `J1`. When the jack connector is not connected, the signal
from `NOP` is the input.

The direct output `DI` allows to cascade the connector signal to another `gate-in` block.

### Input Impedance

When the input signal is positive, the input has a 200kΩ impedance. When the input signal
is negative, the diode `D1` shorts, making a 100kΩ impedance. In all cases the input
impedance is equal or greater to 100kΩ.

### Transistor Base Voltage

The transistor base is fed by a tension divider when tension is positive:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+V_%7BBASE%7D+%3D+V_%7BIN%7D+%5Cfrac%7BR_2%7D%7BR_1%2BR_2%7D+%3D+V_%7BIN%7D+%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D%7D%7B100%5Ctextrm%7Bk%CE%A9%7D%2B100%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+%5Cfrac%7BV_%7BIN%7D%7D%7B2%7D%0A" 
alt="V_{BASE} = V_{IN} \frac{R_2}{R_1+R_2} = V_{IN} \frac{100\textrm{kΩ}}{100\textrm{kΩ}+100\textrm{kΩ}} = \frac{V_{IN}}{2}
">

If the input level is +5V as a usual gate level, the base voltage will be +2.5V.

At +12V, the tension between the base and the collector is 8.7V, which is way smaller than
the 60V collector – base breakdown voltage, as seen in the
[MMBT3904 datasheet](https://www.onsemi.com/pub/Collateral/MMBT3904LT1-D.PDF)
on page 2.

If the tension is negative, the diode `D1` will short `R2`, so that the base voltage is 0V. In the
case of an incorrect –12V input, this prevents to reach –6V on the base, which is the
V<sub>(BR)EBO</sub> reverse breakdown voltage of the base-emitter junction as seen
in the [MMBT3904 datasheet](https://www.onsemi.com/pub/Collateral/MMBT3904LT1-D.PDF)
on page 2.

For a continuous +12V tension, the voltage is far below the 75V peak repetitive reverse voltage
of the [1N4148](https://www.diodes.com/assets/Datasheets/ds12019.pdf) as seen on page 1
of its datasheet.

For a continuous –12V tension, the current flowing through the diode is at maximum:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+I_%7BD_1%7D+%3D+%5Cfrac%7B12%5Ctextrm%7BV%7D%7D%7BR_1%7D+%3D+%5Cfrac%7B12%5Ctextrm%7BV%7D%7D%7B100%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+120%5Ctextrm%7B%C2%B5A%7D" 
alt="I_{D_1} = \frac{12\textrm{V}}{R_1} = \frac{12\textrm{V}}{100\textrm{kΩ}} = 120\textrm{µA}">

Which is well below its 300mA forward continuous current as seen on page 1 on its datasheet.

### Transistor Collector Voltage

When the base voltage is +2.5V, the transistor will saturate as the voltage is higher than
V<sub>BE(sat)</sub> as seen in the
[MMBT3904 datasheet](https://www.onsemi.com/pub/Collateral/MMBT3904LT1-D.PDF)
on page 2, the transistor will behave like a closed switch and `OUT` will be very near `GND` level,
more precisely at V<sub>CE(sat)</sub>.
The resistance `R3` is run through by the current:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+I_%7BR_3%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_%7B%5Ctextrm%7BCE%28sat%29%7D%7D%7D%7BR_3%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+0.2%5Ctextrm%7BV%7D%7D%7B10%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+310%5Ctextrm%7B%C2%B5A%7D" 
alt="I_{R_3} = \frac{3.3\textrm{V} - V_{\textrm{CE(sat)}}}{R_3} = \frac{3.3\textrm{V} - 0.2\textrm{V}}{10\textrm{kΩ}} = 310\textrm{µA}">

When the base voltage is 0V, the transistor will behave like an open switch,
and `OUT` will be near `3V3D` level (the collector cutoff current is at most 50nA),
and the `R3` resistor acts as a pull-up resistor.

Finally, if the input is not connected and `NOP` is floating, `R2` ensures that the base voltage
is 0V.

### Software Implementation Considerations

Because the signal `OUT` is inverted, it needs to be inverted in software.

The `GateIn` class takes care of all those constraints automatically.


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).


## BOM

### Maximum Resistors Power

| Reference | Value | Power |
| - | - | - |
| `R1` | 100kΩ | 100mW |
| `R2` | 100kΩ |  100mW |
| `R3` | 10kΩ |  100mW |

#### `R1` & `R2`

The maximum power of `R1` and `R2`, with the absolute 12V eurorack limit is:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+I_%7BR_1%7D+%3D+I_%7BR_2%7D+%3D+%5Cfrac%7B12%5Ctextrm%7BV%7D%7D%7BR_1+%2B+R_2%7D+%3D+%5Cfrac%7B12%5Ctextrm%7BV%7D%7D%7B200%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+60%5Ctextrm%7B%C2%B5A%7D%0A" 
alt="I_{R_1} = I_{R_2} = \frac{12\textrm{V}}{R_1 + R_2} = \frac{12\textrm{V}}{200\textrm{kΩ}} = 60\textrm{µA}
">

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+P_%7BR_1%7D+%3D+P_%7BR_2%7D+%3D+12%5Ctextrm%7BV%7D+%5Ccdot+I_%7BR_1%7D+%3D+12%5Ctextrm%7BV%7D+%5Ccdot+60%5Ctextrm%7B%C2%B5A%7D+%3D+720%5Ctextrm%7B%C2%B5W%7D" 
alt="P_{R_1} = P_{R_2} = 12\textrm{V} \cdot I_{R_1} = 12\textrm{V} \cdot 60\textrm{µA} = 720\textrm{µW}">

Which is way below their rated 100mW.

#### `R3`

When the base voltage is 0V,
the current flowing through `R3` is the Input leakage current as shown on page 129, table 58
of the Daisy Seed [STM32H750IB](https://www.st.com/resource/en/datasheet/stm32h750ib.pdf)
MCU datasheet.

For both Three-volt Tolerant (TT) and Five-volt Tolerant (FT) input pins, the maximum current
is 250nA.

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+P_%7BR_3%7D+%3D+3.3%5Ctextrm%7BV%7D+%5Ccdot+250%5Ctextrm%7BnA%7D+%3D+825nW" 
alt="P_{R_3} = 3.3\textrm{V} \cdot 250\textrm{nA} = 825nW">

When the base voltage is 2.5V,
the `R3` power is:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+P_%7BR_3%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D%5E2%7D%7B10%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+1.09%5Ctextrm%7BmW%7D" 
alt="P_{R_3} = \frac{3.3\textrm{V}^2}{10\textrm{kΩ}} = 1.09\textrm{mW}">

Which are both far below its rated 100mW.

## Generating Production Files

The gerber files and the BOM in `csv` format can be produced by running the block `build.py`
script. It requires to be launched with the Python KiCad bundled executable.
The files are generated in the `artifacts` block directory.

When using macOS and KiCad is installed in the usual `/Applications` directory, the
`build.py` script can be runned directly from the shell, as the shebang line will automatically
select the right version of Python to run.


## Implementation

The GPIO is configured as an input, with no pull resistor, as the external resistor `R3` already
provides a pull-up resistor.

The GPIO is read with the `libDaisy` `dsy_gpio_read` function.

The class `GateIn` offers two read modes:
- A trigger mode which acts as a rising edge detector,
- A gate mode which just read the GPIO value.

> Math formulas made with [Masaki AOTA's Tex image link generator](https://tex-image-link-generator.herokuapp.com).
