# pot

## Description

This block is a simple potentiometer.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   Pot pot (module, AdcPin6); // 1.

   void process () {
      float pot_value = pot;  // 2.
   }
}
```

1. Attach the pot to the module and specify the same analog pin as the one used for connecting,
2. Retrieve the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point pot value.

The `Pot` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control pot Pot {
      position 19.2mm, 111mm        // 1.
      style rogan.6ps               // 2.
      label "IN"                    // 3.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2019/11/RoganFamily.jpg">

1. Sets the potentiometer position on the front panel,
2. Sets the style of the potentiometer knob,
3. Sets the optional label for the potentiometer, using its default theme positioning.

`style` is the knob style, and is one of:
- `rogan.6ps`
- `rogan.5ps`
- `rogan.3ps`
- `rogan.2ps`
- `rogan.1ps`

> Knobs photos are from the [Thonk shop](https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/).
