# led

## Description

This block is a simple monochromatic LED.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   Led led (module, Pin23);   // 1.
   
   void process () {
      led.on ();              // 2.
      led.off ();             // 3.
      led.pulse ();           // 4.
      led.blink ();           // 5.
   }
}
```

1. Attach the LED to the module and specify the same pin as the one used for connecting,
2. The LED is turned on,
3. The LED is turned off,
4. The LED is shorlty pulsed,
5. The LED is blinking.

The `Led` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control led Led {
      position 19.2mm, 111mm        // 1.
      style led.3mm.red             // 2.
      label "CLK"                   // 3.
   }
}
```

1. Sets the LED position on the front panel,
2. Sets the style of the LED,
3. Sets the optional label for the LED, using its default theme positioning.

`style` is the LED style, and is one of:
- `led.3mm.red`
- `led.3mm.green`
- `led.3mm.yellow`
- `led.3mm.orange`
