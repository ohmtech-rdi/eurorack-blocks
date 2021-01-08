# Design

This design is adapted from the
[Daisy Patch schematics](https://github.com/electro-smith/Hardware/blob/master/reference/daisy_patch/ES_Daisy_Patch_Rev4.pdf),
except the op-amp second stage is left floating when no jack is connected,
as in [Mutable Instruments Warps design](https://mutable-instruments.net/modules/warps/downloads/warps_v30.pdf).


## Schematic

### Overview

This block provides a standard eurorack jack connector that is used for eurorack analog
audio output signals.

The block is an output active amplifier and low-pass filter that adapts to the
[AK4556 onboard codec design](https://www.akm.com/content/dam/documents/products/audio/audio-codec/ak4556vt/ak4556vt-en-datasheet.pdf).

<p align="center"><img src="./schematic.png"></p>

### Codec Output

The daisy seed board has already a 10µF capacitor at the codec input as recommended by the
[AK4556 codec datasheet system design](https://www.akm.com/content/dam/documents/products/audio/audio-codec/ak4556vt/ak4556vt-en-datasheet.pdf)
in Figure 10, page 19.

On page 20, the datasheet specify that the 10µF AC coupling is required as the codec has a
DC offset of a few mV.

The codec output level is 0.7 × 3.3V = 2.31V as decribed on page 20.

<p align="center"><img src="./daisy-schematic.png"></p>

The Daisy Seed codec output filter is a passive high-pass filter.

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+f_c+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+R_%7B29%7D+C_%7B64%7D%7D+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+%5Ccdot+47%5Ctextrm%7Bk%CE%A9%7D+%5Ccdot+10%5Ctextrm%7B%C2%B5F%7D%7D+%3D+0.34%5Ctextrm%7BHz%7D" 
alt="f_c = \frac{1}{2 \pi R_{29} C_{64}} = \frac{1}{2 \pi \cdot 47\textrm{kΩ} \cdot 10\textrm{µF}} = 0.34\textrm{Hz}">

### First Stage Op-amp

The Op-amp part `U1A` configuration is an inverting low-pass filter.

#### Op-amp Gain

The input signal is amplified by:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+gain+%3D+-%5Cfrac%7BR_2%7D%7BR_1%7D+%3D+-%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D%7D%7B10%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+-10" 
alt="gain = -\frac{R_2}{R_1} = -\frac{100\textrm{kΩ}}{10\textrm{kΩ}} = -10">

Note the gain minus sign which shifts the audio signal phase by 180°.

#### Op-amp Low-pass Filter

The `R2` and `C1` components make a low-pass filter, with a frequency cutoff at:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+f_c+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+R_2+C_1%7D+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+%5Ccdot+100%5Ctextrm%7Bk%CE%A9%7D+%5Ccdot+47%5Ctextrm%7BpF%7D%7D+%3D+34%5Ctextrm%7BkHz%7D" 
alt="f_c = \frac{1}{2 \pi R_2 C_1} = \frac{1}{2 \pi \cdot 100\textrm{kΩ} \cdot 47\textrm{pF}} = 34\textrm{kHz}">

### Second Stage Op-amp

The Op-amp part `U1B` configuration is an inverting low-pass filter.

#### Op-amp Gain

The input signal is amplified by:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+gain+%3D+-%5Cfrac%7BR_4%7D%7BR_3%7D+%3D+-%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D%7D%7B100%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+-1" 
alt="gain = -\frac{R_4}{R_3} = -\frac{100\textrm{kΩ}}{100\textrm{kΩ}} = -1">

Note the gain minus sign which shifts the audio signal phase by 180°.

But because the previous stage was already shifting phase by 180°, there is no total phase shift.

#### Op-amp Low-pass Filter

The `R4` and `C2` components make a low-pass filter, with a frequency cutoff at:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+f_c+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+R_4+C_2%7D+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+%5Ccdot+100%5Ctextrm%7Bk%CE%A9%7D+%5Ccdot+47%5Ctextrm%7BpF%7D%7D+%3D+34%5Ctextrm%7BkHz%7D" 
alt="f_c = \frac{1}{2 \pi R_4 C_2} = \frac{1}{2 \pi \cdot 100\textrm{kΩ} \cdot 47\textrm{pF}} = 34\textrm{kHz}">

### Output

`R5` is the output impedance of 1kΩ. The output is a jack connector `J2`. The signal is left
floating when not used.

Since the total output gain is 10, the output level would be 0.7 × 3.3V × 10 = 23.1V ideally.
However the TL072 will start to clip before that.

When powered with ±12 supply ramp, the [TL072](https://www.ti.com/lit/ds/symlink/tl072.pdf)
common-mode voltage range
V<sub>CM</sub> is –12V + 4V = –8V to 12V, as described in the datasheet
on page 11 Section 6.6.

To stay within limits, and follow the eurorack electrical standard, the software implementation
adjusts the gain so that the bipolar range from `-1.f` to `1.f` maps
to the eurorack standard level ±5V.

The gain value is:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+gain+%3D+%5Cfrac%7B10%5Ctextrm%7BV%7D%7D%7B23.1%5Ctextrm%7BV%7D%7D+%3D+0.433" 
alt="gain = \frac{10\textrm{V}}{23.1\textrm{V}} = 0.433">

This is equivalent to a 7.3dB loss of dynamic, which is acceptable.

### Transfer Function

For reference, the total transfer function, accounting for the Daisy seed passive filter and
this block active filter has the following gain response:

<p align="center"><img src="./filter-gain.png"></p>

> [Filter analysis](./filter-analysis/) made with ngspice in Kicad
> using [Texas Instruments TL072 PSpice model](https://www.ti.com/product/TL072).

### Op-amp Bypass & Bulk Capacitor

The capacitors `C3` and `C4` are 100nF bypass capacitors as recommended on page 43 of the datasheet.

The 22µF bulk capacitors are provided by the `power-bus` block.
Theirs values are way above the minimum recommended 1µF, and is shared between blocks.


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).

The bypass capacitors `C3` and `C4` are placed 1mm from `U1`
as close as possible to the power supplies as recommended by the
[TL072 datasheet](https://www.ti.com/lit/ds/symlink/tl072.pdf)
on page 43.


## BOM

### Maximum Resistors Power

| Reference | Value | Power |
| - | - | - |
| `R1` | 10kΩ | 100mW |
| `R2` | 100kΩ |  100mW |
| `R3` | 100kΩ |  100mW |
| `R4` | 100kΩ |  100mW |
| `R5` | 1kΩ |  100mW |

#### `R1`

The maximum power of `R1`, with the maximum codec output is:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+P_%7BR_1%7D+%3D+%5Cfrac%7B2.31%5Ctextrm%7BV%7D%5E2%7D%7B10%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+533%5Ctextrm%7B%C2%B5W%7D" 
alt="P_{R_1} = \frac{2.31\textrm{V}^2}{10\textrm{kΩ}} = 533\textrm{µW}">

Which is way below its rated 100mW.

#### `R2`, `R3` & `R4`

The maximum power of `R4`, with the maximum codec output is:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+P_%7BR_2%7D+%3D+P_%7BR_3%7D+%3D+P_%7BR_4%7D+%3D+%5Cfrac%7B23.1%5Ctextrm%7BV%7D%5E2%7D%7B100%5Ctextrm%7Bk%CE%A9%7D%7D+%3D+5.3%5Ctextrm%7BmW%7D" 
alt="P_{R_2} = P_{R_3} = P_{R_4} = \frac{23.1\textrm{V}^2}{100\textrm{kΩ}} = 5.3\textrm{mW}">

Which is way below its rated 100mW.

### Maximum Capacitors Rated Voltage

| Reference | Value | Rated Voltage |
| - | - | - |
| `C1` | 47pF | 25V |
| `C2` | 47pF | 25V |
| `C3` | 100nF |  25V |
| `C4` | 100nF |  25V |

#### `C1`

`C1` sees at most 23.1V × 0.5 = 11.55V, which is below half of its 25V rated voltage.

#### `C2`

`C1` sees at most 23.1V × 0.5 = 11.55V, which is below half of its 25V rated voltage.

#### `C3` & `C4`

`C3` & `C4` see 12V, which is below half of its 25V rated voltage.

### Worst Case Tolerance Deviation Impact

#### Gain Stage

| Reference | Value | Tolerance |
| - | - | - |
| `R1` | 10kΩ | 1% |
| `R2` | 100kΩ |  1% |
| `R3` | 100kΩ |  1% |
| `R4` | 100kΩ |  1% |

Worst minimum case:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+gain+%3D+%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D-1%5C%25%7D%7B10%5Ctextrm%7Bk%CE%A9%7D+%2B+1%5C%25%7D+%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D-1%5C%25%7D%7B100%5Ctextrm%7Bk%CE%A9%7D+%2B+1%5C%25%7D+%3D+9.8+%5Ccdot+0.98+%3D+9.6" 
alt="gain = \frac{100\textrm{kΩ}-1\%}{10\textrm{kΩ} + 1\%} \frac{100\textrm{kΩ}-1\%}{100\textrm{kΩ} + 1\%} = 9.8 \cdot 0.98 = 9.6">

Worst maximum case:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+gain+%3D+%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D%2B1%5C%25%7D%7B10%5Ctextrm%7Bk%CE%A9%7D+-+1%5C%25%7D+%5Cfrac%7B100%5Ctextrm%7Bk%CE%A9%7D%2B1%5C%25%7D%7B100%5Ctextrm%7Bk%CE%A9%7D+-+1%5C%25%7D+%3D+10.2+%5Ccdot+1.02+%3D+10.4" 
alt="gain = \frac{100\textrm{kΩ}+1\%}{10\textrm{kΩ} - 1\%} \frac{100\textrm{kΩ}+1\%}{100\textrm{kΩ} - 1\%} = 10.2 \cdot 1.02 = 10.4">

Both cases are in acceptable limits.

#### First & Second Stage Low-pass Filter

| Reference | Value | Tolerance |
| - | - | - |
| `R2` | 100kΩ | 1% |
| `C1` | 47pF | 5% |
| `R4` | 100kΩ | 1% |
| `C2` | 47pF | 5% |

The two stages share the same low-pass filter configuration.

Worst minimum case:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+f_c+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+R_2+C_1%7D+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+%5Ccdot+%28100%5Ctextrm%7Bk%CE%A9%7D%2B1%5C%25%29+%5Ccdot+%2847%5Ctextrm%7BpF%7D%2B5%5C%25%29%7D+%3D+31.9%5Ctextrm%7BkHz%7D" 
alt="f_c = \frac{1}{2 \pi R_2 C_1} = \frac{1}{2 \pi \cdot (100\textrm{kΩ}+1\%) \cdot (47\textrm{pF}+5\%)} = 31.9\textrm{kHz}">

Worst maximum case:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+f_c+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+R_2+C_1%7D+%3D+%5Cfrac%7B1%7D%7B2+%5Cpi+%5Ccdot+%28100%5Ctextrm%7Bk%CE%A9%7D-1%5C%25%29+%5Ccdot+%2847%5Ctextrm%7BpF%7D-5%5C%25%29%7D+%3D+36%5Ctextrm%7BkHz%7D" 
alt="f_c = \frac{1}{2 \pi R_2 C_1} = \frac{1}{2 \pi \cdot (100\textrm{kΩ}-1\%) \cdot (47\textrm{pF}-5\%)} = 36\textrm{kHz}">

Both cases are in acceptable limits.


## Generating Production Files

The gerber files and the BOM in `csv` format can be produced by running the block `build.py`
script. It requires to be launched with the Python KiCad bundled executable.
The files are generated in the `artifacts` block directory.

When using macOS and KiCad is installed in the usual `/Applications` directory, the
`build.py` script can be runned directly from the shell, as the shebang line will automatically
select the right version of Python to run.

> Math formulas made with [Masaki AOTA's Tex image link generator](https://tex-image-link-generator.herokuapp.com).
