# audio-in-daisy

## Description

This block is a simple analog audio input for the
[Daisy Seed](https://www.electro-smith.com/daisy/daisy) onboard codec.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   AudioInDaisy audio_in_left (module, AudioInDaisyPinLeft);   // 1.
   AudioInDaisy audio_in_right (module, AudioInDaisyPinRight); // 2.

   void process () {
      for (size_t i = 0 ; i < audio_in_left.size () ; ++i)     // 3.
      {
         float left  = audio_in_left [i];                      // 4.
         float right = audio_in_right [i];                     // 5.
      }
   }
}
```

1. Attach the audio input to the module with the onboard codec left pin (Pin 16),
2. Attach the audio input to the module with the onboard codec right pin (Pin 17),
2. Loop through all the samples in the buffer. `erb::buffer_size` can be used instead,
3. Retrieve the audio input value on codec left pin,
4. Retrieve the audio input value on codec right pin.

The `AudioInDaisy` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control audio_in AudioInDaisy {
      position 19.2mm, 111mm        // 1.
      style thonk.pj398sm.knurled   // 2.
      label "IN"                    // 3.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Sets the audio input position on the front panel,
2. Sets the style of the audio input,
3. Sets the optional label for the audio input, using its default theme positioning.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`
- `thonk.pj398sm.hex`

> Nuts and washers photo are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).
