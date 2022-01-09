# Grammar

This document describes what sequence of tokens form valid inputs of the language.


## How to Read the Grammar

The notation used to describe the formal grammar of `erbb` has the following conventions:

- An arrow (→) is used to mark grammar productions and can be read as "can consist of",
- Alternative grammar productions are either separated by verticals bars (|) or are broken into
   multiple grammar production rules lines,
- [Keywords](./lexical.md#keywords) and [symbols](./lexical.md#symbols) are indicated using
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
it is a set of multiple `import`, `sources`, `base`, `define`, etc. _declarations_.

### Grammar

> _module-declaration_ → **`module`** module-name **`{`** module-entity<sub>_0+_</sub> **`}`** \
> _module-name_ → [identifier](./lexical.md#identifiers) \
> _module-entity_ → [import-declaration](#import) \
> _module-entity_ → [define-declaration](#define) \
> _module-entity_ → [sources-declaration](#sources) \
> _module-entity_ → [base-declaration](#base)


## `import`

An `import` merges the parsed content of the associated path into the parent `module`.

The path is relative to the current parsed file.

### Grammar

> _import-declaration_ → **`import`** [path-literal](./lexical.md#path-literals)


## `base`

A `base` defines a header search path for the `module` `sources`.

The path is relative to the current parsed file.
This is typically used in libraries, to disambiguate file includes with the same name.

### Grammar

> _base-declaration_ → **`base`** [path-literal](./lexical.md#path-literals)


## `define`

A `define` adds a key/value pair for the underlying language preprocessor,
available to the `module` `sources`.

### Grammar

> _define-declaration_ → **`define`** define-key **`=`** define-value \
> _define-key_ → [identifier](./lexical.md#identifiers) \
> _define-value_ → [literal](./lexical.md#literals)

### Language Bindings

_define-key_ is exported to the target language preprocessor.

For example the following `erbb` source code:

```erbb
module Foo {
   define MY_FLAG=1
   sources {
      file "Foo.cpp"
      file "Foo.h"
   }
}
```

Defines `MY_FLAG` for all `sources` in the `module`:

```c++
// Foo.cpp
void  process () {
   #if MY_FLAG == 1
      // do something
   #else
      // do something else
   #endif
}
```

### Predefined keys

Some predefined keys are available for the system and are prefixed by `erb_`. This allows
for example to instrument the buffer size or tell the SdRam system how much memory it
can allocate at max.


## `sources`

The `sources` defines the source code of the module.

### Grammar

> _sources-declaration_ → **`sources`** **`{`** sources-entity<sub>_0+_</sub> **`}`** \
> _sources-entity_ → [file-declaration](#file)


## `file`

A `file` defines a file to compile in the `module` `sources`.

The path is relative to the current parsed file.
This is typically C++ source and header files, but can be also the `erbui` file.

### Grammar

> _file-declaration_ → **`file`** [path-literal](./lexical.md#path-literals)
