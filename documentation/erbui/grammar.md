# Erbui Grammar

This document describes what sequence of tokens form valid inputs of the language.


## How to Read the Grammar

The notation used to describe the formal grammar of `erbui` has the following conventions:

- An arrow (→) is used to mark grammar productions and can be read as "can consist of",
- Alternative grammar productions are either separated by verticals bars (|) or are broken into
   multiple grammar production rules lines,
- [Keywords](./lexical.html#keywords) and [symbols](./lexical.html#symbols) are indicated using
   **`bold inline code`** style text,
- Optional syntactic categories and literals are marked by a trailing subscript (<sub>_opt_</sub>),
- Syntactic category or literal repetitions of 0 or more are marked by a trailing subscript (<sub>_0+_</sub>),
- Syntactic category or literal repetitions of 1 or more are marked by a trailing subscript (<sub>_1+_</sub>).


## Global namespace

The global namespace is the root of the grammar. One and only one module declaration is
valid.

### Grammar

> _global-namespace_ → [module-declaration](#module)


## `module`

A `module` defines a physical module, a unique piece of hardware to produce.
it is a set of multiple `control`, `image`, `label`, `width`, `material`, etc. _declarations_.

### Grammar

> _module-declaration_ → **`module`** module-name module-inheritance-clause<sub>_opt_</sub> **`{`** module-entity<sub>_0+_</sub> **`}`** \
> _module-name_ → [identifier](./lexical.html#identifiers) \
> _module-inheritance-clause_ → **`extends`** [identifier](./lexical.html#identifiers) \
> _module-entity_ → [board-declaration](#board) \
> _module-entity_ → [width-declaration](#width) \
> _module-entity_ → [material-declaration](#material) \
> _module-entity_ → [route-declaration](#route) \
> _module-entity_ → [header-declaration](#header) \
> _module-entity_ → [footer-declaration](#footer) \
> _module-entity_ → [line-declaration](#line) \
> _module-entity_ → [label-declaration](#label) \
> _module-entity_ → [sticker-declaration](#sticker) \
> _module-entity_ → [image-declaration](#image) \
> _module-entity_ → [control-declaration](#control) \
> _module-entity_ → [alias-declaration](#alias) \
> _module-entity_ → [exclude-declaration](#exclude)

### Extensions

The module inheritance clause loads the content of the standard library module with its
identifier name, and populates the extended module with all the inherited module definitions.

For example:

```erbui
// In standard library
module Foo {
   width 12hp
   label "Some Text"
}

// User
module Bar extends Foo {
   header { label "BAR" }
}
```

Is equivalent to:

```erbui
module Bar {
   width 12hp
   label "Some Text"
   header { label "BAR" }
}
```


## `material`

A `material` defines the actual material used to produce the module front panel.

### Grammar

> _material-declaration_ → **`material`** material-name material-color<sub>_opt_</sub> \
> _material-name_ → **`pcb`** \
> _material-name_ → **`aluminum`** \
> _material-name_ → **`brushed_aluminum`** \
> _material-color_ → **`natural`** \
> _material-color_ → **`black`**


## `route`

A `route` defines the way the front PCB is routed, `wire` if not specified (which requires hand soldering).
`manual` allows to manually route the front PCB or use an autorouteur. In that case, all the
hand soldering pads are removed to leave more space for routing.

### Grammar

> _route-declaration_ → **`route`** route-mode \
> _route-mode_ → **`wire`** \
> _route-mode_ → **`manual`**


## `board`

A `board` defines the [board](../../boards/) used for the back panel. Each board comes with
a specific set of digital, analog and audio pins and their associated names for both inputs and
outputs.

A `board` definition can be be made inline as well, and is typically used for custom boards.

### Grammar

> _board-declaration_ → **`board`** [identifier](./lexical.html#identifiers) \
> _board-declaration_ → **`board`** **`{`** board-entity<sub>_0+_</sub> **`}`** \
> _board-entity_ → board-class-declaration \
> _board-entity_ → board-include-declaration \
> _board-entity_ → board-pcb-declaration \
> _board-entity_ → board-pin-declaration \
> _board-entity_ → board-pins-declaration \
> _board-class-declaration_ → **`class`** [string-literal](./lexical.html#string-literals) \
> _board-include-declaration_ → **`include`** [string-literal](./lexical.html#string-literals) \
> _board-pcb-declaration_ → **`pcb`** [string-literal](./lexical.html#string-literals) \
> _board-pin-declaration_ → **`pin`** [identifier](./lexical.html#identifiers) board-pin-clause \
> _board-pins-declaration_ → **`pins`** [identifier](./lexical.html#identifiers) board-pin-range board-pin-clause \
> _board-pin-range_ → **`..`** [integer-literal](./lexical.html#integer-literals) \
> _board-pin-clause_ → board-pin-kinds-declaration **`{`** board-pin-entity<sub>_0+_</sub> **`}`** \
> _board-pin-entity_ → board-pin-bind-declaration \
> _board-pin-entity_ → board-pin-type-declaration \
> _board-pin-kinds-declaration_ → [control-kind](../controls/README.md) \
> _board-pin-kinds-declaration_ → [control-kind](../controls/README.md) **`,`** board-pin-kinds-declaration \
> _board-pin-bind-declaration_ → **`bind`** [string-literal](./lexical.html#string-literals) \
> _board-pin-type-declaration_ → **`type`** board-pin-type-name \
> _board-pin-type-name_ → **`gpio`** \
> _board-pin-type-name_ → **`pwm`** \
> _board-pin-type-name_ → **`dac`**

See individual [boards](../boards/) reference for the available pins configuration for each board.
Inline boards replicate the board `definition.py` python format, but using `erbui` syntax.


## `width`

`width` defines the module width in HP.

If a [board](#board) is defined but no width is defined, then the actual width will be inherited from
the board width.

Only a [specific set of integer HP widths](http://www.doepfer.de/a100_man/a100m_e.htm) are valid.

### Grammar

> _width-declaration_ → **`width`** [distance-literal](./lexical.html#distance-literals)


## `header`

The `header` defines a region at the top of the module, typically used for the
module logo.

### Grammar

> _header-declaration_ → **`header`** **`{`** header-entity<sub>_0+_</sub> **`}`** \
> _header-entity_ → [label-declaration](#label) \
> _header-entity_ → [image-declaration](#image)


## `footer`

The `footer` defines a region at the bottom of the module, typically used for the
company logo.

### Grammar

> _footer-declaration_ → **`footer`** **`{`** footer-entity<sub>_0+_</sub> **`}`** \
> _footer-entity_ → [label-declaration](#label) \
> _footer-entity_ → [image-declaration](#image)

When no footer is defined, an implicit footer is created with the ERB logo.


## `control`

A `control` is an element of the module that is generally apparent on the front panel
and with which the end-user can interact with.

### Grammar

> _control-declaration_ → **`control`** control-name [control-kind](../controls/README.md) **`{`** control-entity<sub>_0+_</sub> **`}`** \
> _control-name_ → [identifier](./lexical.html#identifiers) \
> _control-entity_ → [mode-declaration](#mode) \
> _control-entity_ → [position-declaration](#position) \
> _control-entity_ → [rotation-declaration](#rotation) \
> _control-entity_ → [style-declaration](#style) \
> _control-entity_ → [label-declaration](#label) \
> _control-entity_ → [image-declaration](#image) \
> _control-entity_ → [pins-declaration](#pins) \
> _control-entity_ → [pin-declaration](#pin) \
> _control-entity_ → [normalling-declaration](#normalling)

### Language Bindings

_control-name_ is exported to the target language used to develop the module DSP, such
as C++ or Max.

For example the following `erbui` source code:

```erbui
module Foo {
   control vco_freq Pot { ... }
}
```

Exports the `vco_freq` in C++:

```c++
void  process () {
   float val = ui.vco_freq;
}
``` 

### Supported Entities

Some grammar production rules are specific to some control kinds.
For example `Button` supports `pin` but not `pins`, and conversely, `Switch` supports
`pins` but does not support `pin`.

See individual [controls](../controls/README.md) reference for a list of supported features for each control.


## `alias`

An `alias` gives an alternative name to a control name. It is typically used when extending
a standard library board, to give appropriate names to the entities of a module.

### Grammar

> _alias-declaration_ → **`alias`** [identifier](./lexical.html#identifiers) alias-reference \
> _alias-reference_ → [identifier](./lexical.html#identifiers)


For example:

```erbui
// Standard library daisy_field.erbui
module daisy_field {
   ...
   control pot1 Pot { ... }
   control pot2 Pot { ... }
}

// User code Foo.erbui
module Foo extends daisy_field {
   alias vco_freq pot2
}
```

```c++
// Foo.cpp
void  process ()
{
   float freq_val = ui.pot1;        // not great
   float freq_val2 = ui.vco_freq;   // better
}
```


## `exclude`

An `exclude` allows to prevent the use of one or more pins to be used for the entire module.
It is typically used when a pin is colliding with a control on the board, but it makes more
sense to exclude the pin rather than move the control.

### Grammar

> _exclude-declaration_ → **`exclude`** exclude-entity \
> _exclude-entity_ → [pins-declaration](#pins) \
> _exclude-entity_ → [pin-declaration](#pin)

For example:

```erbui
module Foo {
   board kivu12
   exclude pins P1, P2

   control pot1 Pot { ... }
   control pot2 Pot { ... }
}
```

The pins of `pot1` and `pot2` will be respectively `P3` and `P4`, instead of `P1` and `P2` which
are excluded.


## `mode`

A `mode` defines a range of values presented by the [`control`](#control).

### Grammar

> _mode-declaration_ → **`mode`** mode-value \
> _mode-value_ → **`normalized`** \
> _mode-value_ → **`bipolar`**

### `normalized`

`normalized` represents a range of values from `0` to `1`.
When the control has a jack connector for inputs or outputs,
it maps the value linearly from 0V to 5V.

This is the default mode for `Pot` and `Trim`.

### `bipolar`

`bipolar` represents a range of values from `-1` to `1`.
When the control has a jack connector for inputs or outputs,
it maps the value linearly from –5V to 5V.

This is the default mode for `CvIn` and `CvOut`.

See individual [controls](../controls/README.md) reference for a list of supported modes for each control.


## `style`

A `style` instructs the hardware parts to use for a `control`.
This can represent the component part as mounted on the PCB
as well as one or more decoration elements that the end-user will manipulate,
such as a style of knob.

The style is given as a list of keywords, which represents the developer intent.
The intent can represent for example the color of a LED, or the brand and size of a pot.

Given a manufacturer, each control kind (_eg._ `Pot`, `Led`, `AudioIn`) as a list of sets of
style keywords. When the developer specifies a list of keywords representing their intent,
the style engine selects the first set of keywords in the manufacturer list which matches
best the developer-defined set of keywords.

When no style is specified, the first item of the manufacturer list is returned, which is designed
so that the resulting combination of parts is the most popular for this control kind.

### Grammar

> _style-declaration_ → **`style`** style-argument-list \
> _style-argument-list_ → style-name \
> _style-argument-list_ → style-name **`,`** style-argument-list

See individual [controls](../controls/README.md) reference for a list of supported styles for each control.


## `line`

A `line` is a graphic element printed on the front panel, usually used to indicate a conceptual
link between a pair of controls.

### Grammar

> _line-declaration_ → **`line`** **`{`** line-entity<sub>_0+_</sub> **`}`** \
> _line-entity_ → [position-declaration](#position)


## `offset`

An `offset` represents a relative shift from a position, typically used to reposition a control's label.

### Grammar

> _offset-declaration_ → **`offset`** [distance-literal](./lexical.html#distance-literals) **`,`** [distance-literal](./lexical.html#distance-literals)


## `rotation`

A `rotation` represents a rotation of a front panel element,
typically used for [switches](../controls/Switch.md).

### Grammar

> _rotation-declaration_ → **`rotation`** [rotation-literal](./lexical.html#rotation-literals)

See individual [controls](../controls/README.md) reference for a list of supported rotations for each control, if any.


## `position`

A `position` represents the position of a [control](#control) on the front panel.
Usually, the position is relative to the natural center of the control, when applicable.

### Grammar

> _position-declaration_ → **`position`** [distance-literal](./lexical.html#distance-literals) **`,`** [distance-literal](./lexical.html#distance-literals)

See individual [controls](../controls/README.md) reference for the center definition for each control.


## `sticker`

A `sticker` represents a virtual sticker glued on the front panel.
It is usually used in conjunction of `alias` to display the real name of a value on top of
the default board one.

The `sticker` is only displayed when using the simulator. In particular, it is not present in
the generated front panel files for hardware production.

### Grammar

> _sticker-declaration_ → **`sticker`** [string-literal](./lexical.html#string-literals) sticker-body<sub>_opt_</sub> \
> _sticker-body_ → **`{`** sticker-entity<sub>_0+_</sub> **`}`**  \
> _sticker-entity_ → [position-declaration](#position) \
> _sticker-entity_ → [positioning-declaration](#positioning) \
> _sticker-entity_ → [offset-declaration](#offset)


## `label`

A `label` is a piece of text printed on the front panel, and usually represents the name of
the associated control, or group of controls.

A `label` can be either defined in a control with its positioning relative to the control, or
can be defined freely in the module with a position relative to the module.

### Grammar

> _label-declaration_ → **`label`** [string-literal](./lexical.html#string-literals) label-body<sub>_opt_</sub> \
> _label-body_ → **`{`** label-entity<sub>_0+_</sub> **`}`**  \
> _label-entity_ → [position-declaration](#position) \
> _label-entity_ → [positioning-declaration](#positioning) \
> _label-entity_ → [offset-declaration](#offset)


## `image`

An `image` is a picture printed on the front panel, and is usually used to make a complete
custom front panel design.
The path represents a [Scalable Vector Graphics (SVG)](https://en.wikipedia.org/wiki/Scalable_Vector_Graphics)
file relative to the `erbui` file where the `image` definition takes place.

### Grammar

> _image-declaration_ → **`image`** [path-literal](./lexical.html#path-literals)


## `pin`

A `pin` represents the physical board pin used by a [control](#control).

### Grammar

> _pin-declaration_ → **`pin`** pin-name

See individual [boards](../boards/) reference for the available pins configuration for each board.

The `pin` property is only supported for controls that support exactly one data pin.
See individual [controls](../controls/README.md) reference for a list of pins for each control.


## `pins`

A `pin` represents a set of physical board pins used by a [control](#control).

### Grammar

> _pins-declaration_ → **`pins`** pins-argument-list \
> _pins-argument-list_ → pin-name \
> _pins-argument-list_ → pin-name **`,`** pins-argument-list

See individual [boards](../boards/) reference for the available pins configuration for each board.

The `pins` property is only supported for controls that support more than one data pin.
See individual [controls](../controls/README.md) reference for a list of pins for each control.


## `normalling`

A `normalling` represents a link from the current [control](#control) to the referenced control.

### Grammar

> _normalling-declaration_ → **`normalling`** control-reference \
> _normalling-declaration_ → **`normalling`** **`nothing`** \
> _control-reference_ → [identifier](./lexical.html#identifiers)

`normalling` allows to take the signal of an unplugged input from another input, or "nothing".
Nothing allows to detect jack detection.

For example:

```erbui
module MonoOrStereo {
   ...
   control input_left AudioIn { ... }

   control input_right AudioIn {
      ...
      normalling input_left
   }
}
```

In the example above, when no audio jack is connected into the right input,
the signal seen on `input_right` will be the signal of `input_left`.

This typically allows to a module to work with mono or stereo inputs, or to detect if a user
has connected a jack on a clock input to lock tempo to the rest of the system.

This property is only supported for `GateIn`, `CvIn` and `AudioIn` control kinds.


## `positioning`

A `positioning` represents a positioning of a graphic element relative to its control center.
It is usually used to position labels for a control.

### Grammar

> _positioning-declaration_ → **`positioning`** positioning-name \
> _positioning-name_ → **`center`** \
> _positioning-name_ → **`left`** \
> _positioning-name_ → **`top`** \
> _positioning-name_ → **`right`** \
> _positioning-name_ → **`bottom`**

### `center`

This `positioning` centers the graphic element with the center of its control.

### `left`

This `positioning` places the graphic element to the left of its control.

### `top`

This `positioning` places the graphic element to the top of its control.

### `right`

This `positioning` places the graphic element to the right of its control.

### `bottom`

This `positioning` places the graphic element to the bottom of its control.
