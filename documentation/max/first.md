# Your First Module

For our first module, we will make a simple low-pass filter, with one big knob to control
the cut off frequency.

First create your new project by creating a directory and populating it with a simple template.

You can create your project wherever you see fit. In this example, we created it in our
home folder.

```shell-session
~$ mkdir LowPass
~$ cd LowPass
~/LowPass$ erbb max init LowPass
~/LowPass$ erbb configure
```

If you are using Xcode open `project_vcvrack.xcodeproj` in the `artifacts` folder.

```{note}
In the following source code files, we have removed all comments to
keep the file easy to read for this tutorial.
```

Let's now add the pot with a big knob, by editing the `Lowpass.erbui` file,
as highlighted in the following `erbui` source code:

```{code-block} erbui
---
emphasize-lines: 9, 10, 11, 12, 13
---
// LowPass.erbui

module LowPass {
   width 12hp
   board kivu12
   material aluminum
   header { label "LowPass" }

   control freq Pot {
      position 6hp, 34mm
      style rogan.6ps
      label "FREQ"
   }

   control audio_in AudioIn {
      position 4hp, 96mm
      style thonk.pj398sm.knurled
      label "IN"
   }

   control audio_out AudioOut {
      position 4hp, 111mm
      style thonk.pj398sm.knurled
      label "OUT"
   }
}
```

The highlighted code:
1. Add a pot and give it the name `freq` (we will see how names are used later)
2. Give it a position, first is on the horizontal axis, and second is on the vertical axis.
   Note that both have units, with `hp` being the Eurorack HP for convenience.
   Since half of 12HP is 6HP, this will place the pot at the horizontal center in the module
3. Let's give it a style, which here is the knob style. `rogan.6ps` is the name of the knob used
   in many Mutable Instruments and Make Noise modules
4. Give it an optional label, which will be printed on the front panel aluminum

You can already build the project using {guilabel}`⌘B` and run VCV Rack to see what it looks like.

```{image} first-add-freq.png
:align: center
:width: 50%
```

You can connect inputs and outputs, and you can hear that the input goes on the output
but moving the FREQ knob doesn't have any effect.

Let's now take care of this.
Thanks to Max, we have a large number of DSP blocks available at our fingertips!
 
- Open the `LowPass.maxpat` Max patch in Max, and then open the {guilabel}`gen~` box,
- Remove the 2 `in` and `out` boxes as we are going to replace them,
- Go in the {guilabel}`Help` menu
   and select the {menuselection}`Examples --> gen --> gen~.biquad` example,
- Open the {guilabel}`gen~ @title lowpass` on the right side of the patch,
- After unlocking the file, copy its content to our {guilabel}`gen~` box,
- Replace the {guilabel}`in 2` box with {guilabel}`Param freq @min 20 @max 20000`,
   and note that we use the same param name `freq` as the one in the `erbui` file upper,
- Replace the {guilabel}`in 3` box with {guilabel}`1`,
- Save the file

Your gen patch should look like the following:

```{image} first-gen-patch.png
:align: center
:width: 100%
```

Now you can build the project using {guilabel}`⌘B` and run VCV Rack to see what it sounds like.
That works! Now the FREQ button behaves a bit differently to what you would be used using
Eurorack modules, but that's because we would need to apply an exponential mapping to
the FREQ pot. But that will be for another tutorial!
