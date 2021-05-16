/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"

#include "erb/AudioIn.h"
#include "erb/CvIn.h"

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

,  _audio_double_buffer_inputs (nbr_audio_inputs)
,  _audio_double_buffer_outputs (nbr_audio_outputs)
{
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

template <>
void  BoardGeneric::impl_bind (AudioIn & control, DoubleBuffer & model)
{
   _binding_inputs.push_back (BindingAudioIn {
      control.impl_data (), &model
   });
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



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_need_process
==============================================================================
*/

bool  BoardGeneric::impl_need_process ()
{
   return _audio_double_buffer_inputs [0].tell () == 0;
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
      auto & double_buffer = _audio_double_buffer_inputs [i];
      auto & audio_input = *_inputs (VCV_ROW_AUDIO_IN, i);

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
      auto & double_buffer = _audio_double_buffer_outputs [i];
      auto & audio_output = *_outputs (VCV_ROW_AUDIO_OUT, i);

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
