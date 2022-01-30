# Name Mapping System

In the previous chapter, we've seen that we can have a FAUST primitive with a label, and use
the same label as a control name in `erbui` to make the mapping.
This is convenient as long as your `process` only references local labels in the file.
But this falls short in a certain number of cases, but don't worry! Every cases are handled
with an uniform simple approach.

First, we might use an audio object from an imported module, which would have for
example a `hslider` with the same label `freq`. How do we disambiguate which is which?
This is explained below in [Address binding](#address-binding).

Second, you might use an audio object that exports a lot of different labels. For example
you might use `dm.phaser2_demo`. This one has 3 `checkbox` and 8 `hslider`!
With the small space on your module, you will need to make some choices, and for
example decide that the `Phaser Output Level` should be always 0.5.
If the default value for this primitive is not 0.5, we need a way to set this value.
How do we assign custom default values to a FAUST primitive?
This is explained below in [Custom value initialization](#custom-value-initialization).

Finally, all primitives in FAUST are scalar values. On the other hand, some Eurorack-blocks
controls represent a compound type with more than one property, that is, it can hold more than
one scalar value. The dichromatic LED `LedBi` is an example of it: it has the properties `r` and
`g`, which represents respectively the intensity of the red and green emitted color.
How do we map a FAUST label to a property inside of a control?
This is explained below in [Compound property binding](#compound-property-binding).


## Address binding

Let's take `dm.phaser2_demo` to understand a bit more how name mapping works.

Make a new Phaser FAUST project using `erbb faust init Phaser`
and change the dsp file like the following:

```{code-block} faust
---
lineno-start: 1
emphasize-lines: 3-4
---
// Phaser.dsp

import("stdfaust.lib");
process = dm.phaser2_demo;
```

If you build the project now, the `erbui` transpiler will complain that you have the wrong
number of audio inputs and outputs.
This is because `dm.phaser2_demo` is a stereo effect and `erbb faust init` generated
by default a mono input/output effect.

Let's first fix this quickly by adding one more audio input and output at the end of our `erbui` file, and rearranging the layout of those audio jack connectors:

```{code-block} erbui
---
lineno-start: 1
emphasize-lines: 10, 15-19, 22, 27-31
---
// Phaser.erbui

module Phaser {
   width 12hp
   board kivu12
   material aluminum
   header { label "Phaser" }
   
   control audio_in AudioIn {
      position 4hp, 96mm
      style thonk.pj398sm.knurled
      label "IN L"
   }

   control audio_in2 AudioIn {
      position 8hp, 96mm
      style thonk.pj398sm.knurled
      label "IN R"
   }

   control audio_out AudioOut {
      position 4hp, 111mm
      style thonk.pj398sm.knurled
      label "OUT L"
   }

   control audio_out2 AudioOut {
      position 8hp, 111mm
      style thonk.pj398sm.knurled
      label "OUT R"
   }
```

Now, let's build the project. If you go to your IDE build logs, you will see the following:

```
warning: non mapped checkbox /PHASER2/0x00/Bypass
warning: non mapped checkbox /PHASER2/0x00/Invert Internal Phaser Sum
warning: non mapped checkbox /PHASER2/0x00/Vibrato Mode
warning: non mapped hslider /PHASER2/0x00/Speed
warning: non mapped hslider /PHASER2/0x00/Notch Depth (Intensity)
warning: non mapped hslider /PHASER2/0x00/Feedback Gain
warning: non mapped hslider /PHASER2/0x00/Notch width
warning: non mapped hslider /PHASER2/0x00/Min Notch1 Freq
warning: non mapped hslider /PHASER2/0x00/Max Notch1 Freq
warning: non mapped hslider /PHASER2/0x00/Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)
warning: non mapped hslider /PHASER2/0x00/Phaser Output Level
```

```{note}
If your IDE doesn't show message logs or accessing them is not convenient,
just can also build with `erbb build simulator` instead from your terminal.
```

They represent the list of all values in FAUST that do not have a mapping in `erbui`.
`/PHASER2/0x00/Bypass` represents an address in FAUST.
This is what is used to control FAUST using OSC for example.

Let's say we want to bind the Phaser speed to a control in `erbui`.
You do this by adding a FAUST binding, using its FAUST address:

```{code-block} erbui
---
lineno-start: 9
emphasize-lines: 2
---
   control speed Pot {
      faust { bind { address "/PHASER2/0x00/Speed" } }
      position 6hp, 34mm
      style rogan.6ps
      label "FREQ"
   }
```

You can now build again the project, and you will see that the warning for the phaser
speed has disappeared. Those warnings are handy, because you get to see what is mapped or not.

But wait! In our first example, {doc}`/faust/first`, we didn't use any of this FAUST address binding.
How could this possibly work?

This is the "syntactic sugar" we were talking about in the previous chapter:
when you don't declare a binding, Eurorack-blocks will synthetize one for you.
It created implicitely a line like the following, which happens to match the
FAUST generated `freq` primitive address, as long as the label is local to the FAUST dsp file.

```{code-block} erbui
---
lineno-start: 9
emphasize-lines: 2
---
   control freq Pot {
      faust { bind { address "/LowPass/freq" } } // synthetized
   }
```


## Custom value initialization

We can go on and map all the primitives we want in FAUST with a control in `erbui`.
But now we might come to the point where either we don't have enough space in our
Eurorack module to put another control,
or better, if we planned our design rigorously, that we want to map
only a subset of the FAUST primitives to physical Eurorack controls.

Inside an imported FAUST library, we might have source code like the following:

```{code-block} faust
fc = hslider("freq", 1000, 100, 10000, 1);
```

So that means that the default value for this FAUST primitive,
if we don't bind it, would be 1000Hz.
Now let's say that we want it to be 80Hz by default.
We can do this by specifying a FAUST initial value for the address of this primitive.
How can we do this?
With our Phaser module example,
let's say we want to set the default value of "Phaser Min Notch1 Freq" to 80Hz:

```{code-block} erbui
---
lineno-start: 1
emphasize-lines: 9-11
---
// Phaser.erbui

module Phaser {
   width 12hp
   board kivu12
   material aluminum
   header { label "Phaser" }
   
   faust {
      init { address "/PHASER2/0x00/Min Notch1 Freq" value 80 }
   }

   control speed Pot {
      faust { bind { address "/PHASER2/0x00/Speed" } }
      position 6hp, 34mm
      style rogan.6ps
      label "FREQ"
   }
```

Note that this definition is done at `module` scope.
You can now build the project again, and you will see that the warning for
"Phaser Min Notch1 Freq" has disappeared.

Those warnings are helpful, because they allow you to go systematically through
every FAUST primitives: you either bind them or give them an initial value explicitly.
Should the default value of the imported library be at the correct value already,
you can  just use the "init" value of the primitive in the library to make the warning go away.


## Compound property binding

As we said in the introduction, all FAUST primitives represent scalar values.
But at the same time, some `erbui` controls can have more than one property!
How can we map that?
For this, we just need to specify the `property` in our binding.
Let's say that we have 2 `vbargraph` with label "LED Red" and "LED Green".
We just need to specify a specific property in our binding:

```{code-block} erbui
---
lineno-start: 1
emphasize-lines: 2-5
---
   control led_bi LedBi {
      faust {
         bind { property r address "/Phaser/LED Red" }
         bind { property g address "/Phaser/LED Green" }
      }
      position 10hp, 80mm
      style led.3mm.red_green
      label "LED"
   }
```

Just for the sake of completion (most likely you will never need to use that),
this works with `init` too!
Let's say that you would want to give a specific value to a property.
You can use the same `init` syntax we used at module scope,
but inside the control rather than the module:

```{code-block} erbui
---
lineno-start: 1
emphasize-lines: 4
---
   control led_bi LedBi {
      faust {
         bind { property r address "/Phaser/LED Red" }
         init { property g value 0.5 }
      }
      position 10hp, 80mm
      style led.3mm.red_green
      label "LED"
   }
```

That's it! This chapter cover most of your needs when using FAUST with Eurorack-blocks.
