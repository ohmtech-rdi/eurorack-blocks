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
