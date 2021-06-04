/*****************************************************************************

      LedRgb.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ColorRgb::none
==============================================================================
*/

ColorRgb ColorRgb::none ()
{
   return { 0.f, 0.f, 0.f };
}



/*
==============================================================================
Name : ColorRgb::red
==============================================================================
*/

ColorRgb ColorRgb::red ()
{
   return { 1.f, 0.f, 0.f };
}



/*
==============================================================================
Name : ColorRgb::green
==============================================================================
*/

ColorRgb ColorRgb::green ()
{
   return { 0.f, 1.f, 0.f };
}



/*
==============================================================================
Name : ColorRgb::blue
==============================================================================
*/

ColorRgb ColorRgb::blue ()
{
   return { 0.f, 0.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
LedRgb <Pin, Current>::LedRgb (typename Led <Pin, Current>::BindingType data_r, typename Led <Pin, Current>::BindingType data_g, typename Led <Pin, Current>::BindingType data_b, const uint64_t & clock_ms)
:  r (data_r, clock_ms)
,  g (data_g, clock_ms)
,  b (data_b, clock_ms)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::set_brightness (float perceptual_brightness)
{
   r.set_brightness (perceptual_brightness);
   g.set_brightness (perceptual_brightness);
   b.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : on
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::on (ColorRgb color)
{
   r.on (color.r);
   g.on (color.g);
   b.on (color.b);
}



/*
==============================================================================
Name : off
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::off ()
{
   r.off ();
   g.off ();
   b.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::pulse (ColorRgb color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse (color.r, duration, transition_function);
   g.pulse (color.g, duration, transition_function);
   b.pulse (color.b, duration, transition_function);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::pulse_twice (ColorRgb color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse_twice (color.r, duration, transition_function);
   g.pulse_twice (color.g, duration, transition_function);
   b.pulse_twice (color.b, duration, transition_function);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::pulse_thrice (ColorRgb color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse_thrice (color.r, duration, transition_function);
   g.pulse_thrice (color.g, duration, transition_function);
   b.pulse_thrice (color.b, duration, transition_function);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::blink (ColorRgb color, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   r.blink (color.r, period, transition_function);
   g.blink (color.g, period, transition_function);
   b.blink (color.b, period, transition_function);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedRgb <Pin, Current>::impl_postprocess ()
{
   r.impl_postprocess ();
   g.impl_postprocess ();
   b.impl_postprocess ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
