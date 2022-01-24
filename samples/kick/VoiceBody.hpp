/*****************************************************************************

      VoiceBody.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cmath>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

template <typename T>
float VoiceBody::process (const T & sample)
{
   if (!_active_flag) return 0.f;

   float integral;
   float mix = std::modf (_pos, &integral);
   size_t pos = size_t (_pos);

   float ret_1 = sample.samples [pos];
   float ret_2 = sample.samples [pos + 1];
   float ret = ret_1 + (ret_2 - ret_1) * mix;

   float r = _ramp.process ();
   ret *= (3.f - 2.f * r) * r * r;

   _pos += _step_spl;
   if (_pos + 2.f >= float (sample.samples.size ()))
   {
      _active_flag = false;
   }

   return ret;
}
