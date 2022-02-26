#!/usr/bin/env bash

BUILD_SYSTEM_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-${(%):-%x}}" )" &> /dev/null && pwd )
export PATH=$PATH:$BUILD_SYSTEM_DIR/scripts
export PATH=$PATH:/c/msys64/mingw64/bin

_erbb_complete()
{
   eval $(COMP_LINE=$COMP_LINE COMP_POINT=$COMP_POINT COMP_WORDS="${COMP_WORDS[*]}" COMP_CWORD=$COMP_CWORD erbb_complete.py)
}

if [ $ZSH_VERSION ]
then
   if typeset -f compdef > /dev/null && typeset -f complete > /dev/null; then
      complete -F _erbb_complete erbb
   fi
fi

if [ $BASH_VERSION ]
then
   complete -F _erbb_complete erbb
fi
