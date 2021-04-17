# cv-in

## Description

This block is a simple analog CV input.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   CvIn cv_in (module, AdcPin6);    // 1.
   
   void process () {
      float cv_value = cv_in;       // 2.
   }
}
```

1. Attach the CV to the module and specify the same analog pin as the one used for connecting,
2. Retrieve the bipolar (in the `-1.f` to `1.f` range) floating-point CV value from the
   -8V to 8V electrical range.

The `CvIn` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control cv_in CvIn {
      position 19.2mm, 111mm        // 1.
      style thonk.pj398sm.knurled   // 2.
      label "IN"                    // 3.
   }
}
```

<img align="right" width="30%" src="https://www.thonk.co.uk/wp-content/uploads/2017/02/nutswashers.jpg">

1. Sets the CV input position on the front panel,
2. Sets the style of the CV input,
3. Sets the optional label for the CV input, using its default theme positioning.

`style` is the nut style, and is one of:
- `thonk.pj398sm.knurled`
- `thonk.pj398sm.hex`

> Nuts and washers photo are from the [Thonk shop](https://www.thonk.co.uk/shop/3-5mm-jacks/).
