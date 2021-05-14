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
Name : ctor
==============================================================================
*/

Led::Led (float & data, const uint64_t & clock_ms)
:  _data (data)
,  _clock_ms (clock_ms)
{
}



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

void  Led::on (float brightness)
{
   _animation.set (brightness);
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
      _clock_ms, duration, transition_function,
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
      _clock_ms, duration, transition_function,
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
      _clock_ms, duration, transition_function,
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
      _clock_ms, period, transition_function,
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
Name : impl_postprocess
==============================================================================
*/

void  Led::impl_postprocess ()
{
   _data = _animation.get (_clock_ms) * _brightness;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
