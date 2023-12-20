/*****************************************************************************

      Seed2DfmEvalEuro.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Seed2DfmEvalEuro.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Seed2DfmEvalEuro::process ()
{
   const auto to_freq = [](float norm){
      return 20.f * std::pow (500.f, std::abs (norm));
   };

   const auto to_shape = [](erb::SwitchPosition pos, float x){
      switch (pos)
      {
      case erb::SwitchPosition::First:
      default:
         return x;
      case erb::SwitchPosition::Center:
         return x * x * x;
      case erb::SwitchPosition::Last:
         return x > 0 ? 1.f : 0.f;
      }
   };

   osc1.set (to_freq (std::clamp (ui.osc1_pot + ui.osc1_cv, 0.f, 1.f)));
   osc2.set (to_freq (std::clamp (ui.osc2_pot + ui.osc2_cv, 0.f, 1.f)));
   osc3.set (to_freq (std::clamp (ui.osc3_pot + ui.osc3_cv, 0.f, 1.f)));
   osc4.set (to_freq (std::clamp (float (ui.osc4_pot), 0.f, 1.f)));

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.osc1_out [i]
         = (ui.osc1_in [i] + osc1 ())
         * ((ui.osc1_but.held () || ui.osc1_gate) ? 1.f : 0.f);

      ui.osc2_out [i] = ui.osc2_in [i] + osc2 ();
      ui.osc3_out [i] = ui.osc3_in [i] + osc3 ();
      ui.osc4_out [i] = to_shape (ui.osc4_shape, ui.osc4_in [i] + osc4 ());
   }

   ui.osc1_cv_out = ui.osc1_cv;
   ui.osc2_cv_out = ui.osc2_cv;

   if (ui.enc.button.held ())
   {
      pic = 4;
   }
   else
   {
      pic = (pic + int (ui.enc.encoder) + 4) % 4;
   }
}



/*
==============================================================================
Name : idle
==============================================================================
*/

void  Seed2DfmEvalEuro::idle ()
{
   switch (pic)
   {
   case 0: ui.screen = Seed2DfmEvalEuroData::pic0; break;
   case 1: ui.screen = Seed2DfmEvalEuroData::pic1; break;
   case 2: ui.screen = Seed2DfmEvalEuroData::pic2; break;
   case 3: ui.screen = Seed2DfmEvalEuroData::pic3; break;
   case 4: ui.screen.fill (true); break;
   }
}
