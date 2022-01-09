# Lexical Structure

This document describes what sequence of characters form valid tokens of the language.


## Whitespace and Comments

Whitespace allows to separate tokens in the source file.

Comments are treated as whitespace by the transpiler.
Single line comments begin with `//` and continue until a line feed (`0x0a`)
or carriage return (`0x0d`).
Multiline comments begin with `/*` and end with `*/`. They can't be nested.


## Identifiers

_Identifiers_ begin with an uppercase or lowercase letter A through Z.
After the first character, digits or underscore (`_`) are also allowed.

_Identifiers_ represent tokens of some kind of entity.
They are names with implicitly defined semantic:
- Either a semantic that the developer will define, such as a `control` name,
- Or a dynamic property of the language, interpreted at configuration time,
   such as a `board` name.

The following are examples of identifiers:

```erbui
control myGreatControl { ... }
board kivu12
```

In the above examples, `myGreatControl` and `kivu12` are identifiers.


## Keywords

Unlike identifiers, _keywords_ are predefined list of characters built into the language.
In `erbui`, they can be seen as directives, and each directive can be seen either like
a definition of _something_ in the physical world, or a property of that _thing_ in the
physical world.

The following are examples of keywords:

```erbui
module
control
width
aluminum
black
```


## Symbols

_Symbols_ are predefined list of ponctuation characters built into the language.

The following are examples of symbols:

```erbui
{ }
,
```


## Literals

A literal is the source code representation of a value of a type, such as a number or string.

The following are examples of literals:

```erbui
12mm
2hp
"some text"
90°
```

Literals in `erbui` define a type implicitly.

### Distance literals

_Distance literals_ represent float-point values that can be interpreted as distances in the
physical world. As such, _distance literals_ comes with a unit.

Supported units are [SI units](https://en.wikipedia.org/wiki/SI_base_unit) `mm` or `cm`, as well
as `hp` which represents exactly 5.08mm. The `hp` unit is the standard in Eurorack, and
represents 0.2 inch in the imperial system, used a lot in electronics, yet defined in
SI metrics units (as exactly 5.08mm).

The following are examples of distance literals:

```erbui
12mm
10cm
2hp
```

### Rotation literals

_Rotation literals_ represent a specific set of integer values that can be interpreted as angles
in the physical world. As such, _rotation literals_ comes with a unit.

Supported units are only degrees (`°`) based. The base degree follows axis orientation and is
therefore **clockwise**. The units can specify explicit orientation with proper suffix,
`ccw` for counterclokwise, and `cw` for clockwise.

Finally only a specific set of rotations are supported, usually multiples of 90. See each `control`
reference for supported rotation, if any.

The following are examples of rotation literals:

```erbui
90°
90°ccw
180°cw
```

### String Literals

A string literal is a sequence of characters surrounded by quotation marks.
A string literal is surrounded by double quotation marks and has the following form:

```
"characters"
```

String literals do not support any escaping sequence.
They are a sequence of ASCII-7 characters of whatever the underlying rendering font can
support when converting a stream of character into glyphs.

The following are examples of string literals:

```
"Hello, world!"
"FREQ"
```

### Path Literals

A path literal is a sequence of characters surrounded by quotation marks.
A path literal is surrounded by double quotation marks and has the following form:

```
"characters"
```

Path literals do not support any escaping sequence.
They are a sequence of ASCII-7 characters.

The following are examples of path literals:

```
"relative/path/to/my_file.svg"
"../shared/design.svg"
```
