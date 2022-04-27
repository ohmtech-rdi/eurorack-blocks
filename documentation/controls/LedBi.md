# `LedBi`

## Description

`LedBi` represents a dichromatic LED either driven by a digital output
or a [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) driver.


## Usage

### `erbui`

```erbui
module Example {
   control sync_led LedBi {         // 1.
      position 19.2mm, 111mm        // 2.
      style green_red               // 3.
      label "SYNC"                  // 4.
      pins Pin1, Pin2               // 5.
   }
}
```

1. Creates a LED with name `sync_led`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pins to use:
   - First pin denotes the *green* pin,
   - Second pin denotes the *red* pin.
   If not set, the system will choose them automatically.

### `c++`

`LedBi` is a type that abstracts a physical LED.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      if (ui.sync_gate.triggered ()) {
         ui.sync_led.pulse (ColorBi::yellow ());   // 1.
      }
   }
}
```

1. Pulses the led with a yellow color when the associated gate is triggered.


## `erbui` Control Reference

### `control` definition

```
control <name> LedBi { ... }
```

Where `<name>` is the name of the control.
More details can be found in [`control`](../erbui/grammar.html#control) documentation.

### `position` property

```
position <x>, <y>
```

Sets the position of the control, where the axis origin is the top-left corner.
The `x` axis is oriented from left to right, and the `y` axis is oriented from top to bottom.

The position component values are expressed with their unit, either `mm` or `hp`.

Example:
```
position 2hp, 15mm
```

More details can be found in [`position`](../erbui/grammar.html#position) documentation.

### `style` optional property

```
style <keywords>
```

Where `<keywords>` can only be (for now):
- `3mm, green_red` (this is the default if not specified).

More details can be found in [`style`](../erbui/grammar.html#style) documentation.

### `label` optional property

```
label "<text>"
```

Where `<text>` is the text displayed.
More details can be found in [`label`](../erbui/grammar.html#label) documentation.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`set_brightness`](#set_brightness) | Sets the `LedBi` maximum brightness |
| [`on`](#on) | Turns the `LedBi` on with specified color |
| [`off`](#off) | Turns the `LedBi` off |
| [`pulse`](#pulse) | Shortly pulses the `LedBi` on with specified color |
| [`pulse_twice`](#pulse_twice) | Shortly pulses the `LedBi` on twice with specified color |
| [`pulse_thrice`](#pulse_thrice) | Shortly pulses the `LedBi` on thrice with specified color |
| [`blink`](#blink) | Makes the `LedBi` blink with specified color |


## `c++` Member Functions

### `set_brightness`

```c++
void set_brightness (float brightness);
```

Sets the maximum brightness the `LedBi` can deliver.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

### `on`

```c++
void on (ColorBi color);
```

Turns the `LedBi` on with `color`. The `Color` structure has two fields, one `r` representing
the amount of red in the color, one `g` representing the amount green in the color.

Alternatively, one of the convenient color factory functions can be used:
- `ColorBi::none` which represents the absence of color (_ie._ the LED is off),
- `ColorBi::red` which represents a red color,
- `ColorBi::yellow` which represents a yellow color,
- `ColorBi::green` which represents a green color.

The color space is unspecified and depends on the physical LED used. Please refer to the
LED datasheet for spectrum informations.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

```c++

void  process ()
{
   ui.sync_led.on ({1.f, 0.f});           // 1.
   ui.sync_led.on (ColorBi::yellow ());   // 2.
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
void pulse (ColorBi color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
```

Pulses the `LedBi` to `color`, for `duration` time using brightness decay `transition_function`.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

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

void  process ()
{
   using namespace std::chrono_literals;           // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.pulse (ColorBi::red (), 500ms);  // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` for 500ms.

### `pulse_twice`

```c++
void pulse_twice (ColorBi color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
```

Pulses the `LedBi` to `color` twice, for total `duration` time using brightness decay `transition_function`.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

void  process ()
{
   using namespace std::chrono_literals;              // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.pulse_twice (ColorBi::red (), 2s);  // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` twice for a total duration of 2 seconds.

### `pulse_thrice`

```c++
void pulse_thrice (ColorBi color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
```

Pulses the `LedBi` to `color` 3 times, for total `duration` time using brightness decay `transition_function`.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

void  process ()
{
   using namespace std::chrono_literals;              // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.pulse_thrice (ColorBi::red (), 2s); // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` 3 times for a total duration of 2 seconds.

### `blink`

```c++
void blink (ColorBi color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);
```

Blinks the `LedBi` every `period` time with `color`, 800ms by default.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

`period` represents the total cycle on-off time.

The blink time can be changed, as shown below in the example:

```c++

#include <chrono>

void  process ()
{
   using namespace std::chrono_literals;           // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.blink (ColorBi::red (), 200ms);  // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Blinks the `led` for a very fast 200ms period, or 5 times per second.
