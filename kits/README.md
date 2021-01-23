# kits

## Description

This contains "kits" as panels of the most used block for the most popular digital modules.

Blocks are collected into panels to reduce the cost of producing one panel. The more panels
are ordered, the more it is going to fit any configuration of modules:
- 1 panel is a good setup to start with, covering all simplest needs,
- 2 panels are an excellent setup to cover about any cases,
- 3 panels cover every use, except for very specific ones.

The standard panels contain only very common blocks. Blocks like `slider` are separate
panels.


## Method

This folder contains a `.csv` file which collects the configuration of the most popular
digital modules, as dictated by the
[modulargrid.net most popular digital modules](https://www.modulargrid.net/e/modules/browser?SearchName=&SearchVendor=&SearchFunction=12&SearchSecondaryfunction=&SearchHeight=&SearchTe=&SearchTemethod=max&SearchBuildtype=&SearchLifecycle=&SearchSet=all&SearchMarketplace=&SearchIsmodeled=0&SearchShowothers=0&order=popular&direction=asc).

All modules are considered, apart from heavily specific/utility ones.

This file provides statistics feed into the `stats.py` script, which calculates correlations
to the most popular modules, based on the number of panels ordered.


## Daisy panel

![Daisy Panel](daisy.png)

The standard daisy panel provides:

- 1 [`audio-in-daisy`](../audio-in-daisy/)
- 1 [`audio-out-daisy`](../audio-out-daisy/)
- 1 [`button`](../button/)
- 6 [`cv-in`](../cv-in/)
- 2 [`gate-in`](../gate-in/)
- 2 [`led-bi`](../led-bi/)
- 2 [`led-mono`](../led-mono/)
- 6 [`pot`](../pot/)
- 1 [`switch`](../switch/)
- 3 [`trim`](../trim/)
- 1 [`multiplexer`](../multiplexer/)
- 1 [`power-bus`](../power-bus/)
- 1 [`regulator-daisy`](../regulator-daisy/)

Producing the latest version of the panel can be done by running the `build.py` script.
It will create an `artifacts` folder in which the gerber files along with the BOMs are
produced.

However it is recommended to use the
[releases artifacts](https://github.com/ohmtech-rdi/eurorack-blocks/releases).

### Producing the PCB

Most PCB manufacturer supports visualisation of the produced PCB. Load up the
`panel-daisy-gerber.zip` file into their interface, and make sure the render looks
very similar to the screenshot above.

### Ordering the BOM

This panel uses two distributors.

- Digikey: Load the `panel-daisy-bom-digikey.csv` into their
   [BOM manager](https://www.digikey.de/en/help/features-updates/bom-manager-tour).
   After logged-in, this is available [here](https://www.digikey.de/bom):
   - Click the "Upload BOM",
   - Choose the `panel-daisy-bom-digikey.csv` located in the `kits/artifacts` folder
      (remember to first `build.py` the kits),
   - The BOM should display and be correctly mapped, and starting on row 2,
   - Click "Add to BOM",
   - Check **the entire list** for unavailable components at that time, and report any components
      missing. **Only if every components are available, go the next step**, or use the
      [`replace-bom-parts.py`](../util/) script.
   - Click "Add to Cart",
   - Select "New Cart" unless you want to continue your current "Existing Cart",
   - Select the number of "assemblies": this is the number of panels you which to produce,
   - Click "Add to Cart",
   - Check **the entire list** again for backordered components. It is indeed possible for the
      BOM manager to have components available but which are already sold on the shop side.
      **Only if every components are available, go the next step**, or use the
      [`replace-bom-parts.py`](../util/) script.
   - Finalize your order
- Thonk: Thonk can't automatically process BOMs. However the `panel-daisy-bom-thonk.csv`
   file provides links to their shop. Make sure to order the correct part in the correct quantity.
