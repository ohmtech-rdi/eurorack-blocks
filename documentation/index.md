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

Integration with Max and FAUST 🔀

: You don't need to use C++. Use your favorite audio environment like Max (coming soon) or FAUST (coming soon) to express your ideas quickly.

Enough power to support your wildest ideas 💪

: Eurorack-blocks is using [Daisy Patch Submodule](https://www.electro-smith.com/daisy/patch-sm),
   a DSP platform for Eurorack synthesizer modules. It features a lightning fast STM32 processor,
   high fidelity stereo audio codec, and enough RAM for 10 minute long buffers
   — all with standard signal levels and conditioning for the Eurorack ecosystem.

Open Source ❤️

: Our code is [free and open source](https://github.com/ohmtech-rdi/eurorack-blocks) with a very permissive [license](https://github.com/ohmtech-rdi/eurorack-blocks/blob/main/LICENSE).


## Audience

You should be familiar with either C++, Max or FAUST.

You should know how to use a terminal and a shell like `bash`, but their usage are quite limited.

Some knowledge of `git` and a package manager such as `apt` or `brew` is also adviced,
while not strictly necessary.


## Getting Started

Are you new to Eurorack-blocks?
Start here to learn on how to setup your environment and make your first module.

- **{doc}`/getting-started/before`**
- **{doc}`/getting-started/what`**
- **{doc}`/getting-started/setup`**
- **{doc}`/getting-started/first`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Getting Started

   /getting-started/before
   /getting-started/what
   /getting-started/setup
   /getting-started/first
```


## Programming Guides

Do you have an awesome idea and understood the basic Eurorack-blocks concept
described in the Getting Started section?
Continue here to learn how to create your own module.

- **{doc}`/guides/drop`**
- **{doc}`/guides/reverb`**
- **{doc}`/guides/kick`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Programming Guides

   /guides/drop
   /guides/reverb
   /guides/kick
```


## FAUST Integration

C++ is not your thing and you prefer to use FAUST instead?
Continue here to learn how to create your own module using FAUST.

- **{doc}`/faust/setup`**
- **{doc}`/faust/first`**
- **{doc}`/faust/mapping`**
- **{doc}`/faust/soundfile`**

```{eval-rst}
.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: FAUST Integration

   /faust/setup
   /faust/first
   /faust/mapping
   /faust/soundfile
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
