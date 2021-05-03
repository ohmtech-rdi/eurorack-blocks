# Kivu12

`kivu12` is a board used for 12HP modules.


## Overview

<img align="right" width="20%" src="./render.png">

The 12HP `kivu12` board is designed to host, at the bottom of the module,
12 standard Eurorack 3.5mm jacks  connectors, and/or trimmer potentiometers typically used
to represent attenuverters, distributed into 3 rows.

The rest of the module UI then goes at the top. The pin headers layout on the left and right side
don't allow to place small UI controls too close to the border. The pin header on the top doesn't
allow to place jack connectors, as it is typically done in sequencer modules.

All it's CV inputs are made for common CV levels, but for pitch or ADSR, it is possible to
adapt those to their specific Eurorack levels (0 to 10V and 0 to 8V respectively).
2 jumpers allow to select which mode to use for the first two CV inputs.

The board also provides a miniSD card slot to emulate an
[eMMC](https://en.wikipedia.org/wiki/MultiMediaCard#eMMC), typically used to store
factory samples. The miniSD format allows however to easily remove the miniSD card to change
its content conveniently on your computer with a simple miniSD card reader.

One can also put a miniSD card slot on the front of the module. A set of jumpers select which
miniSD connector (front board or back board) is used.

The MIDI input supports both [TRS MIDI Type A and B](https://minimidi.world/#trs-connections).
A set of jumpers allow to select either Type A or B.

Finally, some predefined user interface design [templates](#templates) are provided below.


## Specifications

<img align="right" width="20%" src="./xray.png">

The Board provide the following features:

- 12 HP,
- 12 Pots/Trims/Sliders `P1..P12`,
- 20 Led pins `L1..L20`,
- miniSD or "emulated eMMC" selectable with jumpers:
   - Either a regular front panel miniSD card connector,
   - Or a miniSD card connector on the back board, acting as if it was a eMMC, but easier to reprogram
- 20 Buttons/Gates In/Switches pins `B1..B20`,
- 1 MIDI In  `MIR` (ring) `MIT` (tip), with TRS Type A or B selectable with jumpers,
- 1 MIDI Out   `MOR` (ring) `MOT` (tip),
- 2 Gate Out `GO1..GO2`,
- 8 CV In `CI1..CI8`:
   - Either with ±5V levels,
   - Or 2 (CI1 and CI2) with optional 0..10V levels, selectable with a jumper, to support CV Pitch and ADSR
- 2 CV Out ±5V `CO1..CO2`,
- 2 Audio In ±5V `AI1..AI2`,
- 2 Audio Out ±5V `AO1..AO2`.


## Templates

The following templates are available:

<img align="right" width="10%" src="./templates/auria.png">

By default, [`auria`](./templates/auria.erbui) has 4 CV inputs, 2 Audio In, 2 Audio out, 4 attenuverters and 4 knobs.
