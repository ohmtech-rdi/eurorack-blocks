/*****************************************************************************

      CvIn.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/CvIn.h"

#include "erb/def.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <FloatRange Range>
CvIn::CvIn (const uint16_t & data)
:  _data_ptr (&data)
{
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

template <FloatRange Range>
CvIn::operator float () const
{
   constexpr float u16_to_norm = 1.f / 65535.f;
   float norm_val = float (*_data_ptr) * u16_to_norm;

   if constexpr (Range == FloatRange::Normalized)
   {
      return norm_val
   }
   else if constexpr (Range == FloatRange::Bipolar)
   {
      return norm_val * 2.f - 1.f;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
