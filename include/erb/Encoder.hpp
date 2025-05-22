/*****************************************************************************

      Encoder.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <EncoderLeadingType LeadingType>
Encoder <LeadingType>::Encoder (const uint8_t & data_a, const uint8_t & data_b)
:  impl_data_a (data_a)
,  impl_data_b (data_b)
{
}



/*
==============================================================================
Name : configure
Description :
   Sets the number of expected zeros to emit an event while debouncing.
   For example 2 zeros will output an event when 100 is observed.
==============================================================================
*/

template <EncoderLeadingType LeadingType>
void  Encoder <LeadingType>::configure (size_t nbr_debounce_zeros)
{
   assert (nbr_debounce_zeros < 32);

   _test = 1 << nbr_debounce_zeros;
   _mask = _test * 2 - 1;
}



/*
==============================================================================
Name : operator int
==============================================================================
*/

template <EncoderLeadingType LeadingType>
Encoder <LeadingType>::operator int () const
{
   return _val;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

template <EncoderLeadingType LeadingType>
void  Encoder <LeadingType>::impl_preprocess ()
{
   _state_a = uint32_t (_state_a << 1) | (impl_data_a != 0);
   _state_b = uint32_t (_state_b << 1) | (impl_data_b != 0);

   if ((_state_a & _mask) == _test && (_state_b & _mask) == 0)
   {
      if constexpr (LeadingType == EncoderLeadingType::A)
      {
         _val = -1;
      }
      else
      {
         _val = 1;
      }
   }
   else if ((_state_b & _mask) == _test && (_state_a & _mask) == 0)
   {
      if constexpr (LeadingType == EncoderLeadingType::A)
      {
         _val = 1;
      }
      else
      {
         _val = -1;
      }
   }
   else
   {
      _val = 0;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
