# Assembling Demo Modules

The Starter Kit comes with two demo modules: Drop which is a stereo DJ filter,
and Frohmage which is a multi-band resonant filter.

```{figure} demos-modules.jpg
:width: 100%
:align: center

Fully assembled Drop and Frohmage front panels.
```


## Frohmage

Let's start with the most fun one, that is maybe the easier one as well.

```{image} demos-frohmage-pins.jpg
:width: 25%
:align: right
```

Take the long pin headers, and cut some pins and place them in the kivu12
board pin socket.
As you can see in the picture, not all pin sockets are populated ⚠️
In particular we don't need the pin headers for the first 8 buttons/gates
labelled from B1 to B8, neither the SD card pins.

Put the Frohmage PCB on top and make sure that everything is proper and flush.
Then solder all the pins.

Once done you can remove the front panel from the Kivu12 board.

```{warning}
Be very careful when removing the front panel from the Kivu12 board to not
bend the front panel pins! ⚠️

Take your time, and always keep the two boards parallel.
```

```{image} demos-frohmage-parts.jpg
:width: 25%
:align: right
```

Place all the components on the board, but **do not solder anything yet!**:

- For the LEDs, **the shortest leg goes into the hole on the right**,
- Put the screw for the switch like on the picture, and try to put the switch tip
   in eliquibrium between the 2 extreme positions, like shown on the picture.
   This will help putting the front panel later.

**Do not solder anything yet!**

```{raw} html
<br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br />
```

```{image} demos-frohmage-screw.jpg
:width: 25%
:align: right
```

Now insert the front panel, align it so that everything is properly centered.
You want to make sure to always keep the front panel and PCB together, or the pins of the
jack connectors will slip out, which can be quite frustrating!

Secure the potentiometer on the panel using the supplied screws. Do the same for the jack
connectors and the switch. Make sure all the screws are properly tighten up ⚠️
Push the LEDs so they fit properly into the panel holes.

Inspect one more time on the front and side to make sure everything is properly aligned.

Solder all the parts.
When it is the LEDs turn, make sure again that the LED fits properly in the front panel hole before soldering.

The LEDs are also the most sensitive part of this build, so do not apply heat more than 2 seconds,
and give it some time to cool down before trying again.

Once everything is soldered, grab your wire cutter and cut the excess wire part
of the LEDs.

Now you can put back the front panel, secure all the screws, and finally put the black knobs.
It's done! 🎉

```{image} demos-frohmage-assembled.jpg
:width: 100%
:align: center
```

And now it's time for a quick testing!
We'll upload the firmware, so you can play a bit with your shiny new module before we continue
the build. The experience is more streamlined when using the Eurorack-blocks environment,
but that will come only in the next chapter.

Download [this firmware file](https://todo) (coming soon), and head over to the
[Daisy Web Programmer](https://electro-smith.github.io/Programmer/)
**using the Google Chrome Browser**.

Connect a USB cable to the Daisy Patch SM, which will turn on its LED.
Press the Connect button on the Daisy Web Programmer and select "DFU in FS Mode".
The click the button "Choose File" in the "Select a file from your computer" section,
and finally click the "Program" button. Wait a bit and tada, the program will be uploaded.

```{important}
When this procedure doesn't work, 99% of the time this is because of a faulty
USB cable, so make sure you are not using a "charging USB cable", or just
take another one, just in case.
```

Now disconnect the USB cable, put your Frohmage module in your rack and connect it
to your case power, and turn it on.

It's now time to make a break and have a good time with your Frohmage module!

Ah! and something neat: if you decide to reuse the Frohmage panel to make your first
modules, we made the panel so that it's symmetrical. This means you can turn it the
other way around, which allows you to start with a blank panel, and use a small chalk marker
to design your front panel (to keep track which control is what) 🤯 How cool is that?


## Drop

The Drop module has a bit of everything, so when you manage to solder this module,
you are set for all other modules after!

```{image} demos-drop-pins.jpg
:width: 25%
:align: right
```

Take the long pin headers, and cut some pins and place them in the kivu12
board pin socket.

Like for Frohmage, not all pin sockets need to be populated ⚠️
In particular we **don't need** the pin headers:
- For the first 8 buttons/gates labelled from B9 to B16,
- nor the LED pins labelled from L9 to L16,
- nor the SD card pins.

If you look closely to the picture on the side, you can see that some pins are
not soldered. This photo was shot when assembling the kivu12 using the Drop panel.

Put the Frohmage PCB on top and make sure that everything is proper and flush.
Then solder all the pins.

Once done you can remove the front panel from the Kivu12 board.

```{warning}
Be very careful when removing the front panel from the Kivu12 board to not
bend the front panel pins! ⚠️

Take your time, and always keep the two boards parallel.
```

```{image} demos-drop-parts.jpg
:width: 25%
:align: right
```

Place all the components on the board, but **do not solder anything yet!**:

- Put the LEDs in their hole, and double check their orientation.
   - For the 2-pin red LEDs, **the shortest leg goes into the square-shaped-pad hole on the left**,
   - For the 3-pin LED, **the shortest leg goes into the hole on the right**.
- Put the screw for the switch like for Frohmage, and try to put the switch tip
   in eliquibrium between the 2 extreme positions.
   This will help putting the front panel later.
- Put the 2 push-buttons and observe the flat side of the button ⚠️ and match it
   to the flat side on the PCB silkscreen, on the left of the button
   in the picture.

**Do not solder anything yet!**

```{raw} html
<br /> <br /> <br /> 
```

```{image} demos-drop-screw.jpg
:width: 25%
:align: right
```

Now insert the front panel, align it so that everything is properly centered.
You want to make sure to always keep the front panel and PCB together, or the pins of the
jack connectors will slip out, which can be quite frustrating!

Secure the potentiometer on the panel using the supplied screws. Do the same for the jack
connectors and the switch. But this time, make sure all the screws are **not** too tight ⚠️

Inspect one more time on the front and side to make sure everything is properly aligned.

Solder all the parts, **except the LEDs** first.
When it is the LEDs turn, make sure the LED fits properly in the front panel hole before soldering.

The LEDs are also the most sensitive part of this build, so do not apply heat more than 2 seconds,
and give it some time to cool down before trying again.

Now remove all the screws and remove carefully the front panel.

```{image} demos-drop-resistor.jpg
:width: 25%
:align: right
```

Grab the resistor and bend its pins to match the resistor holes.
Then turn the board over, make sure the resistor is flush to the board and
solder it. Take your time as it is very tight with the jack connectors around!

Now take your wire cutter and cut the excess wire part of the LEDs and resistor.

Now you can put back the front panel, secure all the screws, and finally put the big
knob for the frequency potentiometer.

```{image} demos-drop-assembled.jpg
:width: 100%
:align: center
```

That's it, you did it! And for you to know, that might be the most complicated build you will
ever have with Eurorack-blocks, so how did it feel?

To test this module, we will use the Eurorack-blocks environment as shown in the next
chapter. Depending on what language you use, C++, Max, we have a project
specificly made for it.

It is time now to install the Eurorack-blocks environment on your computer!
