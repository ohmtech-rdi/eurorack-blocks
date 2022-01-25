# Kick: Samples & Big Programs

[`Kick`](https://github.com/ohmtech-rdi/eurorack-blocks/tree/main/samples/kick) is
a kick module.
This sample illustrates the problem associated when making "big" programs
in general, and storing samples into programs (and therefore making them "big")


## Overview

Wouldn't it be nice if we could use some audio samples into our modules and have
a way to quickly prototype with them?

Ideally we would just add the sample to our project, reference it somewhere, have it
available in our code, and then when we could build it and bundle all this together.
Everytime we would change the sample, it would automatically rebuild.

Let's learn how to do this, but first thing first, we need to understand how to load
bigger programs.


## How does it work?

If you followed very carefully the previous section, you will probably ask the question:
What about this `QSPIFLASH` section of 8MB? Why can't we use it to allocate?

```{code-block} text
---
lineno-start: 8
emphasize-lines: 10
---
MEMORY
{
   FLASH (RX)    : ORIGIN = 0x08000000, LENGTH = 128K
   DTCMRAM (RWX) : ORIGIN = 0x20000000, LENGTH = 128K
   SRAM (RWX)    : ORIGIN = 0x24000000, LENGTH = 512K
   RAM_D2 (RWX)  : ORIGIN = 0x30000000, LENGTH = 288K
   RAM_D3 (RWX)  : ORIGIN = 0x38000000, LENGTH = 64K
   ITCMRAM (RWX) : ORIGIN = 0x00000000, LENGTH = 64K
   SDRAM (RWX)   : ORIGIN = 0xc0000000, LENGTH = 64M
   QSPIFLASH (RX): ORIGIN = 0x90000000, LENGTH = 8M
}
```

We can't modify section when the program is running. While `RWX`means read, write and
execute (a program), `RX` means we can only read or execute from it.

So while we can't use it to put for example our delay lines, we can still use it to store
our program.

Suddenly, instead of having 128K to store our program in `FLASH`, we have this nice large
8MB in `QSPIFLASH` to store our program.

8MB is very large for code. This is the entire size of a compiled minimal Linux kernel already!
So this is the perfect place to store some samples. For sure not minutes of samples, but
you can have a few seconds. In the `Kick` sample, we store the kick body there, as well
as all the different transients to layer on top of that kick body.

The linker script we used before is only meant to store the program in `FLASH` memory.
To use the `QSPIFLASH`, we need:
- To use a bootloader, the reason is explained below,
- To change of linker script.

The bootloader will allow to boot to the program contained in the `QSPIFLASH`, as we can't
boot directly to it.

We have two linker scripts options:
- One which stores the program to `QSPIFLASH` and boot from there,
- One which loads a part of the program to `SRAM` and boot from there.

The advantage of booting from `SRAM` is that this memory is faster than the `QSPIFLASH`
for instruction fetching. In the following, we will use the first option.


## Preparing

First let's configure the IDE project to inspect the project in the comfort of our IDE if you
are using one. Navigate to `eurorack-blocks/samples/kick` and run:

```shell-session
eurorack-blocks$ cd samples/kick
eurorack-blocks/samples/kick$ erbb configure
```

If you are using Xcode, you can navigate to the `artifacts` folder and open the
`project_vcvrack.xcodeproj` Xcode project.

If you are using `VSCode`, just open the `kick` folder in VSCode.

From Xcode, you can build using {guilabel}`⌘B`.
You can also build the VCV Rack module from the command line with:

```shell-session
$ erbb build simulator
```

Now you can open VCV Rack, and add the Kick module and play a bit with it.


## Resources & Data

Maybe have you seen next to our `*UI` class, a `*Data` in each module headers and wondered
what it was? This is where we store our resources.

A resource is a piece of data with an optional type, and one of those types is a convenient
audio sample data type.

```{code-block} erbb
---
lineno-start: 10
emphasize-lines: 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41
---
module Kick {
   section qspi

   import "../dsp/dsp.erbb"

   sources {
      file "Kick.cpp"
      file "Kick.h"
      file "Kick.erbui"

      file "ClockEstimator.cpp"
      file "ClockEstimator.h"
      file "Presence.cpp"
      file "Presence.h"
      file "Space.h"
      file "VoiceBody.h"
      file "VoicesBody.h"
      file "VoicesTransient.h"
      file "VoiceTransient.h"
   }

   resources {
      data body AudioSample { file "media/body.wav" }
      data transient01 AudioSample { file "media/transient01.wav" }
      data transient02 AudioSample { file "media/transient02.wav" }
      data transient03 AudioSample { file "media/transient03.wav" }
      data transient04 AudioSample { file "media/transient04.wav" }
      data transient05 AudioSample { file "media/transient05.wav" }
      data transient06 AudioSample { file "media/transient06.wav" }
      data transient07 AudioSample { file "media/transient07.wav" }
      data transient08 AudioSample { file "media/transient08.wav" }
      data transient09 AudioSample { file "media/transient09.wav" }
      data transient10 AudioSample { file "media/transient10.wav" }
      data transient11 AudioSample { file "media/transient11.wav" }
      data transient12 AudioSample { file "media/transient12.wav" }
      data transient13 AudioSample { file "media/transient13.wav" }
      data transient14 AudioSample { file "media/transient14.wav" }
      data transient15 AudioSample { file "media/transient15.wav" }
      data transient16 AudioSample { file "media/transient16.wav" }
      data transient17 AudioSample { file "media/transient17.wav" }
      data transient18 AudioSample { file "media/transient18.wav" }
   }
}
```

The highlighted line contains a resource declaration of kind `data`.
A `data` is a static variable in your program, that you can access from C++.

What it does here, is to create an `AudioSampleMono` from the file `body.wav`, because the
file has only one channel, with the name `kick_body`.

You can then use this data in your program directly. The `AudioSampleMono` template class
instance is already filled in with the audio sample rate, all the samples.
It is as if you would have loaded a WAV file from within your program, except Eurorack-blocks did it
for you, and the sample is available before your program even starts!

This is because Eurorack-blocks "transpiles" the audio sample to C++ code that get compiled
like the rest of your program.

If you look at `Kick.cpp`:

```{code-block} cpp
---
lineno-start: 109
emphasize-lines: 3
---
for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
{
   float val = body.process (data.body) * active_ramp.process ();
   val += filter.process (transient.process ());
   val = space.process (val);
   val = presence.process (val);

   ui.audio_out [i] = val;
}
```

We call `body.process` with the entire sample `data.body`, which was generated from
`media/body.wav`.

Now if we look into the body implementation in `VoiceBody.h`:

```{code-block} cpp
---
lineno-start: 48
emphasize-lines: 1, 2
---
float ret_1 = sample.samples [pos];
float ret_2 = sample.samples [pos + 1];
float ret = ret_1 + (ret_2 - ret_1) * mix;
```

We access the samples number `pos` and `pos + 1`.

If the `body.wav` file was a stereo audio file, it would generate a `AudioSampleInterleaved`
object, and we could access its content like this:

```{code-block} cpp
float ret_1 = sample.frames [pos].channels [0];
float ret_2 = sample.frames [pos + 1].channels [0];
```

`AudioSampleInterleaved` contains an array of `frames`, and each frame contains an array
of `channels`.


## Program Section

Now if you take a closer look in the project, you will find that the sum of all samples is already
more than the `FLASH` 128K maximum size, and the program total size must therefore be even
bigger than that. So how does it work?

You must have seen it already:

```{code-block} erbb
---
lineno-start: 10
emphasize-lines: 2
---
module Kick {
   section qspi

   import "../dsp/dsp.erbb"
```

We tell the program to use the `QSPIFLASH` section.
This way, the program can easily fit into it.
Internally Eurorack-blocks will use the right linker script so you don't have to care about this.

Let's see what would happen if we don't flash in the QSPI flash:

```{code-block} erbb
---
lineno-start: 10
emphasize-lines: 2
---
module Kick {
   //section qspi

   import "../dsp/dsp.erbb"
```

We commented the line, and by default, programs are flashed to the small 128K `flash`
section.

Now if we run `erbb build`, which builds the firmware:

```{code-block} console
---
emphasize-lines: 6, 7
---
eurorack-blocks/samples/kick$ erbb build
ninja: Entering directory `/Users/raf/Desktop/dev/eurorack-blocks/samples/kick/artifacts/out/Release'
[71/71] LINK Kick
FAILED: Kick 
arm-none-eabi-g++ -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -mcpu=cortex-m7 --specs=nano.specs --specs=nosys.specs -lc -lm -lnosys -Wl,-Map=out.map,--cref -Wl,--gc-sections -T/Users/raf/Desktop/dev/eurorack-blocks/submodules/libDaisy/core/STM32H750IB_flash.lds -o Kick -Wl,--start-group obj/Kick.Kick.o obj/Kick.ClockEstimator.o obj/Kick.Presence.o dsp/Kick.Filter2Poles.o dsp/Kick.GainRamp.o dsp/Kick.ReverbSc.o ../src/daisy/Kick.BoardDaisyField.o ../src/daisy/Kick.BoardDaisyMicropatch.o ../src/daisy/Kick.BoardDaisySeed.o ../src/daisy/Kick.BoardKivu12.o ../src/daisy/Kick.SubmoduleDaisyPatchSm.o ../src/daisy/Kick.SubmoduleDaisySeed.o obj/artifacts/Kick.main_daisy.o obj/artifacts/Kick.plugin_generated_data.o ../src/Kick.Button.o ../src/Kick.GateOut.o ../src/detail/Kick.Animation.o ../src/detail/Kick.Debounce.o ../src/detail/Kick.Sdram.o obj/libdaisy.a -Wl,--end-group  
/usr/local/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/bin/../lib/gcc/arm-none-eabi/10.3.1/../../../../arm-none-eabi/bin/ld: Kick section `.text' will not fit in region `FLASH'
/usr/local/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/bin/../lib/gcc/arm-none-eabi/10.3.1/../../../../arm-none-eabi/bin/ld: region `FLASH' overflowed by 2871000 bytes
collect2: error: ld returned 1 exit status
ninja: build stopped: subcommand failed.
```

If you look at the highlighted lines, you will see that the linker complains that the FLASH
region was overflowed.

```{note}
Building for the simulator using `erbb build simulator` won't be able to detect
memory section overflows.
```


## Installer Support

Flashing the firmware to QSPI is a bit different from Flashing to the internal flash.

Like we said above, we need a bootloader for that. The bootloader is going to be installed
in the internal flash memory and then install the program to the QSPI flash section.
This can be done simply like this:

```shell-session
eurorack-blocks/samples/kick$ erbb bootloader
Enter the system bootloader by holding the BOOT button down,
and then pressing, and releasing the RESET button.
Uploading dsy_bootloader_v4 to flash section...
...
eurorack-blocks/samples/kick$ erbb install dfu
Enter the Daisy bootloader by pressing the RESET button.
Press Enter to continue...
Uploading Kick to qspi section...
dfu-util 0.11
```

First, when installing the bootloader, you need to press both BOOT and RESET to write to flash memory.

Then, as soon as you press the RESET button, the Daisy bootloader starts, and you will see
the User LED flashing on the board. It will wait for 5 seconds in this state, so you should
be prepared to start the `erbb install`. If you missed the bootloader start, just press
the RESET button again.

After that, the bootloader will go in a different LED dance, and you will see the program
being downloaded to the Daisy hardware. Note that in the case of the Kick module, it
takes quite some time, but still less than a minute. This is because the program is nearly
3MB with all those samples!

```{important}
Note that when using the bootloader, you only press the RESET button, **not**
combined with the BOOT button.
```


The `erbb install` command will parameter the installation automatically.

```{important}
The bootloader needs to be installed only once. However, if you install after
a new program in the flash section, you will need to reinstall the bootloader.
```

```{note}
`erbb install` cannot be used with the `openocd` option when flashing to
QSPI.
```
