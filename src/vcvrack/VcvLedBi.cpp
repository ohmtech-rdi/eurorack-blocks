/*****************************************************************************

      VcvLedBi.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvLedBi.h"

#include "erb/vcvrack/VcvModule.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Color::none
==============================================================================
*/

VcvLedBi::Color   VcvLedBi::Color::none ()
{
   return { 0.f, 0.f };
}



/*
==============================================================================
Name : Color::red
==============================================================================
*/

VcvLedBi::Color   VcvLedBi::Color::red ()
{
   return { 1.f, 0.f };
}



/*
==============================================================================
Name : Color::green
==============================================================================
*/

VcvLedBi::Color   VcvLedBi::Color::green ()
{
   return { 0.f, 1.f };
}



/*
==============================================================================
Name : Color::yellow
==============================================================================
*/

VcvLedBi::Color   VcvLedBi::Color::yellow ()
{
   return { 1.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvLedBi::VcvLedBi (VcvModule & module, const VcvPin & pin_r, const VcvPin & pin_g)
:  _led_green (module, pin_g)
,  _led_red (module, pin_r)
{
}



/*
==============================================================================
Name : index
==============================================================================
*/

size_t   VcvLedBi::index () const
{
   return _led_green.index ();
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  VcvLedBi::set_brightness (float perceptual_brightness)
{
   _led_red.set_brightness (perceptual_brightness);
   _led_green.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  VcvLedBi::on (Color color)
{
   _led_red.on (color.r);
   _led_green.on (color.g);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  VcvLedBi::off ()
{
   _led_red.off ();
   _led_green.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  VcvLedBi::pulse (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse (color.r, duration, transition_function);
   _led_green.pulse (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  VcvLedBi::pulse_twice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse_twice (color.r, duration, transition_function);
   _led_green.pulse_twice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  VcvLedBi::pulse_thrice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse_thrice (color.r, duration, transition_function);
   _led_green.pulse_thrice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  VcvLedBi::blink (Color color, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _led_red.blink (color.r, period, transition_function);
   _led_green.blink (color.g, period, transition_function);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
