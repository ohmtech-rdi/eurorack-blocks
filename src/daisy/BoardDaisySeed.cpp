/*****************************************************************************

      BoardDaisySeed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardDaisySeed.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardDaisySeed::BoardDaisySeed ()
{
   enable_fz ();

   _this_ptr = this;

   _seed.Configure ();
   _seed.Init (true /* boost */);

   for (auto & buffer : _audio_buffer_inputs) buffer.fill (0.f);
   for (auto & buffer : _audio_buffer_outputs) buffer.fill (0.f);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisySeed::impl_preprocess ()
{

}



/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  BoardDaisySeed::impl_process ()
{
   _process ();
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardGeneric::impl_postprocess ()
{
   

   _clock.tick ();
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

void  BoardDaisySeed::enable_fz ()
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

void  BoardDaisySeed::do_run ()
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

void  BoardDaisySeed::audio_callback_proc (float ** in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  BoardDaisySeed::audio_callback (float ** in, float ** out, size_t /* size */)
{
   process_audio_inputs (_audio_buffer_inputs, in);

   _run ();

   process_audio_outputs (out, _audio_buffer_outputs);
}



/*
==============================================================================
Name : process_audio_inputs
Description :
   Map eurorack audio level (-5V, 5V) to (-1.f, 1.f)
==============================================================================
*/

void  BoardDaisySeed::process_audio_inputs (AudioBufferInputs & buffer_inputs, float ** in)
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
Name : process_audio_outputs
Description :
   Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   10V / (0.7 x 3.3V x 10) = 0.433
==============================================================================
*/

void  BoardDaisySeed::process_audio_outputs (float ** out, AudioBufferOutputs & buffer_outputs)
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



BoardDaisySeed * BoardDaisySeed::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
