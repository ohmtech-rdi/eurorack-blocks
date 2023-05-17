/*****************************************************************************

      Drop.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Drop.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Drop::process ()
{
   if (ui.arm_button.pressed () || ui.arm_gate.triggered ())
   {
      dsp.toggle_arm ();
      ui.arm_led.pulse ();
   }

   if (ui.sync_button.pressed () || ui.sync_gate.triggered ())
   {
      dsp.sync ();
      ui.sync_led.pulse ();
   }

   auto mode
      = ui.mute_hp.position_last ()
      ? DropDsp::Mode::Mute
      : DropDsp::Mode::HighPass;

   dsp.set_mode (mode);
   float freq_norm = ui.freq_pot;
   if (ui.freq_cv.plugged ())
   {
      freq_norm += float (ui.freq_cv) * float (ui.freq_trim);
   }
   if (freq_norm > 1.f) freq_norm = 1.f;
   if (freq_norm < 0.f) freq_norm = 0.f;

   float freq_hz = 20.f * std::pow (1000.f, freq_norm);
   dsp.set_highpass_freq (freq_hz);

   const float * const in [] = {
      &ui.audio_in_left [0],
      &ui.audio_in_right [0],
   };

   float * const out [] = {
      &ui.audio_out_left [0],
      &ui.audio_out_right [0],
   };

   dsp.process (out, in, ui.audio_out_left.size ());

   auto state = dsp.state ();
   if (_old_state != state)
   {
      _old_state = state;

      if ((state == DropDsp::State::Off) | (state == DropDsp::State::Active))
      {
         ui.state_gate.trigger ();
      }

      switch (state)
      {
      case DropDsp::State::None:   ui.state_led.off (); break;
      case DropDsp::State::Off:    ui.state_led.on (erb::ColorBi::green ()); break;
      case DropDsp::State::Armed:  ui.state_led.blink (erb::ColorBi::yellow ()); break;
      case DropDsp::State::Active: ui.state_led.on (erb::ColorBi::red ()); break;
      }
   }
}
