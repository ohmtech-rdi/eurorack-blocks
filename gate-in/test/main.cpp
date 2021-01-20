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
   AudioOutDaisy audio_out0 (module, AudioOutDaisy::Pin::Channel0);
   AudioOutDaisy audio_out1 (module, AudioOutDaisy::Pin::Channel1);

   // Pins are the same as the GATE IN 1/2 on Daisy Patch
   GateIn gate_in_1 (module, Pin20);
   GateIn gate_in_2 (module, Pin19, GateIn::Mode::Gate);

   module.run ([&](){
      auto out_val = (gate_in_1 || gate_in_2) ? 1.f : 0.f;

      audio_out0.fill (out_val);
      audio_out1.fill (out_val);
   });
}
