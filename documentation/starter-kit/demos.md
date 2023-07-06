# Assembling Demo Modules

The Starter Kit comes with two demo modules: Drop which is a stereo DJ filter,
and Frohmage which is a multi-band resonant filter.


## Frohmage

Let's start with the most fun one, that is maybe the easier one as well.

Place all the potentiometers on the board, and make sure they are on the right side of the board.
The potentiometer legs might be a bit misplaced, so make sure they go nicely into the holes
and be gentle as the pins can bend easily.

**Do not solder anything yet!**

Now place the 8 jack connectors.

**Do not solder anything yet!**

Put the LEDs in their hole, and double check their orientation.
**the shortest leg goes into the hole on the right**.

**Do not solder anything yet!**

Now insert the front panel, align it so that everything is properly centered.
You want to make sure to always keep the front panel and PCB together, or the pins of the
jack connectors will slip out, which can be quite frustrating!

Secure the potentiometer on the panel using the supplied screws. Do the same for the jack
connectors.

Inspect one more time on the front and side to make sure everything is properly aligned.

Solder all the parts, **except the LEDs** first.
When it is the LEDs turn, make sure the LED fits properly in the front panel hole before soldering.

The LEDs are also the most sensitive part of this build, so do not apply heat more than 2 seconds,
and give it some time to cool down before trying again.

Now remove all the screws and remove carefully the front panel.

Cut and put the pin headers in your kivu12 board. Note that we don't put pin headers in
every pin sockets, so make sure to place them as in the picture.

Fit your Frohmage board and solder one pin, make sure that everything is flush, and proceed to
the next pins.

Now you can put back the front panel, secure all the screws, and finally put the black knobs.

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
to design your front panel (to keep track which control is what). How cool is that?


## Drop

The Drop module has a bit of everything, so when you manage to solder this module,
you are set for all other modules after!

Place all the potentiometers on the board, and make sure they are on the right side of the board.
The potentiometer legs might be a bit misplaced, so make sure they go nicely into the holes
and be gentle as the pins can bend easily.

**Do not solder anything yet!**

Now place all the other parts, buttons, 2-position switch, and the 8 jack connectors.

Observe the flat side for the 2 buttons!
Push button from the other side to make sure it sits flush to the PCB.

**Do not solder anything yet!**

Put the LEDs in their hole, and double check their orientation.
- For the 2-pin LEDs, **the shortest leg goes into the square-shaped-pad hole on the left**,
- For the 3-pin LED, **the shortest leg goes into the hole on the right**.

**Do not solder anything yet!**

Now insert the front panel, align it so that everything is properly centered.
You want to make sure to always keep the front panel and PCB together, or the pins of the
jack connectors will slip out, which can be quite frustrating!

Secure the potentiometer on the panel using the supplied screws. Do the same for the jack
connectors. Finally screw the 2-position switch, but don't screw too much, so that the switch
itself stays flush to the board.

Inspect one more time on the front and side to make sure everything is properly aligned.

Solder all the parts, **except the LEDs** first.
When it is the LEDs turn, make sure the LED fits properly in the front panel hole before soldering.

The LEDs are also the most sensitive part of this build, so do not apply heat more than 2 seconds,
and give it some time to cool down before trying again.

Now remove all the screws and remove carefully the front panel.

Cut and put the pin headers in your kivu12 board. Note that we don't put pin headers in
every pin sockets, so make sure to place them as in the picture.

Fit your Drop board and solder one pin, make sure that everything is flush, and proceed to
the next pins.

Now you can put back the front panel, secure all the screws, and finally put the big
knob for the frequency potentiometer.

That's it, you did it! And for you to know, that might be the most complicated build you will
ever have with Eurorack-blocks, so how did it feel?

To test this module, we will use the Eurorack-blocks environment as shown in the next
chapter. Depending on what language you use, C++, Max, we have a project
specificly made for it.

It is time now to install the Eurorack-blocks environment on your computer!
