/*****************************************************************************

      Micropatch.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Micropatch.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Micropatch::process ()
{
   const bool osc1_gate = ui.osc1_button.held () || ui.osc1_gate;
   const float osc1_amp = (ui.osc1_amp + ui.osc1_amp2) * osc1_gate;
   const float osc1_freq_norm = ui.osc1_freq + ui.osc1_freq2;
   const float osc1_freq = 20.f * std::pow (500.f, std::abs (osc1_freq_norm));
   osc1.set_freq (osc1_freq);

   float osc2_amp = ui.osc2_amp + ui.osc2_amp2;
   const float osc2_freq_norm = ui.osc2_freq + ui.osc2_freq2;
   const float osc2_freq = 20.f * std::pow (500.f, std::abs (osc2_freq_norm));
   osc2.set_freq (osc2_freq);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = ui.audio_in1 [i] + osc1_amp * osc1.process ();

      if (ui.osc2_type.position_first ())
      {
         ui.audio_out2 [i] = ui.audio_in2 [i] + osc2_amp * osc2.process ();
      }
      else if (ui.osc2_type.position_last ())
      {
         ui.audio_out2 [i] = ui.audio_in2 [i] + osc2_amp * (osc2.process () > 0.f ? 1.f : -1.f);
      }
      else
      {
         ui.audio_out2 [i] = ui.audio_in2 [i];
      }
   }

   ui.osc1_state = osc1_gate;
   ui.osc2_state = ui.osc2_gate;
   ui.osc1_lvl = osc1_amp;

   ui.led = ui.pot1;
}
