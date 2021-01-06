# power-bus

## Description

This block is a simple eurorack power bus connector adapter.
Its design is detailed [here](./documentation/design.md).


## Connecting

This block provides:
- The 3 standard `+12V`, `GND`, `–12V` lines, to typically power the audio op-amps,
   such as `audio-in-daisy` or `audio-out-daisy`,
- A rectified +12V line, named `+12R`, suitable for use with subsequent power regulators,
   such as `regulator-daisy`.
