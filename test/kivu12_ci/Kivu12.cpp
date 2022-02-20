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
   bool active = ui.button.held () || ui.gate;
   ui.led = active;

   float freq_norm = ui.cvin;
   float freq_hz = 20.f * std::pow (2.f, 10.f * freq_norm); // 10 octaves
   osc.set_freq (freq_hz);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = active ? osc.process () : 0.f;

      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }
}
