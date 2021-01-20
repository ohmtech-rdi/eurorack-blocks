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

   AudioInDaisy audio_in_left (module, AudioInDaisy::Pin::Left);
   AudioInDaisy audio_in_right (module, AudioInDaisy::Pin::Right);

   AudioOutDaisy audio_out_left (module, AudioOutDaisy::Pin::Left);
   AudioOutDaisy audio_out_right (module, AudioOutDaisy::Pin::Right);

   module.run ([&](){
      audio_out_left = audio_in_left;
      audio_out_right = audio_in_right;
   });
}
