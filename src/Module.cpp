/*****************************************************************************

      Module.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Module.h"

#include "erb/CvIn.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/Led.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Module::Module ()
:  _adc_channels (_seed)
{
   enable_fz ();

   _this_ptr = this;

   const bool boost = false;

   _seed.Configure ();
   _seed.Init (boost);

   for (auto & frame : _onboard_codec_buffer_output) frame.fill (0.f);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : now_ms
==============================================================================
*/

uint32_t Module::now_ms ()
{
   return _seed.system.GetNow ();
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  Module::add (AnalogControlBase & control, const Pin & pin)
{
   _adc_channels.add (control, pin);
   _listeners.add (control);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  Module::add (ModuleListener & listener)
{
   _listeners.add (listener);
}



/*
==============================================================================
Name : impl_onboard_codec_buffer_input
==============================================================================
*/

const Module::Buffer &  Module::impl_onboard_codec_buffer_input () const
{
   return _onboard_codec_buffer_input;
}



/*
==============================================================================
Name : impl_onboard_codec_buffer_output
==============================================================================
*/

Module::Buffer &  Module::impl_onboard_codec_buffer_output ()
{
   return _onboard_codec_buffer_output;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : enable_fz
Description :
   Enable FZ (flush-to-zero) denormal behavior
==============================================================================
*/

void  Module::enable_fz ()
{
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);
}



/*
==============================================================================
Name : do_run
==============================================================================
*/

void  Module::do_run ()
{
   _adc_channels.init ();

   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);

   for (;;) {}
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  Module::audio_callback_proc (float ** in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  Module::audio_callback (float ** in, float ** out, size_t /* size */)
{
   // Map eurorack audio level (-5V, 5V) to (-1.f, 1.f)
   constexpr float gain_in = 2.3f;

   for (size_t i = 0 ; i < onboard_codec_nbr_channel ; ++i)
   {
      auto & frame = _onboard_codec_buffer_input [i];
      const auto & in_arr = in [i];

      for (size_t j = 0 ; j < buffer_size ; ++j)
      {
         frame [j] = gain_in * in_arr [j];
      }
   }

   _listeners.notify_audio_buffer_start ();

   _buffer_callback ();

   _listeners.notify_audio_buffer_end ();

   // Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   // 10V / (0.7 x 3.3V x 10) = 0.433
   constexpr float gain_out = 0.433f;

   for (size_t i = 0 ; i < onboard_codec_nbr_channel ; ++i)
   {
      auto & out_arr = out [i];
      const auto & frame = _onboard_codec_buffer_output [i];

      for (size_t j = 0 ; j < buffer_size ; ++j)
      {
         out_arr [j] = gain_out * frame [j];
      }
   }
}



Module * Module::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
