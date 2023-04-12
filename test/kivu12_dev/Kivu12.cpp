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
      ui.AO1 [i] = osc1.process ();
      ui.AO2 [i] = osc2.process ();
   }

#elif 1
   const float phase_step = 0.25f * erb_BUFFER_SIZE / erb_SAMPLE_RATE;
   phase += phase_step;
   if (phase > 1.f)
   {
      phase = 0.f;
   }

   ui.L1 = phase;
   ui.L2 = phase;
   ui.L3 = phase;
   ui.L4 = phase;
   ui.L5 = phase;
   ui.L6 = phase;
   ui.L7 = phase;
   ui.L8 = phase;
   ui.L9 = phase;
   ui.L10 = phase;
   ui.L11 = phase;
   ui.L12 = phase;
   ui.L13 = phase;
   ui.L14 = phase;
   ui.L15 = phase;
   ui.L16 = phase;

#elif 0
   ui.L1 = ui.P1;
   ui.L2 = ui.P2;
   ui.L3 = ui.P3;
   ui.L4 = ui.P4;
   ui.L5 = ui.P5;
   ui.L6 = ui.P6;
   ui.L7 = ui.P7;
   ui.L8 = ui.P8;
   ui.L9 = ui.P9;
   ui.L10 = ui.P10;
   ui.L11 = ui.P11;
   ui.L12 = ui.P12;
   ui.L13 = 0.f;
   ui.L14 = 1.f;
   ui.L15 = 0.f;
   ui.L16 = 1.f;

#elif 0
   const float phase_step = 1.f * erb_BUFFER_SIZE / erb_SAMPLE_RATE;
   phase += phase_step;
   if (phase > 1.f)
   {
      phase = 0.f;
   }

   ui.GO1 = phase > 0.5f;
   ui.GO2 = phase > 0.5f;

   ui.L1 = ui.B1.held ();
   ui.L2 = ui.B2;
   ui.L3 = ui.B3.held ();
   ui.L4 = ui.B4;
   ui.L5 = ui.B5.held ();
   ui.L6 = ui.B6;
   ui.L7 = ui.B7.held ();
   ui.L8 = ui.B8;
   ui.L9 = ui.B9.held ();
   ui.L10 = ui.B10;
   ui.L11 = ui.B11.held ();
   ui.L12 = ui.B12;
   ui.L13 = ui.B13.held ();
   ui.L14 = ui.B14;
   ui.L15 = ui.B15.held ();
   ui.L16 = ui.B16;

#elif 1
   const float phase_step = 0.25f * erb_BUFFER_SIZE / erb_SAMPLE_RATE;
   phase += phase_step;
   if (phase > 1.f)
   {
      phase = 0.f;
   }

   ui.CO1 = phase;
   ui.CO2 = phase;

   ui.L1 = std::abs (ui.CI1);
   ui.L2 = std::abs (ui.CI2);
   ui.L3 = std::abs (ui.CI3);
   ui.L4 = std::abs (ui.CI4);
   ui.L5 = std::abs (ui.CI5);
   ui.L6 = std::abs (ui.CI6);
   ui.L7 = std::abs (ui.CI7);
   ui.L8 = std::abs (ui.CI8);

#endif
}
