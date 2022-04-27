# `GateIn`

## Description

`GateIn` represents a gate input.


## Usage

### `erbui`

```erbui
module Example {
   control clock GateIn {           // 1.
      position 19.2mm, 111mm        // 2.
      style knurled                 // 3.
      label "CLK"                   // 4.
      cascade sync                  // 5.
      pin Pin1                      // 6.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Creates a Gate input control with name `clock`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional cascade control for the control,
6. Sets the optional physical board pin to use. If not set, the system will choose it automatically.

> Nuts and washers photos are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).

### `c++`

`GateIn` is a type that abstracts a physical gate input block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      auto clock_fired = ui.clock.triggered ();  // 1.
   }
}
```

1. Checks if the gate was triggered.


## `erbui` Control Reference

### `control` definition

```
control <name> GateIn { ... }
```

Where `<name>` is the name of the control.
More details can be found in [`control`](../erbui/grammar.html#control) documentation.

### `position` property

```
position <x>, <y>
```

Sets the position of the control, where the axis origin is the top-left corner.
The `x` axis is oriented from left to right, and the `y` axis is oriented from top to bottom.

The position component values are expressed with their unit, either `mm` or `hp`.

Example:
```
position 2hp, 15mm
```

More details can be found in [`position`](../erbui/grammar.html#position) documentation.

### `style` optional property

```
style <keywords>
```

Where `<keywords>` is one of:
- `knurled` (this is the default if not specified),
- `hex`.

More details can be found in [`style`](../erbui/grammar.html#style) documentation.

### `label` optional property

```
label "<text>"
```

Where `<text>` is the text displayed.
More details can be found in [`label`](../erbui/grammar.html#label) documentation.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`operator bool`](#operator-bool) | Returns the gate value |
| [`triggered`](#triggered) | Returns true when the gate is triggered |


## `c++` Member Functions

### `operator float`

```c++
operator float () const;
```

Returns the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
floating-point value.

### `triggered`

```c++
bool triggered () const;
```

Returns true when a rising edge of the input signal is detected, false otherwise.
