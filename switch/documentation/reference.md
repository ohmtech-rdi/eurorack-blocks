# `Switch` Class Reference

| Declared in | `erb/Switch.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class Switch;
```

`Switch` is a type that abstracts a physical `switch` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `Switch` |
| [Destructor](#destructor) | Destructs the `Switch` |
| [`operation Position`](#operator-position) | Returns the switch position |


## Member Functions

### Constructor

```c++
Switch (Module & module, const dsy_gpio_pin & pin_0, const dsy_gpio_pin & pin_1);
```

Constructs the `Switch` with `pin_0` and `pin_1` and attach it to its `module`.

> `pin` should use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~Switch ();
```

Destructs the `Switch`.

### `operator Position`

```c++
operator Position () const;
```

Returns the switch position, one of the following value:
- `Switch::Position::Out0` when the switch is on the left,
- `Switch::Position::Center` when the switch is centered,
- `Switch::Position::Out1` when the switch is on the right.

After the switch has finished bouncing, it will take 7 process cycles, so 7ms if the buffer
size is 48 samples, for the change to be detected.

Even if a 2-position switch is used, the `Center` position needs to be taken into account
as it will transiently transition to it when going from left to right or right to left.
