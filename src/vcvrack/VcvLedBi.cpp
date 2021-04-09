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
Name : on
==============================================================================
*/

void  VcvLedBi::on (Color color)
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

void  VcvLedBi::pulse (Color color, std::chrono::milliseconds duration)
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

void  VcvLedBi::blink (Color color, std::chrono::milliseconds half_period)
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

VcvLedBi::State   VcvLedBi::to_state (Color color)
{
   switch (color)
   {
   case Color::Red:
      return { true, false };

   case Color::Yellow:
      return { true, true };

   case Color::Green:
      return { false, true };

#if defined (__GNUC__) && ! defined (__clang__)
   default:
      return { false, false };
#endif
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
