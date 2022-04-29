// Custom.cpp

#include "Custom.h"

#include <cmath>


void  Custom::init ()
{
   filter.set_sample_freq (erb_SAMPLE_RATE);
   filter.set_type_low_pass ();
   filter.set_resonance (1.f);
}


void  Custom::process ()
{
   float freq_hz = 20.f * std::pow (1000.f, ui.freq);
   filter.set_freq (freq_hz);
   filter.update ();

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out [i] = filter.process (ui.audio_in [i]);
   }
}
