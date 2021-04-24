/*****************************************************************************

      DaisyLedRgb.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyLedRgb.h"

#include "erb/daisy/DaisyModule.h"
#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Color::none
==============================================================================
*/

DaisyLedRgb::Color DaisyLedRgb::Color::none ()
{
   return { 0.f, 0.f, 0.f };
}



/*
==============================================================================
Name : Color::red
==============================================================================
*/

DaisyLedRgb::Color DaisyLedRgb::Color::red ()
{
   return { 1.f, 0.f, 0.f };
}



/*
==============================================================================
Name : Color::green
==============================================================================
*/

DaisyLedRgb::Color DaisyLedRgb::Color::green ()
{
   return { 0.f, 1.f, 0.f };
}



/*
==============================================================================
Name : Color::blue
==============================================================================
*/

DaisyLedRgb::Color DaisyLedRgb::Color::blue ()
{
   return { 0.f, 0.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyLedRgb::DaisyLedRgb (DaisyModule & module, const Pin & pin_r, const Pin & pin_g, const Pin & pin_b)
:  _led_red (module, pin_r)
,  _led_green (module, pin_g)
,  _led_blue (module, pin_b)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  DaisyLedRgb::set_brightness (float perceptual_brightness)
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

void  DaisyLedRgb::on (Color color)
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

void  DaisyLedRgb::off ()
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

void  DaisyLedRgb::pulse (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

void  DaisyLedRgb::pulse_twice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

void  DaisyLedRgb::pulse_thrice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
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

void  DaisyLedRgb::blink (Color color, std::chrono::milliseconds period, TransitionFunction transition_function)
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
