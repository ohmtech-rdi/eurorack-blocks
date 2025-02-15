/*****************************************************************************

      Encoder.hpp
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

template <EncoderLeadingType LeadingType>
Encoder <LeadingType>::Encoder (const uint8_t & data_a, const uint8_t & data_b)
:  impl_data_a (data_a)
,  impl_data_b (data_b)
{
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
   _state_a = uint8_t (_state_a << 1) | (impl_data_a != 0);
   _state_b = uint8_t (_state_b << 1) | (impl_data_b != 0);

   if ((_state_a & 0x07) == 0x04 && (_state_b & 0x07) == 0x00)
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
   else if ((_state_b & 0x07) == 0x04 && (_state_a & 0x07) == 0x00)
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
