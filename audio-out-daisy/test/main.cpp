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
   erb::Module module;

   constexpr float pim2 = 2.f * float (M_PI);
   constexpr float phase_step = pim2 * 440.f / erb::sample_rate;
   const float step_cos = std::cos (phase_step);
   const float step_sin = std::sin (phase_step);

   float pos_cos = 1.f;
   float pos_sin = 0.f;

   module.run ([&](auto out, auto /* in */, auto size){
      for (size_t i = 0 ; i < size ; ++i)
      {
         const float old_cos = pos_cos;
         const float old_sin = pos_sin;
         pos_cos = old_cos * step_cos - old_sin * step_sin;
         pos_sin = old_cos * step_sin + old_sin * step_cos;

         out [0][i] = pos_sin;
         out [1][i] = pos_sin;
      }
   });
}
