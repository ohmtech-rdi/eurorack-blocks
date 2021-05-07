/*****************************************************************************

      Led.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Led.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  Led::set_brightness (float perceptual_brightness)
{
   _brightness = perceptual_brightness;
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  Led::on (bool state)
{
   _animation.set (state ? 1.f : 0.f);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  Led::off ()
{
   _animation.set (0.f);
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  Led::pulse (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse (
      *_now_ms_ptr, duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  Led::pulse_twice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_twice (
      *_now_ms_ptr, duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  Led::pulse_thrice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_thrice (
      *_now_ms_ptr, duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  Led::blink (float brightness, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _animation.blink (
      *_now_ms_ptr, period, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : animation
==============================================================================
*/

Animation <float, 8> &  Led::animation ()
{
   return _animation;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  Led::impl_bind (float & val, uint64_t & now_ms)
{
   _val_ptr = &val;
   _now_ms_ptr = &now_ms;
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  Led::impl_notify_audio_buffer_start ()
{
   *_val_ptr = _animation.get (*_now_ms_ptr) * _brightness;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
