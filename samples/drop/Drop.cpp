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
   if (arm_button.pressed () || arm_gate)
   {
      drop_dsp.toggle_arm ();
      arm_led.pulse ();
   }

   if (sync_button.pressed () || sync_gate)
   {
      drop_dsp.sync ();
      sync_led.pulse ();
   }

   auto mode
      = (mute_hp == Switch::Position::Out1)
      ? DropDsp::Mode::Mute
      : DropDsp::Mode::HighPass;

   drop_dsp.set_mode (mode);
   float freq_norm = float (freq_pot) + float (freq_cv) * float (freq_trim);
   if (freq_norm > 1.f) freq_norm = 1.f;
   if (freq_norm < 0.f) freq_norm = 0.f;

   float freq_hz = 20.f * std::pow (1000.f, freq_norm);
   drop_dsp.set_highpass_freq (freq_hz);

   const float * const in [] = {
      &audio_in_left [0],
      &audio_in_right [0],
   };

   float * const out [] = {
      &audio_out_left [0],
      &audio_out_right [0],
   };

   drop_dsp.process (out, in, audio_out_left.size ());

   auto state = drop_dsp.state ();
   if (_old_state != state)
   {
      _old_state = state;

      if ((state == DropDsp::State::Off) | (state == DropDsp::State::Active))
      {
         state_gate.trigger ();
      }

      switch (state)
      {
      case DropDsp::State::None:   state_led.off (); break;
      case DropDsp::State::Off:    state_led.on (LedBi::Color::Green); break;
      case DropDsp::State::Armed:  state_led.blink (LedBi::Color::Yellow); break;
      case DropDsp::State::Active: state_led.on (LedBi::Color::Red); break;
      }
   }
}
