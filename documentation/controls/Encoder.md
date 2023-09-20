# `Encoder`

## Description

`Encoder` represents a quadrature encoder, without a push momentary switch.
For the latter, refer to `EncoderButton` (coming soon).


## Usage

### `erbui`

```erbui
module Example {
   control shape Encoder {          // 1.
      position 19.2mm, 111mm        // 2.
      style small, rogan            // 3.
      label "SHAPE"                 // 4.
      pins Pin1, Pin2               // 5.
   }
}
```

1. Creates an encoder control with name `shape`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pins to use, quadrature A and B in that order.
   If not set, the system will choose it automatically.

<img width="30%" src="https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/410/PEC11R-4220F-S00xx.jpg">

> Bourns PEC11R photo is from [Digikey](https://www.digikey.de/en/products/detail/bourns-inc/PEC11R-4220F-N0024/4699220).

### `c++`

`Encoder` is a type that abstracts a physical quadrature encoder block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      int increment = ui.shape;  // 1.
      ...
   }
}
```

1. Converts the encoder to an integer representing the increment. The values
   are either `1` (rotating clock-wise), `-1` (rotating counter-clock-wise)
   or `0` (no rotation).


## `erbui` Control Reference

### `control` definition

```
control <name> Encoder { ... }
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

Where `<keywords>` is the first best matching subset of:
- `rogan.1s, rogan, 1s, small, skirt, d_shaft` (this is the default if not specified),

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
| [`operator int`](#operator-int) | Returns the increment |


## `c++` Member Functions

### `operator int`

```c++
operator int () const;
```

Returns either :
- `1` if the knob is turned by one notch clock-wise,
- `-1` if the knob is turned by one notch counter-clock-wise,
- `0` if the knob is not turned.
