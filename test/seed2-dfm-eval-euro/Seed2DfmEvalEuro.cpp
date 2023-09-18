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
   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i]
         = (ui.audio_in1 [i] + osc1 ())
         * ((ui.osc1_but.held () || ui.osc1_gate) ? 1.f : 0.f);

      ui.audio_out2 [i] = (ui.audio_in2 [i] + osc2 ());
      ui.audio_out3 [i] = (ui.audio_in3 [i] + osc3 ());
      ui.audio_out4 [i] = (ui.audio_in4 [i] + osc4 ());
   }
}
