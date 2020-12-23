/*****************************************************************************

      DropModule.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropModule.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  DropModule::process ()
{
   if (arm_button.pressed () || arm_gate)
   {
      drop_dsp.toggle_arm ();
      arm_led.pulse ();
   }

   if (sync_gate)
   {
      drop_dsp.sync ();
      sync_led.pulse ();
   }

   auto mode
      = (mute_hp == Switch::Position::Out1)
      ? DropDsp::Mode::Mute
      : DropDsp::Mode::HighPass;

   drop_dsp.set_mode (mode);
   float freq_hz = 20.f * std::pow (1000.f, freq);
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

      switch (state)
      {
      case DropDsp::State::None:   state_led.off (); break;
      case DropDsp::State::Off:    state_led.on (LedBi::Color::Green); break;
      case DropDsp::State::Armed:  state_led.blink (LedBi::Color::Yellow); break;
      case DropDsp::State::Active: state_led.on (LedBi::Color::Red); break;
      }
   }
}
