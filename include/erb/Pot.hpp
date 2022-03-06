/*****************************************************************************

      Pot.hpp
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
Pot <Range>::Pot (const float & data)
:  impl_data (data)
{
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

template <FloatRange Range>
Pot <Range>::operator float () const
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
   else if constexpr (Range == FloatRange::Pitch)
   {
      return impl_data * 10.f;
   }

#elif defined (erb_TARGET_VCV_RACK)
   return impl_data;

#else
   #error

#endif
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
