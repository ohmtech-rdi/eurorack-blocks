# Setting up the Environment

## Requirements

Make sure you have the following requirements before starting:

- A [GitHub account](https://github.com/join)
- [`git`](https://git-scm.com/download)
- [Python 3](https://www.python.org/downloads/)
- [Homebrew](https://brew.sh) on macOS X
- [Xcode](https://developer.apple.com/xcode/) on macOS X
- [Max](https://cycling74.com/products/max)

You then only need minimum knowledge on how the terminal works to get going.

Your Max installation **needs to have a valid authorization** for `gen~` code to be exported,
on which Eurorack-blocks relies.


## Licensing

Eurorack-blocks has a very permissive [license](https://github.com/ohmtech-rdi/eurorack-blocks/blob/poc-max-integration/LICENSE)
that allows commercial use, modifications, distribution and private use,
as long  as you follow the license requirements.

However, the use of Max-generated code follows a different license,
that you need to follow as well.
Don't worry, if you are a hobbyist and don't plan to make any commercial use,
still read the license to be aware of it in the future,
or check your understanding of commercial-use in the license context, and just go on.
However if you plan to do commercial use of your module using Max-generated code,
you need to comply to Cycling '74's license and read their following license carefully:

```
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing@cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
```

Additionally, Cycling '74 provides a FAQ if you need more details, that you can read
[here](https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ).
Finally if you have still more questions, please don't hesitate to contact
[licensing@cycling74.com](mailto:licensing@cycling74.com). They won't bite you!


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


## Adding in Max

You can add the Max package contained in Eurorack-blocks directly to Max, by making
a symbolic link to it in your Max packages directory.

```
```shell-session
~/eurorack-blocks$ cd max
~/eurorack-blocks/max$ ln -s "$(pwd)/Eurorack-blocks" ~/Documents/Max\ 8/Packages/Eurorack-blocks
```

You can now start to use `eurorack-blocks`  with Max 🎉


## Testing a Sample

Let's test a sample. We'll use the Max sample.

```shell-session
~/eurorack-blocks$ cd max/reverb
~/eurorack-blocks/max/reverb$ erbb configure
warning: No gen code found. Please open Reverb.maxpat and save it to generate gen code. 
```

For now, let's just ignore the warning.
If you inspect the `max` folder, it now contains an `artifacts` directory, with a lot of files.

```{image} setup-configure.png
:width: 100%
:align: center
```

## Generating gen code

Before you can build, you need to generate the Max gen code from the Max patch.
This is exactly what the warning was telling you to do!
So let's open the `Reverb.maxpat` file in the `reverb` directory and just save it
to create the Max gen code.

```{note}
Everytime you save your Max patch file, the gen code is regenerated.
```

Now you are ready to test in the simulator using VCVRack as well as already generate the
firmware files for your Eurorack module.


## Building in Xcode

If you are using Xcode, a `project_vcvrack.xcodeproj` has been created,
which is the project to use to develop and test in the VCV Rack simulator.

This will open the project in Xcode:

```shell-session
~/eurorack-blocks/max/reverb$ open artifacts/project_vcvrack.xcodeproj
```

```{image} setup-xcode.png
:width: 100%
:align: center
```

Press {guilabel}`⌘B` to build.

The build process will output the VCV Rack module in the `Rack/plugins-v1` folder.


## Building from the command line

Alternatively, you can build the VCV Rack module using the command line.

```shell-session
~/eurorack-blocks/max/reverb$ erbb build simulator
Build settings from command line:
    SYMROOT = /Users/raf/dev/eurorack-blocks/max/reverb/artifacts/build
...
** BUILD SUCCEEDED **
```

The build process will output the VCV Rack module in the `Rack/plugins-v1` folder.


## Testing in VCV Rack

Now run VCV Rack, and the `Reverb` module will appear in the library when right-clicking
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
