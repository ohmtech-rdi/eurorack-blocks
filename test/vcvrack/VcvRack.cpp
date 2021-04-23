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
   if (first_flag)
   {
      first_flag = false;

      ui.led_3mm_red.blink ();
      ui.led_3mm_green.blink ();
      ui.led_3mm_yellow.blink ();
      ui.led_3mm_green_red.blink (erb::LedBi::Color::Yellow);
   }
}
