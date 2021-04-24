/*****************************************************************************

      VcvLedRgb.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvLedRgb.h"

#include "erb/vcvrack/VcvModule.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Color::none
==============================================================================
*/

VcvLedRgb::Color   VcvLedRgb::Color::none ()
{
   return { 0.f, 0.f, 0.f };
}



/*
==============================================================================
Name : Color::red
==============================================================================
*/

VcvLedRgb::Color   VcvLedRgb::Color::red ()
{
   return { 1.f, 0.f, 0.f };
}



/*
==============================================================================
Name : Color::green
==============================================================================
*/

VcvLedRgb::Color   VcvLedRgb::Color::green ()
{
   return { 0.f, 1.f, 0.f };
}



/*
==============================================================================
Name : Color::blue
==============================================================================
*/

VcvLedRgb::Color   VcvLedRgb::Color::blue ()
{
   return { 0.f, 0.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvLedRgb::VcvLedRgb (VcvModule & module, const VcvPin & pin_r, const VcvPin & pin_g, const VcvPin & pin_b)
:  _led_red (module, pin_r)
,  _led_green (module, pin_g)
,  _led_blue (module, pin_b)
{
}



/*
==============================================================================
Name : index
==============================================================================
*/

size_t   VcvLedRgb::index () const
{
   return _led_red.index ();
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  VcvLedRgb::set_brightness (float perceptual_brightness)
{
   _led_red.set_brightness (perceptual_brightness);
   _led_green.set_brightness (perceptual_brightness);
   _led_blue.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  VcvLedRgb::on (Color color)
{
   _led_red.on (color.r);
   _led_green.on (color.g);
   _led_blue.on (color.b);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  VcvLedRgb::off ()
{
   _led_red.off ();
   _led_green.off ();
   _led_blue.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  VcvLedRgb::pulse (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse (color.r, duration, transition_function);
   _led_green.pulse (color.g, duration, transition_function);
   _led_blue.pulse (color.b, duration, transition_function);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  VcvLedRgb::pulse_twice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse_twice (color.r, duration, transition_function);
   _led_green.pulse_twice (color.g, duration, transition_function);
   _led_blue.pulse_twice (color.b, duration, transition_function);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  VcvLedRgb::pulse_thrice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse_thrice (color.r, duration, transition_function);
   _led_green.pulse_thrice (color.g, duration, transition_function);
   _led_blue.pulse_thrice (color.b, duration, transition_function);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  VcvLedRgb::blink (Color color, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _led_red.blink (color.r, period, transition_function);
   _led_green.blink (color.g, period, transition_function);
   _led_blue.blink (color.b, period, transition_function);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
