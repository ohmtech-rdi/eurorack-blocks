/*****************************************************************************

      Field.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Field.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Field::process ()
{
   bool osc1_gate = ui.osc1_button.held () || ui.osc1_gate;
   float osc1_amp = (ui.osc1_amp + ui.osc1_amp2) * osc1_gate;
   osc1.set_freq_norm (ui.osc1_freq + ui.osc1_freq2);

   float osc2_amp = (ui.osc2_amp + ui.osc2_amp2) * ui.osc2_button.held ();
   osc2.set_freq_norm (ui.osc2_freq + ui.osc2_freq2);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = ui.audio_in1 [i] + osc1_amp * osc1.process ();
      ui.audio_out2 [i] = ui.audio_in2 [i] + osc2_amp * osc2.process ();
   }

   ui.osc1_state = osc1_gate;
   ui.osc1_lvl = osc1_amp;
   ui.osc2_lvl = osc2_amp;

   ui.led1 = ui.pot1;
   ui.led2 = ui.pot2;
   ui.led3 = ui.pot3;
   ui.led4 = ui.pot4;
   ui.led5 = ui.pot5;
   ui.led6 = ui.pot6;
   ui.led7 = ui.pot7;
   ui.led8 = ui.pot8;
}
