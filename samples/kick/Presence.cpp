/*****************************************************************************

      Presence.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Presence.h"

#include <cmath>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set
==============================================================================
*/

void  Presence::set (float presence)
{
   _presence_ramp = presence;
}



/*
==============================================================================
Name : process
==============================================================================
*/

float Presence::process (float x)
{
   const float drive = _presence_ramp.process ();
   const float compensation = std::exp (- drive) + 0.367879441171442f;

   constexpr float pid2 = 1.570796326794897f;

   const float r = std::abs (x * drive);
   const float s = (x > 0) ? 1.f : -1.f;

   float shape = (r < pid2) ? std::sin (r) : 1.f;

   return s * shape * compensation;
}
