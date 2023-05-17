/*****************************************************************************

      CvInJackDetection.hpp
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

template <FloatRange Range>
CvInJackDetection <Range>::CvInJackDetection (const float & data, const uint8_t & npr)
:  impl_data (data)
,  impl_npr (npr)
{
}



/*
==============================================================================
Name : plugged
==============================================================================
*/

template <FloatRange Range>
bool  CvInJackDetection <Range>::plugged () const
{
   return _jack_detection.plugged ();
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

template <FloatRange Range>
CvInJackDetection <Range>::operator float () const
{
#if defined (erb_TARGET_DAISY)
   if constexpr (Range == FloatRange::Normalized)
   {
      return impl_data;
   }
   else if constexpr (Range == FloatRange::Bipolar)
   {
      return impl_data * 2.f - 1.f;
   }

#elif defined (erb_TARGET_VCV_RACK)
   return impl_data;

#else
   #error

#endif
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

template <FloatRange Range>
void  CvInJackDetection <Range>::impl_preprocess ()
{
   _jack_detection.push (impl_data > .5f, impl_npr != 0);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
