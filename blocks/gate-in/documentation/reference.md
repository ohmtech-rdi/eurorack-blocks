# `GateIn` Class Reference

| Declared in | `erb/GateIn.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class GateIn;
```

`GateIn` is a type that abstracts a physical `gate-in` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `GateIn` |
| [Destructor](#destructor) | Destructs the `GateIn` |
| [`set_mode`](#set_mode) | Sets the gate mode |
| [`operator bool`](#operator-bool) | Returns the gate value |


## Member Functions

### Constructor

```c++
GateIn (Module & module, const dsy_gpio_pin & pin, Mode mode = Mode::Trigger);
```

Constructs the `GateIn` with `pin` and attach it to its `module` with `mode`.

`mode` is one of the following:
- `GateIn::Mode::Trigger` which change the gate state only on a rising edge,
   _this is the default value_,
- `GateIn::Mode::Gate` which mirrors the input value.

> `pin` must use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~GateIn ();
```

Destructs the `GateIn`.

### `set_mode`

```c++
void set_mode (Mode mode);
```

Change the read mode. See [Constructor](#constructor) for possible enumerator values.

### `operator bool`

```c++
operator bool () const;
```

Returns the gate value.
