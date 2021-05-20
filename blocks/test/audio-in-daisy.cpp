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

   AudioIn audio_in_left (module, AudioInPinLeft);
   AudioIn audio_in_right (module, AudioInPinRight);

   AudioOut audio_out_left (module, AudioOutPinLeft);
   AudioOut audio_out_right (module, AudioOutPinRight);

   module.run ([&](){
      audio_out_left = audio_in_left;
      audio_out_right = audio_in_right;
   });
}
