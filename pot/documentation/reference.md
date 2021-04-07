# `Pot` Class Reference

| Declared in | `erb/Pot.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class Pot;
```

`Pot` is a type that abstracts a physical `pot` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `Pot` |
| [Destructor](#destructor) | Destructs the `Pot` |
| [`set_mode`](#set_mode) | Sets the pot mode |
| [`operator float`](#operator-float) | Returns the pot value |


## Member Functions

### Constructor

```c++
Pot (Module & module, const AdcPin & pin, Mode mode = Mode::Normalized); // 1.
Pot (Multiplexer & multiplexer, const MultiplexerPin & pin, Mode mode = Mode::Normalized); // 2.
```

1. Constructs the `Pot` with `pin` and attach it to its `module` with `mode`.
2. Constructs the `Pot` with `pin` and attach it to its `multiplexer` with `mode`.

`mode` is one of the following:
- `Pot::Mode::Normalized` to return a value between `0.f` and `1.f`,
   _this is the default value_,
- `Pot::Mode::Bipolar` to return a value between `-1.f` and `1.f`.

> `pin` must use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~Pot ();
```

Destructs the `Pot`.

### `set_mode`

```c++
void set_mode (Mode mode);
```

Change the read mode. See [Constructor](#constructor) for possible enumerator values.

### `operator float`

```c++
operator float () const;
```

Returns the pot value.
