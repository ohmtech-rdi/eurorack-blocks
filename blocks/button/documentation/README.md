# button

## Description

This block is a simple trigger push button.
Its design is detailed [here](./design.md).


## Using

### `c++`

```c++
struct Example
{
   Module module;
   Button button (module, Pin23);   // 1.
   
   void process () {
      if (button.pressed ()) ...    // 2.
      if (button.held ()) ...       // 3.
      if (button.released ()) ...   // 4.
   }
}
```

1. Attach the button to the module and specify the same pin as the one used for connecting,
2. The button was just pressed,
3. The button is held down,
4. The button was just released.

The `Button` class reference is available [here](./reference.md).

### `erbui`

```erbui
module Example {
   control button Button {
      position 19.2mm, 111mm        // 1.
      style tl1105                  // 2.
      label "IN"                    // 3.
   }
}
```

1. Sets the button position on the front panel,
2. Sets the style of the button,
3. Sets the optional label for the button, using its default theme positioning.

`style` is the button style, and is one of:
- [`tl1105`](https://www.digikey.de/product-detail/en/e-switch/TL1105SPF250Q/EG1862-ND/271559)
- [`ck.d6r.black`](https://www.thonk.co.uk/shop/radio-music-switch/)

The `tl1105` button is typically mounted with a [cap](https://www.digikey.de/product-detail/en/e-switch/1RBLK/EG1882-ND/271579).

The `ck.d6r.black` is typically used in sequencers, or to enhance the performing experience:

<img  src="https://www.thonk.co.uk/wp-content/uploads/2015/01/Radio_Switch_Black.jpg">

> C&K D6R Black photo is from the [Thonk shop](https://www.thonk.co.uk/shop/radio-music-switch/).
