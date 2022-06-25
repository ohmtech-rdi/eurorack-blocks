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


## Cloning

First, clone the repository. This will create a `eurorack-blocks` directory **into the current working directory**, with all dependencies.


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

- The `daisy` folder contains the build files for the Daisy firmware,
- The `simulator` folder contains the build files when building from the command line,
- The `Drop.code-workspace` is a Visual Studio Code workspace, to develop, build and debug either the simulator or firmware,
- The `project_vcvrack.xcodeproj` is an Xcode project, to develop, build and debug the simulator module on macOS.


## Building from the command line

Alternatively, you can build the VCV Rack module using the command line.
This works on both Linux, macOS and Windows, with a different output depending on the build system
used. Below, we should an extract of the output on macOS.

```shell-session
~/eurorack-blocks/samples/drop$ erbb build simulator
mkdir Release
ACTION UI
COPY include/erb/vcvrack/resource/rogan.5ps.svg
...
CXX dsp/ReverbSc.cpp
LINK plugin.dylib
PACKAGE Release Drop
INSTALL /Users/raf/Documents/Rack2/plugins/Drop/
```

The build process will output the VCV Rack module in the `Rack2/plugins` folder.


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


## Debugging using Visual Studio Code

The Visual Studio Code workspace file allows to debug your module both for the simulator and the Daisy hardware platform.

```{image} setup-vscode.png
:width: 100%
```

- Choose `File > Open Workspace from File...`,
- Locate your module `artifacts` folder and open the `code-workspace` in it,
- Choose the `Run & Debug` tab in the side bar,
- Select the target you want to debug,
   - `Launch Firmware Release` will debug the firmware in Release configuration on the connected Daisy using a STLink probe with OpenOCD,
   - `Launch Firmware Debug` will debug the firmware in Debug configuration on the connected Daisy using a STLink probe with OpenOCD,
   - `Launch Simulator Debug` will debug your module with the simulator in VCV Rack,
- Hit the green play button to start debugging.

```{image} setup-vscode-debug.png
:width: 100%
```

You might want to debug your firmware in Release configuration when the Debug configuration is too big for the internal Flash memory.


## Building with Xcode

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

The build process will output the VCV Rack module in the `Rack2/plugins` folder.


## Debugging in the simulator using Xcode

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


