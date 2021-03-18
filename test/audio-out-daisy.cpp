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

   Module module;
   AudioOutDaisy audio_out_left (module, AudioOutDaisyPinLeft);
   AudioOutDaisy audio_out_right (module, AudioOutDaisyPinRight);

   constexpr double pim2 = 2.f * M_PI;
   constexpr double phase_step = pim2 * 440.f / erb::sample_rate;
   const double step_cos = std::cos (phase_step);
   const double step_sin = std::sin (phase_step);

   double pos_cos = 1.f;
   double pos_sin = 0.f;

   module.run ([&](){
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
