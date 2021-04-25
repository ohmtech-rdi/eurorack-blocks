# led-rgb

## Description

This block is a simple RGB LED.

## Using

### `c++`

```c++
struct Example
{
   Module module;
   LedRgb led (module, Pin23, Pin24, Pin25); // 1.
   
   void process () {
      led.on (LedRgb::Color::red ());        // 2.
      led.off ();                            // 3.
      led.pulse (LedRgb::Color::blue ());    // 4.
      led.blink (LedRgb::Color::green ());   // 5.
   }
}
```

1. Attach the LED to the module and specify the same pins as the one used for connecting,
2. The LED is turned on with a red color,
3. The LED is turned off,
4. The LED is shorlty pulsed with a blue color,
5. The LED is blinking with a green color.

The `LedRgb` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control led LedRgb {
      position 19.2mm, 111mm        // 1.
      style led.3mm.rgb             // 2.
      label "STATE"                 // 3.
   }
}
```

1. Sets the LED position on the front panel,
2. Sets the style of the LED,
3. Sets the optional label for the LED, using its default theme positioning.

`style` is the LED style, and is one of:
- `led.3mm.rgb`
