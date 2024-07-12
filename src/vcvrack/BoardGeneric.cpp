/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardGeneric::BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs)
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
Name : use_persistent_map
==============================================================================
*/

BoardGeneric::PersistentMap & BoardGeneric::use_persistent_map ()
{
   return _persistent_map;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_need_process
==============================================================================
*/

bool  BoardGeneric::impl_need_process ()
{
   if (!_rack_audio_inputs.empty ())
   {
      return _double_buffer_inputs [0].tell () == 0;
   }
   else if (!_rack_audio_outputs.empty ())
   {
      return _double_buffer_outputs [0].tell () == 0;
   }
   else
   {
      return false;
   }
}



/*
==============================================================================
Name : impl_pull_audio_inputs
==============================================================================
*/

void  BoardGeneric::impl_pull_audio_inputs ()
{
   for (std::size_t i = 0 ; i < _rack_audio_inputs.size () ; ++i)
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
   for (std::size_t i = 0 ; i < _rack_audio_outputs.size () ; ++i)
   {
      auto & double_buffer = _double_buffer_outputs [i];
      auto & audio_output = *_rack_audio_outputs [i];

      float sample = double_buffer.pull ();

      audio_output.setVoltage (sample * 5.f);
   }
}



/*
==============================================================================
Name : impl_feed_mini_input
==============================================================================
*/

void  BoardGeneric::impl_feed_midi_input (const std::vector <uint8_t> & data)
{
   for (auto b : data)
   {
      bool ok = _midi_input.write (b);
      assert (ok);   // stream is full
   }
}



/*
==============================================================================
Name : impl_pop_midi_output
==============================================================================
*/

std::optional <MidiIn::Message>   BoardGeneric::impl_pop_midi_output ()
{
   return _midi_output_slicer.pop ();
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
      std::visit (
         [](auto && arg){
            arg.process ();
         },
         binding
      );
   }
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
      std::visit (
         [](auto && arg){
            arg.process ();
         },
         binding
      );
   }

   // Linear congruential generator
   _npr_rand_state = _npr_rand_state * 1103515245 + 12345;
   _npr = _npr_rand_state >> 31;

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
Name : BindingAudioInJackDetection::process
==============================================================================
*/

void  BoardGeneric::BindingAudioInJackDetection::process ()
{
   if (input_ptr->isConnected ())
   {
      *data_ptr = *db_ptr;
   }
   else
   {
      data_ptr->fill (board_ptr->npr () != 0);
   }
}



/*
==============================================================================
Name : BindingAudioOut::process
==============================================================================
*/

void  BoardGeneric::BindingAudioOut::process ()
{
   *db_ptr = *data_ptr;
}



/*
==============================================================================
Name : BindingAudioStereoIn::process
==============================================================================
*/

void  BoardGeneric::BindingAudioStereoIn::process ()
{
   *data_left_ptr = *db_left_ptr;
   *data_right_ptr = *db_right_ptr;
}



/*
==============================================================================
Name : BindingAudioStereoInJackDetection::process
==============================================================================
*/

void  BoardGeneric::BindingAudioStereoInJackDetection::process ()
{
   if (input_left_ptr->isConnected ())
   {
      *data_left_ptr = *db_left_ptr;
      *data_right_ptr = *db_right_ptr;
   }
   else
   {
      data_left_ptr->fill (board_ptr->npr () != 0);
      data_right_ptr->fill (board_ptr->npr () != 0);
   }
}



/*
==============================================================================
Name : BindingAudioStereoOut::process
==============================================================================
*/

void  BoardGeneric::BindingAudioStereoOut::process ()
{
   *db_left_ptr = *data_left_ptr;
   *db_right_ptr = *data_right_ptr;
}



/*
==============================================================================
Name : BindingButton::process
==============================================================================
*/

void  BoardGeneric::BindingButton::process ()
{
   *data_ptr = param_ptr->getValue () != 0.f;
}



/*
==============================================================================
Name : BindingCvIn::process
==============================================================================
*/

void  BoardGeneric::BindingCvIn::process ()
{
   if (bipolar)
   {
      *data_ptr = input_ptr->getVoltage () * 0.2f;
   }
   else
   {
      *data_ptr = input_ptr->getVoltage () * 0.1f + 0.5f;
   }
}



/*
==============================================================================
Name : BindingCvInJackDetection::process
==============================================================================
*/

void  BoardGeneric::BindingCvInJackDetection::process ()
{
   if (input_ptr->isConnected ())
   {
      if (bipolar)
      {
         *data_ptr = input_ptr->getVoltage () * 0.2f;
      }
      else
      {
         *data_ptr = input_ptr->getVoltage () * 0.1f + 0.5f;
      }
   }
   else
   {
      *data_ptr = float (board_ptr->npr () != 0);
   }
}



/*
==============================================================================
Name : BindingCvOut::process
==============================================================================
*/

void  BoardGeneric::BindingCvOut::process ()
{
   if (bipolar)
   {
      output_ptr->setVoltage (*data_ptr * 10.f - 5.f);
   }
   else
   {
      output_ptr->setVoltage (*data_ptr * 5.f);
   }
}



