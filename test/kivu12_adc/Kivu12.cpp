/*****************************************************************************

      Kivu12.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Kivu12.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Kivu12::process ()
{
#if 0
   // Basic: check if audio output works
   osc1.set_freq (440.f);
   osc2.set_freq (880.f);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = osc1.process ();
      ui.audio_out2 [i] = osc2.process ();
   }

#elif 1
   // Change pot pin assignment in erbui file to check every input
   osc1.set_freq_norm (ui.freq_pot);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      auto val = osc1.process ();
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 0
   // Check for one input influencing the other
   osc1.set_freq_norm (ui.freq_pot);
   osc2.set_freq_norm (ui.freq2_pot);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      auto val = (osc1.process () + osc2.process ()) * 0.5f;
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#endif
}
