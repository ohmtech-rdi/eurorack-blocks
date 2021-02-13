# `AudioInDaisy` Class Reference

| Declared in | `erb/AudioInDaisy.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class AudioInDaisy;
```

`AudioInDaisy` is a type that abstracts a physical `audio-in-daisy` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `AudioInDaisy` |
| [Destructor](#destructor) | Destructs the `AudioInDaisy` |
| [`operator Buffer`](#operator-buffer) | Returns the whole audio buffer |
| [`size`](#size) | Returns the audio buffer size |
| [`operator []`](#operator-) | Returns the sample at index in the audio buffer |


## Member Functions

### Constructor

```c++
AudioInDaisy (Module & module, AudioInDaisyPin pin);
```

Constructs the `Button` with `pin` and attach it to its `module`.

`pin` is one of:
- `AudioInDaisyPinLeft`: the left channel on the onboard daisy seed audio codec,
- `AudioInDaisyPinRight`: the right channel on the onboard daisy seed audio codec,
- `AudioInDaisyPin0`: an alias to the left channel,
- `AudioInDaisyPin1`: an alias to the right channel.

### Destructor

```c++
~AudioInDaisy ();
```

Destructs the `AudioInDaisy`.

### `operator Buffer`

```c++
operator Buffer () const;
```

Returns the whole audio buffer. It is represented as an `std::array` of `float` values.

### `size`

```c++
size_t size () const;
```

Returns the size of the audio buffer. This is the same value as `erb::buffer_size`.

### `operator []`

```c++
const float & operator [] (size_t index);
```

Returns the sample at `index` in the audio buffer.

Since it is a reference, syntaxes like the following can be used:

```
AudioInDaisy audio_in (module, AudioInDaisyPinLeft);
MyDsp my_dsp;

my_dsp.process_input (&audio_in [0], audio_in.size ());
```
