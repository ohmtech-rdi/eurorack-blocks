/*****************************************************************************

      VcvLed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvLed.h"

#include "erb/vcvrack/VcvModule.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvLed::VcvLed (VcvModule & module, const VcvPin & /* pin */)
:  VcvLightBase (module)
,  _module (module)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  VcvLed::set_brightness (float perceptual_brightness)
{
   _brightness = perceptual_brightness;
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  VcvLed::on (bool state)
{
   _animation.set (state ? 1.f : 0.f);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  VcvLed::off ()
{
   _animation.set (0.f);
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  VcvLed::pulse (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse (
      _module.now_ms (), duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  VcvLed::pulse_twice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_twice (
      _module.now_ms (), duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  VcvLed::pulse_thrice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_thrice (
      _module.now_ms (), duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  VcvLed::blink (float brightness, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _animation.blink (
      _module.now_ms (), period, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : animation
==============================================================================
*/

Animation <float, 8> &  VcvLed::animation ()
{
   return _animation;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  VcvLed::impl_notify_audio_buffer_start ()
{
   float value = _animation.get (_module.now_ms ());

   set_norm_val (_brightness * value);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
