/*****************************************************************************

      BoardKivu12.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardKivu12.h"

#include <rack.hpp>

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardKivu12::BoardKivu12 ()
{
   {
      size_t o = 0;

      for (size_t i = 0 ; i < NBR_POTS ; ++i, ++o)
      {
         _to_vcv_index [&_adc16_channels [o]] = i;
      }

      for (size_t i = 0 ; i < NBR_CV_INPUTS ; ++i)
      {
         _to_vcv_index [&_adc16_channels [o]] = i;
      }
   }

   {
      size_t o = 0;

      for (size_t i = NBR_POTS ; i < NBR_PARAMS ; ++i, ++o)
      {
         _to_vcv_index [&_buttons [o]] = i;
      }
   }

   {
      size_t o = 0;

      for (size_t i = 0 ; i < NBR_GATE_OUTPUTS ; ++i, ++o)
      {
         _to_vcv_index [&_outputs [o]] = i;
      }
   }

   {
      size_t o = 0;

      for (size_t i = 0 ; i < NBR_LEDS ; ++i, ++o)
      {
         _to_vcv_index [&_lights [o]] = i;
      }
   }

   {
      size_t o = 0;

      for (size_t i = NBR_CV_INPUTS ; i < NBR_INPUTS ; ++i, ++o)
      {
         _to_vcv_index [&_audio_buffer_inputs [o]] = i;
      }
   }

   {
      size_t o = 0;

      for (size_t i = NBR_GATE_OUTPUTS ; i < NBR_OUTPUTS ; ++i, ++o)
      {
         _to_vcv_index [&_audio_buffer_outputs [o]] = i;
      }
   }
}



/*
==============================================================================
Name : nbr_params
==============================================================================
*/

size_t   BoardKivu12::nbr_params () const
{
   return NBR_PARAMS;
}



/*
==============================================================================
Name : nbr_inputs
==============================================================================
*/

size_t   BoardKivu12::nbr_inputs () const
{
   return NBR_INPUTS;
}



/*
==============================================================================
Name : nbr_outputs
==============================================================================
*/

size_t   BoardKivu12::nbr_outputs () const
{
   return NBR_OUTPUTS;
}



/*
==============================================================================
Name : nbr_lights
==============================================================================
*/

size_t   BoardKivu12::nbr_lights () const
{
   return NBR_LIGHTS;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardKivu12::impl_bind (size_t idx, rack::engine::Param & param)
{
   _params [idx] = &param;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardKivu12::impl_bind (size_t idx, rack::engine::Input & input)
{
   _inputs [idx] = &input;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardKivu12::impl_bind (size_t idx, rack::engine::Output & output)
{
   _outputs [idx] = &output;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  BoardKivu12::impl_bind (size_t idx, rack::engine::Light & light)
{
   _lights [idx] = &light;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_to_vcv_index
==============================================================================
*/

size_t   BoardKivu12::impl_to_vcv_index (const void * data) const
{
   return _to_vcv_index.at (data);
}



/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  BoardKivu12::impl_process ()
{
   constexpr uint64_t sample_rate_ull = uint64_t (erb_SAMPLE_RATE);
   constexpr uint64_t buffer_size_ull = erb_BUFFER_SIZE;

   for (auto input_ptr : _audio_inputs) input_ptr->impl_pull_sample ();

   auto buffer_phase = _now_spl % buffer_size_ull;

   if (buffer_phase == 0)
   {
      _now_ms = (_now_spl * 1000) / sample_rate_ull;

      _listeners.notify_audio_buffer_start ();
      _buffer_callback ();
      _listeners.notify_audio_buffer_end ();
   }

   ++_now_spl;

   for (auto output_ptr : _audio_outputs) output_ptr->impl_push_sample ();
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  BoardKivu12::impl_notify_audio_buffer_start ()
{
   convert_to_adc16_channels ();
   convert_to_buttons ();
}



/*
==============================================================================
Name : impl_notify_audio_buffer_end
==============================================================================
*/

void  BoardKivu12::impl_notify_audio_buffer_end ()
{
   convert_from_gate_outputs ();
   convert_from_leds ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : convert_to_adc16_channels
==============================================================================
*/

void  BoardKivu12::convert_to_adc16_channels ()
{
   size_t o = 0;

   constexpr float float_to_u16 = 65535.f;

   for (size_t i = 0 ; i < NBR_POTS ; ++i, ++o)
   {
      auto norm_val = _params [i]->getValue ();
      norm_val = std::clamp (norm_val, 0.f, 1.f);
      _adc16_channels [o] = uint16_t (norm_val * float_to_u16);
   }

   for (size_t i = 0 ; i < NBR_CV_INPUTS ; ++i)
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

void  BoardKivu12::convert_to_buttons ()
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

void  BoardKivu12::convert_from_gate_outputs ()
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

void  BoardKivu12::convert_from_leds ()
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
