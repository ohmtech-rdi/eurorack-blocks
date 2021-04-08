# gate-in

## Description

This block is a simple gate input.
Its design is detailed [here](./documentation/design.md).


## Connecting

<p align="center"><img src="./documentation/connecting.png" width="100%"></p>

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally,
- This block needs its `3V3D` to be connected to the Daisy Seed 3V3 Digital Power I/O on Pin 38,
- The `NOP` pin can be either connected to:
   - `GND` to send zeros to the software implementation,
   - Cascading the `DI` signal from another `gate-in` block,
   - A pseudo-random predefined signal to detect a jack connection
      as explained on the Mutable Instruments forums
      [here](https://forum.mutable-instruments.net/t/plaits-normalization-probe/14358/2)
      and implemented
      [here](https://github.com/pichenettes/eurorack/blob/master/plaits/ui.cc#L368).
- The signal `OUT` is the Gate input signal. It should be connected to any Digital
   (and preferably non-Analog) GPIO
   of the target MCU. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.

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
   GateIn gate_in (module, Pin7);   // 1.
   
   module.run ([&](){
      bool gate_value = gate_in;    // 2.
   });
}
```

1. Attach the gate to the module and specify the same digital pin as the one used for connecting,
2. Retrieve the boolean gate value.

The `GateIn` class reference is available [here](./documentation/reference.md).
