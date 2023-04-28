#!/usr/bin/env fish

set PREVIOUS_DIR (pwd)
set BUILD_SYSTEM_DIR (cd (dirname (status -f)); and pwd)
cd $PREVIOUS_DIR

set -x -g PATH $PATH $BUILD_SYSTEM_DIR/scripts

# not optimal, but it does the trick
function __erbb_seen_subcommand_from
   set -l cmd (commandline -poc)
   set -e cmd[1]

   if test (count $cmd) -gt 1
      return 1
   end

   for i in $cmd
      if contains -- $i $argv
         return 0
      end
   end

   return 1
end

# COMPLETIONS
complete -f -c erbb -n '__fish_use_subcommand' -a 'setup' -d 'Install all dependencies'
complete -f -c erbb -n '__fish_use_subcommand' -a 'init' -d 'Create a new project in current directory'
complete -f -c erbb -n '__fish_use_subcommand' -a 'configure' -d 'Create the simulator project and hardware make file'

# Build command
complete -f -c erbb -n '__fish_use_subcommand build' -a 'build' -d 'Build the IDE project or make file'
complete -f -c erbb -n '__erbb_seen_subcommand_from build' -a 'daisy' -d 'Daisy firmware'
complete -f -c erbb -n '__erbb_seen_subcommand_from build' -a 'gerber' -d 'Front panel PCB files from Kicad file only'
complete -f -c erbb -n '__erbb_seen_subcommand_from build' -a 'hardware' -d 'Front panel hardware files'
complete -f -c erbb -n '__erbb_seen_subcommand_from build' -a 'simulator' -d 'Simulator plug-in module'

complete -f -c erbb -n '__fish_seen_subcommand_from daisy' -a 'debug' -d 'Debug configuration'
complete -f -c erbb -n '__fish_seen_subcommand_from daisy' -a 'release' -d 'Release configuration (default)'

complete -f -c erbb -n '__fish_seen_subcommand_from simulator' -a 'debug' -d 'Debug configuration'
complete -f -c erbb -n '__fish_seen_subcommand_from simulator' -a 'release' -d 'Release configuration (default)'

# Install command
complete -f -c erbb -n '__fish_use_subcommand' -a 'install' -d 'Install the firmware on the Daisy hardware'
complete -f -c erbb -n '__erbb_seen_subcommand_from install' -a 'openocd' -d 'Install using OpenOCD if installed (default)'
complete -f -c erbb -n '__erbb_seen_subcommand_from install' -a 'dfu' -d 'Install using USB (fallback)'

complete -f -c erbb -n '__fish_seen_subcommand_from install' -a 'debug' -d 'Debug configuration'
complete -f -c erbb -n '__fish_seen_subcommand_from install' -a 'release' -d 'Release configuration (default)'

# Bootloader command
complete -f -c erbb -n '__fish_use_subcommand' -a 'bootloader' -d 'Install the QSPI bootloader on the Daisy hardware'

# Max command
complete -f -c erbb -n '__fish_use_subcommand' -a 'max' -d "Cycling'74 Max commands"
complete -f -c erbb -n '__fish_seen_subcommand_from max' -a 'init' -d 'Name of Max project, random name if not specified'

# Faust command
complete -f -c erbb -n '__fish_use_subcommand' -a 'faust' -d 'Faust commands' 
complete -f -c erbb -n '__fish_seen_subcommand_from faust' -a 'init' -d 'Name of Faust project, random name if not specified'


