/*****************************************************************************

      main.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"



/*\\\ FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : main
==============================================================================
*/

int main ()
{
   using namespace erb;

   BoardDaisySeed board;

   AudioOut audio_out0 { board.audioout (0) };
   AudioOut audio_out1 { board.audioout (1) };

   // Pins are the same as the GATE IN 1/2 on Daisy Patch
   GateIn gate_in_1 { board.gpi (20) };
   GateIn gate_in_2 { board.gpi (19) };

   board.run ([&](){
      auto out_val = (gate_in_1.triggered () || gate_in_2) ? 1.f : 0.f;

      audio_out0.fill (out_val);
      audio_out1.fill (out_val);
   });
}
