# power-bus

## Description

This block is a simple eurorack power bus connector adapter.
It is protected against eurorack connector accidental polarity inversion.

It is adapted from the [Mutable Instuments Tides schematics](https://mutable-instruments.net/modules/tides/downloads/tides_v40.pdf).


## Usage

This block provides:
- The 3 standard `+12V`, `GND`, `–12V` lines, to typically power the audio op-amps,
   such as `audio-in-daisy` or `audio-out-daisy`,
- A rectified +12V line, named `+12R`, suitable for use with subsequent power regulators,
   such as `regulator-daisy`.


## Design

The `+12V` and `-12V` are protected against potential digital switching noise from other
eurorack modules in the system using ferrite beads.

In contrast, the `+12R` is only rectified against accidental polarity inversion, but not against
noise. It is expected that this line would be connected to a linear voltage regulator, such
as the one in `regulator-daisy`, which are very good at preventing noise to flow back
into the circuit.
The implicit star configuration is going to prevent that when prototyping with those blocks.
But care needs to be taken for return currents in the `GND` plane when designing the module
PCB.


<img src="./documentation/top.svg" width="490"> <img src="./documentation/bottom.svg" width="490">

> Gerber renders made with [tracespace view](https://tracespace.io/view/).
