/*****************************************************************************

      DaisyLedBi.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyLedBi.h"

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

DaisyLedBi::Color DaisyLedBi::Color::none ()
{
   return { 0.f, 0.f };
}



/*
==============================================================================
Name : Color::red
==============================================================================
*/

DaisyLedBi::Color DaisyLedBi::Color::red ()
{
   return { 1.f, 0.f };
}



/*
==============================================================================
Name : Color::green
==============================================================================
*/

DaisyLedBi::Color DaisyLedBi::Color::green ()
{
   return { 0.f, 1.f };
}



/*
==============================================================================
Name : Color::yellow
==============================================================================
*/

DaisyLedBi::Color DaisyLedBi::Color::yellow ()
{
   return { 1.f, 1.f };
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyLedBi::DaisyLedBi (DaisyModule & module, const Pin & pin_r, const Pin & pin_g)
:  _led_red (module, pin_r)
,  _led_green (module, pin_g)
{
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  DaisyLedBi::set_brightness (float perceptual_brightness)
{
   _led_red.set_brightness (perceptual_brightness);
   _led_green.set_brightness (perceptual_brightness);
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  DaisyLedBi::on (Color color)
{
   _led_red.on (color.r);
   _led_green.on (color.g);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  DaisyLedBi::off ()
{
   _led_red.off ();
   _led_green.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  DaisyLedBi::pulse (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse (color.r, duration, transition_function);
   _led_green.pulse (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  DaisyLedBi::pulse_twice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse_twice (color.r, duration, transition_function);
   _led_green.pulse_twice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  DaisyLedBi::pulse_thrice (Color color, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _led_red.pulse_thrice (color.r, duration, transition_function);
   _led_green.pulse_thrice (color.g, duration, transition_function);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  DaisyLedBi::blink (Color color, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _led_red.blink (color.r, period, transition_function);
   _led_green.blink (color.g, period, transition_function);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
