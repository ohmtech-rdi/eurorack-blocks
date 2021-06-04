/*****************************************************************************

      Led.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
Led <Pin, Current>::Led (BindingType data, const uint64_t & clock_ms)
:  impl_data (data)
,  _clock_ms (clock_ms)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::set_brightness (float perceptual_brightness)
{
   _brightness = perceptual_brightness;
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
Led <Pin, Current> & Led <Pin, Current>::operator = (float brightness)
{
   _animation.set (brightness);

   return *this;
}



/*
==============================================================================
Name : on
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::on (float brightness)
{
   _animation.set (brightness);
}



/*
==============================================================================
Name : off
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::off ()
{
   _animation.set (0.f);
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::pulse (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::pulse_twice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::pulse_thrice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::blink (float brightness, std::chrono::milliseconds period, TransitionFunction transition_function)
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

template <PinType Pin, CurrentMode Current>
Animation <typename Led <Pin, Current>::KeyframeTargetType, Led <Pin, Current>::NBR_MAX_KEYFRAMES> &  Led <Pin, Current>::animation ()
{
   return _animation;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  Led <Pin, Current>::impl_postprocess ()
{
   auto relative_brightness = _animation.get (_clock_ms);

   if constexpr (Current == CurrentMode::Sinking)
   {
      relative_brightness = 1.f - relative_brightness;
   }

   impl_data = _animation.get (_clock_ms) * _brightness;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
