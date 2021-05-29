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

   BoardDaisySeed board;

   AudioOut audio_out_left { board.audioout (0) };
   AudioOut audio_out_right { board.audioout (1) };

   CvIn <FloatRange::Normalized> ctrl { board.adc (0) };

   board.run ([&](){
      for (size_t i = 0 ; i < audio_out_left.size () ; ++i)
      {
         float out_val = ctrl;

         audio_out_left [i] = out_val;
         audio_out_right [i] = out_val;
      }
   });
}
