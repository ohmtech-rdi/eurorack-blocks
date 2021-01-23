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


## Value Proposition

This project fills the gap between a slick but limited prototyping platform
and a full finished product, by providing atomic blocks such as audio in/out, CV,
gates, knobs and LEDs and supporting-infrastructure like power or
CV-multiplexer blocks, to allow full functional test of the module.

To do so, this projects provides the files to manufacture small "breakout"
PCBs: each PCB represents an atomic function such as gate, CV or pot, that
can plug on standard [breadboards](https://en.wikipedia.org/wiki/Breadboard)
and provides eurorack-compatible connectors, such as power bus and 3.5mm mono jack
connectors.

The PCBs have been cost-optimised to provide standard configurations of
module "blocks". Soldering has been made convenient by regrouping sets of blocks
on a single panel when using hot-air soldering or reflow ovens.

Videos are provided to show everything needed to do manual hot-air
soldering for SMD components, and reducing the fear associated with
this soldering technic.

Finally each block was heavily inspired by eurorack open-hardware projects,
with probably [Mutable Instruments](https://github.com/pichenettes/eurorack)
by pichennettes/Emilie Gillet,
and [Electrosmith Daisy Patch](https://github.com/electro-smith/Hardware/tree/master/reference/daisy_patch)
as the most influential ones.


## Design Choices

### SMD

We believe that SMD soldering is easy and efficient when using the right tools. We also think
that those tools are not much more expensive than "traditional" conduction-based
soldering, and should be part of the hobbyist tool set.

We believe that the fear around SMD soldering can be annihilated by providing the right
directions.

### Only 3V3

Most MCUs and codecs used in the eurorack world are 3V3. Therefore our blocks
only supports 3V3. They wouldn't support most of the Arduino's boards
for example, as most of them are 5V.

### CV/Pots/Attenuverter Separation

It is not uncommon to find CV and associated pot and potential
attenuverter in the same hardware design block in well-known eurorack modules.

In our design, this is intentionnally left as separate blocks, for the following reasons:

- We believe that having connectors at the bottom of the module and
  pots on the upper part of the module is a good design choice. Having
  the different connectors and pots on the same op-amp means layout
  is more difficult as long traces need to go through the whole PCB,
- We believe that having the CV-offset controlled by a pot or the
   CV-amplitude controller by another pot in a linear fashion is
   sub-optimal in many cases, for the pots reaction to follow users
   expectations while going through the whole range. Making CV pot modulation
   in software solves this problem.

### CV Fixed Range

CVs can have all kind of ranges of parameter in practice:

- LFO CVs are supposed to be in the ±2.5V range but it is not
  uncommon to find CVs that are done with the same swing as for the
  audio range (±5V),
- ADSR CVs are supposed to be in the 0-8V range.

For this reason, the original design takes all values from ±8V even
with the associated loss of dynamic.

However one could use different resistors when assembling the related
blocks. Those adaptations can be infered by following each block documentation.

### Bus Connector

The power block only draws current from the ±12V lines of the eurorack
power bus connector. In particular the +5V, CV and Gate lines are not used.


## Functional Limitations

Because a prototype module will sit on a breadboard, the system is not
convenient for usability field testing.


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
   - Prevent mistakes that could fry the board
      - Route all ±12V and 5V power supplies and making not available for patching
      - Separate clearly all eurorack signal voltages from the 3V3 patching bay
   - Allow software functional testing
      - Supporting VCV Rack plug-in architecture
   - Allow field functional testing
      - Make a plug-n-play combo that contains all blocks: power bus, regular, Daisy Seed, 10 CVs, 16 pots, 2 multiplexer, etc.
      - The combo only exposes basic routing on the PCB so that absolutely no hardware skills
         are necessary
      - Box can be put at the back of the modular system with no possibility of shortages with the
         rest of the system
      - Connectors are used to connect from the board to the front panel. Each interface design
         (CV/gate, pot/trim, led, button) needs to have a connector with the front panel element
         on one side, and a male pin header on the other side, and the appropriate cable in-between 
      - The combo can be produced by a PCBA service
