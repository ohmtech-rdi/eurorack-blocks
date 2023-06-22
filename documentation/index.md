# Eurorack-blocks: Software to Hardware Prototyping for Eurorack

The Eurorack-blocks project allows to develop your own custom Eurorack module for either prototyping or fun in the comfort of your day-to-day IDE and debugging in a virtual Eurorack environment, and when ready, to auto-magically generate all the needed files to manufacture the Eurorack module for you to use in a real Eurorack modular system.

```{image} getting-started/what-boards.png
:width: 50%
:align: center
```

No embedded system or hardware knowledge needed 🤗

: You don't need to be an embedded software or hardware engineer to produce a Eurorack module.
   Eurorack-blocks takes care of this so you can focus exclusively on the creative part of your module.

Build an debug in your favorite IDE 💻

: Thanks to the simulator, you can test your module completely in a virtual Eurorack environment, [VCV Rack](https://vcvrack.com).
   Iterate and refine your module, and think about creating the hardware only later.

Integration with Max and Faust 🔀

: You don't need to use C++. Use your favorite audio environment like Max or Faust to express your ideas quickly.

Enough power to support your wildest ideas 💪

: Eurorack-blocks is using [Daisy Patch Submodule](https://www.electro-smith.com/daisy/patch-sm),
   a DSP platform for Eurorack synthesizer modules. It features a lightning fast STM32 processor,
   high fidelity stereo audio codec, and enough RAM for 10 minute long buffers
   — all with standard signal levels and conditioning for the Eurorack ecosystem.

Open Source ❤️

: Our code is [free and open source](https://github.com/ohmtech-rdi/eurorack-blocks) with a very permissive [license](https://github.com/ohmtech-rdi/eurorack-blocks/blob/main/LICENSE).


## Audience

You should be familiar with either C++, Max or Faust.

You should know how to use a terminal and a shell like `bash`, but their usage are quite limited.

Some knowledge of `git` and a package manager such as `apt` or `brew` when using Faust
is also adviced, while not strictly necessary.


## Getting Started

Are you new to Eurorack-blocks?
Start here to get to know the environment and what it will bring to you.

- **{doc}`/getting-started/before`**
- **{doc}`/getting-started/what`**
- **{doc}`/getting-started/setup`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Getting Started

   /getting-started/before
   /getting-started/what
   /getting-started/setup
```

## ERB Starter Kit

The ERB starter kit available on our shop (coming soon)
is the easiest way to get into Eurorack-blocks development quickly.
Continue here to assemble it and make some sound with the included demos.

- **{doc}`/starter-kit/content`**
- **{doc}`/starter-kit/requirements`**
- **{doc}`/starter-kit/kivu12`**
- **{doc}`/starter-kit/demos`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: ERB Starter Kit

   /starter-kit/content
   /starter-kit/requirements
   /starter-kit/kivu12
   /starter-kit/demos
```


## Environment Setup

Now that you have an Eurorack-blocks board to develop with,
it's time to get ready for developping your own creation.
Head over to setup the Eurorack-blocks environment for C++,
Max or Faust on macOS, Windows or Linux.

- **{doc}`/setup/select`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Environment Setup

   /setup/select
   /setup/macos-cpp-xcode
   /setup/macos-cpp-vscode
   /setup/macos-cpp-cli
   /setup/macos-max
   /setup/macos-faust
```


## C++ Programming Guides

Do you have an awesome idea and understood the basic Eurorack-blocks concept
described in the Getting Started section?
Continue here to learn how to create your own module.

- **{doc}`/guides/first`**
- **{doc}`/guides/drop`**
- **{doc}`/guides/reverb`**
- **{doc}`/guides/kick`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: C++ Programming Guides

   /guides/first
   /guides/drop
   /guides/reverb
   /guides/kick
```


## Max Integration

Do you use Max in your company to prototype your software and only go for C++ later on?
Or is Max your go-to visual programming language to prototype your instruments
and effects idea?
Continue here to learn how to develop your module using Max with `gen~` and
its vibrant community.

- **{doc}`/max/first`**
- **{doc}`/max/ui`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Max Integration

   /max/first
   /max/ui
```


## Faust Integration

C++ is not your thing and you prefer to use [Faust](https://faust.grame.fr),
a functional programming language for sound synthesis and audio processing instead?
Continue here to learn how to create your own module using Faust.

- **{doc}`/faust/first`**
- **{doc}`/faust/mapping`**
- **{doc}`/faust/soundfile`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Faust Integration

   /faust/first
   /faust/mapping
   /faust/soundfile
```


## DIY Corner

Now that you tested your shiny new module in the simulator, one task only is left:
making it an object in the real world to use in your Eurorack system.
The Eurorack-blocks market place (coming soon) is a super convenient way
to get your new module delivered already assembled to your door.
But maybe you adhere to the DIY philosophy and want to be able to build your own
module without the direct aid of our service?
Eurorack-blocks got you covered! so read on to get your hands dirty:

- **{doc}`/diy/intro`**
- **{doc}`/diy/board`**
- **{doc}`/diy/drc`**
- **{doc}`/diy/routing`**
- **{doc}`/diy/order-assemble`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: DIY Corner

   /diy/intro
   /diy/board
   /diy/drc
   /diy/routing
   /diy/order-assemble
```


## Controls Reference

### Audio Signals

- **{doc}`/controls/AudioIn`**
- **{doc}`/controls/AudioOut`**

### Control Voltages

- **{doc}`/controls/CvIn`**
- **{doc}`/controls/CvOut`**

### Trigger, Gate and Clock Signals

- **{doc}`/controls/GateIn`**
- **{doc}`/controls/GateOut`**

### Human Interface Devices

- **{doc}`/controls/Button`**
- **{doc}`/controls/Led`**
- **{doc}`/controls/LedBi`**
- **{doc}`/controls/LedRgb`**
- **{doc}`/controls/Pot`**
- **{doc}`/controls/Switch`**
- **{doc}`/controls/Trim`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Controls Reference

   /controls/README
   /controls/AudioIn
   /controls/AudioOut
   /controls/Button
   /controls/CvIn
   /controls/CvOut
   /controls/GateIn
   /controls/GateOut
   /controls/Led
   /controls/LedBi
   /controls/LedRgb
   /controls/Pot
   /controls/Switch
   /controls/Trim
```


## Erbb Language Reference

- **{doc}`/erbb/lexical`**
- **{doc}`/erbb/grammar`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Erbb Language Reference

   /erbb/lexical
   /erbb/grammar
```


## Erbui Language Reference

- **{doc}`/erbui/lexical`**
- **{doc}`/erbui/grammar`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Erbui Language Reference

   /erbui/lexical
   /erbui/grammar
```
