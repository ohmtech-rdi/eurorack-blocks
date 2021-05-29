/*****************************************************************************

      main.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"

#include <cmath>



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

   constexpr double pim2 = 2.0 * M_PI;
   constexpr double phase_step = pim2 * 440.0 / erb_SAMPLE_RATE;
   const double step_cos = std::cos (phase_step);
   const double step_sin = std::sin (phase_step);

   double pos_cos = 1.0;
   double pos_sin = 0.0;

   board.run ([&](){
      for (size_t i = 0 ; i < audio_out_left.size () ; ++i)
      {
         const double old_cos = pos_cos;
         const double old_sin = pos_sin;
         pos_cos = old_cos * step_cos - old_sin * step_sin;
         pos_sin = old_cos * step_sin + old_sin * step_cos;

         audio_out_left [i] = float (pos_sin);
         audio_out_right [i] = float (pos_sin);
      }
   });
}
