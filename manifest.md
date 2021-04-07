# Manifest

## State of Art

Platforms like [Electrosmith Daisy Seed](https://www.electro-smith.com/daisy/daisy)
or [Teensy](https://www.pjrc.com/store/teensy41.html)
are excellent to start embedded audio development by focusing almost only
on the embedded software part of the work.
[Daisy Patch](https://www.electro-smith.com/daisy/patch)
and [Noise Engineering Versio](https://www.noiseengineering.us/blog/lib-daisy)
go beyond by providing eurorack-compatible modules following the
eurorack mechanical and electrical specifications.

However passionate hobbyist will face limitations when trying to design
a full functional prototype for their module, as they will be limited by
the design choices (_eg._ number of Gates, CV, etc.) of those prototyping modules.


## Story/Workflow

Alex has a new great idea for a eurorack module. They first make the DSP for it.

Eurorack-blocks allows from a simple configuration file to have the UI working in software in
a simulated eurorack environment (VCV Rack). Once they are satisfied with the result, the same
configuration file allows the automatic production of the front aluminimum panel, the PCB
gerbers and BOM for the UI elements connected to the front panel.

They select the right back panel which contains the electronics and connection to Daisy Seed
depending on their module width in HP and order it already assembled through a PCBA service.

When they receive everything, they just need to solder the THT components of the UI PCB,
and the routing with wires on front panel.

Then, they plug the front panel to the back panel, and they now have a full module they can
use in their Eurorack case to play and make music with.


## Value Proposition

This project fills the gap between a slick but limited prototyping platform
and a full finished product, by providing atomic blocks such as audio in/out, CV,
gates, knobs and LEDs and supporting-infrastructure like power or
CV-multiplexer blocks, to allow full functional test and field test of the module.

To do so, this project provides automation so that the software developer can focus entirely
on making their module, with close to zero hardware electronics knowledge.

Given the DSP code and a GUI configuration file that indicates placements for the eurorack
UI elements, scripts generate automatically production files for the front aluminimum panel,
the PCB holding all the UI elements screwed to the front aluminimum panel.

The latter PCB then plugs to a back PCB whichs contains all the electronics and can be
produced by a PCBA service. This back PCB can be reused from projects to projects and
is available in a collection of different popular HP width.

Finally the configuration of the UI is done using standard wire, and using a common soldering
iron.

The configuration can also be used to completely test the module in a
[Eurorack virtual environment](https://vcvrack.com)
before the hardware is produced, allowing the software
developer to develop and debug their module in the comfort of their familiar day-to-day IDE.

Finally because the layout of a module can be a difficult task, a series of configuration
templates are available to start hacking with.


## Timeline

### Design Check

- Audience:
   - DIY Hobbyist
      - Has SMD soldering equipment, and comfortable with SMD soldering
      - Can order PCB, BOM and assemble the full product themselves
- Goals:
   - Validate design
      - Making sure each design is working appropriately
      - Provides a testbed for new block design development

### Minimum Viable Product

- Audience:
   - Software Developer
- Goals:
   - Provide automations to develop and debug in a Eurorack virtual environment
   - Provide automations to generate all production files to build the module
   - Allow module to be assembled with very minimal electronics skills
   - Allow full field functional testing
