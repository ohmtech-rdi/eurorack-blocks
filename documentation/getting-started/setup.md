# Setting up the Environment

## Requirements

Make sure you have the following requirements before starting:

- A [GitHub account](https://github.com/join)
- [`git`](https://git-scm.com/download)
- [Python 3](https://www.python.org/downloads/)
- [Homebrew](https://brew.sh) on macOS X
- [Xcode](https://developer.apple.com/xcode/) on macOS X

You then only need minimum knowledge on how the terminal works to get going.


## Cloning

First, clone the repository. This will create a `eurorack-blocks` directory **into the current working directory**, with all dependencies.


```shell-session
~$ git clone --recurse-submodules git@github.com:ohmtech-rdi/eurorack-blocks.git
~$ cd eurorack-blocks
~/eurorack-blocks$
```


## Setting up

Install by running the script below:

```shell-session
~/eurorack-blocks$ ./build-system/install.py
```

This will add the `erbb` script to your `PATH`.

```shell-session
~/eurorack-blocks$ erbb setup
```

This will install all the needed dependencies. You would typically re-run this command when
upgrading `eurorack-blocks`.

In particular, this will install VCV Rack and Kicad. Don't worry if you already have installed those
applications! The setup script won't overwrite your installation.

You can now start to use `eurorack-blocks` 🎉


## Testing a Sample

Let's test a sample. We'll use the Drop sample.

```shell-session
~/eurorack-blocks$ cd samples/drop
~/eurorack-blocks/samples/drop$ erbb configure
```

If you inspect the `drop` folder, it now contains an `artifacts` directory, with some folders and files.

```{image} setup-configure.png
:width: 100%
:align: center
```

- The `daisy` folder contains the build files for the [`ninja` build system](https://ninja-build.org), to produce the Daisy firmware,
- The `project_vcvrack.xcodeproj` is an Xcode project,
   to produce the VCV Rack simulator module on macOS,
- Not shown on the screenshot above, the `simulator` folder contains the build files for the `ninja` build system,
   to produce the VCV Rack simulator module on Linux.


## Building in Xcode

If you are using Xcode, use  `project_vcvrack.xcodeproj` to develop, test and debug in the VCV Rack simulator.
This will open the project in Xcode:

```shell-session
~/eurorack-blocks/samples/drop$ open artifacts/project_vcvrack.xcodeproj
```

```{image} setup-xcode.png
:width: 100%
:align: center
```

Press {guilabel}`⌘B` to build.

The build process will output the VCV Rack module in the `Rack/plugins-v1` folder.


## Building from the command line

Alternatively, you can build the VCV Rack module using the command line.
This works on both Linux and macOS, with a different output depending on the build system
used. Below, we should an extract of the output on macOS.

```shell-session
~/eurorack-blocks/samples/drop$ erbb build simulator
Build settings from command line:
    SYMROOT = /Users/raf/dev/eurorack-blocks/samples/drop/artifacts/build
...
** BUILD SUCCEEDED **
```

The build process will output the VCV Rack module in the `Rack/plugins-v1` folder.


## Testing in VCV Rack

Now run VCV Rack, and the `Drop` module will appear in the library when right-clicking
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


## Debugging in VCV Rack using Xcode

```{image} setup-debug-scheme.png
:width: 32%
```
```{image} setup-debug-executable.png
:width: 32%
```
```{image} setup-debug-document.png
:width: 32%
```

To debug on Xcode, the following configuration must be first done:
- Select the `Product > Scheme > Drop` scheme,
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


