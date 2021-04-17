# led-bi

## Description

This block is a simple dichromatic LED.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   LedBi led (module, Pin23, Pin24);      // 1.
   
   void process () {
      led.on (LedBi::Color::Red);         // 2.
      led.off ();                         // 3.
      led.pulse (LedBi::Color::Yellow);   // 4.
      led.blink (LedBi::Color::Green);    // 5.
   }
}
```

1. Attach the LED to the module and specify the same pins as the one used for connecting,
2. The LED is turned on with a red color,
3. The LED is turned off,
4. The LED is shorlty pulsed with a yellow color,
5. The LED is blinking with a green color.

The `LedBi` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control led LedBi {
      position 19.2mm, 111mm        // 1.
      style led.3mm.green_red       // 2.
      label "STATE"                 // 3.
   }
}
```

1. Sets the LED position on the front panel,
2. Sets the style of the LED,
3. Sets the optional label for the LED, using its default theme positioning.

`style` is the LED style, and is one of:
- `led.3mm.green_red`
