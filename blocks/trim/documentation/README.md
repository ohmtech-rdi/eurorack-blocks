# trim

## Description

This block is a simple potentiometer, using a trim pot, typically used for attenuverters.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   Trim trim (module, AdcPin6);  // 1.

   void process () {
      float trim_value = trim;   // 2.
   }
}
```

1. Attach the trim to the module and specify the same analog pin as the one used for connecting,
2. Retrieve the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point trim value.

The `Trim` type is an alias to the `Pot` class.
The `Pot` class reference is available [here](./../../pot/documentation/reference.md).

### `erbui`

```erbui
module Example {
   control trim Trim {
      position 19.2mm, 111mm        // 1.
      style songhuei.9mm            // 2.
      label "PARAM"                 // 3.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2014/10/R0904N_Product1.jpg">

1. Sets the trim position on the front panel,
2. Sets the style of the trim,
3. Sets the optional label for the trim, using its default theme positioning.

`style` is one of:
- `songhuei.9mm`

> Trim photo is from the [Thonk shop](https://www.thonk.co.uk/shop/ttpots/).
