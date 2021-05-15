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
   _nbr_buttons = nbr_buttons;
   _nbr_pots = nbr_pots;

   _params.resize ({nbr_buttons, nbr_pots}, nullptr);
}



/*
==============================================================================
Name : resize_inputs
==============================================================================
*/

void  BoardGeneric::resize_inputs (size_t nbr_gate_ins, size_t nbr_cv_ins, size_t nbr_audio_ins)
{
   _nbr_gate_ins = nbr_gate_ins;
   _nbr_cv_ins = nbr_cv_ins;
   _nbr_audio_ins = nbr_audio_ins;

   _inputs.resize ({nbr_gate_ins, nbr_cv_ins, nbr_audio_ins}, nullptr);
}



/*
==============================================================================
Name : resize_outputs
==============================================================================
*/

void  BoardGeneric::resize_outputs (size_t nbr_gate_outs, size_t nbr_cv_outs, size_t nbr_audio_outs)
{
   _nbr_gate_outs = nbr_gate_outs;
   _nbr_cv_outs = nbr_cv_outs;
   _nbr_audio_outs = nbr_audio_outs;

   _outputs.resize ({nbr_gate_outs, nbr_cv_outs, nbr_audio_outs}, nullptr);
}



/*
==============================================================================
Name : resize_lights
==============================================================================
*/

void  BoardGeneric::resize_lights (size_t nbr_leds)
{
   _nbr_leds = nbr_leds;

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
   for (size_t i = 0 ; i < _digital_inputs.size (HW_ROW_BUTTON) ; ++i)
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
   }
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
   for (size_t i = 0 ; i < _digital_outputs.size (HW_ROW_GATE_OUT) ; ++i)
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
   }

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
   init_digital_inputs ();
   init_analog_inputs ();
   init_audio_inputs ();

   init_digital_outputs ();
   init_analog_outputs ();
   init_audio_outputs ();
}



/*
==============================================================================
Name : init_digital_inputs
==============================================================================
*/

void  BoardGeneric::init_digital_inputs ()
{
   _digital_inputs.resize ({_nbr_buttons, _nbr_gate_ins}, 0);

   setup_hw_representation (
      _digital_inputs, HW_ROW_BUTTON,
      _params, VCV_ROW_BUTTON
   );

   setup_hw_representation (
      _digital_inputs, HW_ROW_GATE_IN,
      _inputs, VCV_ROW_GATE_IN
   );
}



/*
==============================================================================
Name : init_analog_inputs
==============================================================================
*/

void  BoardGeneric::init_analog_inputs ()
{
   _analog_inputs.resize ({_nbr_pots, _nbr_cv_ins}, 0);

   setup_hw_representation (
      _analog_inputs, HW_ROW_POTS,
      _params, VCV_ROW_POT
   );

   setup_hw_representation (
      _analog_inputs, HW_ROW_CV_IN,
      _inputs, VCV_ROW_CV_IN
   );
}



/*
==============================================================================
Name : init_audio_inputs
==============================================================================
*/

void  BoardGeneric::init_audio_inputs ()
{
   _audio_inputs.resize ({_nbr_audio_ins}, Buffer {});

   setup_hw_representation (
      _audio_inputs, HW_ROW_AUDIO_IN,
      _inputs, VCV_ROW_AUDIO_IN
   );
}



/*
==============================================================================
Name : init_digital_outputs
==============================================================================
*/

void  BoardGeneric::init_digital_outputs ()
{
   _digital_outputs.resize ({_nbr_gate_outs}, 0);

   setup_hw_representation (
      _digital_outputs, HW_ROW_GATE_OUT,
      _outputs, VCV_ROW_GATE_OUT
   );
}



/*
==============================================================================
Name : init_analog_outputs
==============================================================================
*/

void  BoardGeneric::init_analog_outputs ()
{
   _analog_outputs.resize ({_nbr_cv_outs, _nbr_leds}, 0);

   setup_hw_representation (
      _analog_outputs, HW_ROW_CV_OUT,
      _outputs, VCV_ROW_CV_OUT
   );

   setup_hw_representation (
      _analog_outputs, HW_ROW_LED,
      _lights, VCV_ROW_LED
   );
}



/*
==============================================================================
Name : init_audio_outputs
==============================================================================
*/

void  BoardGeneric::init_audio_outputs ()
{
   _audio_outputs.resize ({_nbr_audio_outs}, Buffer {});

   setup_hw_representation (
      _audio_outputs, HW_ROW_AUDIO_OUT,
      _outputs, VCV_ROW_AUDIO_OUT
   );
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
