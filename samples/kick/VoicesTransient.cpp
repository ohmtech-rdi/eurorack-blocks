/*****************************************************************************

      VoicesTransient.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "VoicesTransient.h"

#include <cmath>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : trigger
==============================================================================
*/

void  VoicesTransient::trigger ()
{
   _cur_voice = (_cur_voice + 1) % _voices.size ();
   for (size_t i = 0 ; i < _voices.size () ; ++i)
   {
      auto & voice = _voices [i];
      if (i == _cur_voice)
      {
         voice.trigger ();
      }
      else
      {
         voice.stop ();
      }
   }
}



/*
==============================================================================
Name : set_transient_morph
==============================================================================
*/

void  VoicesTransient::set_transient_morph (float transient_morph)
{
   _transient_morph_ramp = transient_morph;
}



/*
==============================================================================
Name : set_speed
==============================================================================
*/

void  VoicesTransient::set_speed (float step_spl)
{
   for (auto && voice : _voices)
   {
      voice.set_speed (step_spl);
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

float  VoicesTransient::process ()
{
   float transient_morph = _transient_morph_ramp.process ();

   float integral;
   float mix = std::modf (transient_morph * 18.f, &integral);
   size_t index = size_t (integral + 18.f);

   const auto & sample_1 = get_sample (index);
   const auto & sample_2 = get_sample (index + 1);

   float val = 0.f;
   for (auto && voice : _voices)
   {
      val += voice.process (sample_1, sample_2, mix);
   }

   return val;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : get_sample
==============================================================================
*/

const erb::AudioSample <float, 38400, 1> &   VoicesTransient::get_sample (size_t index)
{
   index = index % 18;

   switch (index)
   {
   default:
   case 0: return _data.transient01;
   case 1: return _data.transient02;
   case 2: return _data.transient03;
   case 3: return _data.transient04;
   case 4: return _data.transient05;
   case 5: return _data.transient06;
   case 6: return _data.transient07;
   case 7: return _data.transient08;
   case 8: return _data.transient09;
   case 9: return _data.transient10;
   case 10: return _data.transient11;
   case 11: return _data.transient12;
   case 12: return _data.transient13;
   case 13: return _data.transient14;
   case 14: return _data.transient15;
   case 15: return _data.transient16;
   case 16: return _data.transient17;
   case 17: return _data.transient18;
   }
}
