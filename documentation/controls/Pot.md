# `Pot`

## Description

`Pot` represents a potentiometer.


## Usage

### `erbui`

```erbui
module Example {
   control freq Pot {               // 1.
      position 19.2mm, 111mm        // 2.
      style rogan, medium           // 3.
      label "FREQ"                  // 4.
      pin AdcPin1                   // 5.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2019/11/RoganFamily.jpg">

1. Creates a button control with name `arm`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pin to use. If not set, the system will choose it automatically.

`style` is the knob style, and is one of:
- `rogan, 3ps, size3, large, skirt, d_shaft`, this is the default if `style` is omitted,
- `rogan, 2ps, size2, medium, skirt, d_shaft`,
- `rogan, 1ps, size1, small, skirt, d_shaft`,
- `rogan, 2p, size2, medium, unskirted, d_shaft`,
- `rogan, 1p, size1, small, unskirted, d_shaft`,
- `rogan, 6ps, size6, xlarge, skirt, d_shaft`,
- `rogan, 5ps, size5, larger, skirt, d_shaft`,
- `sifam, selco, dbn150, large, skirt, d_shaft, white`,
- `sifam, selco, dbn151, large, skirt, d_shaft, white, line`,
- `sifam, selco, drn110, small, skirt, d_shaft, white`,
- `sifam, selco, drn111, small, skirt, d_shaft, white, line`,
- `sifam, selco, db150, large, unskirted, d_shaft, white`,
- `sifam, selco, db151, large, unskirted, d_shaft, white, line`,
- `sifam, selco, dr110, small, unskirted, d_shaft, white`,
- `sifam, selco, dr111, small, unskirted, d_shaft, white, line`.

```{note}
You don't need to give all those keywords to make a selection.
The style engine takes the best match from your list of styles.
```

For example `style rogan` will select the Rogan 3PS knob with skirt and D-shaft,
and `style sifma, small` will select the Sifam/Selco small knob with skirt, white, without line.


> Knobs photos are from the [Thonk shop](https://www.thonk.co.uk/shop/make-noise-mutable-style-knobs/).

### `c++`

`Pot` is a type that abstracts a potentiometer block.

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
control <name> Pot { ... }
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
- `rogan, 3ps, size3, large, skirt, d_shaft`,
- `rogan, 2ps, size2, medium, skirt, d_shaft`,
- `rogan, 1ps, size1, small, skirt, d_shaft`,
- `rogan, 2p, size2, medium, unskirted, d_shaft`,
- `rogan, 1p, size1, small, unskirted, d_shaft`,
- `rogan, 6ps, size6, xlarge, skirt, d_shaft`,
- `rogan, 5ps, size5, larger, skirt, d_shaft`,
- `sifam, selco, dbn150, large, skirt, d_shaft, white`,
- `sifam, selco, dbn151, large, skirt, d_shaft, white, line`,
- `sifam, selco, drn110, small, skirt, d_shaft, white`,
- `sifam, selco, drn111, small, skirt, d_shaft, white, line`,
- `sifam, selco, db150, large, unskirted, d_shaft, white`,
- `sifam, selco, db151, large, unskirted, d_shaft, white, line`,
- `sifam, selco, dr110, small, unskirted, d_shaft, white`,
- `sifam, selco, dr111, small, unskirted, d_shaft, white, line`.

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
| [`operator float`](#operator-float) | Returns the pot value |


## `c++` Member Functions

### `operator float`

```c++
operator float () const;
```

Returns the pot value.
