# `Switch`

## Description

`Switch` represents a 2 or 3-position switch.


## Usage

### `erbui`

```erbui
module Example {
   control mode Switch {            // 1.
      position 19.2mm, 111mm        // 2.
      style on_off_on               // 3.
      label "ARM"                   // 4.
      rotation 90°ccw               // 5.
      pins Pin1, Pin2               // 6.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/05/switches-pcb-mount.jpg">

1. Creates a switch control with name `mode`,
2. Sets the control position on the front panel,
3. Sets the optional style of the control,
4. Sets the optional label for the control, using its default theme positioning,
5. Sets the optional rotation for the switch,
6. Sets the optional physical board pins to use, one for each extreme position.
   If not set, the system will choose them automatically.

> Dailywell toggle switches photo are from the [Thonk shop](https://www.thonk.co.uk/shop/sub-mini-toggle-switches/).

### `c++`

`Switch` is a type that abstracts a physical button block.

```c++
struct Example
{
   ExampleUi ui;
   
   void process () {
      if (ui.mode.position_first ()) {          // 1.
         ...
      } else if (ui.mode.position_center ()) {  // 2.
         ...
      } else if (ui.mode.position_last ()) {    // 3.
         ...
      }
   }
}
```

1. Checks if the switch position is on the left,
2. Checks if the switch position is in the middle,
3. Checks if the switch position is on the right.


## `erbui` Control Reference

### `control` definition

```
control <name> Switch { ... }
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

Where `<keywords>` is one of:
- `on_on` 2-position toggle switch (this is the default if not specified),
- `on_off_on` 3-position toggle switch.

More details can be found in [`style`](../erbui/grammar.html#style) documentation.

### `label` optional property

```
label "<text>"
```

Where `<text>` is the text displayed.
More details can be found in [`label`](../erbui/grammar.html#label) documentation.


### `rotation` optional property

```
rotation <angle>
```

Where `<angle>` is the angle to rotate the element.
The `rotation` value only supports quarter turns, so that `<angle>` can only be a multiple of 90.

 `<angle>` supported units are:
- `°ccw` (Counter Clockwise),
- `°ccw` (Clockwise),
- `°` (Clockwise, as the position y-axis goes from top to bottom).

More details can be found in [`rotation`](../erbui/grammar.html#rotation) documentation.


## `c++` Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [`position_first`](#position_first) | Returns true iff the switch position is first |
| [`position_center`](#position_center) | Returns true iff the switch position is centered |
| [`position_last`](#position_last) | Returns true iff the switch position is last |
| [`operation Position`](#operator-position) | Returns the switch position |


## `c++` Member Functions

### `position_first`

```c++
bool position_first () const;
```

Returns true if and only if the switch is in the first position.

The first position depends on the rotation. When no rotation is applied, it corresponds to
the left one.

After the switch has finished bouncing, it will take 7 process cycles, so 7ms if the buffer
size is 48 samples, for the change to be detected.

### `position_center`

```c++
bool position_center () const;
```

Returns true if and only if the switch is in the center position.

Even if a 2-position switch is used, the `Center` position needs to be taken into account
as it will transiently transition to it when going from left to right or right to left.

### `position_last`

```c++
bool position_last () const;
```

Returns true if and only if the switch is in the last position.

The first position depends on the rotation. When no rotation is applied, it corresponds to
the right one.

After the switch has finished bouncing, it will take 7 process cycles, so 7ms if the buffer
size is 48 samples, for the change to be detected.

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
