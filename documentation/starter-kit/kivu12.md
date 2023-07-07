# Assembling Kivu12

Kivu12 is our 12HP Eurorack motherboard. It is meant to be used for audio digital effects.
As so, all the jack connectors are most likely to be placed at the bottom of your module.

```{figure} kivu12-assembled.jpg
:width: 100%
:align: center

Fully assembled kivu12 board with jumpers configured
to use the SD connector on the board, and two first CVs in pitch mode.
```


Soldering Kivu12 is quite easy. All Surface-Mounted Devices (SMD) are already assembled,
so the only thing that is left to do is to solder the pin headers and sockets.
The main consideration to keep in mind is to properly align the headers so our future front panel
can fit into it without using too much force.
This can be done manually by inspecting the pin sockets are flush to the board
and aligned visually.
In the nexts sections we will show how to use a rubber band or soldering jig to achieve this
more easily.

Now, locate the parts bag and take out all the pin sockets and headers, including those
long pin headers.

```{important}
Avoid touching the SMD components with your fingers if you don't have an
anti-static wrist strap band,
and in all cases be very careful not to poke them with your soldering iron tip!
```

In the following, please don't hesitate to click on the pictures to see a
biffer version of them.


## Using a Rubber Band

```{image} kivu12-headers-sockets.jpg
:width: 25%
:align: right
```

Take the long pin headers, and cut it to make assemblies for every pin sockets.
Plug them and make sure there is no gap between the pin header and the pin
socket. The photo shows how the 4 pin socket and header are being assembled.
Orient them all in the same direction, for example all pin sockets on the
left and pin headers on the right, like in the picture.

```{raw} html
<br />
```

```{image} kivu12-headers-in-place.jpg
:width: 25%
:align: right
```

