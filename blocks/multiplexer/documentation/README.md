# multiplexer

## Description

This block allows to multiplex up to 8 `pot` or `trim` values into a single value.
Its design is detailed [here](./design.md).


## Overview

The number of actual Analog GPIOs on an MCU is always very limited, and one can quickly
have more controls and CVs on their panel than the number of available Analog GPIOs.

Multiplexing multiple signals to one signal allows to overcome this problem, at the expense
of a slower reading rate. Therefore it is suited for slowly varying signals such as the ones
delivered by a potentiometer.

This block provides up to 8 signals multiplexing. Reading a particular input is done
by putting the address of the input as a number expressed in binary.

Since 1 Analog GPIO is needed for the signal, 3 General GPIOs for the address, to reach a total
of 8 inputs, when a traditional MCU has far more General GPIOs than analog GPIOs.

Multiple `multiplexer` can be used, for example for a module with 8 parameters,
one `multiplexer` for the 8 `pot`, and another for the 8 attenuverter `trim`.
In that case, note that the same 3 GPIO outputs address can be reused for both multiplexers.

Conversely, not all pins of the multiplexer needs to be read if not needed. If less than 4 pots
are needed, then just the A and B part of the address can be used.


## Using

```c++
struct Example
{
   Module module;
   Multiplexer multiplexer (
      module, AdcPin0,                       // 1.
      Pin23, Pin24, Pin25                    // 2.
   );
   
   Pot pot1 (multiplexer, MultiplexerPin0);  // 3.
   ...
   Pot pot8 (multiplexer, MultiplexerPin7);

   void process () {
      float pot1_value = pot1;               // 4.
      ...
      float pot8_value = pot8;
   }
}
```

1. Attach the multiplexer to the module and specify the same analog pin
   as the one used for connecting,
2. And specify the same digitals pins as the one used for connecting,
3. Attach the pot to the multiplexer and specify the same analog pin
   as the one used for connecting,
4. Retrieve the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point pot value.

The `Multiplexer` class reference is available [here](./reference.md).
