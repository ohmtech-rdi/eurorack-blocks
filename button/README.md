# button

## Description

This block is a simple trigger push button.
Its design is detailed [here](./documentation/design.md).


## Connecting

<p align="center"><img src="./documentation/connecting.png" width="100%"></p>

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally.
- The signal `OUT` is the button signal. It should be connected to any GPIO of the
   target MCU, **preferably non-analog** GPIOs. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.


## Using

```c++
int main ()
{
   using namespace erb;
   
   Module module;
   Button button (module, Pin23);   // 1.
   
   module.run ([&](){
      if (button.pressed ()) ...    // 2.
      if (button.held ()) ...       // 3.
      if (button.released ()) ...   // 4.
   });
}
```

1. Attach the button to the module and specify the same pin as the one used for connecting,
2. The button was just pressed,
3. The button is held down,
4. The button was just released.

The `Button` class reference is available [here](./documentation/reference.md).
