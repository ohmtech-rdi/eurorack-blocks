/*****************************************************************************

      CvOut.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <FloatRange Range>
CvOut <Range>::CvOut (float & data)
:  impl_data (data)
{
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <FloatRange Range>
CvOut <Range> &   CvOut <Range>::operator = (float val)
{
   if constexpr (Range == FloatRange::Normalized)
   {
      impl_data = val;
   }
   else if constexpr (Range == FloatRange::Bipolar)
   {
      impl_data = val * 0.5f + 0.5f;
   }
   else if constexpr (Range == FloatRange::Pitch)
   {
      impl_data = val * 0.1f;
   }

   return *this;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
