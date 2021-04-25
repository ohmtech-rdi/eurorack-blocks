# `LedRgb` Class Reference

| Declared in | `erb/LedRgb.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class LedRgb;
```

`LedRgb` is a type that abstracts a physical `led-rgb` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `LedRgb` |
| [Destructor](#destructor) | Destructs the `LedRgb` |
| [`set_brightness`](#set_brightness) | Sets the `LedRgb` maximum brightness |
| [`on`](#on) | Turns the `LedRgb` on with specified color |
| [`off`](#off) | Turns the `LedRgb` off |
| [`pulse`](#pulse) | Shortly pulses the `LedRgb` on with specified color |
| [`pulse_twice`](#pulse_twice) | Shortly pulses the `LedRgb` on twice with specified color |
| [`pulse_thrice`](#pulse_thrice) | Shortly pulses the `LedRgb` on thrice with specified color |
| [`blink`](#blink) | Makes the `LedRgb` blink with specified color |


## Member Functions

### Constructor

```c++
LedRgb (Module & module, const dsy_gpio_pin & pin_r, const dsy_gpio_pin & pin_g, const dsy_gpio_pin & pin_b);
```

Constructs the `LedRgb` with red `pin_r`, green `pin_g` and blue `pin_b`, and attach it to its `module`.

> `pin_r`, `pin_g` and `pin_b` should use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~LedRgb ();
```

Destructs the `LedRgb`.

### `set_brightness`

```c++
void set_brightness (float brightness);
```

Sets the maximum brightness the `LedRgb` can deliver.

> Note: only 32 levels of brightness are available when running on the Daisy target.

### `on`

```c++
void on (Color color);
```

Turns the `LedRgb` on with `color`. The `Color` structure has two fields, one `r` representing
the amount of red in the color, one `g` representing the amount green in the color, and one
`b` representing the amount of blue in the color.

Alternatively, one of the convenient color factory functions can be used:
- `LedRgb::Color::none` which represents the absence of color (_ie._ the LED is off),
- `LedRgb::Color::red` which represents a red color,
- `LedRgb::Color::blue` which represents a blue color,
- `LedRgb::Color::green` which represents a green color.

The color space is unspecified and depends on the physical LED used. Please refer to the
LED datasheet for spectrum informations.

```c++

#include <chrono>

int main (void)
{
   LedRgb led (...);

   led.on ({1.f, 0.f, 0.f});          // 1.
   led.on (LedRgb::Color::blue ());   // 2.
}
```

1. Sets the LED to a red color,
2. Sets the LED to a blue color.

### `off`

```c++
void off ();
```

Turns the `LedRgb` off.

### `pulse`

```c++
void pulse (Color color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
```

Pulses the `LedRgb` to `color`, for `duration` time using brightness decay `transition_function`.

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
   using namespace std::chrono_literals;    // 1.

   Led led (...);

   led.pulse (LedRgb::Color::red (), 500ms); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` for 500ms.

### `pulse_twice`

```c++
void pulse_twice (Color color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
```

Pulses the `LedRgb` to `color` twice, for total `duration` time using brightness decay `transition_function`.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;   // 1.

   Led led (...);

   pulse_twice (LedRgb::Color::red (), 2s); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` twice for a total duration of 2 seconds.

### `pulse_thrice`

```c++
void pulse_thrice (Color color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
```

Pulses the `LedRgb` to `color` 3 times, for total `duration` time using brightness decay `transition_function`.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;    // 1.

   Led led (...);

   pulse_thrice (LedRgb::Color::red (), 2s); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` 3 times for a total duration of 2 seconds.

### `blink`

```c++
void blink (Color color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);
```

Blinks the `LedRgb` every `period` time with `color`, 800ms by default.

`period` represents the total cycle on-off time.

The blink time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;    // 1.

   Led led (...);

   led.blink (LedRgb::Color::red (), 200ms); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Blinks the `led` for a very fast 200ms period, or 5 times per second.