Put the Kivu12 board in equilibrium on top of a Rogan 6PS Knob
(that's the only black and white big knob in the bag of parts),
and put your pin socket/header assembly
in each respective holes on the sides of the board.

Make sure you see the
ERB logo to ensure you are putting the pin sockets/headers on the right
side of the board.

Also ensure that the ⚠️ **pin sockets** ⚠️ are mounted on
the ERB kivu12 board, and not the pin headers.

```{raw} html
<br /> <br /> <br />
```

```{image} kivu12-rubber-band.jpg
:width: 25%
:align: right
```

Put one of the demo board, typically the one you want to assemble first,
on top of this assembly, and align both boards so that your pin sockets/headers
assemblies are secured into each board.
The correct side of the demo board is the one where you can see the pictogram
of the pots we will solder later.
Next grab your rubber band and secure this big assembly.
Ideally, place the rubber band as shown in the picture, it will be easier
to solder pins later.
Finally turn your assembly over, so you are facing the back of the kivu12
board, as shown in the picture.
At this stage, you want to make sure that all pin sockets/headers are flush
to the board, and nicely perpendicular.
Also you want to verify again that the **pin sockets** are mounted on the
ERB kivu12 board, and not the pin headers.

Let us emphasize this one more time.

```{warning}
⚠️ Be sure to solder the pin sockets on the kivu12 board side ⚠️

Desoldering pin headers or sockets is nearly impossible without proper
specialized equipment, so you really want to double check this
before soldering!
```

```{image} kivu12-sockets-done.jpg
:width: 25%
:align: right
```

Now solder every pin sockets on the kivu12 board.
Avoid the 2 pins next to the rubber band at first, but when all other pins
are soldered, **move** the rubber band on one side two solder those 2 last
pins. We move it instead of removing it because the demo board is
not soldered yet.

At this stage you might want also to solder the front panel pin headers
if you feel like so, if not, you can always do it later.

We did it with the Drop demo module. You will get the following result
as shown on the picture on the side.

Put the demo module aside, and let's continue soldering the pin headers
and sockets.

```{image} kivu12-headers.jpg
:width: 25%
:align: right
```

Take the 3 6-position and 2 3-position pin headers and 6 jumpers, and make
an assembly as shown in the picture.
This allows to make a block of headers and align them properly.

Then place it on the board as shown in the picture.

Turn the board over and make sure everything is sitting flush.
You can check this by ensuring that the tips of the headers you are going
to solder are sticking out of the kivu12 board by the same length.

When everything is flush and proper, solder all those pins. 

```{raw} html
<br /> <br /> <br /> <br /> <br /> <br /> <br /> <br />
```

```{image} kivu12-dpsm-sockets.jpg
:width: 25%
:align: right
```

Take the 4 5x2-position pin sockets and place them on the Daisy Patch Submodule.

The kivu12 board as this weird "ziz-zag pattern" for the pin sockets holes that
allows to secure the pin sockets on the board while soldering.
It's a tip from Electro-smith and quite a smart one!

Turn the board over and make sure everything is sitting flush.
You can check this by ensuring that the tips of the headers you are going
to solder are sticking out of the kivu12 board by the same length.

When everything is flush and proper, solder all those pins.

```{image} kivu12-power.jpg
:width: 25%
:align: right
```

Finally the last soldering step! Find the 5x2-position shrouded pin headers
and put it on the back of the board.

Make sure the key of the pin header follows the orientation as shown on
the PCB. If you look well on the picture, the key is located on the left.

Before turning over the board, remove the Daisy Patch Submodule.
Because the pin header is as high as the other pin sockets for the
Daisy Patch Submodule, that's easier to keep the power header flush
to the board.

Double-check that the key of the pin header is in the right position ⚠️
and finally solder the pin header.

```{image} kivu12-jumpers.jpg
:width: 25%
:align: right
```

Finally put all the jumpers on the board.

For the 6-position headers, which are used for SD card reader,
put them on the **left** of the pin headers, as shown in the
picture. This selects the SD card connector on the kivu12 board
itself.

For the 3-position headers, which are use to convert at most the first
two CVs to pitch mode (0..10V), put them on the **right** of the pin headers.
Putting CI1 and CI2 to bipolar mode (±5V) is important for later, because
the two demo modules relies on this mode to be selected in order to
function correctly.

Congratulations! Your kivu12 board is completed and waiting for your creations 🎉 




## Using a Breadboard

```{important}
Be sure to solder the pin sockets and headers on the right side of the board!
Use the pictures below to ensure that, and take your time.
```

### Front panel pin sockets

Take the long pin headers, and cut it to achieve this inverted L-shape for the left part of
the board.
Then plug-in the pin sockets, and align the board to it.

When soldering the first pin of a pin socket,
press gently on the corner to make sure the pin sockets are properly flush and aligned to the board.
Visually inspect that this is the case before going to the next pin socket.
If for some reason this is not properly flush, you can always reflow that first pin to adjust.
That would be far more complicated if all pins were already soldered, so make sure to first
verify everything on the first soldered pin before soldering the other pins.

Repeat this process with the right part of the board.

### SD Card and Pitch mode pin headers

Cut the pin headers and make an assembly using the provided 5x2 pin socket to look like
the picture.
Then solder one pin of this assembly, and verify that everything is flush before proceeding
to the other pins.
The alignment is not very crucial with this one.

Repeat the same process for the pin headers on the bottom part of the board.

### Daisy Patch SM pin sockets

Plug the 4 5x2 pin sockets on your Daisy Patch SM and fit this assembly to the board.
Same as usual, solder one pin and make sure everything is flush before moving to the next
pins.

This time, you'll also want to make sure to not heat the pin for too long, so aim for around
2 seconds. If you didn't solder properly during those 2 seconds, no problem, give it some
seconds to cool down and try again.
We do this because they are sensitive parts on the Daisy Patch SM.

### Power connector

Put the power connector in place.

```{important}
Make sure that the key of the connector is the same as pictured on the board!
```

Keep the power connector secured with one finger, and put a bit of solder on your iron tip
to finally put that solder on the pin. The goal here is not to make a proper joint but just to
keep the power connector in place.

If everything is flush, proceed to the other pins. Finally when they are all done, solder properly
the first pin.


## Using the Soldering Jig 

```{important}
Be sure to solder the pin sockets and headers on the right side of the board!
Use the pictures below to ensure that, and take your time.
```

### Top Side

Put the soldering jig on a flat surface,
then all the pin headers and sockets of the top side in their respective holes, and fit the board
on top. Solder one pin while pressing gently in the middle in the board to make sure everything
is flush. Verify visually and if everything is file, solder all the other pins.

### Bottom Side

Repeat the same process for the 4 5x2 pin sockets.

### Power connector

Use the same process as explained in the previous section.


## Finishing the Assembly

Locate the jumpers in the parts bag, and place them as shown in this picture.


## Testing

At this point, you can connect the included 10pin-to-16pin header to the kivu12 motherboard,
then to your rack, and power it up.
At this stage, you should see a LED turning on on the Daisy Patch SM.
