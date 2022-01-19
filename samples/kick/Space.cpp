/*****************************************************************************

      Space.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Space.h"

#include <cmath>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : tick
==============================================================================
*/

void  Space::tick (uint64_t clock_ms, float space)
{
   size_t quarter_ms = _estimator.process (clock_ms);
   size_t beat_ms = quarter_ms * 4;
   size_t beat_spl = beat_ms * 48;

   _space_spl = size_t (beat_spl * space);
}



/*
==============================================================================
Name : trigger
==============================================================================
*/

void  Space::trigger ()
{
   _ramp.reset (1.f);
   _step_spl = 0;
   _active = true;
}



/*
==============================================================================
Name : process
==============================================================================
*/

float Space::process (float x)
{
   const float r = _ramp.process ();
   const float ret = (3.f - 2.f * r) * r * r * x;

   if (_active)
   {
      ++_step_spl;
      if (_step_spl > _space_spl)
      {
         _ramp = 0.f;
         _active = false;
      }
   }

   return ret;
}
