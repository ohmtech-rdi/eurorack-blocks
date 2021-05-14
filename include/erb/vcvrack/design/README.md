# Design

## Overview

This folder contains designs for all eurorack blocks widgets.


## Strategy

VCV Rack contains already many widgets very close to ours but:

- They are not exactly the same variants we are looking for, in term of colors for example,
- There dimensions and associated panel drills are not strictly following the specs,
- Their look is not realistic enough for the product designer or developer to get a close enough
   simulation of what they are trying to build.

The main rationale is that the look is important regarding prototyping, even if it implies a
performance loss. We want to make sure that:

- The look is overall the most realistic possible considering VCV Rack capabilities,
- Any sort of randomness (like nut rotation), is captured in the module display.


## Workflow

Designing Illustrator files to output `svg` files compatible with the partial SVG implementation
of VCV Rack is not straightforward. The following process must be precisely followed:

- Design is made in Illustrator, with `mm` units,
- Illustrator file is saved in `ai` format, 2020 version,
- Nothing fancy is used in Illustrator, just splines with stroke and fills, simple colors,
- File is imported in Inkscape, with default settings,
- `Document properties` must be set to:
   - `Display units` to `mm` instead of `px`,
   - `Custome size` to `mm` instead of `px`,
- File must be `Save as` from Inkscape to `svg`, default options.
