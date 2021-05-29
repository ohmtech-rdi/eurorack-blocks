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

   AudioIn audio_in_left { board.audioin (0) };
   AudioIn audio_in_right { board.audioin (1) };

   AudioOut audio_out_left { board.audioout (0) };
   AudioOut audio_out_right { board.audioout (1) };

   board.run ([&](){
      audio_out_left = audio_in_left;
      audio_out_right = audio_in_right;
   });
}
