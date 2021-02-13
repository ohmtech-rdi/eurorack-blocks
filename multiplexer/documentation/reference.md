# `Multiplexer` Class Reference

| Declared in | `erb/Multiplexer.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class Multiplexer;
```

`Multiplexer` is a type that abstracts a physical `multiplexer` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `Multiplexer` |
| [Destructor](#destructor) | Destructs the `Multiplexer` |
| [`operator [](size_t idx)`](#operator-size_t-idx) | Returns the bipolar CV value at index |


## Member Functions

### Constructor

```c++
Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b, const Pin & pin_c);
```

Constructs the `Multiplexer` with the pins and attach it to its `module`.

> All pins must use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~Multiplexer ();
```

Destructs the `Multiplexer`.

### `operator [](size_t idx)`

```c++
float operator [](size_t idx) const;
```

Returns the normalized pot value in the `0.f` to `1.f` range at input number `idx`.
`idx` must be a number between 0 and 7.
