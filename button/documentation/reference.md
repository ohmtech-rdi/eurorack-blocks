# `Button` Class Reference

| Declared in | `erb/Button.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class Button;
```

`Button` is a type that abstracts a physical `button` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `Button` |
| [Destructor](#destructor) | Destructs the `Button` |
| [`pressed`](#pressed) | Returns `true` iff the button was pressed |
| [`held`](#held) | Returns `true` iff the button is held |
| [`released`](#released) | Returns `true` iff the button was released |


## Member Functions

### Constructor

```c++
Button (Module & module, const dsy_gpio_pin & pin);
```

Constructs the `Button` with `pin` and attach it to its `module`.

> `pin` should use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~Button ();
```

Destructs the `Button`.

### `pressed`

```c++
bool pressed () const;
```

Returns `true` if and only if the button was just pressed.

After the button has finished bouncing, it will take 7 process cycles, so 7ms if the buffer
size is 48 samples, for the change to be detected.

### `held`

```c++
bool held () const;
```

Returns `true` if and only if the button is being held down.

### `released`

```c++
bool released () const;
```

Returns `true` if and only if the button was just released.

After the button has finished bouncing, it will take 7 process cycles, so 7ms if the buffer
size is 48 samples, for the change to be detected.
