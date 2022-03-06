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

   // Scientific pitch notation:
   // For standard A440 pitch equal temperament, the system begins at a
   // frequency of 16.35160 Hz, which is assigned the value C0.
   // C0 is MIDI note 12
   // A 88-key piano goes from A0 to C8

   float freq_voct = ui.cvin;
   float freq_hz = 16.35160f /* C0 */ * std::pow (2.f, freq_voct);
   osc.set_freq (freq_hz);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = active ? osc.process () : 0.f;

      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }
}
