/*****************************************************************************

      Reverb.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Reverb.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Reverb::process ()
{
   float wet
      = float (ui.wet_pot)
      + float (ui.wet_cv) * float (ui.wet_trim);
   if (wet > 1.f) wet = 1.f;
   if (wet < 0.f) wet = 0.f;
   dsp.set_wet (wet);

   float feedback
      = float (ui.feedback_pot)
      + float (ui.feedback_cv) * float (ui.feedback_trim);
   if (feedback > 1.f) feedback = 1.f;
   if (feedback < 0.f) feedback = 0.f;
   dsp.set_feedback (feedback);

   float low_pass_freq_norm
      = float (ui.low_pass_freq_pot)
      + float (ui.low_pass_freq_cv) * float (ui.low_pass_freq_trim);
   if (low_pass_freq_norm > 1.f) low_pass_freq_norm = 1.f;
   if (low_pass_freq_norm < 0.f) low_pass_freq_norm = 0.f;

   float low_pass_freq_hz = 20.f * std::pow (1000.f, low_pass_freq_norm);
   dsp.set_low_pass_freq (low_pass_freq_hz);

   float high_pass_freq_norm
      = float (ui.high_pass_freq_pot)
      + float (ui.high_pass_freq_cv) * float (ui.high_pass_freq_trim);
   if (high_pass_freq_norm > 1.f) high_pass_freq_norm = 1.f;
   if (high_pass_freq_norm < 0.f) high_pass_freq_norm = 0.f;

   float high_pass_freq_hz = 20.f * std::pow (1000.f, high_pass_freq_norm);
   dsp.set_high_pass_freq (high_pass_freq_hz);

   const float * const in [] = {
      &ui.audio_in_left [0],
      &ui.audio_in_right [0],
   };

   float * const out [] = {
      &ui.audio_out_left [0],
      &ui.audio_out_right [0],
   };

   dsp.process (out, in, ui.audio_out_left.size ());
}
