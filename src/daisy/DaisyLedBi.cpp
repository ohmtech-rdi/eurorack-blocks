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
Name : on
==============================================================================
*/

void  DaisyLedBi::on (Color color)
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

void  DaisyLedBi::pulse (Color color, std::chrono::milliseconds duration)
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

void  DaisyLedBi::blink (Color color, std::chrono::milliseconds half_period)
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

DaisyLedBi::State   DaisyLedBi::to_state (Color color)
{
   switch (color)
   {
   case Color::Red:
      return { true, false };

   case Color::Yellow:
      return { true, true };

   case Color::Green:
      return { false, true };

#if erb_GNUC_SWITCH_COVERAGE_FIX
   default:
      return { false, false };
#endif
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
