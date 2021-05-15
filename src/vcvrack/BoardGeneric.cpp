/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"

#include <rack.hpp>

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : resize_params
==============================================================================
*/

void  BoardGeneric::resize_params (size_t nbr_buttons, size_t nbr_pots)
{
   _params.resize ({nbr_buttons, nbr_pots}, nullptr);
}



/*
==============================================================================
Name : resize_inputs
==============================================================================
*/

void  BoardGeneric::resize_inputs (size_t nbr_gate_ins, size_t nbr_cv_ins, size_t nbr_audio_ins)
{
   _inputs.resize ({nbr_gate_ins, nbr_cv_ins, nbr_audio_ins}, nullptr);
}



/*
==============================================================================
Name : resize_outputs
==============================================================================
*/

void  BoardGeneric::resize_outputs (size_t nbr_gate_outs, size_t nbr_cv_outs, size_t nbr_audio_outs)
{
   _outputs.resize ({nbr_gate_outs, nbr_cv_outs, nbr_audio_outs}, nullptr);
}



/*
==============================================================================
Name : resize_lights
==============================================================================
*/

void  BoardGeneric::resize_lights (size_t nbr_leds)
{
   _outputs.resize ({nbr_leds}, nullptr);
}



/*
==============================================================================
Name : nbr_params
==============================================================================
*/

size_t   BoardGeneric::nbr_params () const
{
   return _params.size ();
}



/*
==============================================================================
Name : nbr_inputs
==============================================================================
*/

size_t   BoardGeneric::nbr_inputs () const
{
   return _inputs.size ();
}



/*
==============================================================================
Name : nbr_outputs
==============================================================================
*/

size_t   BoardGeneric::nbr_outputs () const
{
   return _outputs.size ();
}



/*
==============================================================================
Name : nbr_lights
==============================================================================
*/

size_t   BoardGeneric::nbr_lights () const
{
   return _lights.size ();
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardGeneric::impl_bind (size_t idx, rack::engine::Param & param)
{
   _params [idx] = &param;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardGeneric::impl_bind (size_t idx, rack::engine::Input & input)
{
   _inputs [idx] = &input;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardGeneric::impl_bind (size_t idx, rack::engine::Output & output)
{
   _outputs [idx] = &output;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardGeneric::impl_bind (size_t idx, rack::engine::Light & light)
{
   _lights [idx] = &light;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_to_vcv_index
==============================================================================
*/

size_t   BoardGeneric::impl_to_vcv_index (const void * data) const
{
   return _to_vcv_index.at (data);
}



/*
==============================================================================
Name : impl_to_vcv_index
==============================================================================
*/

bool  BoardGeneric::impl_need_process ()
{
   return _audio_buffer_inputs [0].tell () == 0;
}



/*
==============================================================================
Name : impl_pull_audio_inputs
==============================================================================
*/

void  BoardGeneric::impl_pull_audio_inputs ()
{
   for (size_t i = 0 ; i < _audio_buffer_inputs.size () ; ++i)
   {
      auto & double_buffer = _audio_buffer_inputs [i];
      auto & audio_input = *_inputs (ROW_AUDIO_IN, i);

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
   for (size_t i = 0 ; i < _audio_buffer_outputs.size () ; ++i)
   {
      auto & double_buffer = _audio_buffer_outputs [i];
      auto & audio_output = *_outputs (ROW_AUDIO_OUT, i);

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
   convert_to_adc16_channels ();
   convert_to_buttons ();
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
   convert_from_gate_outputs ();
   convert_from_leds ();
   _clock.tick ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init
==============================================================================
*/

void  BoardGeneric::init ()
{
   setup_hw_representation (_buttons, _params.size (ROW_BUTTON));
   setup_hw_representation (_adc16_channels_pots, _params.size (ROW_POT));

   setup_hw_representation (_gate_inputs, _inputs.size (ROW_GATE_IN));
   setup_hw_representation (_adc16_channels_cvins, _inputs.size (ROW_CV_IN));
   setup_hw_representation (_audio_buffer_inputs, _inputs.size (ROW_AUDIO_IN));

   setup_hw_representation (_gate_outputs, _outputs.size (ROW_GATE_OUT));
   setup_hw_representation (_cv_outputs, _outputs.size (ROW_CV_OUT));
   setup_hw_representation (_audio_buffer_outputs, _outputs.size (ROW_AUDIO_OUT));

   setup_hw_representation (_leds, _lights.size (ROW_LED));
}



/*
==============================================================================
Name : convert_to_adc16_channels
==============================================================================
*/

void  BoardGeneric::convert_to_adc16_channels ()
{
   size_t o = 0;

   constexpr float float_to_u16 = 65535.f;

   for (size_t i = 0 ; i < NBR_POTS ; ++i, ++o)
   {
      auto norm_val = _params [i]->getValue ();
      norm_val = std::clamp (norm_val, 0.f, 1.f);
      _adc16_channels [o] = uint16_t (norm_val * float_to_u16);
   }

   for (size_t i = 0 ; i < NBR_CV_INPUTS ; ++i, ++o)
   {
      auto norm_val = _inputs [i]->getVoltage () * 0.1f + 0.5f;
      norm_val = std::clamp (norm_val, 0.f, 1.f);
      _adc16_channels [o] = uint16_t (norm_val * float_to_u16);
   }
}



/*
==============================================================================
Name : convert_to_buttons
==============================================================================
*/

void  BoardGeneric::convert_to_buttons ()
{
   size_t o = 0;

   for (size_t i = NBR_POTS ; i < NBR_PARAMS ; ++i, ++o)
   {
      auto norm_val = _params [i]->getValue ();
      _buttons [o] = norm_val > 0.1f ? 1 : 0;
   }
}



/*
==============================================================================
Name : convert_from_gate_outputs
==============================================================================
*/

void  BoardGeneric::convert_from_gate_outputs ()
{
   size_t o = 0;

   for (size_t i = 0 ; i < NBR_GATE_OUTPUTS ; ++i, ++o)
   {
      auto val = _gate_outputs [i];
      _outputs [o]->setVoltage (float (val) * 5.f);
   }
}



/*
==============================================================================
Name : convert_from_leds
==============================================================================
*/

void  BoardGeneric::convert_from_leds ()
{
   size_t o = 0;

   for (size_t i = 0 ; i < NBR_LEDS ; ++i, ++o)
   {
      auto val = _leds [i];
      _lights [o]->setBrightness (val);
   }
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
