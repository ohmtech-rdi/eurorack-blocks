/*****************************************************************************

      EncoderButton.hpp
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
EncoderButton <LeadingType>::EncoderButton (const uint8_t & data_a, const uint8_t & data_b, const uint8_t & data_sw)
:  encoder (data_a, data_b)
,  button (data_sw)
{
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

template <EncoderLeadingType LeadingType>
void  EncoderButton <LeadingType>::impl_preprocess ()
{
   encoder.impl_preprocess ();
   button.impl_preprocess ();
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

template <EncoderLeadingType LeadingType>
void  EncoderButton <LeadingType>::impl_postprocess ()
{
   encoder.impl_postprocess ();
   button.impl_postprocess ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
