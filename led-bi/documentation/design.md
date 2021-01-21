# Design

This design is adapted from the Mutable Instuments
[Frames](https://mutable-instruments.net/modules/frames/downloads/frames_v03.pdf) and
[Tides](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf) and
schematics.

## Schematic

This block provides a two-color red/green LED.

<p align="center"><img src="./schematic.png"></p>

A general LED analysis is already provided in the [`led` design](../../led/documentation/design.md).

Following the [WP3VEGW datasheet](https://www.kingbrightusa.com/images/catalog/SPEC/WP3VEGW.pdf),
targetting 30mcd gives the following resistor calculation:

### Red LED

- With a nominal 40mcd, the relative luminosity if 0.75 which gives a 15mA forward current,
- At 15mA, the forward voltage is 1.95V 

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+R_1+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_f%7D%7BI_f%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+1.95%5Ctextrm%7BV%7D%7D%7B15%5Ctextrm%7BmA%7D%7D+%3D+90%5Ctextrm%7B%CE%A9%7D" 
alt="R_1 = \frac{3.3\textrm{V} - V_f}{I_f} = \frac{3.3\textrm{V} - 1.95\textrm{V}}{15\textrm{mA}} = 90\textrm{Ω}">

### Green LED

- With a nominal 40mcd, the relative luminosity if 0.75 which gives a 15mA forward current,
- At 15mA, the forward voltage is 2.1V 

<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+R_2+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+V_f%7D%7BI_f%7D+%3D+%5Cfrac%7B3.3%5Ctextrm%7BV%7D+-+2.1%5Ctextrm%7BV%7D%7D%7B15%5Ctextrm%7BmA%7D%7D+%3D+80%5Ctextrm%7B%CE%A9%7D" 
alt="R_2 = \frac{3.3\textrm{V} - V_f}{I_f} = \frac{3.3\textrm{V} - 2.1\textrm{V}}{15\textrm{mA}} = 80\textrm{Ω}">


## PCB Layout

<img src="./top.svg" height="275"> <img src="./bottom.svg" height="275">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).


## BOM

The resistor values `R1` and `R2` are 100Ω instead of their respective calculated values of
90Ω and 80Ω to reduce the number of different components for the pick & place machine
when using PCBA services.

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
