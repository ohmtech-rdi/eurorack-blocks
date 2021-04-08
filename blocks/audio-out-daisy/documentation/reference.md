# `AudioOutDaisy` Class Reference

| Declared in | `erb/AudioOutDaisy.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class AudioOutDaisy;
```

`AudioOutDaisy` is a type that abstracts a physical `audio-out-daisy` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `AudioOutDaisy` |
| [Destructor](#destructor) | Destructs the `AudioOutDaisy` |
| [`operator =`](#operator-) | Assigns the whole audio buffer |
| [`size`](#size) | Returns the audio buffer size |
| [`operator []`](#operator--1) | Returns the sample at index in the audio buffer |
| [`fill`](#fill) | Assigns the given value to all samples in the audio buffer |


## Member Functions

### Constructor

```c++
AudioOutDaisy (Module & module, AudioOutDaisyPin pin);
```

Constructs the `Button` with `pin` and attach it to its `module`.

`pin` is one of:
- `AudioOutDaisyPinLeft`: the left channel on the onboard daisy seed audio codec,
- `AudioOutDaisyPinRight`: the right channel on the onboard daisy seed audio codec,
- `AudioOutDaisyPin0`: an alias to the left channel,
- `AudioOutDaisyPin1`: an alias to the right channel.

### Destructor

```c++
~AudioOutDaisy ();
```

Destructs the `AudioOutDaisy`.

### `operator =`

```c++
AudioOutDaisy & operator = (const Buffer & buffer);
```

Assigns the whole audio buffer with `buffer`.
It is represented as an `std::array` of `float` values.

Syntaxes like the following can be used:

```
AudioInDaisy audio_in (module, AudioInDaisyPinLeft);
AudioOutDaisy audio_out (module, AudioOutDaisyPinLeft);

audio_in = audio_out; // equivalent to a bypass
```

### `size`

```c++
size_t size () const;
```

Returns the size of the audio buffer. This is the same value as `erb::buffer_size`.

### `operator []`

```c++
float & operator [] (size_t index);
```

Returns the sample at `index` in the audio buffer.

Since it is a reference, syntaxes like the following can be used:

```
AudioOutDaisy audio_out (module, AudioOutDaisyPinLeft);
MyDsp my_dsp;

my_dsp.process_output (&audio_out [0], audio_out.size ());
```

### `fill`

```c++
void fill (float val);
```

Assigns `val` to all samples in the audio buffer.

This can be used to silence a buffer:

```
AudioOutDaisy audio_out (module, AudioOutDaisyPinLeft);

audio_out.fill (0.f); // silence
```
