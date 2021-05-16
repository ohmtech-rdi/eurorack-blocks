/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/CvIn.h"
#include "erb/Pot.h"

#include <rack.hpp>

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

BoardGeneric::BoardGeneric (size_t nbr_digital_inputs, size_t nbr_analog_inputs, size_t nbr_audio_inputs, size_t nbr_digital_outputs, size_t nbr_analog_outputs, size_t nbr_audio_outputs)
:  _digital_inputs (nbr_digital_inputs, 0)
,  _analog_inputs (nbr_analog_inputs, 0.f)
,  _audio_inputs (nbr_audio_inputs, Buffer {})
,  _digital_outputs (nbr_digital_outputs, 0)
,  _analog_outputs (nbr_analog_outputs, 0.f)
,  _audio_outputs (nbr_audio_outputs, Buffer {})

,  _double_buffer_inputs (nbr_audio_inputs)
,  _double_buffer_outputs (nbr_audio_outputs)
{
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
void  BoardGeneric::impl_bind (AudioIn & control, rack::engine::Input & model)
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
void  BoardGeneric::impl_bind (AudioOut & control, rack::engine::Output & model)
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
void  BoardGeneric::impl_bind (CvIn <FloatRange::Normalized> & control, rack::engine::Input & model)
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
void  BoardGeneric::impl_bind (Pot <FloatRange::Normalized> & control, rack::engine::Param & model)
{
   _binding_inputs.push_back (BindingPot {
      .data_ptr = const_cast <float *> (&control.impl_data),
      .param_ptr = &model
   });
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_need_process
==============================================================================
*/

bool  BoardGeneric::impl_need_process ()
{
   return _double_buffer_inputs [0].tell () == 0;
}



/*
==============================================================================
Name : impl_pull_audio_inputs
==============================================================================
*/

void  BoardGeneric::impl_pull_audio_inputs ()
{
   for (size_t i = 0 ; i < _audio_inputs.size () ; ++i)
   {
      auto & double_buffer = _double_buffer_inputs [i];
      auto & audio_input = *_rack_audio_inputs [i];

      float sample = audio_input.getVoltage () * 0.2f;

      double_buffer.push (sample);
   }
}



/*
==============================================================================
Name : impl_push_audio_outputs
==============================================================================
*/

void  BoardGeneric::impl_push_audio_outputs ()
{
   for (size_t i = 0 ; i < _audio_outputs.size () ; ++i)
   {
      auto & double_buffer = _double_buffer_outputs [i];
      auto & audio_output = *_rack_audio_outputs [i];

      float sample = double_buffer.pull ();

      audio_output.setVoltage (sample * 5.f);
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardGeneric::impl_preprocess ()
{
   for (auto && binding : _binding_inputs)
   {
      std::visit ([](auto && arg){arg.process ();}, binding);
   }

   /*for (size_t i = 0 ; i < _digital_inputs.size (HW_ROW_BUTTON) ; ++i)
   {
      auto norm_val = _params (VCV_ROW_BUTTON, i)->getValue ();
      _digital_inputs (HW_ROW_BUTTON, i) = norm_val != 0.f;
   }

   for (size_t i = 0 ; i < _digital_inputs.size (HW_ROW_GATE_IN) ; ++i)
   {
      auto norm_val = _inputs (VCV_ROW_GATE_IN, i)->getVoltage ();
      _digital_inputs (HW_ROW_GATE_IN, i) = norm_val > 0.1f;
   }

   for (size_t i = 0 ; i < _analog_inputs.size (HW_ROW_POTS) ; ++i)
   {
      auto norm_val = _params (VCV_ROW_POT, i)->getValue ();
      norm_val = std::clamp (norm_val, 0.f, 1.f);
      _analog_inputs (HW_ROW_POTS, i) = norm_val;
   }

   for (size_t i = 0 ; i < _analog_inputs.size (HW_ROW_CV_IN) ; ++i)
   {
      auto norm_val = _inputs (VCV_ROW_CV_IN, i)->getVoltage () * 0.1f + 0.5f;
      norm_val = std::clamp (norm_val, 0.f, 1.f);
      _analog_inputs (HW_ROW_CV_IN, i) = norm_val;
   }

   for (size_t i = 0 ; i < _audio_inputs.size (HW_ROW_AUDIO_IN) ; ++i)
   {
      _audio_inputs (HW_ROW_AUDIO_IN, i) = _audio_double_buffer_inputs [i];
   }*/
}



/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  BoardGeneric::impl_process ()
{
   _buffer_callback ();
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardGeneric::impl_postprocess ()
{
   for (auto && binding : _binding_outputs)
   {
      std::visit ([](auto && arg){arg.process ();}, binding);
   }

   /*for (size_t i = 0 ; i < _digital_outputs.size (HW_ROW_GATE_OUT) ; ++i)
   {
      auto val = _digital_outputs (HW_ROW_GATE_OUT, i);
      _outputs (VCV_ROW_GATE_OUT, i)->setVoltage (float (val) * 5.f);
   }

   for (size_t i = 0 ; i < _analog_outputs.size (HW_ROW_CV_OUT) ; ++i)
   {
      auto val = _analog_outputs (HW_ROW_CV_OUT, i);
      _outputs (VCV_ROW_CV_OUT, i)->setVoltage (float (val) * 5.f);
   }

   for (size_t i = 0 ; i < _analog_outputs.size (HW_ROW_LED) ; ++i)
   {
      auto val = _analog_outputs (HW_ROW_LED, i);
      _lights (VCV_ROW_LED, i)->setBrightness (val);
   }

   for (size_t i = 0 ; i < _audio_outputs.size (HW_ROW_AUDIO_OUT) ; ++i)
   {
      _audio_double_buffer_outputs [i] = _audio_outputs (HW_ROW_AUDIO_OUT, i);
   }*/

   _clock.tick ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : BindingAudioIn::process
==============================================================================
*/

void  BoardGeneric::BindingAudioIn::process ()
{
   *data_ptr = *db_ptr;
}



/*
==============================================================================
Name : BindingCvIn::process
==============================================================================
*/

void  BoardGeneric::BindingCvIn::process ()
{
   *data_ptr = std::clamp (
      input_ptr->getVoltage () * 0.1f + 0.5f,
      0.f, 1.f
   );
}



/*
==============================================================================
Name : BindingCvOut::process
==============================================================================
*/

void  BoardGeneric::BindingCvOut::process ()
{
   output_ptr->setVoltage (float (*data_ptr) * 5.f);
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
