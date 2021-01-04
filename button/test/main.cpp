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
   Button button_1 (module, Pin20);
   Button button_2 (module, Pin19);

   module.run ([&](auto out, auto /* in */, auto size){
      bool out_b = button_1.pressed () || button_2.released ();
      auto out_val = out_b ? 1.f : 0.f;

      for (size_t i = 0 ; i < size ; ++i)
      {
         out [0][i] = out_val;
         out [1][i] = out_val;
      }
   });
}
