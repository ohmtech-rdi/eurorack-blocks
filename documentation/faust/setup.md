# Setting up the Environment

## Requirements

Make sure you have the following requirements before starting.
You then only need minimum knowledge on how the terminal works to get going.

### All platforms

- [`git`](https://git-scm.com/download)
- [Python 3](https://www.python.org/downloads/)
- [VCV Rack](https://vcvrack.com/Rack)

### macOS

- macOS at least version 10.15 (Catalina)
- The [Homebrew](https://brew.sh) package manager
- The [Xcode](https://developer.apple.com/xcode/) IDE and build environment

### Linux

- Linux Ubuntu 20.04

### Windows

- Windows at least version 10
- The [Git Bash](https://git-scm.com/download) shell
- The [Chocolatey](https://chocolatey.org) package manager
- The [MSYS2](https://www.msys2.org) software distribution and building platform

All commands on Windows are expecting the use of Git Bash.
They are not compatible with Cmd or PowerShell.


## Setting up Faust

The Faust compiler comes with some additional programs, but also a set of headers, and it should be configured so
that Faust headers are available to the development environment.
In general it is best to install it with your package manager. This will make sure that both
the Faust programs and development environment are correctly installed.

### macOS

```
brew install faust
```

### Linux

```
sudo apt-get install faust
```

### Windows

Download the [Faust Windows installer](https://github.com/grame-cncm/faust/releases/download/2.37.3/Faust-2.37.3-win64.exe)
and follows the on-screen instructions.

Then add the Faust install path to your `PATH` by running the following command into Git Bash:

```
echo 'export PATH=$PATH:/c/Program\ Files/Faust/bin' >> ~/.bash_profile
```

You need to close and open a new Git Bash shell to make sure your environment change is properly updated.


## Cloning

Then, clone the repository. This will create a `eurorack-blocks` directory **into the current working directory**, with all dependencies.


```shell-session
~$ git clone --recurse-submodules https://github.com/ohmtech-rdi/eurorack-blocks.git
~$ cd eurorack-blocks
~/eurorack-blocks$
```


## Setting up

Install by running the script below:

```shell-session
~/eurorack-blocks$ ./build-system/install.py
```

This will add the `erbb` script to your `PATH`, but the `PATH` will be set only for new terminals.
You can either close your current terminal and open a new one, or source the `erbb` environment
explicitly into your current shell session:

```shell-session
~/eurorack-blocks$ source ./build-system/init.sh
```

Then:

```shell-session
~/eurorack-blocks$ erbb setup
```

This will install all the needed dependencies. You would typically re-run this command when
upgrading `eurorack-blocks`.
If you prefer to install everything manually, just navigate the `erbb` Python script
to the `setup` function to see what get installed and how, depending on your platform.

You can now start to use `eurorack-blocks` with Faust 🎉


## Testing a Sample

Let's test a sample. We'll use the Faust sample.

```shell-session
~/eurorack-blocks$ cd samples/faust
~/eurorack-blocks/samples/faust$ erbb configure
~/eurorack-blocks/samples/faust$ erbb build simulator
mkdir Release
ACTION Faust
ACTION UI
COPY include/erb/vcvrack/resource/rogan.5ps.svg
...
CXX dsp/ReverbSc.cpp
LINK plugin.dylib
PACKAGE Release Flanger
INSTALL /Users/raf/Documents/Rack2/plugins/Flanger/
```


## Testing in VCV Rack

Now run VCV Rack, and the `FLANGER` module will appear in the library when right-clicking
in the rack empty space.

```{image} setup-rack.png
:width: 100%
:align: center
```

```{important}
Before starting to play with it, make sure to setup your audio device,
and set the sample rate to 48kHz!
This requirement will be explained later in the tutorial.
```

```{image} setup-rack-audio.png
:align: center
```
