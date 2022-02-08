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

template <PinType Pin>
Led <Pin>::Led (BindingType data, const uint64_t & clock_ms)
:  impl_data (data)
,  _clock_ms (clock_ms)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::set_brightness (float perceptual_brightness)
{
   _brightness = perceptual_brightness;
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <PinType Pin>
Led <Pin> & Led <Pin>::operator = (float brightness)
{
   _animation.set (static_cast <KeyframeTargetType> (brightness));

   return *this;
}



/*
==============================================================================
Name : on
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::on (float brightness)
{
   _animation.set (static_cast <KeyframeTargetType> (brightness));
}



/*
==============================================================================
Name : off
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::off ()
{
   _animation.set (0);
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::pulse (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse (
      _clock_ms, duration, transition_function,
      static_cast <KeyframeTargetType> (brightness), 0.f
   );
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::pulse_twice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_twice (
      _clock_ms, duration, transition_function,
      static_cast <KeyframeTargetType> (brightness), 0.f
   );
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::pulse_thrice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_thrice (
      _clock_ms, duration, transition_function,
      static_cast <KeyframeTargetType> (brightness), 0.f
   );
}



/*
==============================================================================
Name : blink
==============================================================================
*/

template <PinType Pin>
void  Led <Pin>::blink (float brightness, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _animation.blink (
      _clock_ms, period, transition_function,
      static_cast <KeyframeTargetType> (brightness), 0.f
   );
}



/*
==============================================================================
Name : animation
==============================================================================
*/

template <PinType Pin>
Animation <typename Led <Pin>::KeyframeTargetType, Led <Pin>::NBR_MAX_KEYFRAMES> &  Led <Pin>::animation ()
{
   return _animation;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <>
inline void Led <PinType::Gpio>::impl_postprocess ()
{
   float val = float (_animation.get (_clock_ms)) * _brightness;
   impl_data = val > 0.f;
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <>
inline void Led <PinType::Dac>::impl_postprocess ()
{
   impl_data = static_cast <KeyframeTargetType> (_animation.get (_clock_ms) * _brightness);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <>
inline void Led <PinType::Pwm>::impl_postprocess ()
{
   impl_data = static_cast <KeyframeTargetType> (_animation.get (_clock_ms) * _brightness);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
