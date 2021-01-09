# `Led` Class Reference

| Declared in | `erb/Led.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class Led;
```

`Led` is a type that abstracts a physical `led` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `Led` |
| [Destructor](#destructor) | Destructs the `Led` |
| [`on`](#on) | Turns the `Led` on |
| [`off`](#off) | Turns the `Led` off |
| [`pulse`](#pulse) | Shortly pulses the `Led` on |
| [`blink`](#blink) | Makes the `Led` blink |


## Member Functions

### Constructor

```c++
Led (Module & module, const dsy_gpio_pin & pin);
```

Constructs the `Led` with `pin` and attach it to its `module`.

> `pin` should use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~Led ();
```

Destructs the `Led`.

### `on`

```c++
void on (bool state = true);
```

Turns the `Led` on if and only if `state` is `true`, otherwise, turns it off.

### `off`

```c++
void off ();
```

Turns the `Led` off.

### `pulse`

```c++
void pulse (std::chrono::milliseconds duration = 200ms);
```

Pulses the `Led` for `duration` time, 200ms by default.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;  // 1.

   Led led (...);

   led.pulse (500ms);                     // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` for 500ms.

### `blink`

```c++
void blink (std::chrono::milliseconds half_period = 500ms);
```

Blinks the `Led` for `half_period` time, 500ms by default.

The `half_period` represents the duration of one LED state.
For example, when using 500ms, the total cycle on-off time is 1s.

The blink time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;  // 1.

   Led led (...);

   led.blink (200ms);                     // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Blinks the `led` for half period 200ms, representing a 400ms full on-off cycle.
