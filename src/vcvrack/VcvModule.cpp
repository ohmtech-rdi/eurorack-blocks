/*****************************************************************************

      VcvModule.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvModule.h"

#include "erb/vcvrack/VcvAudioInDaisy.h"
#include "erb/vcvrack/VcvAudioOutDaisy.h"
#include "erb/vcvrack/VcvInputBase.h"
#include "erb/vcvrack/VcvLightBase.h"
#include "erb/vcvrack/VcvOutputBase.h"
#include "erb/vcvrack/VcvParamBase.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : nbr_params
==============================================================================
*/

size_t   VcvModule::nbr_params () const
{
   return _params.size ();
}



/*
==============================================================================
Name : nbr_inputs
==============================================================================
*/

size_t   VcvModule::nbr_inputs () const
{
   return _inputs.size ();
}



/*
==============================================================================
Name : nbr_outputs
==============================================================================
*/

size_t   VcvModule::nbr_outputs () const
{
   return _outputs.size ();
}



/*
==============================================================================
Name : nbr_lights
==============================================================================
*/

size_t   VcvModule::nbr_lights () const
{
   return _lights.size ();
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  VcvModule::impl_bind (size_t idx, rack::engine::Param & param)
{
   _params [idx]->impl_bind (idx, param);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  VcvModule::impl_bind (size_t idx, rack::engine::Input & input)
{
   _inputs [idx]->impl_bind (idx, input);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  VcvModule::impl_bind (size_t idx, rack::engine::Output & output)
{
   _outputs [idx]->impl_bind (idx, output);
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  VcvModule::impl_bind (size_t idx, rack::engine::Light & light)
{
   _lights [idx]->impl_bind (idx, light);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : now_ms
==============================================================================
*/

uint64_t VcvModule::now_ms ()
{
   return _now_ms;
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  VcvModule::add (VcvParamBase & param)
{
   _params.push_back (&param);
   _listeners.add (param);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  VcvModule::add (VcvInputBase & input)
{
   _inputs.push_back (&input);
   _listeners.add (input);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  VcvModule::add (VcvOutputBase & output)
{
   _outputs.push_back (&output);
   _listeners.add (output);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  VcvModule::add (VcvLightBase & light)
{
   _lights.push_back (&light);
   _listeners.add (light);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  VcvModule::add (VcvAudioInDaisy & input)
{
   _audio_inputs.push_back (&input);
   _inputs.push_back (&input);
   _listeners.add (input);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  VcvModule::add (VcvAudioOutDaisy & output)
{
   _audio_outputs.push_back (&output);
   _outputs.push_back (&output);
   _listeners.add (output);
}



/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  VcvModule::impl_process ()
{
   constexpr uint64_t sample_rate_ull = uint64_t (sample_rate);
   constexpr uint64_t buffer_size_ull = buffer_size;

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



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
