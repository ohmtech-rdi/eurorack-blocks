# `CvIn`

## Description

`CvIn` represents an analog CV input.


## Usage

### `erbui`

```erbui
module Example {
   control vco_amp CvIn {           // 1.
      position 19.2mm, 111mm        // 2.
      style thonk.pj398sm.knurled   // 3.
      label "AMP"                   // 4.
      mode bipolar                  // 5.
      cascade vco_amp2              // 6.
      pin AdcPin1                   // 7.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Creates a CV input control with name `vco_amp`,
2. Sets the control position on the front panel,
3. Sets the style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional mode for the control, bipolar by default,
6. Sets the optional cascade control for the control,
7. Sets the physical board pin to use.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`,
- `thonk.pj398sm.hex`.

> Nuts and washers photos are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).

### `c++`

`CvIn` is a type that abstracts a physical CV input block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      float vco_amp = ui.vco_amp;   // 1.
   }
}
```

1. Retrieves the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point value.


## `erbui` Control Reference

### `control` definition

```
control <name> CvIn { ... }
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
- `thonk.pj398sm.knurled`,
- `thonk.pj398sm.hex`.

More details can be found in [`style`](../language/grammar.md#style) documentation.

### `label` optional property

```
label "<text>"
```

Where `<text>` is the text displayed.
More details can be found in [`label`](../language/grammar.md#label) documentation.

### `mode` optional property

`mode` defines the electrical range used on the jack connector input.

```
mode <name>
```

Where `<name>` is one of:
- `bipolar`, ±5V, this is the _default_ value,
- `normalized`, from 0V to 5V.

More details can be found in [`mode`](../language/grammar.md#mode) documentation.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`operator float`](#operator-float) | Returns the bipolar CV value |


## `c++` Member Functions

### `operator float`

```c++
operator float () const;
```

Returns the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
floating-point value.
