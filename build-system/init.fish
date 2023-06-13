#!/usr/bin/env fish

set PREVIOUS_DIR (pwd)
set BUILD_SYSTEM_DIR (cd (dirname (status -f)); and pwd)
cd $PREVIOUS_DIR

set -x -g PATH $PATH $BUILD_SYSTEM_DIR/scripts

function __fish__eurorack-blocks_build-system_scripts_erbb_complete
   set -x ERBB_COMPLETION_FISH 1
   set -x COMP_LINE (commandline -p)
   erbb_complete.py
end

complete -c erbb -f -a '(__fish__eurorack-blocks_build-system_scripts_erbb_complete)'
