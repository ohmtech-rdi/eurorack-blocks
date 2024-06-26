/*****************************************************************************

      Animation.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Animation.h"



namespace erb
{



/*
==============================================================================
Name : interpolate
==============================================================================
*/

float interpolate (float val0, float val1, float t)
{
   return val0 + (val1 - val0) * t;
}



/*
==============================================================================
Name : step
==============================================================================
*/

float step (float t)
{
   return (t >= 1.f) ? 1.f : 0.f;
}



/*
==============================================================================
Name : inverse_step
==============================================================================
*/

float inverse_step (float t)
{
   return (t > 0.f) ? 1.f : 0.f;
}



/*
==============================================================================
Name : linear
==============================================================================
*/

float linear (float t)
{
   return t;
}



/*
==============================================================================
Name : ease_in
==============================================================================
*/

float ease_in (float t)
{
   return t * t;
}



/*
==============================================================================
Name : ease_out
==============================================================================
*/

float ease_out (float t)
{
   return 2.f * t - t * t;
}



/*
==============================================================================
Name : ease_in_out
==============================================================================
*/

float ease_in_out (float t)
{
   auto t2 = t * t;
   return - 2.f * t * t2 + 3.f * t2;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
