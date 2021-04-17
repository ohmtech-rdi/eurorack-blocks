# audio-out-daisy

## Description

This block is a simple analog audio output for the
[Daisy Seed](https://www.electro-smith.com/daisy/daisy) onboard codec.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   AudioOutDaisy audio_out_left (module, AudioOutDaisyPinLeft);   // 1.
   AudioOutDaisy audio_out_right (module, AudioOutDaisyPinRight); // 2.
   
   void process () {
      for (size_t i = 0 ; i < audio_out_left.size () ; ++i)       // 3.
      {
         audio_out_left [i] = ...;                                // 4.
         audio_out_right [i] = ...;                               // 5.
      }
   }
}
```

1. Attach the audio output to the module with the onboard codec left pin (Pin 18),
2. Attach the audio output to the module with the onboard codec right pin (Pin 19),
3. Loop through all the samples in the buffer. `erb::buffer_size` can be used instead,
4. Set the audio output value on codec left pin,
5. Set the audio output value on codec right pin.

The `AudioOutDaisy` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control audio_out AudioOutDaisy {
      position 19.2mm, 111mm        // 1.
      style thonk.pj398sm.knurled   // 2.
      label "OUT"                   // 3.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Sets the audio out position on the front panel,
2. Sets the style of the audio out,
3. Sets the optional label for the audio out, using its default theme positioning.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`
- `thonk.pj398sm.hex`

> Nuts and washers photo are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).
