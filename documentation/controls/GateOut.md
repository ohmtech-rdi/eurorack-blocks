# `GateOut`

## Description

`GateOut` represents a gate output.


## Usage

### `erbui`

```erbui
module Example {
   control active GateOut {   // 1.
      position 19.2mm, 111mm  // 2.
      style knurled           // 3.
      label "ACT"             // 4.
      pin Pin1                // 5.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Creates a gate output control with name `active`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pin to use. If not set, the system will choose it automatically.

`style` is the nut style, and is one of:
- `hex`, this is the default if `style` is omitted,
- `knurled`.

> Nuts and washers photos are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).

### `c++`

`GateOut` is a type that abstracts a physical gate output block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      if (dsp.activity_changed () && dsp.is_active ()) {
         ui.active.trigger ();                           // 1.
      }
   }
}
```

1. Triggers the gate.


## `erbui` Control Reference

### `control` definition

```
control <name> GateOut { ... }
```

Where `<name>` is the name of the control.
More details can be found in [`control`](../language/grammar.md#control) documentation.

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

More details can be found in [`position`](../language/grammar.md#position) documentation.

### `style` property

```
style <name>
```

Where `<name>` is one of:
- `knurled`,
- `hex`.

More details can be found in [`style`](../language/grammar.md#style) documentation.

### `label` optional property

```
label "<text>"
```

Where `<text>` is the text displayed.
More details can be found in [`label`](../language/grammar.md#label) documentation.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`operator =`](#operator-=) | Sets the gate value |
| [`on`](#on) | Turns on the gate |
| [`off`](#off) | Turns off the gate |
| [`trigger`](#trigger) | Triggers the gate |


## `c++` Member Functions

### `operator =`

```c++
GateOut & operator = (bool val);
```

Sets the game to the boolean value.

### `on`

```c++
void on ();
```

Turns on the gate.

### `off`

```c++
void off ();
```

Turns on the gate.

### `trigger`

```c++
void trigger (std::chrono::milliseconds duration = 6ms);
```

Turns on the gate for the specified amount of time, 6ms by default, and then turns off the
gate.
