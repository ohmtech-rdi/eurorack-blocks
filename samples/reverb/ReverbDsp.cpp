/*****************************************************************************

      ReverbDsp.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "ReverbDsp.h"



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

ReverbDsp::ReverbDsp (float sample_freq, AuxiliaryBuffer & aux_buffer)
:  _reverb (sample_freq, aux_buffer)
{
   _wet.target = 0.f;

   for (auto & filter : _filters_lp)
   {
      filter.set_sample_freq (sample_freq);
      filter.set_type_low_pass ();
   }

   for (auto & filter : _filters_hp)
   {
      filter.set_sample_freq (sample_freq);
      filter.set_type_high_pass ();
   }

   _reverb.set_low_pass_freq (24000.f);
}



/*
==============================================================================
Name : set_wet
==============================================================================
*/

void  ReverbDsp::set_wet (float wet)
{
   _wet.target = wet;
}



/*
==============================================================================
Name : set_feedback
==============================================================================
*/

void  ReverbDsp::set_feedback (float feedback)
{
   _reverb.set_feedback (feedback);
}



/*
==============================================================================
Name : set_low_pass_freq
==============================================================================
*/

void  ReverbDsp::set_low_pass_freq (float freq)
{
   for (auto & filter : _filters_lp) filter.set_freq (freq);
}



/*
==============================================================================
Name : set_high_pass_freq
==============================================================================
*/

void  ReverbDsp::set_high_pass_freq (float freq)
{
   for (auto & filter : _filters_hp) filter.set_freq (freq);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  ReverbDsp::process (float * const out [], const float * const in [], size_t size)
{
   for (auto & filter : _filters_lp) filter.update ();
   for (auto & filter : _filters_hp) filter.update ();

   auto in_left = in [0];
   auto in_right = in [1];
   auto out_left = out [0];
   auto out_right = out [1];

   for (size_t i = 0 ; i < size ; ++i)
   {
      _wet.process ();

      float in_spl_left = in_left [i];
      float in_spl_right = in_right [i];

      float & out_spl_left = out_left [i];
      float & out_spl_right = out_right [i];

      const float lp_l = _filters_lp [0].process (in_spl_left);
      const float hp_l = _filters_hp [0].process (lp_l);

      const float lp_r = _filters_lp [1].process (in_spl_right);
      const float hp_r = _filters_hp [1].process (lp_r);

      auto reverb_frame = _reverb.process ({hp_l, hp_r});

      const auto dry = 1.f - _wet;

      out_spl_left = dry * in_spl_left + _wet * reverb_frame.left;
      out_spl_right = dry * in_spl_right + _wet * reverb_frame.right;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
