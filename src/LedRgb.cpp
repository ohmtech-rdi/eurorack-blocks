/*****************************************************************************

      LedRgb.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/LedRgb.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Color::none
==============================================================================
*/

LedRgb::Color LedRgb::Color::none ()
{
   return { 0.f, 0.f, 0.f };
}



/*
==============================================================================
Name : Color::red
==============================================================================
*/

LedRgb::Color LedRgb::Color::red ()
{
   return { 1.f, 0.f, 0.f };
}



/*
==============================================================================
Name : Color::green
==============================================================================
*/

LedRgb::Color LedRgb::Color::green ()
{
   return { 0.f, 1.f, 0.f };
}



/*
==============================================================================
Name : Color::blue
==============================================================================
*/

LedRgb::Color LedRgb::Color::blue ()
{
   return { 0.f, 0.f, 1.f };
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  LedRgb::set_brightness (float perceptual_brightness)
{
   r.set_brightness (perceptual_brightness);
   g.set_brightness (perceptual_brightness);
   b.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

LedRgb::LedRgb (float & data_r, float & data_g, float & data_b, const uint64_t & clock_ms)
:  r (data_r, clock_ms)
,  g (data_g, clock_ms)
,  b (data_b, clock_ms)
{
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  LedRgb::on (Color color)
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

void  LedRgb::off ()
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

void  LedRgb::pulse (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

void  LedRgb::pulse_twice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

void  LedRgb::pulse_thrice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

void  LedRgb::blink (Color color, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   r.blink (color.r, period, transition_function);
   g.blink (color.g, period, transition_function);
   b.blink (color.b, period, transition_function);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
