# Reverb

<img align="right" width="20%" src="./screenshot.png">

`Reverb` is a sample to illustrate the problem with using a lot of memory, here shown with
reverb delay lines.

On embedded platforms, like the Daisy Seed, the natively available memory is very limited
compared to what desktop or mobile software developers are used to.
For example, with the STM32H7 and on the Daisy Seed, the memory allocator is using
a memory called "SRAM", and this memory is only 512KB.

However, this is not all the memory available to your application. The Daisy Seed has for
example a SDRAM chip connected to the main processor, and this SDRAM chip can handle
up to 64MB of memory.

Unlike desktop computers, The Daisy Seed processor, like most embedded processors,
doesn't have a memory management unit (MMU), and the 32-bit addresses available
to your application map directly to the hardware, like the Linux kernel would see them.

When you are running your program, the stack and the heap are using this small SRAM memory.
Unlike desktop applications though, you don't need to allocate memory, you just claim a range
of addresses, and in fact this is your entire responsibility!

Should you use the SRAM or SDRAM, the address space is quite small. And because you
don't have a MMU, memory allocations suffer from the same plague that was hitting old OSes
running on processors with no MMU like the very old Apple Macintosh:
memory fragmentation.

To avoid that, and when possible, allocations are done once and for all using the maximum
possible memory your application could use. Internally, your program uses just a portion of it.

This is what is done in this sample: We calculate the biggest delay possible and use it as
a maximum bound, as shown [here](../dsp/ReverbSc.h#L33).

Finally, while the SRAM is very fast, the SDRAM is comparatively slow. A good balance must
be found by keeping the most accessed data in SRAM, while keeping the less accessed
data in SDRAM.

The `Reverb` sample illustrates this technic by running all filters in SRAM, but keeping less
frequently accessed delay line samples in SDRAM. The whole idea is to separate those into
two blocks of memory, SRAM as the default for filters, and use `erb::make_sdram_object`
for delay lines samples in SDRAM as illustrated [here](./Reverb.h#L25-L26).

The project can generate builds to both run on VCV Rack and on the hardware Daisy platform,
with the same source code. Though, the purpose of this example is only relevant to the Daisy
target hardware.

> Note: The reverb delay lines consumes only 132KB of memory, so this technic is not
> strictly needed here, but is given as a concrete example.

## Overview

This module implements a pre-filtered reverb,
using [Sean Costello open-source reverb](http://www.csounds.com/manual/html/reverbsc.html).


## Requirements

Make sure to first [set-up](https://github.com/ohmtech-rdi/eurorack-blocks/tree/main#setting-up)
your development environment.

> In the following sections, it is assumed that `python` is an alias to Python 3. If this is not the
> case on your platform, use `python3` instead. Alternatively, if your shell supports shebang,
> just run the script in your shell from its directory (_eg._ `./configure.py`)

### Quick Installation on macOS

Provided that [Homebrew](https://brew.sh) is already installed and up-to-date,
that Xcode is already installed as well,
then all dependencies can be installed by running:

    $ brew install armmbed/formulae/arm-none-eabi-gcc dfu-util ninja cairo libffi
    $ pip3 install cairosvg cairocffi ezdxf

The D-DIN Font must be installed on the system to render panel labels properly.
This font and its permissive SIL Open Font License
can be found [here in the repository](../../include/erb/vcvrack/design/d-din).

    $ cd eurorack-blocks/include/erb/vcvrack/design/d-din
    $ cp *.otf ~/Library/Fonts


## Configuring

    $ python configure.py

This will create an `artifacts` folder with everything needed to build for Daisy and VCV Rack.


## Building for VCV Rack

Open the generated project file into your IDE. Building will automatically copy the files to
the VCV Rack plug-in folder.

> In Xcode, make sure to select the `Product > Scheme > reverb-vcvrack` scheme before building.


## Debugging on Xcode

To debug on Xcode, the following configuration must be first done:
- Select the `Product > Scheme > reverb-vcvrack` scheme,
- Go to `Product > Scheme > Edit Scheme...`,
- Select `Run` on the left column,
- In the `Info` tab:
   - Make sure the `Build Configuration` is `Debug`,
   - Choose VCV Rack as the `Executable`,
   - Select `Wait for executable to be launched` for Launch Option,
- In the `Options` tab:
   - Make sure the `Document Versions: Allow debugging... Versions Browser` is **unchecked**.

Now when running (`Product > Run`) the debugger will launch but will wait for VCV Rack to be
started manually.

> ⚠️ The implementation only supports the Daisy native sample rate, so make sure to set your audio
> output configuration to `48kHz` before testing!


## Building for Daisy

    $ python build.py
    ninja: Entering directory `/Users/raf/dev/eurorack-blocks/samples/reverb/artifacts/out/Release'
    [10/10] LINK reverb-daisy
    OBJCOPY reverb-daisy
    ...

This will create a binary file to upload to the Daisy seed. It is the `reverb-daisy.bin` file
output in the `artifacts/out/Release` build directory.


## Deploying for Daisy

    $ python deploy.py
    Enter the system bootloader by holding the BOOT button down,
    and then pressing, and releasing the RESET button.
    Press Enter to continue...
    Flashing...
    dfu-util 0.9
    [...]
    Downloading to address = 0x08000000, size = 36484
    Download   [=========================] 100%        36484 bytes
    Download done.
    File downloaded successfully
    dfu-util: Error during download get_status
    Run command exited with 74

Follow the onscreen instructions and this will download the `reverb-daisy.bin` firmware to the
Daisy Seed when it is connected to USB.

The error 74 reported from `dfu-util` can be safely ignored.

Alternatively, if `dfu-util` does not work properly on your computer,
one may use the [Daisy Web Programmer](https://electro-smith.github.io/Programmer/)
in the [Chrome](https://support.google.com/chrome/answer/95346) browser instead.
