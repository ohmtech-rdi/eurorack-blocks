# `Trim`

## Description

`Trim` represents a potentiometer.


## Usage

### `erbui`

```erbui
module Example {
   control freq Trim {              // 1.
      position 19.2mm, 111mm        // 2.
      style tall                    // 3.
      label "FREQ"                  // 4.
      pin AdcPin1                   // 5.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2014/10/R0904N_Product1.jpg">

1. Creates a button control with name `arm`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pin to use. If not set, the system will choose it automatically.

> Trim photo is from the [Thonk shop](https://www.thonk.co.uk/shop/ttpots/).

### `c++`

`Trim` is a type that abstracts a potentiometer block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      float freq_val = ui.freq;  // 1.
   }
}
```

1. Retrieves the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point pot value.


## `erbui` Control Reference

### `control` definition

```
control <name> Trim { ... }
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

Where `<keywords>` can only be (for now):
- `tall` (this is the default if not specified).

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
| [`operator float`](#operator-float) | Returns the pot value |


## `c++` Member Functions

### `operator float`

```c++
operator float () const;
```

Returns the pot value.
