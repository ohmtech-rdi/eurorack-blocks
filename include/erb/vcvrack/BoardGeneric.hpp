/*****************************************************************************

      BoardGeneric.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/Led.h"
#include "erb/LedBi.h"
#include "erb/LedRgb.h"
#include "erb/Pot.h"
#include "erb/Switch.h"

#include <rack.hpp>



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
inline void  BoardGeneric::impl_bind (Button & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingButton {
      .data_ptr = const_cast <uint8_t *> (&control.impl_data),
      .param_ptr = &model
   });
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
inline void  BoardGeneric::impl_bind (CvIn <FloatRange::Bipolar> & control, rack::engine::Input & model)
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
inline void  BoardGeneric::impl_bind (GateIn & control, rack::engine::Input & model)
{
   _binding_inputs.push_back (BindingGateIn {
      .data_ptr = const_cast <uint8_t *> (&control.impl_data),
      .input_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (GateOut & control, rack::engine::Output & model)
{
   _binding_outputs.push_back (BindingGateOut {
      .data_ptr = &control.impl_data,
      .output_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Led & control, rack::engine::Light & model)
{
   _binding_outputs.push_back (BindingLed {
      .data_ptr = &control.impl_data,
      .light_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (LedBi & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedBi {
      .data_r_ptr = &control.r.impl_data,
      .data_g_ptr = &control.g.impl_data,
      .light_r_ptr = &model_ptr [0],
      .light_g_ptr = &model_ptr [1]
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (LedRgb & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedRgb {
      .data_r_ptr = &control.r.impl_data,
      .data_g_ptr = &control.g.impl_data,
      .data_b_ptr = &control.b.impl_data,
      .light_r_ptr = &model_ptr [0],
      .light_g_ptr = &model_ptr [1],
      .light_b_ptr = &model_ptr [2]
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
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Switch & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingSwitch {
      .data_0_ptr = const_cast <uint8_t *> (&control._0.impl_data),
      .data_1_ptr = const_cast <uint8_t *> (&control._1.impl_data),
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
