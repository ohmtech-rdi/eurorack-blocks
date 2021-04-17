# gate-in

## Description

This block is a simple gate input.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   GateIn gate_in (module, Pin7);   // 1.
   
   void process () {
      bool gate_value = gate_in;    // 2.
   }
}
```

1. Attach the gate to the module and specify the same digital pin as the one used for connecting,
2. Retrieve the boolean gate value.

The `GateIn` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control gate_in GateIn {
      position 19.2mm, 111mm        // 1.
      style thonk.pj398sm.knurled   // 2.
      label "IN"                    // 3.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Sets the gate input position on the front panel,
2. Sets the style of the gate input,
3. Sets the optional label for the gate input, using its default theme positioning.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`
- `thonk.pj398sm.hex`

> Nuts and washers photo are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).
