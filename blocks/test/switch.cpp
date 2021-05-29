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

   AudioOut audio_out0 { board.audioout (0) };
   AudioOut audio_out1 { board.audioout (1) };
   Switch <3> switch_ { board.gpi (19), board.gpi (20) };

   constexpr float pim2 = 2.f * float (M_PI);
   constexpr float phase_step = pim2 * 440.f / erb_SAMPLE_RATE;
   const float step_cos = std::cos (phase_step);
   const float step_sin = std::sin (phase_step);

   float pos_cos = 1.f;
   float pos_sin = 0.f;

   board.run ([&](){
      for (size_t i = 0 ; i < audio_out0.size () ; ++i)
      {
         const float old_cos = pos_cos;
         const float old_sin = pos_sin;
         pos_cos = old_cos * step_cos - old_sin * step_sin;
         pos_sin = old_cos * step_sin + old_sin * step_cos;

         float out_val = 0.f;

         switch (switch_)
         {
         case SwitchPosition::First:
            out_val = pos_sin;
            break;

         case SwitchPosition::Center:
            out_val = 0.f;
            break;

         case SwitchPosition::Last:
            out_val = (pos_sin > 0.f) ? 1.f : -1.f;
            break;
         }

         audio_out0 [i] = out_val;
         audio_out1 [i] = out_val;
      }
   });
}
