# led-rgb

## Description

This block is a simple RGB LED.


## Using

```c++
int main ()
{
   using namespace erb;
   
   Module module;
   LedRgb led (module, Pin23, Pin24, Pin25); // 1.
   
   module.run ([&](){
      led.on (LedRgb::Color::red ());        // 2.
      led.off ();                            // 3.
      led.pulse (LedRgb::Color::blue ());    // 4.
      led.blink (LedRgb::Color::green ());   // 5.
   });
}
```

1. Attach the LED to the module and specify the same pins as the one used for connecting,
2. The LED is turned on with a red color,
3. The LED is turned off,
4. The LED is shorlty pulsed with a blue color,
5. The LED is blinking with a green color.

The `LedRgb` class reference is available [here](./documentation/reference.md).
