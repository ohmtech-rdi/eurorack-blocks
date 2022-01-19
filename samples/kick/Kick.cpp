/*****************************************************************************

      Kick.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Kick.h"

#include <cmath>



/*
==============================================================================
Name : init
==============================================================================
*/

void  Kick::init ()
{
   filter.set_sample_freq (48000.f);
   filter.set_type_high_pass ();
   filter.set_resonance (0.7071f);
   filter.reset ();

   active_ramp.reset (1.f);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  Kick::process ()
{
   if (ui.clock_gate.triggered ())
   {
      const float space_norm
         = ui.space_pot
         + ui.space_cv * ui.space_trim * ui.space_trim * ui.space_trim;

      space.tick (ui.board.clock (), std::clamp (space_norm, 0.f, 1.f));
   }

   if (
      ui.trigger_button.pressed ()
      || ui.trigger_gate.triggered ()
   )
   {
      ui.trigger_led.pulse ();

      body.trigger ();
      transient.trigger ();
      space.trigger ();

      bool cur_active = active_ramp.target () != 0.f;

      if (cur_active != active)
      {
         active_ramp = active ? 1.f : 0.f;
      }
   }

   if (ui.mute_button.pressed ())
   {
      active = !active;

      ui.mute_led = !active;
   }

   {
      const float pitch_norm = std::clamp (
         ui.body_pitch_pot + ui.body_pitch_cv, 0.f, 1.f
      );
      const float speed = 0.5f * std::pow (4.f, pitch_norm);

      body.set_speed (speed);
   }

   {
      const float pitch_norm = std::clamp (
         ui.transient_pitch_pot + ui.transient_pitch_cv, 0.f, 1.f
      );
      const float speed = 0.5f * std::pow (4.f, pitch_norm);

      transient.set_speed (speed);
   }

   const float freq_norm
      = ui.transient_freq_pot
      + ui.transient_freq_cv * ui.transient_freq_trim * ui.transient_freq_trim * ui.transient_freq_trim;
   const float freq_hz = 20.f * std::pow (1000.f, std::clamp (freq_norm, 0.f, 1.f));

   filter.set_freq (freq_hz);
   filter.update ();

   presence.set (ui.presence_pot + ui.presence_cv);

   transient.set_transient_morph (ui.transient_morph_pot + ui.transient_morph_cv);

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float val = body.process (data.body) * active_ramp.process ();
      val += filter.process (transient.process ());
      val = space.process (val);
      val = presence.process (val);

      ui.audio_out [i] = val;
   }
}
