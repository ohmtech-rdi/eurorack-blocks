/*****************************************************************************

      VoiceTransient.hpp
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
float VoiceTransient::process (const T & sample_1, const T & sample_2, float mix)
{
   if (!_active_flag) return 0.f;

   float integral;
   float mix_pos = std::modf (_pos, &integral);
   size_t pos = size_t (_pos);

   float ret_a1 = sample_1.samples [pos];
   float ret_a2 = sample_2.samples [pos];
   float ret_a = ret_a1 + (ret_a2 - ret_a1) * mix;

   float ret_b1 = sample_1.samples [pos + 1];
   float ret_b2 = sample_2.samples [pos + 1];
   float ret_b = ret_b1 + (ret_b2 - ret_b1) * mix;

   float ret = ret_a + (ret_b - ret_a) * mix_pos;

   float r = _ramp.process ();
   ret *= (3.f - 2.f * r) * r * r;

   _pos += _step_spl;
   if (_pos + 2.f >= float (sample_1.samples.size ()))
   {
      _active_flag = false;
   }

   return ret;
}
