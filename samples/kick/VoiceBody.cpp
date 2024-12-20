/*****************************************************************************

      VoiceBody.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "VoiceBody.h"

#include <cmath>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : trigger
==============================================================================
*/

void  VoiceBody::trigger ()
{
   _active_flag = true;
   _pos = 0;
   _ramp.reset (1.f);
}



/*
==============================================================================
Name : stop
==============================================================================
*/

void  VoiceBody::stop ()
{
   _ramp = 0.f;
}



/*
==============================================================================
Name : set_speed
==============================================================================
*/

void  VoiceBody::set_speed (float step_spl)
{
   _step_spl = step_spl;
}
