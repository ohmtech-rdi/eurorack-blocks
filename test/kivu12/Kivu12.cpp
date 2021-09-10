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
   osc1.set_freq (440.f);
   osc2.set_freq (880.f);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = osc1.process ();
      ui.audio_out2 [i] = osc2.process ();
   }

#elif 0
   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = ui.audio_in1 [i];
      ui.audio_out2 [i] = ui.audio_in2 [i];
   }

#elif 0
   osc1.set_freq_norm (ui.freq_cv);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = osc1.process ();
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 0
   osc1.set_freq_norm (ui.freq_pot);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = osc1.process ();
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 0
   osc1.set_freq_norm (ui.freq_pot);
   osc2.set_freq_norm (ui.freq2_pot);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = osc1.process ();
      ui.audio_out2 [i] = osc2.process ();
   }

#elif 0
   osc1.set_freq (440.f);

   auto phase = ui.board.clock () % 2000ull;
   //ui.led = (phase < 1000) ? 1.f : 0.f;
   //ui.led = 0.5f;
   ui.led = float (phase) / 1999.f;

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = osc1.process ();
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 0
   osc1.set_freq (440.f);

   ui.led = ui.button.held () ? 1.f : 0.f;

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = osc1.process ();
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 1
   osc1.set_freq (440.f);

   auto phase = ui.board.clock () % 2000ull;
   ui.gate_out = (phase < 1000) ? 1.f : 0.f;

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = osc1.process ();
      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 0
   bool osc1_gate = ui.osc1_button.held () || ui.osc1_gate;
   float osc1_amp = (ui.osc1_amp + ui.osc1_amp2) * osc1_gate;
   osc1.set_freq_norm (ui.osc1_freq + ui.osc1_freq2);

   float osc2_amp = ui.osc2_amp + ui.osc2_amp2;
   osc2.set_freq_norm (ui.osc2_freq + ui.osc2_freq2);

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
#endif
}
