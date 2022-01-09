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

> Note: The reverb delay lines consumes only 132KB of memory, so this technic is not
> strictly needed here, but is given as a concrete example.

<img align="center" src="./photo.png">

## `erb::SdramPtr`

This is what is done in this sample: We calculate the biggest delay possible and use it as
a maximum bound, as shown [here](../dsp/ReverbSc.h#L70).

Finally, while the SRAM is very fast, the SDRAM is comparatively slow. A good balance must
be found by keeping the most accessed data in SRAM, while keeping the less accessed
data in SDRAM.

The `Reverb` sample illustrates this technic by running all filters and delay lines states in SRAM,
but keeping less frequently accessed delay line samples in SDRAM.

The whole idea is to separate those into
two blocks of memory, SRAM as the default for filters and states as illustrated [here](../dsp/ReverbSc.h#L111),
and use `erb::SdramPtr`
for delay lines samples in SDRAM as illustrated [here](../dsp/ReverbSc.h#L109).

`erb::SdramPtr` is in a way similar to `std::unique_ptr`. It can be moved, and "owns" the
underlying memory.

The differences are:
- It uses a monotonic memory pool, meaning that allocating always grows the amount of
   memory used,
- This implies that destroying a `erb::SdramPtr` doesn't allow you to reclaim the memory
   for another allocation, and is therefore similar to leaking.

Whether leaking or not is appropriate for your application, it depends. If this is done in a
bounded number of times and you are doing on purpose, then this is fine. If not, then there
is a conceptual problem in your algorithm.


## Memory Pool Size

The preprocessor macro `erb_SDRAM_MEM_POOL_SIZE` can be used to instrument the
total amount of memory available to `erb::SdramPtr`.

This is useful in the case where you are using code that is already using `DSY_SDRAM_BSS`
so that the full `SDRAM` section is not entirely available to `erb::SdramPtr`.

When this happen, building will return an error stating the `SDRAM` section is overflowing,
for example:

```console
$ erbb build
ninja: Entering directory `/Users/raf/Desktop/dev/eurorack-blocks/samples/reverb/artifacts/out/Release'
[4/4] LINK Reverb
FAILED: Reverb
...
arm-none-eabi/bin/ld: Reverb section `.sdram_bss' will not fit in region `SDRAM'
arm-none-eabi/bin/ld: region `SDRAM' overflowed by 10000 bytes
...
```

You can then adjust the `erb_SDRAM_MEM_POOL_SIZE` value by subtracting 64MB with the
overflow value in bytes, typically:

```
module Reverb {
   define erb_SDRAM_MEM_POOL_SIZE = 67098864 // 64 * 1024 * 1024 - 10000
   ...
}
```

You typically do this for every targets (both the Daisy and Simulator), and this can be done
using `erbb` like [this](./Reverb.erbb#L15).


## Simulation

The project can generate builds to both run on VCV Rack and on the hardware Daisy platform,
with the same source code.

The VCV Rack implementation will still monitor the amount of memory you use, and will `throw`
should you use more in your module than the allowed memory pool size.

Also, when a `erb::SdramPtr` is destroyed, and when launching VCV Rack in the IDE debugger,
the module will report potential memory leaks on the standard output.

The simulator check will only run properly when only one module is tested. If you want to
test the same module twice in VCV Rack, and each module is likely to consume more than
the half of the memory pool, then you can disable checks by adding
`erb_SDRAM_MEM_POOL_SIZE_SIMULATOR_CHECK=0` in the preprocessor flags.

```
module Reverb {
   define erb_SDRAM_MEM_POOL_SIZE_SIMULATOR_CHECK=0
   ...
}
```

You typically do this for every targets (both the Daisy and Simulator), and this can be done
using `erbb` like [this](./Reverb.erbb#L16).


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

```console
$ brew install armmbed/formulae/arm-none-eabi-gcc dfu-util ninja cairo libffi
$ pip3 install cairosvg cairocffi ezdxf soundfile numpy
```

The D-DIN Font must be installed on the system to render panel labels properly.
This font and its permissive SIL Open Font License
can be found [here in the repository](../../include/erb/vcvrack/design/d-din).

```console
$ cd eurorack-blocks/include/erb/vcvrack/design/d-din
$ cp *.otf ~/Library/Fonts
```


## Setting Up

```console
$ source eurorack-blocks/build-system/init.sh
```

This will add the `erbb` command line in your `PATH` for the current terminal.

You may want to add this line with the correct path to your `~/.profile` or `~/.bash_profile`,
to avoid to reload it each time.


## Configuring

```console
$ erbb configure
```

This will create an `artifacts` folder with everything needed to build for Daisy and VCV Rack.


## Building for VCV Rack

Open the generated project file into your IDE. Building will automatically copy the files to
the VCV Rack plug-in folder.


## Debugging on Xcode

To debug on Xcode, the following configuration must be first done:
- Select the `Product > Scheme > Reverb` scheme,
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

```console
$ erbb build
ninja: Entering directory `/Users/raf/dev/eurorack-blocks/samples/reverb/artifacts/out/Release'
[10/10] LINK Reverb
OBJCOPY Reverb
...
```

This will create a binary file to upload to the Daisy seed. It is the `Reverb.bin` file
output in the `artifacts/out/Release` build directory.


## Deploying for Daisy

```console
$ erbb install dfu
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
```

Follow the onscreen instructions and this will download the `Reverb.bin` firmware to the
Daisy Seed when it is connected to USB.

The error 74 reported from `dfu-util` can be safely ignored.

Alternatively, if `dfu-util` does not work properly on your computer,
one may use the [Daisy Web Programmer](https://electro-smith.github.io/Programmer/)
in the [Chrome](https://support.google.com/chrome/answer/95346) browser instead.