/*
==============================================================================
Name : BindingEncoderLeadingA::process
==============================================================================
*/

void  BoardGeneric::BindingEncoderLeadingA::process ()
{
   // Assume 24 notches per rotation
   int phase = int (std::floor (param_ptr->getValue () * 24.f * 4.f)) % 4;

   *data_a_ptr = (phase == 0) || (phase == 1);
   *data_b_ptr = (phase == 1) || (phase == 2);
}



/*
==============================================================================
Name : BindingEncoderLeadingB::process
==============================================================================
*/

void  BoardGeneric::BindingEncoderLeadingB::process ()
{
   // Assume 24 notches per rotation
   int phase = int (std::floor (param_ptr->getValue () * 24.f * 4.f)) % 4;

   *data_a_ptr = (phase == 1) || (phase == 2);
   *data_b_ptr = (phase == 0) || (phase == 1);
}



/*
==============================================================================
Name : BindingEncoderButtonLeadingA::process
==============================================================================
*/

void  BoardGeneric::BindingEncoderButtonLeadingA::process ()
{
   // Assume 24 notches per rotation
   int phase = int (std::floor (param_ab_ptr->getValue () * 24.f * 4.f)) % 4;

   *data_a_ptr = (phase == 0) || (phase == 1);
   *data_b_ptr = (phase == 1) || (phase == 2);

   *data_sw_ptr = param_sw_ptr->getValue () != 0.f;
}



/*
==============================================================================
Name : BindingEncoderButtonLeadingB::process
==============================================================================
*/

void  BoardGeneric::BindingEncoderButtonLeadingB::process ()
{
   // Assume 24 notches per rotation
   int phase = int (std::floor (param_ab_ptr->getValue () * 24.f * 4.f)) % 4;

   *data_a_ptr = (phase == 1) || (phase == 2);
   *data_b_ptr = (phase == 0) || (phase == 1);

   *data_sw_ptr = param_sw_ptr->getValue () != 0.f;
}



/*
==============================================================================
Name : BindingGateIn::process
==============================================================================
*/

void  BoardGeneric::BindingGateIn::process ()
{
   *data_ptr = input_ptr->getVoltage () > 0.1f;
}



/*
==============================================================================
Name : BindingGateInJackDetection::process
==============================================================================
*/

void  BoardGeneric::BindingGateInJackDetection::process ()
{
   if (input_ptr->isConnected ())
   {
      *data_ptr = input_ptr->getVoltage () > 0.1f;
   }
   else
   {
      *data_ptr = board_ptr->npr () != 0;
   }
}



/*
==============================================================================
Name : BindingGateOut::process
==============================================================================
*/

void  BoardGeneric::BindingGateOut::process ()
{
   output_ptr->setVoltage (float (*data_ptr) * 5.f);
}



/*
==============================================================================
Name : BindingLedFloat::process
==============================================================================
*/

void  BoardGeneric::BindingLedFloat::process ()
{
   light_ptr->setBrightness (*data_ptr);
}



/*
==============================================================================
Name : BindingLedBiFloat::process
==============================================================================
*/

void  BoardGeneric::BindingLedBiFloat::process ()
{
   light_r_ptr->setBrightness (*data_r_ptr);
   light_g_ptr->setBrightness (*data_g_ptr);
}



/*
==============================================================================
Name : BindingLedRgbFloat::process
==============================================================================
*/

void  BoardGeneric::BindingLedRgbFloat::process ()
{
   light_r_ptr->setBrightness (*data_r_ptr);
   light_g_ptr->setBrightness (*data_g_ptr);
   light_b_ptr->setBrightness (*data_b_ptr);
}



/*
==============================================================================
Name : BindingLedBool::process
==============================================================================
*/

void  BoardGeneric::BindingLedBool::process ()
{
   light_ptr->setBrightness (*data_ptr ? 1.f : 0.f);
}



/*
==============================================================================
Name : BindingLedBiBool::process
==============================================================================
*/

void  BoardGeneric::BindingLedBiBool::process ()
{
   light_r_ptr->setBrightness (*data_r_ptr ? 1.f : 0.f);
   light_g_ptr->setBrightness (*data_g_ptr ? 1.f : 0.f);
}



/*
==============================================================================
Name : BindingLedRgbBool::process
==============================================================================
*/

void  BoardGeneric::BindingLedRgbBool::process ()
{
   light_r_ptr->setBrightness (*data_r_ptr ? 1.f : 0.f);
   light_g_ptr->setBrightness (*data_g_ptr ? 1.f : 0.f);
   light_b_ptr->setBrightness (*data_b_ptr ? 1.f : 0.f);
}



/*
==============================================================================
Name : BindingPot::process
==============================================================================
*/

void  BoardGeneric::BindingPot::process ()
{
   // already acknowledging unipolar or bipolar, as this is set when
   // configure the pot in the simulator.
   *data_ptr = param_ptr->getValue ();
}



/*
==============================================================================
Name : BindingSwitch::process
==============================================================================
*/

void  BoardGeneric::BindingSwitch::process ()
{
   auto val = param_ptr->getValue () * scale;

   *data_0_ptr = val < 0.25f;
   *data_1_ptr = val > 0.75f;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
