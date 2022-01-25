# Erbb Lexical Structure

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
- Either a semantic that the developer will define, such as a `data` name,
- Or a dynamic property of the language, interpreted at configuration time,
   such as a `AudioSample` name.

The following are examples of identifiers:

```erbb
module myGreatModule { ... }
data sample
```

In the above examples, `myGreatModule` and `sample` are identifiers.


## Keywords

Unlike identifiers, _keywords_ are predefined list of characters built into the language.
In `erbb`, they can be seen as directives, and each directive can be seen either like
a definition of _something_ in the physical world, or a property of that _thing_ in the
physical world.

The following are examples of keywords:

```erbb
module
import
base
defines
sources
```


## Symbols

_Symbols_ are predefined list of ponctuation characters built into the language.

The following are examples of symbols:

```erbb
{ }
```


## Literals

A literal is the source code representation of a value of a type, such as a number or string.

The following are examples of literals:

```erbb
"some text"
123
```

Literals in `erbb` define a type implicitly.

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
