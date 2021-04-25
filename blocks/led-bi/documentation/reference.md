# `LedBi` Class Reference

| Declared in | `erb/LedBi.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class LedBi;
```

`LedBi` is a type that abstracts a physical `led-bi` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `LedBi` |
| [Destructor](#destructor) | Destructs the `LedBi` |
| [`set_brightness`](#set_brightness) | Sets the `LedBi` maximum brightness |
| [`on`](#on) | Turns the `LedBi` on with specified color |
| [`off`](#off) | Turns the `LedBi` off |
| [`pulse`](#pulse) | Shortly pulses the `LedBi` on with specified color |
| [`pulse_twice`](#pulse_twice) | Shortly pulses the `LedBi` on twice with specified color |
| [`pulse_thrice`](#pulse_thrice) | Shortly pulses the `LedBi` on thrice with specified color |
| [`blink`](#blink) | Makes the `LedBi` blink with specified color |


## Member Functions

### Constructor

```c++
LedBi (Module & module, const dsy_gpio_pin & pin_r, const dsy_gpio_pin & pin_g);
```

Constructs the `LedBi` with red `pin_r` and green `pin_g`, and attach it to its `module`.

> `pin_r` and `pin_g` should use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~LedBi ();
```

Destructs the `LedBi`.

### `set_brightness`

```c++
void set_brightness (float brightness);
```

Sets the maximum brightness the `LedBi` can deliver.

> Note: only 32 levels of brightness are available when running on the Daisy target.

### `on`

```c++
void on (Color color);
```

Turns the `LedBi` on with `color`. The `Color` structure has two fields, one `r` representing
the amount of red in the color, one `g` representing the amount green in the color.

Alternatively, one of the convenient color factory functions can be used:
- `LedBi::Color::none` which represents the absence of color (_ie._ the LED is off),
- `LedBi::Color::red` which represents a red color,
- `LedBi::Color::yellow` which represents a yellow color,
- `LedBi::Color::green` which represents a green color.

The color space is unspecified and depends on the physical LED used. Please refer to the
LED datasheet for spectrum informations.

```c++

#include <chrono>

int main (void)
{
   LedBi led (...);

   led.on ({1.f, 0.f});              // 1.
   led.on (LedBi::Color::yellow ()); // 2.
}
```

1. Sets the LED to a red color,
2. Sets the LED to a yellow color.

### `off`

```c++
void off ();
```

Turns the `LedBi` off.

### `pulse`

```c++
void pulse (Color color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
```

Pulses the `LedBi` to `color`, for `duration` time using brightness decay `transition_function`.

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

   led.pulse (LedBi::Color::red (), 500ms); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` for 500ms.

### `pulse_twice`

```c++
void pulse_twice (Color color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
```

Pulses the `LedBi` to `color` twice, for total `duration` time using brightness decay `transition_function`.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;   // 1.

   Led led (...);

   pulse_twice (LedBi::Color::red (), 2s); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` twice for a total duration of 2 seconds.

### `pulse_thrice`

```c++
void pulse_thrice (Color color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
```

Pulses the `LedBi` to `color` 3 times, for total `duration` time using brightness decay `transition_function`.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;    // 1.

   Led led (...);

   pulse_thrice (LedBi::Color::red (), 2s); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` 3 times for a total duration of 2 seconds.

### `blink`

```c++
void blink (Color color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);
```

Blinks the `LedBi` every `period` time with `color`, 800ms by default.

`period` represents the total cycle on-off time.

The blink time can be changed, as shown below in the example:

```c++

#include <chrono>

int main (void)
{
   using namespace std::chrono_literals;    // 1.

   Led led (...);

   led.blink (LedBi::Color::red (), 200ms); // 2.
}
```

1. Adds `chrono` duration literals to the current scope,
2. Blinks the `led` for a very fast 200ms period, or 5 times per second.
