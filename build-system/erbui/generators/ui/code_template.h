/*****************************************************************************

      %module.name%Ui.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"

#if defined (erb_TARGET_DAISY)
   #include "%module.board.firmware.path%"

#elif defined (erb_TARGET_VCV_RACK)
   #include "%module.board.simulator.path%"

#endif



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct %module.name%Ui
{
   %type(module.board)% board;

%entities%
};
