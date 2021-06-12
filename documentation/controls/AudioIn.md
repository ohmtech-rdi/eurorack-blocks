# `AudioIn`

## Description

`AudioIn` represents an audio input.


## Usage

### `erbui`

```erbui
module Example {
   control in_left AudioIn {        // 1.
      position 19.2mm, 111mm        // 2.
      style thonk.pj398sm.knurled   // 3.
      label "IN L"                  // 4.
      cascade in_right              // 5.
      pin AudioInPinLeft            // 6.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Creates an audio input control with name `in_left`,
2. Sets the control position on the front panel,
3. Sets the style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional cascade control for the control,
6. Sets the physical board pin to use.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`,
- `thonk.pj398sm.hex`.

> Nuts and washers photos are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).

### `c++`

`AudioIn` is a type that abstracts a physical audio input block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      Buffer buffer = ui.in_left;   // 1.
      
      for (auto && sample : buffer) {
         ...
      }
   }
}
```

1. Retrieves the buffer of samples (in the `-1.f` to `1.f` range) floating-point value.


## `erbui` Control Reference

### `control` definition

```
control <name> AudioIn { ... }
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


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`operator Buffer`](#operator-buffer) | Returns the whole audio buffer |
| [`size`](#size) | Returns the audio buffer size |
| [`operator []`](#operator-) | Returns the sample at index in the audio buffer |


## `c++` Member Functions

### `operator Buffer`

```c++
operator Buffer () const;
```

Returns the whole audio buffer. It is represented as an `std::array` of `float` values.

### `size`

```c++
size_t size () const;
```

Returns the size of the audio buffer. This is the same value as `erb_BUFFER_SIZE`.

### `operator []`

```c++
const float & operator [] (size_t index);
```

Returns the sample at `index` in the audio buffer.

Since it is a reference, syntaxes like the following can be used:

```
MyDsp dsp;
dsp.process_input (&ui.in_left [0], ui.in_left.size ());
```
