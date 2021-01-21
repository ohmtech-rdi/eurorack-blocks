/*****************************************************************************

      LedBi.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/LedBi.h"

#include "erb/Module.h"

#if defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wpedantic"
   #pragma GCC diagnostic ignored "-Wignored-qualifiers"
   #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "daisy_seed.h"

#if defined (__GNUC__)
   #pragma GCC diagnostic pop
#endif



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

LedBi::LedBi (Module & module, const Pin & pin_r, const Pin & pin_g)
:  _led_red (module, pin_r)
,  _led_green (module, pin_g)
{
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  LedBi::on (Color color)
{
   auto state = to_state (color);

   _led_red.on (state.red);
   _led_green.on (state.green);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  LedBi::off ()
{
   _led_red.off ();
   _led_green.off ();
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  LedBi::pulse (Color color, std::chrono::milliseconds duration)
{
   auto state = to_state (color);

   if (state.red)
   {
      _led_red.pulse (duration);
   }
   else
   {
      _led_red.off ();
   }

   if (state.green)
   {
      _led_green.pulse (duration);
   }
   else
   {
      _led_green.off ();
   }
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  LedBi::blink (Color color, std::chrono::milliseconds half_period)
{
   auto state = to_state (color);

   if (state.red)
   {
      _led_red.blink (half_period);
   }
   else
   {
      _led_red.off ();
   }

   if (state.green)
   {
      _led_green.blink (half_period);
   }
   else
   {
      _led_green.off ();
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : to_state
==============================================================================
*/

LedBi::State   LedBi::to_state (Color color)
{
   switch (color)
   {
   case Color::Red:
      return { true, false };

   case Color::Yellow:
      return { true, true };

   case Color::Green:
      return { false, true };

#if defined (__GNUC__)
   default:
      return { false, false };
#endif
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
