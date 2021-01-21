# Design

This design is adapted from the [Mutable Instuments Frames schematics](https://mutable-instruments.net/modules/frames/downloads/frames_v03.pdf).

## Schematic

<p align="center"><img src="./schematic.png"></p>

Given the forward voltage V<sub>f</sub> and the forward current I<sub>f</sub>,
the resistor `R1` value is:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+R_1+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_f%7D%7BI_f%7D" 
alt="R_1 = \frac{3.3\textrm{V} - V_f}{I_f}">

The relation between the forward voltage and the forward current is deduced from page 3 of the
[WP710A10GD datasheet](https://www.kingbrightusa.com/images/catalog/SPEC/WP710A10GD.pdf),
only considering its linear part starting at 1.9V:
- V<sub>f</sub> = 1.9V when  I<sub>f</sub> = 2mA
- V<sub>f</sub> = 2.1V when  I<sub>f</sub> = 14mA

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+V_f+%3D+1.9%5Ctextrm%7BV%7D+%2B+%5Cfrac%7B%282.1%5Ctextrm%7BV%7D-1.9%5Ctextrm%7BV%7D%29+%5Ccdot+%28I_f+-+2%5Ctextrm%7BmA%7D%29%7D%7B14%5Ctextrm%7BmA%7D-2%5Ctextrm%7BmA%7D%7D" 
alt="V_f = 1.9\textrm{V} + \frac{(2.1\textrm{V}-1.9\textrm{V}) \cdot (I_f - 2\textrm{mA})}{14\textrm{mA}-2\textrm{mA}}">

Expressing the forward current I<sub>f</sub> as a function of the resistor `R1`:

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Barray%7D%7Bl%7D%0AR_1+%5Ccdot+I_f+%3D+3.3%5Ctextrm%7BV%7D+-+V_f+%5C%5C%0AR_1+%5Ccdot+I_f+%3D+3.3%5Ctextrm%7BV%7D+-+%5Cleft%28+1.9%5Ctextrm%7BV%7D+%2B+%5Cfrac%7B%282.1%5Ctextrm%7BV%7D-1.9%5Ctextrm%7BV%7D%29+%5Ccdot+%28I_f+-+2%5Ctextrm%7BmA%7D%29%7D%7B14%5Ctextrm%7BmA%7D-2%5Ctextrm%7BmA%7D%7D+%5Cright%29+%5C%5C%0A%28R_1+%2B+16.66%5Ctextrm%7B%CE%A9%7D%29+%5Ccdot+I_f+%3D+1.4%5Ctextrm%7BV%7D+%2B+0.033%5Ctextrm%7BV%7D+%5C%5C%0AI_f+%3D+%5Cfrac%7B1.433%5Ctextrm%7BV%7D%7D%7BR_1+%2B+16.66%5Ctextrm%7B%CE%A9%7D%7D+%5C%5C%0A%5Cend%7Barray%7D" 
alt="\begin{array}{l}
R_1 \cdot I_f = 3.3\textrm{V} - V_f \\
R_1 \cdot I_f = 3.3\textrm{V} - \left( 1.9\textrm{V} + \frac{(2.1\textrm{V}-1.9\textrm{V}) \cdot (I_f - 2\textrm{mA})}{14\textrm{mA}-2\textrm{mA}} \right) \\
(R_1 + 16.66\textrm{Ω}) \cdot I_f = 1.4\textrm{V} + 0.033\textrm{V} \\
I_f = \frac{1.433\textrm{V}}{R_1 + 16.66\textrm{Ω}} \\
\end{array}">

Which gives the following values of forward current depending on the resistor:

| Forward current I<sub>f</sub> | Resistor `R1` |
| - | - |
| 12.28mA | 100Ω |
| 9.7mA | 130Ω |

With a 100Ω resistor, and using the graph on page 3 giving the relation between the relative
luminosity and forward current, the luminosity is around 1.2 × 25mcd = 30mcd.

30mcd offers a good balance to achieve enough contrast in daylight, and not being to
bright in the dark.

The maximum forward voltage of 2.4V as described on page 2, is still below the 3.3V power
supply.


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).


## BOM

This block comes with a
[green LED](https://www.digikey.de/product-detail/en/kingbright/WP710A10GD/754-1603-ND/2769808),
but alternative colors might be used, such as:
- [Red](https://www.digikey.de/product-detail/en/kingbright/WP710A10ID/754-1606-ND/2769809),
- [Yellow](https://www.digikey.de/product-detail/en/kingbright/WP710A10YD/754-1602-ND/2769824),
- [Orange](https://www.digikey.de/product-detail/en/kingbright/WP710A10ND/754-1892-ND/3084190).

Those LEDs have different forward current to voltage relations, so the associated resistance
needs to be adapted.

The values below are targetting 30mcd, noting that
[Candela](https://en.wikipedia.org/wiki/Candela) is a photometric unit.

| Manufacturer Part Number | Lens Color | Resistor Value |
| - | - | - |
| WP710A10GD | Green | 130Ω |
| WP710A10ID | Red | 130Ω |
| WP710A10YD | Yellow | 60Ω |
| WP710A10ND | Orange | 135Ω |

### WP710A10ID Red Resistor Value

Following the
[WP710A10ID](https://www.kingbrightusa.com/images/catalog/SPEC/WP710A10ID.pdf)
datasheet:
- 30mcd is achieved with a 10mA forward current,
- At 10mA, the forward voltage is 2V

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+R_1+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_f%7D%7BI_f%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+2%5Ctextrm%7BV%7D%7D%7B10%5Ctextrm%7BmA%7D%7D+%3D+130%5Ctextrm%7B%CE%A9%7D" 
alt="R_1 = \frac{3.3\textrm{V} - V_f}{I_f} = \frac{3.3\textrm{V} - 2\textrm{V}}{10\textrm{mA}} = 130\textrm{Ω}">

### WP710A10YD Yellow Resistor Value

Following the
[WP710A10YD](https://www.kingbrightusa.com/images/catalog/SPEC/WP710A10YD.pdf)
datasheet:
- 30mcd is achieved with a 20mA forward current,
- At 20mA, the forward voltage is 2.1V

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+R_1+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_f%7D%7BI_f%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+2.1%5Ctextrm%7BV%7D%7D%7B20%5Ctextrm%7BmA%7D%7D+%3D+60%5Ctextrm%7B%CE%A9%7D" 
alt="R_1 = \frac{3.3\textrm{V} - V_f}{I_f} = \frac{3.3\textrm{V} - 2.1\textrm{V}}{20\textrm{mA}} = 60\textrm{Ω}">

### WP710A10ND Orange Resistor Value

Following the
[WP710A10ND](https://www.kingbrightusa.com/images/catalog/SPEC/WP710A10ND.pdf)
datasheet:
- 30mcd is achieved with a 10mA forward current,
- At 10mA, the forward voltage is 1.95V

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+R_1+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_f%7D%7BI_f%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+1.95%5Ctextrm%7BV%7D%7D%7B10%5Ctextrm%7BmA%7D%7D+%3D+135%5Ctextrm%7B%CE%A9%7D" 
alt="R_1 = \frac{3.3\textrm{V} - V_f}{I_f} = \frac{3.3\textrm{V} - 1.95\textrm{V}}{10\textrm{mA}} = 135\textrm{Ω}">

### Spacer

When producing the final module, a spacer such as the
[Keystone 8910](https://www.digikey.de/product-detail/en/keystone-electronics/8910/36-8910-ND/317202)
with a 7.62mm length can be used.


## Generating Production Files

The gerber files and the BOM in `csv` format can be produced by running the block `build.py`
script. It requires to be launched with the Python KiCad bundled executable.
The files are generated in the `artifacts` block directory.

When using macOS and KiCad is installed in the usual `/Applications` directory, the
`build.py` script can be runned directly from the shell, as the shebang line will automatically
select the right version of Python to run.

> Math formulas made with [Masaki AOTA's Tex image link generator](https://tex-image-link-generator.herokuapp.com).
