/*****************************************************************************

      VcvRack.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "VcvRack.h"

#include <cmath>



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

      led_3mm_red.blink ();
      led_3mm_green.blink ();
      led_3mm_yellow.blink ();
      led_3mm_green_red.blink (LedBi::Color::Yellow);
   }
}
