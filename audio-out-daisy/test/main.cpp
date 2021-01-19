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
   AudioOutDaisy audio_out (module);

   constexpr float pim2 = 2.f * float (M_PI);
   constexpr float phase_step = pim2 * 440.f / erb::sample_rate;
   const float step_cos = std::cos (phase_step);
   const float step_sin = std::sin (phase_step);

   float pos_cos = 1.f;
   float pos_sin = 0.f;

   module.run ([&](){
      for (size_t i = 0 ; i < audio_out.size () ; ++i)
      {
         const float old_cos = pos_cos;
         const float old_sin = pos_sin;
         pos_cos = old_cos * step_cos - old_sin * step_sin;
         pos_sin = old_cos * step_sin + old_sin * step_cos;

         audio_out.left [i] = pos_sin;
         audio_out.right [i] = pos_sin;
      }
   });
}
