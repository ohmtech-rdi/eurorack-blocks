/*****************************************************************************

      AudioStereoInJackDetection.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

AudioStereoInJackDetection::AudioStereoInJackDetection (const Buffer & data_left, const Buffer & data_right, const uint8_t & npr)
:  left (data_left)
,  right (data_right)
,  impl_npr (npr)
{
}



/*
==============================================================================
Name : plugged
==============================================================================
*/

bool  AudioStereoInJackDetection::plugged () const
{
   return _jack_detection.plugged ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  AudioStereoInJackDetection::impl_preprocess ()
{
   // left is tip so last to plug
   _jack_detection.push (left.impl_data [left.impl_data.size () - 1] < .1f, impl_npr != 0);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
