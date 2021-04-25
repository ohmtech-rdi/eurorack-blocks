# led-bi

## Description

This block is a simple dichromatic LED.
Its design is detailed [here](./documentation/design.md).


## Connecting

- This block needs its `GND` to be connected to the ground. All `GND` pins are connected
   internally.
- The signal `INR` is the LED red signal. It should be connected to any GPIO of the
   target MCU, **preferably non-analog** GPIOs. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.
- The signal `ING` is the LED green signal. It should be connected to any GPIO of the
   target MCU, **preferably non-analog** GPIOs. See [Daisy Seed pinout](https://images.squarespace-cdn.com/content/v1/58d03fdc1b10e3bf442567b8/1591827747342-HCXMM2NNR26SP5F4U2CJ/ke17ZwdGBToddI8pDm48kN5PbQBGNYbW-5Hm1pf8hRF7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0kLp48N9LluBiCpBrPZntaz462IffsVrAff3VJkwKncM1HZuDnV98dfxM9yHlqFkUQ/DaisyPinoutRev4%404x.png?format=500w) for details.


## Using

```c++
int main ()
{
   using namespace erb;
   
   Module module;
   LedBi led (module, Pin23, Pin24);       // 1.
   
   module.run ([&](){
      led.on (LedBi::Color::red ());       // 2.
      led.off ();                          // 3.
      led.pulse (LedBi::Color::yellow ()); // 4.
      led.blink (LedBi::Color::green ());  // 5.
   });
}
```

1. Attach the LED to the module and specify the same pins as the one used for connecting,
2. The LED is turned on with a red color,
3. The LED is turned off,
4. The LED is shorlty pulsed with a yellow color,
5. The LED is blinking with a green color.

The `LedBi` class reference is available [here](./documentation/reference.md).
