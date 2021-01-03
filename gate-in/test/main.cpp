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

   // Pins are the same as the GATE IN 1/2 on Daisy Patch
   GateIn gate_in_1 (module, Pin20);
   GateIn gate_in_2 (module, Pin19, GateIn::Mode::Gate);

   module.run ([&](auto out, auto /* in */, auto size){
      auto out_val = (gate_in_1 || gate_in_2) ? 1.f : 0.f;

      for (size_t i = 0 ; i < size ; ++i)
      {
         out [0][i] = out_val;
         out [1][i] = out_val;
      }
   });
}
