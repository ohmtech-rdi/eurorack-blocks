# Faust on macOS


## Requirements

```{note}
macOS 10.15 (Catalina) has limited support. Some tools do not always work
properly, so macOS 11 (Big Sur) or later is recommended.
```

Before we can setup Eurorack-blocks, we will need to have on your system:

- [`git`](https://git-scm.com/download)
- [Python 3](https://www.python.org/downloads/)
- [Xcode command line tools](https://developer.apple.com/xcode/)
- [Faust](https://faust.grame.fr)
- [VCV Rack version 2](https://vcvrack.com/Rack)

If you are a developer, there is a chance that most of them are installed already.

In all cases, please make sure that the Python in use is not the one from Xcode.
You can verify this by typing `which python3` in the Terminal and looking for the mention
of `Xcode` in the returned path. If this command didn't return anything, then you do not
have Python installed, and please use the link above to install it.

Experienced developers might already have one (or multiple!) versions of Python installed.
For Eurorack-blocks, please use at least Python 3.7.

```{note}
Please use the copy button on the top right corner of the following code blocks
to copy/paste the commands in your terminal.
```

The Xcode command line tools come already with Xcode, so one option is to install Xcode
as well. If you want to avoid having to install Xcode, you can selectively install the Xcode
command line tools by running:

```{code-block} shell-session
MyMac:~ $ xcode-select --install
```

You can check your installation by trying the following commands, and checking it doesn't
return an error or something else than it version. Versions are shown here for a concrete
example, they might be different on your computer.

You can download Faust [here](https://faust.grame.fr/downloads/). Please make sure to
follow their installation instructions. You want to make sure that the program `faust`
is in your `PATH`.

```{code-block} shell-session
MyMac:~ $ git --version
git version 2.41.0
```

```{code-block} shell-session
MyMac:~ $ python3 --version
Python 3.11.4
```

```{code-block} shell-session
MyMac:~ $ xcodebuild -version
Xcode 13.4
Build version 13F17a
```

```{code-block} shell-session
MyMac:~ $ faust -version
FAUST Version 2.60.3
Embedded backends:
Embedded backends: 
   DSP to C
   DSP to C++
   ...
Build with LLVM version 14.0.6
Copyright (C) 2002-2022, GRAME - Centre National de Creation Musicale. All rights reserved. 
```

```{code-block} shell-session
MyMac:~ $ which python3
/Library/Frameworks/Python.framework/Versions/3.11/bin/python3
```
Note that `Xcode` doesn't appear in the above path.


## Cloning

Clone the repository. This will create a `eurorack-blocks` directory **into the current working directory**, with all dependencies.

```{code-block} shell-session
MyMac:~ $ git clone --recurse-submodules https://github.com/ohmtech-rdi/eurorack-blocks.git
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
MyMac:~ $ cd eurorack-blocks
```

Then install by running the script below:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ ./build-system/install.py
```

This will add the `erbb` script to your `PATH`, but the `PATH` will be set only for new terminals.
You can either close your current terminal and open a new one, or source the `erbb` environment
explicitly into your current shell session:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ source ./build-system/init.sh
```

Then:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ erbb setup
```

This will take a bit of time depending on your Internet connection.

`erbb setup` by itself is installing dependencies internally without modifying anything on
your system. If you delete the `eurorack-blocks` folder, boom, everything is gone.

You can now start to use `eurorack-blocks` 🎉


## Testing a Sample

Let's test a sample. We'll use the Faust sample.

```{code-block} shell-session
MyMac:~/eurorack-blocks $ cd samples/faust
MyMac:~/eurorack-blocks/samples/faust $ erbb configure
```

You can build and install the simulator module by running:

```{code-block} shell-session
MyMac:~/eurorack-blocks/samples/faust $ erbb build simulator
```

You can then run VCV Rack and play with your module.

You can build the firmware by running:

```{code-block} shell-session
MyMac:~/eurorack-blocks/samples/faust $ erbb build firmware
```

And so on. Please run `erbb ... --help` to navigate all different options.
For example `erbb build simulator --help` lists all options to build the simulator.

If you have the Xcode or Visual Studio Code, you can actually use those IDE to edit the
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

```{image} vcvrack-audio.png
:align: center
```

That's it! You are now all set to start building your own modules!
