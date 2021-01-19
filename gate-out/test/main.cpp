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
   AudioInDaisy audio_in (module);
   AudioOutDaisy audio_out (module);

   // Pin is the same as the GATE OUT on Daisy Patch
   GateOut gate_out (module, Pin17);

   uint32_t phase = 0;

   module.run ([&](){
      audio_out [0] = audio_in [0];
      audio_out [1] = audio_in [1];

      auto old_sec = phase / 48014;
      phase += audio_in.size ();
      auto new_sec = phase / 48014;

      if (old_sec != new_sec)
      {
         gate_out.trigger ();
      }
   });
}
