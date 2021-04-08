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


## Member Functions

### Constructor

```c++
Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b, const Pin & pin_c);
Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b);
Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a);
```

Constructs the `Multiplexer` with the pins and attach it to its `module`.

> All pins must use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~Multiplexer ();
```

Destructs the `Multiplexer`.
