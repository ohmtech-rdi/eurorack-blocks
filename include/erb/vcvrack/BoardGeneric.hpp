/*****************************************************************************

      BoardGeneric.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioInJackDetection.h"
#include "erb/AudioOut.h"
#include "erb/AudioStereoIn.h"
#include "erb/AudioStereoInJackDetection.h"
#include "erb/AudioStereoOut.h"
#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/CvInJackDetection.h"
#include "erb/CvOut.h"
#include "erb/Encoder.h"
#include "erb/EncoderButton.h"
#include "erb/GateIn.h"
#include "erb/GateInJackDetection.h"
#include "erb/GateOut.h"
#include "erb/Led.h"
#include "erb/LedBi.h"
#include "erb/LedRgb.h"
#include "erb/Pot.h"
#include "erb/Switch.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_VCVRACK
#include <rack.hpp>
erb_RESTORE_WARNINGS



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
   std::size_t audio_input_index = _rack_audio_inputs.size ();

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
inline void  BoardGeneric::impl_bind (AudioInJackDetection & control, rack::engine::Input & model)
{
   std::size_t audio_input_index = _rack_audio_inputs.size ();

   auto & double_buffer = _double_buffer_inputs [audio_input_index];

   _binding_inputs.push_back (BindingAudioInJackDetection {
      .board_ptr = this,
      .data_ptr = const_cast <Buffer *> (&control.impl_data),
      .npr_ptr = const_cast <uint8_t *> (&control.impl_npr),
      .db_ptr = &double_buffer,
      .input_ptr = &model
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
   std::size_t audio_output_index = _rack_audio_outputs.size ();

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
inline void  BoardGeneric::impl_bind (AudioStereoIn & control, rack::engine::Input & model)
{
   std::size_t audio_input_index = _rack_audio_inputs.size ();

   auto & double_buffer_left = _double_buffer_inputs [audio_input_index];
   auto & double_buffer_right = _double_buffer_inputs [audio_input_index + 1];

   _binding_inputs.push_back (BindingAudioStereoIn {
      .data_left_ptr = const_cast <Buffer *> (&control.left.impl_data),
      .data_right_ptr = const_cast <Buffer *> (&control.right.impl_data),
      .db_left_ptr = &double_buffer_left,
      .db_right_ptr = &double_buffer_right
   });

   auto * model_ptr = &model;
   _rack_audio_inputs.push_back (&model_ptr [0]);
   _rack_audio_inputs.push_back (&model_ptr [1]);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (AudioStereoInJackDetection & control, rack::engine::Input & model)
{
   std::size_t audio_input_index = _rack_audio_inputs.size ();

   auto & double_buffer_left = _double_buffer_inputs [audio_input_index];
   auto & double_buffer_right = _double_buffer_inputs [audio_input_index + 1];

   _binding_inputs.push_back (BindingAudioStereoInJackDetection {
      .board_ptr = this,
      .data_left_ptr = const_cast <Buffer *> (&control.left.impl_data),
      .data_right_ptr = const_cast <Buffer *> (&control.right.impl_data),
      .npr_ptr = const_cast <uint8_t *> (&control.impl_npr),
      .db_left_ptr = &double_buffer_left,
      .db_right_ptr = &double_buffer_right,
      .input_left_ptr = &model
   });

   auto * model_ptr = &model;
   _rack_audio_inputs.push_back (&model_ptr [0]);
   _rack_audio_inputs.push_back (&model_ptr [1]);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (AudioStereoOut & control, rack::engine::Output & model)
{
   std::size_t audio_output_index = _rack_audio_outputs.size ();

   auto & double_buffer_left = _double_buffer_outputs [audio_output_index];
   auto & double_buffer_right = _double_buffer_outputs [audio_output_index + 1];

   _binding_outputs.push_back (BindingAudioStereoOut {
      .data_left_ptr = const_cast <Buffer *> (&control.left.impl_data),
      .data_right_ptr = const_cast <Buffer *> (&control.right.impl_data),
      .db_left_ptr = &double_buffer_left,
      .db_right_ptr = &double_buffer_right
   });

   auto * model_ptr = &model;
   _rack_audio_outputs.push_back (&model_ptr [0]);
   _rack_audio_outputs.push_back (&model_ptr [1]);
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
      .input_ptr = &model,
      .bipolar = false,
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (CvInJackDetection <FloatRange::Normalized> & control, rack::engine::Input & model)
{
   _binding_inputs.push_back (BindingCvInJackDetection {
      .board_ptr = this,
      .data_ptr = const_cast <float *> (&control.impl_data),
      .npr_ptr = const_cast <uint8_t *> (&control.impl_npr),
      .input_ptr = &model,
      .bipolar = false,
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
      .input_ptr = &model,
      .bipolar = true
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (CvInJackDetection <FloatRange::Bipolar> & control, rack::engine::Input & model)
{
   _binding_inputs.push_back (BindingCvInJackDetection {
      .board_ptr = this,
      .data_ptr = const_cast <float *> (&control.impl_data),
      .npr_ptr = const_cast <uint8_t *> (&control.impl_npr),
      .input_ptr = &model,
      .bipolar = true
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (CvOut <FloatRange::Normalized> & control, rack::engine::Output & model)
{
   _binding_outputs.push_back (BindingCvOut {
      .data_ptr = &control.impl_data,
      .output_ptr = &model,
      .bipolar = false
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (CvOut <FloatRange::Bipolar> & control, rack::engine::Output & model)
{
   _binding_outputs.push_back (BindingCvOut {
      .data_ptr = &control.impl_data,
      .output_ptr = &model,
      .bipolar = true
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Encoder <erb::EncoderLeadingType::A> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingEncoderLeadingA {
      .data_a_ptr = const_cast <uint8_t *> (&control.impl_data_a),
      .data_b_ptr = const_cast <uint8_t *> (&control.impl_data_b),
      .param_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Encoder <erb::EncoderLeadingType::B> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingEncoderLeadingB {
      .data_a_ptr = const_cast <uint8_t *> (&control.impl_data_a),
      .data_b_ptr = const_cast <uint8_t *> (&control.impl_data_b),
      .param_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (EncoderButton <erb::EncoderLeadingType::A> & control, rack::engine::Param & model)
{
   auto * model_ptr = &model;

   _binding_inputs.push_back (BindingEncoderButtonLeadingA {
      .data_a_ptr = const_cast <uint8_t *> (&control.encoder.impl_data_a),
      .data_b_ptr = const_cast <uint8_t *> (&control.encoder.impl_data_b),
      .data_sw_ptr = const_cast <uint8_t *> (&control.button.impl_data),
      .param_ab_ptr = &model_ptr [0],
      .param_sw_ptr = &model_ptr [1]
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (EncoderButton <erb::EncoderLeadingType::B> & control, rack::engine::Param & model)
{
   auto * model_ptr = &model;

   _binding_inputs.push_back (BindingEncoderButtonLeadingB {
      .data_a_ptr = const_cast <uint8_t *> (&control.encoder.impl_data_a),
      .data_b_ptr = const_cast <uint8_t *> (&control.encoder.impl_data_b),
      .data_sw_ptr = const_cast <uint8_t *> (&control.button.impl_data),
      .param_ab_ptr = &model_ptr [0],
      .param_sw_ptr = &model_ptr [1]
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
inline void  BoardGeneric::impl_bind (GateInJackDetection & control, rack::engine::Input & model)
{
   _binding_inputs.push_back (BindingGateInJackDetection {
      .board_ptr = this,
      .data_ptr = const_cast <uint8_t *> (&control.impl_data),
      .npr_ptr = const_cast <uint8_t *> (&control.impl_npr),
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
inline void  BoardGeneric::impl_bind (Led <PinType::Pwm> & control, rack::engine::Light & model)
{
   _binding_outputs.push_back (BindingLedFloat {
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
inline void  BoardGeneric::impl_bind (LedBi <PinType::Pwm> & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedBiFloat {
      .data_r_ptr = &control.r.impl_data,
      .data_g_ptr = &control.g.impl_data,
      // red and green are inverted in the GreenRed VCV light
      .light_r_ptr = &model_ptr [1],
      .light_g_ptr = &model_ptr [0]
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (LedRgb <PinType::Pwm> & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedRgbFloat {
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
inline void  BoardGeneric::impl_bind (Led <PinType::Gpio> & control, rack::engine::Light & model)
{
   _binding_outputs.push_back (BindingLedBool {
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
inline void  BoardGeneric::impl_bind (LedBi <PinType::Gpio> & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedBiBool {
      .data_r_ptr = &control.r.impl_data,
      .data_g_ptr = &control.g.impl_data,
      // red and green are inverted in the GreenRed VCV light
      .light_r_ptr = &model_ptr [1],
      .light_g_ptr = &model_ptr [0]
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (LedRgb <PinType::Gpio> & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedRgbBool {
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
inline void  BoardGeneric::impl_bind (Led <PinType::Dac> & control, rack::engine::Light & model)
{
   _binding_outputs.push_back (BindingLedFloat {
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
inline void  BoardGeneric::impl_bind (LedBi <PinType::Dac> & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedBiFloat {
      .data_r_ptr = &control.r.impl_data,
      .data_g_ptr = &control.g.impl_data,
      // red and green are inverted in the GreenRed VCV light
      .light_r_ptr = &model_ptr [1],
      .light_g_ptr = &model_ptr [0]
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (LedRgb <PinType::Dac> & control, rack::engine::Light & model)
{
   auto * model_ptr = &model;

   _binding_outputs.push_back (BindingLedRgbFloat {
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
      .param_ptr = &model,
      .bipolar = false
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
      .param_ptr = &model,
      .bipolar = true
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Switch <2> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingSwitch {
      .data_0_ptr = const_cast <uint8_t *> (&control._0.impl_data),
      .data_1_ptr = const_cast <uint8_t *> (&control._1.impl_data),
      .scale = 1.f,
      .param_ptr = &model
   });
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
inline void  BoardGeneric::impl_bind (Switch <3> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingSwitch {
      .data_0_ptr = const_cast <uint8_t *> (&control._0.impl_data),
      .data_1_ptr = const_cast <uint8_t *> (&control._1.impl_data),
      .scale = 0.5f,
      .param_ptr = &model
   });
}



/*
==============================================================================
Name : load
==============================================================================
*/

template <std::size_t N>
std::array <uint8_t, N> BoardGeneric::load (size_t page)
{
   auto it = _persistent_map.find (page);

   if (it != _persistent_map.end ())
   {
      const auto & stored = it->second;
      auto ret = std::array <uint8_t, N> {};
      std::memcpy (&ret [0], &stored [0], std::min (stored.size (), N));

      return ret;
   }
   else
   {
      return {};
   }
}



/*
==============================================================================
Name : save
==============================================================================
*/

template <typename Data>
void  BoardGeneric::save (size_t page, const Data & data)
{
   auto & stored = _persistent_map [page];
   stored = std::vector <uint8_t> { data.begin (), data.end () };
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
