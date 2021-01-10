# multiplexer

## Description

This block allows to multiplex up to 8 `pot` or `trim` values into a single value.
Its design is detailed [here](./documentation/design.md).


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


## Connecting

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally,
- This block needs its `3V3A` to be connected to the Daisy Seed 3V3 Analog Power I/O on Pin 21,
- The signal `OUT` is the multiplexer output. It should be connected to any Analog GPIO of the
   target MCU. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.
- The signals from `IN0` to `IN7` are the inputs signals which would typically be connected to
   a `pot` or `trim` block `OUT`.


## Using

```c++
int main ()
{
   using namespace erb;
   
   Module module;
   Multiplexer mux (
      module, AdcPin6,              // 1.
      Pin23, Pin24, Pin25           // 2.
   );
   
   module.run ([&](){
      for (size_t i = 0 ; i < 8 ; ++i)
      {
         float pot_value = mux [i]; // 3.
      }
   });
}
```

1. Attach the multiplexer to the module and specify the same analog pin
   as the one used for connecting,
2. And specify the same digitals pins as the one used for connecting,
3. Retrieve the normalized (in the `0.f` to `1.f` range) floating-point pot value
   for input `IN` number `i`.

The `Multiplexer` class reference is available [here](./documentation/reference.md).
