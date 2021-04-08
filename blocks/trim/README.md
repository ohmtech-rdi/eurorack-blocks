# trim

## Description

This block is a simple potentiometer, using a trim pot, typically used for attenuverters.
Its design is detailed [here](./documentation/design.md).


## Connecting

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally,
- This block needs its `3V3A` to be connected to the Daisy Seed 3V3 Analog Power I/O on Pin 21,
- The signal `OUT` is the potentiometer value. It should be connected to any Analog GPIO of the
   target MCU. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.


## Using

```c++
int main ()
{
   using namespace erb;

   Module module;
   Trim trim (module, AdcPin6);  // 1.

   module.run ([&](){
      float trim_value = trim;   // 2.
   });
}
```

1. Attach the trim to the module and specify the same analog pin as the one used for connecting,
2. Retrieve the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point trim value.

The `Trim` type is an alias to the `Pot` class.
The `Pot` class reference is available [here](./../pot/documentation/reference.md).
