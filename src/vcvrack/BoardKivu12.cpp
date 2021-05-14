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



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  BoardKivu12::impl_process ()
{
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
