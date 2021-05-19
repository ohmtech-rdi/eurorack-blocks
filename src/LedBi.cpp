/*****************************************************************************

      LedBi.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/LedBi.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Color::none
==============================================================================
*/

LedBi::Color LedBi::Color::none ()
{
   return { 0.f, 0.f };
}



/*
==============================================================================
Name : Color::red
==============================================================================
*/

LedBi::Color LedBi::Color::red ()
{
   return { 1.f, 0.f };
}



/*
==============================================================================
Name : Color::green
==============================================================================
*/

LedBi::Color LedBi::Color::green ()
{
   return { 0.f, 1.f };
}



/*
==============================================================================
Name : Color::yellow
==============================================================================
*/

LedBi::Color LedBi::Color::yellow ()
{
   return { 1.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

LedBi::LedBi (float & data_r, float & data_g, const uint64_t & clock_ms)
:  r (data_r, clock_ms)
,  g (data_g, clock_ms)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  LedBi::set_brightness (float perceptual_brightness)
{
   r.set_brightness (perceptual_brightness);
   g.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  LedBi::on (Color color)
{
   r.on (color.r);
   g.on (color.g);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  LedBi::off ()
{
   r.off ();
   g.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  LedBi::pulse (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse (color.r, duration, transition_function);
   g.pulse (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  LedBi::pulse_twice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse_twice (color.r, duration, transition_function);
   g.pulse_twice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  LedBi::pulse_thrice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   r.pulse_thrice (color.r, duration, transition_function);
   g.pulse_thrice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  LedBi::blink (Color color, std::chrono::milliseconds period, TransitionFunction transition_function)
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

void  LedBi::impl_postprocess ()
{
   r.impl_postprocess ();
   g.impl_postprocess ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
