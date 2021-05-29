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

   AudioOut audio_out_left { board.audioout (0) };
   AudioOut audio_out_right { board.audioout (1) };

   // Pins are the same as the GATE IN 1/2 on Daisy Patch
   Button button_1 { board.gpi (20) };
   Button button_2 { board.gpi (19) };

   board.run ([&](){
      bool out_b = button_1.pressed () || button_2.released ();
      auto out_val = out_b ? 1.f : 0.f;

      audio_out_left.fill (out_val);
      audio_out_right.fill (out_val);
   });
}
