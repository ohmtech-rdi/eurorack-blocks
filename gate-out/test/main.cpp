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

   // Pin is the same as the GATE OUT on Daisy Patch
   GateOut gate_out (module, Pin17);

   uint32_t phase = 0;

   module.run ([&](auto out, auto in, auto size){
      for (size_t i = 0 ; i < size ; ++i)
      {
         out [0][i] = in [0][i];
         out [1][i] = in [1][i];
      }

      auto old_sec = phase / 48014;
      phase += size;
      auto new_sec = phase / 48014;

      if (old_sec != new_sec)
      {
         gate_out.trigger ();
      }
   });
}
