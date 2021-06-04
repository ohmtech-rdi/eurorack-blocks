/*****************************************************************************

      LedBi.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ColorBi::none
==============================================================================
*/

ColorBi  ColorBi::none ()
{
   return { 0.f, 0.f };
}



/*
==============================================================================
Name : ColorBi::red
==============================================================================
*/

ColorBi  ColorBi::red ()
{
   return { 1.f, 0.f };
}



/*
==============================================================================
Name : ColorBi::green
==============================================================================
*/

ColorBi  ColorBi::green ()
{
   return { 0.f, 1.f };
}



/*
==============================================================================
Name : ColorBi::yellow
==============================================================================
*/

ColorBi  ColorBi::yellow ()
{
   return { 1.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
LedBi <Pin, Current>::LedBi (typename Led <Pin, Current>::BindingType data_r, typename Led <Pin, Current>::BindingType data_g, const uint64_t & clock_ms)
:  r (data_r, clock_ms)
,  g (data_g, clock_ms)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::set_brightness (float perceptual_brightness)
{
   r.set_brightness (perceptual_brightness);
   g.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : on
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::on (ColorBi color)
{
   r.on (color.r);
   g.on (color.g);
}



/*
==============================================================================
Name : off
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::off ()
{
   r.off ();
   g.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::pulse (ColorBi color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse (color.r, duration, transition_function);
   g.pulse (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::pulse_twice (ColorBi color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse_twice (color.r, duration, transition_function);
   g.pulse_twice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::pulse_thrice (ColorBi color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse_thrice (color.r, duration, transition_function);
   g.pulse_thrice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::blink (ColorBi color, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   r.blink (color.r, period, transition_function);
   g.blink (color.g, period, transition_function);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <PinType Pin, CurrentMode Current>
void  LedBi <Pin, Current>::impl_postprocess ()
{
   r.impl_postprocess ();
   g.impl_postprocess ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
