# Documentation

## Reference Documentation

### `erbui` Language Reference

#### Syntax

- [Lexical Structure](./language/lexical.md) describes what sequence of characters form valid
   tokens of the language,
- [Grammar](./language/grammar.md) describes what sequence of tokens form valid
   inputs of the language.

#### Keywords

- [`module`](./language/grammar.md#module) describes a module declaration,
- [`control`](./language/grammar.md#control) describes a control declaration,
- [`board`](./language/grammar.md#board) describes a module's board property,
- [`width`](./language/grammar.md#width) describes a module's width property,
- [`header`](./language/grammar.md#header) describes a module's header declaration,
- [`footer`](./language/grammar.md#footer) describes a module's footer declaration,
- [`line`](./language/grammar.md#line) describes a module's graphical line declaration,
- [`sticker`](./language/grammar.md#sticker) describes a module's sticker declaration,
- [`image`](./language/grammar.md#image) describes a module or control's image declaration or property,
- [`label`](./language/grammar.md#label) describes a module or control's label declaration or property,
- [`pin`](./language/grammar.md#pin) describes a control's pin property,
- [`pins`](./language/grammar.md#pins) describes a control's multiple pins property,
- [`mode`](./language/grammar.md#mode) describes a control's analog voltage range property,
- [`position`](./language/grammar.md#position) describes a control's position property,
- [`rotation`](./language/grammar.md#rotation) describes a control's rotation property,
- [`style`](./language/grammar.md#style) describes a control's style property,
- [`positioning`](./language/grammar.md#positioning) describes a label or sticker's relative positioning
   property to its control,
- [`offset`](./language/grammar.md#offset) describes a label or sticker's position offset property to its
   control.

### Controls Reference

#### Audio Signals

- [`AudioIn`](./controls/AudioIn.md) represents an audio input block,
- [`AudioOut`](./controls/AudioOut.md) represents an audio output block.

#### Control Voltages

- [`CvIn`](./controls/CvIn.md) represents a CV input block,
- [`CvOut`](./controls/CvOut.md) represents a CV output block.

#### Trigger, Gate and Clock Signals

- [`GateIn`](./controls/GateIn.md) represents a gate input block,
- [`GateOut`](./controls/GateOut.md) represents a gate output block.

#### Human Interface Devices

- [`Button`](./controls/Button.md) represents a switch button,
- [`Led`](./controls/Led.md) represents a monochromatic LED,
- [`LedBi`](./controls/LedBi.md) represents a dichromatic LED,
- [`LedRgb`](./controls/LedRgb.md) represents a RGB LED,
- [`Pot`](./controls/Pot.md) represents a potentiometer block,
- [`Switch`](./controls/Switch.md) represents a 2 or 3 positions toggle switch,
- [`Trim`](./controls/Trim.md) represents a trim potentiometer block.
