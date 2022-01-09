# Documentation

## Reference Documentation

### `erbb` Language Reference

#### Syntax

- [Lexical Structure](./erbb/lexical.md) describes what sequence of characters form valid
   tokens of the language,
- [Grammar](./erbb/grammar.md) describes what sequence of tokens form valid
   inputs of the language.

#### Keywords

- [`module`](./erbb/grammar.md#module) describes a module declaration,
- [`import`](./erbb/grammar.md#import) describes an import statement,
- [`base`](./erbb/grammar.md#base) describes an header search path,
- [`define`](./erbb/grammar.md#define) describes a define declaration,
- [`sources`](./erbb/grammar.md#sources) describes a module sources declaration,
- [`file`](./erbb/grammar.md#file) describes a module sources file declaration.


### `erbui` Language Reference

#### Syntax

- [Lexical Structure](./erbui/lexical.md) describes what sequence of characters form valid
   tokens of the language,
- [Grammar](./erbui/grammar.md) describes what sequence of tokens form valid
   inputs of the language.

#### Keywords

- [`module`](./erbui/grammar.md#module) describes a module declaration,
- [`control`](./erbui/grammar.md#control) describes a control declaration,
- [`board`](./erbui/grammar.md#board) describes a module's board property,
- [`width`](./erbui/grammar.md#width) describes a module's width property,
- [`header`](./erbui/grammar.md#header) describes a module's header declaration,
- [`footer`](./erbui/grammar.md#footer) describes a module's footer declaration,
- [`line`](./erbui/grammar.md#line) describes a module's graphical line declaration,
- [`sticker`](./erbui/grammar.md#sticker) describes a module's sticker declaration,
- [`image`](./erbui/grammar.md#image) describes a module or control's image declaration or property,
- [`label`](./erbui/grammar.md#label) describes a module or control's label declaration or property,
- [`pin`](./erbui/grammar.md#pin) describes a control's pin property,
- [`pins`](./erbui/grammar.md#pins) describes a control's multiple pins property,
- [`mode`](./erbui/grammar.md#mode) describes a control's analog voltage range property,
- [`position`](./erbui/grammar.md#position) describes a control's position property,
- [`rotation`](./erbui/grammar.md#rotation) describes a control's rotation property,
- [`style`](./erbui/grammar.md#style) describes a control's style property,
- [`positioning`](./erbui/grammar.md#positioning) describes a label or sticker's relative positioning
   property to its control,
- [`offset`](./erbui/grammar.md#offset) describes a label or sticker's position offset property to its
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
