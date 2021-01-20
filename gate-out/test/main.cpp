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
   AudioInDaisy audio_in0 (module, AudioInDaisyPin0);
   AudioInDaisy audio_in1 (module, AudioInDaisyPin1);
   AudioOutDaisy audio_out0 (module, AudioOutDaisyPin0);
   AudioOutDaisy audio_out1 (module, AudioOutDaisyPin1);

   // Pin is the same as the GATE OUT on Daisy Patch
   GateOut gate_out (module, Pin17);

   uint32_t phase = 0;

   module.run ([&](){
      audio_out0 = audio_in0;
      audio_out1 = audio_in1;

      auto old_sec = phase / 48014;
      phase += audio_in0.size ();
      auto new_sec = phase / 48014;

      if (old_sec != new_sec)
      {
         gate_out.trigger ();
      }
   });
}
