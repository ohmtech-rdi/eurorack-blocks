# Faust on Linux


## Requirements

```{note}
Ubuntu Focal (20.04) or later is recommended.
```

Before we can setup Eurorack-blocks, we will need to have on your system:

- [`git`](https://git-scm.com/download)
- [Python 3](https://www.python.org/downloads/)
- [Faust](https://faust.grame.fr)
- [VCV Rack version 2](https://vcvrack.com/Rack)

If you are a developer, there is a chance that most of them are installed already.

Experienced developers might already have one (or multiple!) versions of Python installed.
For Eurorack-blocks, please use at least Python 3.7.

```{note}
Please use the copy button on the top right corner of the following code blocks
to copy/paste the commands in your terminal.
```

Typically on Ubuntu, you would use `apt` to install `git` and `python3`.

Make sure everything is up-to-date: 

```{code-block} shell-session
MyPC:~ $ sudo apt-get update
```

To install Git, run the following command:

```{code-block} shell-session
MyPC:~ $ sudo apt-get install git-all
```

To install Python 3, run the following command:

```{code-block} shell-session
MyPC:~ $ sudo apt-get install python3
```

You can download Faust [here](https://faust.grame.fr/downloads/). Please make sure to
follow their installation instructions. You want to make sure that the program `faust`
is in your `PATH`.

You can check your installation by trying the following commands, and checking it doesn't
return an error or something else than it version. Versions are shown here for a concrete
example, they might be different on your computer.

```{code-block} shell-session
MyPC:~ $ git --version
git version 2.41.0
```

```{code-block} shell-session
MyPC:~ $ python3 --version
Python 3.11.4
```

```{code-block} shell-session
MyPC:~ $ faust --version
FAUST Version 2.60.3
Embedded backends:
Embedded backends: 
   DSP to C
   DSP to C++
   ...
Build with LLVM version 14.0.6
Copyright (C) 2002-2022, GRAME - Centre National de Creation Musicale. All rights reserved. 
```


## Cloning

Clone the repository. This will create a `eurorack-blocks` directory **into the current working directory**, with all dependencies.

```{code-block} shell-session
MyPC:~ $ git clone --recurse-submodules https://github.com/ohmtech-rdi/eurorack-blocks.git
```

Will typically output:

```{code-block} shell-session
Cloning into 'eurorack-blocks'...
remote: Enumerating objects: 14327, done.
...
Submodule path 'submodules/libDaisy/tests/googletest': checked out 'f5e592d8ee5ffb1d9af5be7f715ce3576b8bf9c4'
Submodule path 'submodules/vcv-rack-sdk': checked out '91fd742827c04d36ba9b0e5e179571e393682326'
```


## Setting up

First change the current directory to `eurorack-blocks`:

```{code-block} shell-session
MyPC:~ $ cd eurorack-blocks
```

Then install by running the script below:

```{code-block} shell-session
MyPC:~/eurorack-blocks $ ./build-system/install.py
```

This will add the `erbb` script to your `PATH`, but the `PATH` will be set only for new terminals.
You can either close your current terminal and open a new one, or source the `erbb` environment
explicitly into your current shell session:

```{code-block} shell-session
MyPC:~/eurorack-blocks $ source ./build-system/init.sh
```

Then:

```{code-block} shell-session
MyPC:~/eurorack-blocks $ erbb setup --with-apt
```

This will take a bit of time depending on your Internet connection.

`erbb setup` by itself is installing dependencies internally without modifying anything on
your system. If you delete the `eurorack-blocks` folder, boom, everything is gone.

The additional options, usually starting with `--with` do change your system. For example
here we install the needed toolchain using `apt`.

You might have a different package manager (for example `dnf` on Fedora), that is not supported
natively in Eurorack-blocks, or you just want to make sure that Eurorack-blocks doesn't install
programs without you knowing exactly what is installed.

If you want to see exactly what it does, navigate to `build-system/scripts/erbb`,
and look at the Linux section in the `setup` function.

You can now start to use `eurorack-blocks` 🎉


## Testing a Sample

Let's test a sample. We'll use the Faust sample.

```{code-block} shell-session
MyPC:~/eurorack-blocks $ cd samples/faust
MyPC:~/eurorack-blocks/samples/faust $ erbb configure
```

You can build and install the simulator module by running:

```{code-block} shell-session
MyPC:~/eurorack-blocks/samples/faust $ erbb build simulator
ACTION Faust
ACTION UI
ACTION VCV Rack
COPY include/erb/vcvrack/resource/rogan.6ps.svg
...
LINK plugin.dylib
PACKAGE Release Flanger
INSTALL /Users/raf/Documents/Rack2/plugins/Flanger/
```

You can then run VCV Rack and play with your module.

You can build the firmware by running:

```{code-block} shell-session
MyPC:~/eurorack-blocks/samples/faust $ erbb build firmware
ACTION Faust
ACTION UI
ACTION VCV Rack
...
LINK Release/Flanger.elf
Memory region         Used Size  Region Size  %age Used
           FLASH:       77416 B       128 KB     59.06%
         DTCMRAM:          0 GB       128 KB      0.00%
            SRAM:      519736 B       512 KB     99.13%
          RAM_D2:       16968 B       288 KB      5.75%
          RAM_D3:          0 GB        64 KB      0.00%
         ITCMRAM:          0 GB        64 KB      0.00%
           SDRAM:         64 MB        64 MB    100.00%
       QSPIFLASH:          0 GB         8 MB      0.00%
OBJCOPY Release/Flanger.bin
OBJCOPY Release/Flanger.hex
```

And so on. Please run `erbb ... --help` to navigate all different options.
For example `erbb build simulator --help` lists all options to build the simulator.

If you have the Visual Studio Code, you can actually use those IDE to edit the
Eurorack-blocks files if you wish. For this please follow the instructions in the respective
chapters.


## Testing in VCV Rack

In VCV Rack the `Faust` module will appear in the library when right-clicking in the rack empty space.

```{image} vcvrack-faust.png
:width: 100%
:align: center
```

```{important}
Before starting to play with it, make sure to setup your audio device,
and set the sample rate to 48kHz!
This requirement will be explained later in the tutorial.
```

```{image} macos-vcvrack-audio.png
:align: center
```

Maybe now is a good time to head over to **{doc}`/faust/first`** to learn more about the
Faust integration in Eurorack-blocks.
