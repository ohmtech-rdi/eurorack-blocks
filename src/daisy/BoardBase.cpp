/*****************************************************************************

      BoardBase.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardBase.h"



namespace erb
{
namespace daisy
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardBase::BoardBase ()
{
   enable_fz ();

   _this_ptr = this;

   _seed.Configure ();
   _seed.Init (true /* boost */);

   for (auto & buffer : _buffer_inputs) buffer.fill (0.f);
   for (auto & buffer : _buffer_outputs) buffer.fill (0.f);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : enable_fz
Description :
   Enable FZ (flush-to-zero) denormal behavior
==============================================================================
*/

void  BoardBase::enable_fz ()
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

void  BoardBase::do_run ()
{
   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);

   for (;;) {}
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  BoardBase::audio_callback_proc (float ** in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  BoardBase::audio_callback (float ** in, float ** out, size_t /* size */)
{
   process_inputs (_buffer_inputs, in);

   _clock_ms = (_clock_spl * 1000) / uint64_t (erb_SAMPLE_RATE);
   _clock_spl += uint64_t (erb_BUFFER_SIZE);

   do_notify_audio_buffer_start ();

   _buffer_callback ();

   do_notify_audio_buffer_end ();

   process_outputs (out, _buffer_outputs);
}



/*
==============================================================================
Name : process_inputs
Description :
   Map eurorack audio level (-5V, 5V) to (-1.f, 1.f)
==============================================================================
*/

void  BoardBase::process_inputs (BufferInputs & buffer_inputs, float ** in)
{
   constexpr float gain_in = 2.3f;

   for (size_t i = 0 ; i < NBR_AUDIO_CHANNELS ; ++i)
   {
      auto & buffer = buffer_inputs [i];
      const auto & in_arr = in [i];

      for (size_t j = 0 ; j < erb_BUFFER_SIZE ; ++j)
      {
         buffer [j] = gain_in * in_arr [j];
      }
   }
}



/*
==============================================================================
Name : process_outputs
Description :
   Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   10V / (0.7 x 3.3V x 10) = 0.433
==============================================================================
*/

void  BoardBase::process_outputs (float ** out, BufferOutputs & buffer_outputs)
{
   constexpr float gain_out = 0.433f;

   for (size_t i = 0 ; i < NBR_AUDIO_CHANNELS ; ++i)
   {
      auto & out_arr = out [i];
      const auto & buffer = buffer_outputs [i];

      for (size_t j = 0 ; j < erb_BUFFER_SIZE ; ++j)
      {
         out_arr [j] = gain_out * buffer [j];
      }
   }
}



BoardBase * BoardBase::_this_ptr = nullptr;



}  // namespace daisy
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
