/*****************************************************************************

      BoardGeneric.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/CvIn.h"
#include "erb/Pot.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (AudioIn & control, rack::engine::Input & model)
{
   size_t audio_input_index = _rack_audio_inputs.size ();

   auto & double_buffer = _double_buffer_inputs [audio_input_index];

   _binding_inputs.push_back (BindingAudioIn {
      .data_ptr = const_cast <Buffer *> (&control.impl_data),
      .db_ptr = &double_buffer
   });

   _rack_audio_inputs.push_back (&model);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (AudioOut & control, rack::engine::Output & model)
{
   size_t audio_output_index = _rack_audio_outputs.size ();

   auto & double_buffer = _double_buffer_outputs [audio_output_index];

   _binding_outputs.push_back (BindingAudioOut {
      .data_ptr = const_cast <Buffer *> (&control.impl_data),
      .db_ptr = &double_buffer
   });

   _rack_audio_outputs.push_back (&model);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (CvIn <FloatRange::Normalized> & control, rack::engine::Input & model)
{
   _binding_inputs.push_back (BindingCvIn {
      .data_ptr = const_cast <float *> (&control.impl_data),
      .input_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Pot <FloatRange::Normalized> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingPot {
      .data_ptr = const_cast <float *> (&control.impl_data),
      .param_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Pot <FloatRange::Bipolar> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingPot {
      .data_ptr = const_cast <float *> (&control.impl_data),
      .param_ptr = &model
   });
}



/*
==============================================================================
Name : bind_process
==============================================================================
*/

template <typename F>
void  BoardGeneric::bind_process (F && f)
{
   _buffer_callback = std::forward <F> (f);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
