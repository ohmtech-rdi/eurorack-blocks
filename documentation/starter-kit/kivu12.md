# Assembling Kivu12

Kivu12 is our 12HP Eurorack motherboard. It is meant to be used for audio digital effects.
As so, all the jack connectors are most likely to be placed at the bottom of your module.

Soldering Kivu12 is quite easy. All Surface-Mounted Devices (SMD) are already assembled,
so the only thing that is left to do is to solder the pin headers and sockets.
The main consideration to keep in mind is to properly align the headers so our future front panel
can fit into it without using too much force.
This can be done manually by inspecting the pin sockets are flush to the board
and aligned visually.
In the nexts sections we will show how to use a breadboard or soldering jig to achieve this
more easily.

Now, locate the parts bag and take out all the pin sockets and headers, including those
long pin headers.


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
