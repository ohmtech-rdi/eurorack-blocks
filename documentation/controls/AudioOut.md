# `AudioOut`

## Description

`AudioOut` represents an audio output.


## Usage

### `erbui`

```erbui
module Example {
   control out_left AudioOut {      // 1.
      position 19.2mm, 111mm        // 2.
      style knurled                 // 3.
      label "OUT L"                 // 4.
      pin AudioOutPinLeft           // 5.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Creates an audio output control with name `out_left`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pin to use. If not set, the system will choose it automatically.

> Nuts and washers photos are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).

### `c++`

`AudioOut` is a type that abstracts a physical audio output block.

```c++
struct Example
{
   ExampleUi ui;
   ExampleDsp dsp;
   
   void process () {
      for (size_t i = 0 ; i < ui.out_left.size () ; ++i) // 1.
      {
         ui.out_left [i] = ...;                          // 2.
      }
   }
}
```

1. Loop through all the samples in the buffer. `erb_BUFFER_SIZE` can be used instead,
2. Set the audio output value on codec left pin.


## `erbui` Control Reference

### `control` definition

```
control <name> AudioOut { ... }
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
| [`operator =`](#operator-) | Assigns the whole audio buffer |
| [`size`](#size) | Returns the audio buffer size |
| [`operator []`](#operator--1) | Returns the sample at index in the audio buffer |
| [`fill`](#fill) | Assigns the given value to all samples in the audio buffer |


## `c++` Member Functions

### `operator =`

```c++
AudioOut & operator = (const Buffer & buffer);
```

Assigns the whole audio buffer with `buffer`.
It is represented as an `std::array` of `float` values.

Syntaxes like the following can be used:

```
// AudioIn audio_in
// AudioOut audio_out

ui.audio_in = ui.audio_out; // equivalent to a bypass
```

### `size`

```c++
size_t size () const;
```

Returns the size of the audio buffer. This is the same value as `erb_BUFFER_SIZE`.

### `operator []`

```c++
float & operator [] (size_t index);
```

Returns the sample at `index` in the audio buffer.

Since it is a reference, syntaxes like the following can be used:

```
MyDsp dsp;

dsp.process_output (&ui.out_left [0], ui.out_left.size ());
```

### `fill`

```c++
void fill (float val);
```

Assigns `val` to all samples in the audio buffer.

This can be used to silence a buffer:

```
ui.out_left.fill (0.f); // silence
```
