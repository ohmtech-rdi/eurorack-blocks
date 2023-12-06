# C++ on Windows with CLI only


## Requirements

```{note}
Windows 10 or later is recommended.
```

Before we can setup Eurorack-blocks, we will need to have on your system:

- [`git`](https://git-scm.com/download) and in particular the Git Bash shell
- [Python 3](https://www.python.org/downloads/)
- [VCV Rack at least version 2.4](https://vcvrack.com/Rack)

If you are a developer, there is a chance that most of them are installed already.

In all cases, please make sure that the Python in use is not the one from the Windows Store.

Experienced developers might already have one (or multiple!) versions of Python installed.
For Eurorack-blocks, please use at least Python 3.7.

For all the following commands, we will use Git Bash that comes included with `git` on
Windows.

```{important}
All commands are expecting the use of Git Bash.
They are not compatible with Cmd or PowerShell.
```

```{note}
Please use the copy button on the top right corner of the following code blocks
to copy/paste the commands in your terminal.
```

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
MyPC:~/eurorack-blocks $ erbb setup
```

This will take a bit of time depending on your Internet connection.

`erbb setup` by itself is installing dependencies internally without modifying anything on
your system. If you delete the `eurorack-blocks` folder, boom, everything is gone.

You can now start to use `eurorack-blocks` 🎉


## Testing a Sample

Let's test a sample. We'll use the Drop sample.

```{code-block} shell-session
MyPC:~/eurorack-blocks $ cd samples/drop
MyPC:~/eurorack-blocks/samples/drop $ erbb configure
```

You can build and install the simulator module by running:

```{code-block} shell-session
MyPC:~/eurorack-blocks/samples/drop $ erbb build simulator
mkdir Release
ACTION UI
ACTION VCV Rack
COPY include/erb/vcvrack/resource/rogan.6ps.svg
...
LINK plugin.dylib
PACKAGE Release Drop
INSTALL /Users/raf/Documents/Rack2/plugins-win-x64/Drop/
```

You can then run VCV Rack and play with your module.

Modules are built with `clang` and will require `lldb`. You can build a debug version
of the simulator by running:

```{code-block} shell-session
MyPC:~/eurorack-blocks/samples/drop $ erbb build simulator --configuration debug
mkdir Debug
ACTION UI
ACTION VCV Rack
COPY include/erb/vcvrack/resource/rogan.6ps.svg
...
LINK plugin.dylib
PACKAGE Debug Drop
INSTALL /Users/raf/Documents/Rack2/plugins-win-x64/Drop/
```

You can build the firmware by running:

```{code-block} shell-session
MyPC:~/eurorack-blocks/samples/drop $ erbb build firmware
BUILD libDaisy
mkdir Release
ACTION UI
ACTION Daisy
...
LINK Release/Drop.elf
Memory region         Used Size  Region Size  %age Used
           FLASH:       81928 B       128 KB     62.51%
         DTCMRAM:          0 GB       128 KB      0.00%
            SRAM:      519696 B       512 KB     99.12%
          RAM_D2:       16968 B       288 KB      5.75%
          RAM_D3:          0 GB        64 KB      0.00%
         ITCMRAM:          0 GB        64 KB      0.00%
           SDRAM:          0 GB        64 MB      0.00%
       QSPIFLASH:          0 GB         8 MB      0.00%
OBJCOPY Release/Drop.bin
OBJCOPY Release/Drop.hex
```

And so on. Please run `erbb ... --help` to navigate all different options.
For example `erbb build simulator --help` lists all options to build the simulator.


## Testing in VCV Rack

In VCV Rack the `Drop` module will appear in the library when right-clicking in the rack empty space.

```{image} vcvrack-drop.png
:width: 100%
:align: center
```

```{important}
Before starting to play with it, make sure to setup your audio device,
and set the sample rate to 48kHz!
This requirement will be explained later in the tutorial.
```

```{image} windows-vcvrack-audio.png
:align: center
```


## Testing in your Eurorack System

If you bougth the Eurorack-blocks Starter Kit, it comes with the Drop module, and you should
have already assembled it by now.

To install the firmware, that we previously built in the section above:
- Connect the same USB cable that you used for installing the Frohmager firmware,
- Run the following command and follow the on-screen instructions:

```{code-block} shell-session
MyPC:~/eurorack-blocks/samples/drop $ erbb install firmware
Enter the system bootloader by holding the BOOT button down,
and then pressing, and releasing the RESET button.
Press Enter to continue...
...
```

```{image} stlink-v3-mini.png
:width: 30%
:align: right
```

Note that if you bought a STLink V3 Mini
for example from [Electro-smith](https://www.electro-smith.com/daisy/stlink-v3mini),
you can use it to program the Daisy Patch Submodule.
It has the advantage to be more convenient, as:
- It is typically faster than using the USB port on the Daisy Patch Submodule,
- You don't need to remove your module from your base to press those BOOT and RESET
   button.

The `install` command will automatically select the STLink V3 Mini to install the firmware
if it is plugged on your computer.

Have fun!

Maybe now is a good time to head over to **{doc}`/guides/first`** to learn more about the
Eurorack-blocks' C++ framework.
