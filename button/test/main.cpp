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
   Button button_1 (module, Pin20);
   Button button_2 (module, Pin19);

   module.run ([&](){
      bool out_b = button_1.pressed () || button_2.released ();
      auto out_val = out_b ? 1.f : 0.f;

      audio_out.left.fill (out_val);
      audio_out.right.fill (out_val);
   });
}
