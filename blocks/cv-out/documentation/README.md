# `CvOut`

## Description

This block is an analog CV output.


## Usage

### `erbui`

```erbui
module Example {
   control cv_out CvOut {
      position 19.2mm, 111mm        // 1.
      style thonk.pj398sm.knurled   // 2.
      label "OUT"                   // 3.
      mode bipolar                  // 4.
      pin DacPin1                   // 5.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Sets the CV output position on the front panel,
2. Sets the style of the CV output,
3. Sets the optional label for the CV output, using its default theme positioning,
4. Sets the optional mode for the CV output, bipolar by default,
5. Sets the physical pin to use.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`,
- `thonk.pj398sm.hex`.

> Nuts and washers photo are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).

### `c++`

`CvOut` is a type that abstracts a physical CV output block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      ui.cv_out = ...; // 1.        
   }
}
```

1. Sets the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
   floating-point pot value.


## `erbui` Control Reference

### `control` definition

```
control <name> CvOut { ... }
```

Where `<name>` is the name of the control.

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

### `style` property

```
style <name>
```

Where `<name>` is one of:
- `thonk.pj398sm.knurled`,
- `thonk.pj398sm.hex`.

### `label` optional property

```
label "<name>"
```

Where `<name>` is the text displayed.
More details can be found in [`label`](./label.md) documentation.

### `mode` optional property

`mode` defines the electrical range used on the jack connector output.

```
mode <name>
```

Where `<name>` is one of:
- `bipolar`, ±5V, this is the _default_ value,
- `normalized`, from 0V to 5V.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`operator =`](#operator-=) | Sets the CV value |


## `c++` Member Functions

### `operator =`

```c++
CvOut & operator = (float val);
```

Sets the normalised (in the  `0.f` to `1.f` range) or bipolar (in the `-1.f` to `1.f` range)
floating-point pot value.
