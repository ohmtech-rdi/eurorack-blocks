#!/usr/bin/env fish

function __fish__eurorack-blocks_build-system_scripts_erbb_complete
   set -x ERBB_COMPLETION_FISH 1
   set -x COMP_LINE (commandline -p)
   erbb_complete.py
end

complete -c erbb -f -a '(__fish__eurorack-blocks_build-system_scripts_erbb_complete)'
