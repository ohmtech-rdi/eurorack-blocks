# cv-in

## Description

This block is a simple analog CV input.
Its design is detailed [here](./documentation/design.md).


## Connecting

<p align="center"><img src="./documentation/connecting.png" width="100%"></p>

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally,
- This block needs its `-12V` to be connected to the `-12V` of the `power-bus`,
- This block needs its `3V3A` to be connected to the Daisy Seed 3V3 Analog Power I/O on Pin 21,
- The `NOP` pin can be either connected to:
   - `GND` to send (slightly noisy) zeros to the software implementation,
   - Cascading the `DI` signal from another `cv-in` block,
   - A pseudo-random predefined signal to detect a jack connection
      as explained on the Mutable Instruments forums
      [here](https://forum.mutable-instruments.net/t/plaits-normalization-probe/14358/2)
      and implemented
      [here](https://github.com/pichenettes/eurorack/blob/master/plaits/ui.cc#L368).
- The signal `OUT` is the CV input signal. It should be connected to any Analog GPIO of the
   target MCU. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.

The `DI` pin is the signal coming out directly from the jack connector and should be left floating
if not used.

The pseudo-random predefined signal jack detection method allows,
from a user experience point of view, to dissociate a non-connected
jack from a connected jack at `GND` level.


## Using

```c++
int main ()
{
   using namespace erb;
   
   Module module;
   CvIn cv_in (module, AdcPin6);    // 1.
   
   module.run ([&](){
      float cv_value = cv_in;       // 2.
   });
}
```

1. Attach the CV to the module and specify the same analog pin as the one used for connecting,
2. Retrieve the bipolar (in the `-1.f` to `1.f` range) floating-point CV value from the
   -8V to 8V electrical range.

The `CvIn` class reference is available [here](./documentation/reference.md).
