# `Led`

## Description

`Led` represents a monochromatic LED either driven by a digital output
or a [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) driver.


## Usage

### `erbui`

```erbui
module Example {
   control sync_led Led {     // 1.
      position 19.2mm, 111mm  // 2.
      style red               // 3.
      label "SYNC"            // 4.
      pin Pin1                // 5.
   }
}
```

1. Creates a LED with name `sync_led`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional physical board pin to use. If not set, the system will choose it automatically.

`style` is the LED style, and is one of:
- `tht, 3mm, red`, this is the default if `style` is omitted,
- `tht, 3mm, green`,
- `tht, 3mm, yellow`,
- `tht, 3mm, orange`.

### `c++`

`Led` is a type that abstracts a physical LED.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      if (ui.sync_gate.triggered ()) {
         ui.sync_led.pulse ();         // 1.
      }
   }
}
```

1. Pulses the led when the associated gate is triggered.


## `erbui` Control Reference

### `control` definition

```
control <name> Led { ... }
```

Where `<name>` is the name of the control.
More details can be found in [`control`](../language/grammar.md#control) documentation.

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

More details can be found in [`position`](../language/grammar.md#position) documentation.

### `style` property

```
style <name>
```

Where `<name>` is one of:
- `tht, 3mm, red`,
- `tht, 3mm, green`,
- `tht, 3mm, yellow`,
- `tht, 3mm, orange`.

More details can be found in [`style`](../language/grammar.md#style) documentation.

### `label` optional property

```
label "<text>"
```

Where `<text>` is the text displayed.
More details can be found in [`label`](../language/grammar.md#label) documentation.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`set_brightness`](#set_brightness) | Sets the `Led` maximum brightness |
| [`on`](#on) | Turns the `Led` on |
| [`off`](#off) | Turns the `Led` off |
| [`pulse`](#pulse) | Shortly pulses the `Led` on |
| [`pulse_twice`](#pulse_twice) | Shortly pulses the `Led` on twice |
| [`pulse_thrice`](#pulse_thrice) | Shortly pulses the `Led` on thrice |
| [`blink`](#blink) | Makes the `Led` blink |


## `c++` Member Functions

### `set_brightness`

```c++
void set_brightness (float brightness);
```

Sets the maximum brightness the `Led` can deliver.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

### `on`

```c++
void on (float brightness = 1.f);
```

Turns the `Led` on with `brightness`.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

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
   using namespace std::chrono_literals;  // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.pulse (1.f, 500ms);     // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` for 500ms.

### `pulse_twice`

```c++
void pulse_twice (float brightness = 1.f, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
```

Pulses the `Led` to `brightness` twice, for total `duration` time using brightness decay `transition_function`.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

void  process ()
{
   using namespace std::chrono_literals;  // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.pulse_twice (1.f, 2s);  // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` twice for a total duration of 2 seconds.

### `pulse_thrice`

```c++
void pulse_thrice (float brightness = 1.f, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
```

Pulses the `Led` to `brightness` 3 times, for total `duration` time using brightness decay `transition_function`.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

See `transition_function` possible values in [`pulse`](#pulse) reference above.

The pulse time can be changed, as shown below in the example:

```c++

#include <chrono>

void  process ()
{
   using namespace std::chrono_literals;  // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.pulse_thrice (1.f, 2s); // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Pulses the `led` 3 times for a total duration of 2 seconds.

### `blink`

```c++
void blink (float brightness = 1.f, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);
```

Blinks the `Led` every `period` time with `brightness`, 800ms by default.

> Warning: When using a non-PWM drived pin, any brightness value below 1 won't allow the
> LED to turn on.

`period` represents the total cycle on-off time.

The blink time can be changed, as shown below in the example:

```c++

#include <chrono>

void  process ()
{
   using namespace std::chrono_literals;  // 1.

   if (dsp.sync_triggered ()) {
      ui.sync_led.blink (1.f, 200ms);     // 2.
   }
}
```

1. Adds `chrono` duration literals to the current scope,
2. Blinks the `led` for a very fast 200ms period, or 5 times per second.
