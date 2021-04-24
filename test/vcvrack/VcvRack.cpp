/*****************************************************************************

      VcvRack.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "VcvRack.h"

#include "erb/erb.h"



/*
==============================================================================
Name : process
==============================================================================
*/

void  VcvRack::process ()
{
   using namespace std::chrono_literals;

   if (first_flag)
   {
      first_flag = false;

      ui.led_3mm_red.blink ();
      ui.led_3mm_green.blink (1.f, 2s, erb::linear);
      ui.led_3mm_yellow.blink (1.f, 2s, erb::ease_in_out);
      ui.led_3mm_green_red.blink (erb::LedBi::Color::yellow ());
   }

   ui.led_3mm_red.set_brightness (ui.pot);
   ui.led_3mm_green.set_brightness (ui.pot);
   ui.led_3mm_yellow.set_brightness (ui.pot);
   ui.led_3mm_green_red.set_brightness (ui.pot);

   if (ui.button.pressed ())
   {
      ui.led_3mm_red.pulse (1.f, 3s, erb::ease_in_out);
   }
}
