# `CvIn` Class Reference

| Declared in | `erb/CvIn.h` |
| - | - |
| Inherits from | `ModuleListener` |

```c++
class CvIn;
```

`CvIn` is a type that abstracts a physical `cv-in` block.


## Member Functions Synopsys

| Name | Synopsys |
| - | - |
| [Constructor](#constructor) | Constructs the `CvIn` |
| [Destructor](#destructor) | Destructs the `CvIn` |
| [`operator float`](#operator-float) | Returns the bipolar CV value |


## Member Functions

### Constructor

```c++
CvIn (Module & module, const AdcPin & pin);
```

Constructs the `CvIn` with `pin` and attach it to its `module`.

> `pin` must use the constants as defined in `erb/Pins.h` for clarity.

### Destructor

```c++
~CvIn ();
```

Destructs the `CvIn`.

### `operator float`

```c++
operator float () const;
```

Returns the bipolar CV value in the `-1.f` to `1.f` range.
