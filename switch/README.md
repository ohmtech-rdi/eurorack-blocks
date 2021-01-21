# button

## Description

This block is a simple 3-position switch.
Its design is detailed [here](./documentation/design.md).


## Connecting

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally.
- The signal `OUT0` and `OUT1` are the button signals. They should be connected to any GPIO of the
   target MCU, **preferably non-analog** GPIOs. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.


## Using

```c++
int main ()
{
   using namespace erb;
   
   Module module;
   Switch switch_ (module, Pin23, Pin24); // 1.
   
   module.run ([&](){
      switch (switch_)
      {
      case Switch::Position::Out0: ...    // 2.
      case Switch::Position::Center: ...  // 3.
      case Switch::Position::Out1: ...    // 4.
      }
   });
}
```

1. Attach the switch to the module and specify the same 2 pins as the one used for connecting,
2. The switch position is on the left,
3. The switch position is on the middle,
4. The switch position is on the right.

The `Switch` class reference is available [here](./documentation/reference.md).
