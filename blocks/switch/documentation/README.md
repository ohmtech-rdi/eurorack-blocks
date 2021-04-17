# switch

## Description

This block is a simple 3-position switch.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   Switch switch_ (module, Pin23, Pin24); // 1.
   
   void process () {
      switch (switch_)
      {
      case Switch::Position::Out0: ...    // 2.
      case Switch::Position::Center: ...  // 3.
      case Switch::Position::Out1: ...    // 4.
      }
   }
}
```

1. Attach the switch to the module and specify the same 2 pins as the one used for connecting,
2. The switch position is on the left,
3. The switch position is on the middle,
4. The switch position is on the right.

The `Switch` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control switch_ Switch {
      position 19.2mm, 111mm        // 1.
      style dailywell.2ms1          // 2.
      rotation 90°ccw               // 3.
      label "IN"                    // 4.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/05/switches-pcb-mount.jpg">

1. Sets the switch position on the front panel,
2. Sets the style of the switch,
3. Sets the optional rotation for the switch,
4. Sets the optional label for the switch, using its default theme positioning.

`style` is the switch style, and is one of:
- `dailywell.2ms1`, which is a SPDT On-On (2 positions) switch
- `dailywell.2ms3`, which is a SPDT On-Off-On (3 positions) switch

> Switch photos are from the [Thonk shop](https://www.thonk.co.uk/shop/sub-mini-toggle-switches/).

`rotation` is the switch rotation on the panel. Supported units are:
- `°ccw` (Counter Clockwise)
- `°ccw` (Clockwise)
- `°` (Clockwise, as the position y-axis goes from top to bottom)

The `rotation` value only supports quarter turns.
