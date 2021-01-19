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

   Module module;
   AudioOutDaisy audio_out (module);

   // Pins are the same as the GATE IN 1/2 on Daisy Patch
   GateIn gate_in_1 (module, Pin20);
   GateIn gate_in_2 (module, Pin19, GateIn::Mode::Gate);

   module.run ([&](){
      auto out_val = (gate_in_1 || gate_in_2) ? 1.f : 0.f;

      audio_out [0].fill (out_val);
      audio_out [1].fill (out_val);
   });
}
