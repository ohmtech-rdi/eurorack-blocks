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
| [`set_brightness`](#set_brightness) | Sets the `Led` maximum brightness |
| [`on`](#on) | Turns the `Led` on |
| [`off`](#off) | Turns the `Led` off |
| [`pulse`](#pulse) | Shortly pulses the `Led` on |
| [`pulse_twice`](#pulse_twice) | Shortly pulses the `Led` on twice |
| [`pulse_thrice`](#pulse_thrice) | Shortly pulses the `Led` on thrice |
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

### `set_brightness`

```c++
void set_brightness (float brightness);
```

Sets the maximum brightness the `Led` can deliver.

> Note: only 32 levels of brightness are available when running on the Daisy target.

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
void pulse (float brightness = 1.f, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
```

Pulses the `Led` to `brightness`, for `duration` time using brightness decay `transition_function`.

`transition_function` is one of:
- `erb::step`: which makes abrupt changes of brightness after the specified duration, _this is the default_,
- `erb::inverse_step`: which makes abrupt changes of brightness immediatly but runs the specified duration,
- `erb::linear`: which makes linear perceptual changes of brightness,
- `erb::ease_in`: which reaches full brightness late,
- `erb::ease_out`: which reaches full brightness early,
- `erb::ease_in_out`: which produces a breathing effect.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;  // 1.

   Led led (...);

   led.pulse (1.f, 500ms);                // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` for 500ms.

### `pulse_twice`

```c++
void pulse_twice (float brightness = 1.f, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
```

Pulses the `Led` to `brightness` twice, for total `duration` time using brightness decay `transition_function`.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;  // 1.

   Led led (...);

   pulse_twice (1.f, 2s);                 // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` twice for a total duration of 2 seconds.

### `pulse_thrice`

```c++
void pulse_thrice (float brightness = 1.f, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
```

Pulses the `Led` to `brightness` 3 times, for total `duration` time using brightness decay `transition_function`.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;  // 1.

   Led led (...);

   pulse_thrice (1.f, 2s);                // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` 3 times for a total duration of 2 seconds.

### `blink`

```c++
void blink (float brightness = 1.f, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);
```

Blinks the `Led` every `period` time with `brightness`, 800ms by default.

`period` represents the total cycle on-off time.

The blink time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;  // 1.

   Led led (...);

   led.blink (1.f, 200ms);                // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Blinks the `led` for a very fast 200ms period, or 5 times per second.
