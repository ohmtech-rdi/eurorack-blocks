/*****************************************************************************

      SubmoduleDaisySeed2Dfm.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/SubmoduleDaisySeed2Dfm.h"

#include "dev/codec_ak4556.h"

#undef erb_DAISY_HEARTBEAT



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

SubmoduleDaisySeed2Dfm::SubmoduleDaisySeed2Dfm ()
{
   _this_ptr = this;

   init_audio ();

   _audio.SetAudioBlockSize (erb_BUFFER_SIZE);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_audio
==============================================================================
*/

void  SubmoduleDaisySeed2Dfm::init_audio ()
{
   erb_DISABLE_WARNINGS_DAISY

   using namespace daisy;

   SaiHandle sai_1_handle;
   sai_1_handle.Init (SaiHandle::Config {
      .periph = SaiHandle::Config::Peripheral::SAI_1,
      .pin_config = {
         .mclk = {DSY_GPIOE, 2},
         .fs = {DSY_GPIOE, 4},
         .sck = {DSY_GPIOE, 5},
         .sa = {DSY_GPIOE, 6},
         .sb = {DSY_GPIOE, 3}
      },
      .sr = SaiHandle::Config::SampleRate::SAI_48KHZ,
      .bit_depth = SaiHandle::Config::BitDepth::SAI_24BIT,
      .a_sync = SaiHandle::Config::Sync::MASTER,
      .b_sync = SaiHandle::Config::Sync::SLAVE,
      .a_dir = SaiHandle::Config::Direction::TRANSMIT,
      .b_dir = SaiHandle::Config::Direction::RECEIVE,
   });

   // PCM3060 disable deemphasis pin
   dsy_gpio codec_deemphasis = {
      .pin = {DSY_GPIOB, 11},
      .mode = DSY_GPIO_MODE_OUTPUT_PP,
      .pull = DSY_GPIO_NOPULL,
   };
   dsy_gpio_init (&codec_deemphasis);
   dsy_gpio_write (&codec_deemphasis, 0);
   // don't deinit GPIO

   _audio.Init (
      {
         .blocksize = 48,
         .samplerate = SaiHandle::Config::SampleRate::SAI_48KHZ,
         .postgain = 1.f,
      },
      sai_1_handle
   );

   erb_RESTORE_WARNINGS
}



/*
==============================================================================
Name : do_run
==============================================================================
*/

void  SubmoduleDaisySeed2Dfm::do_run ()
{
   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  SubmoduleDaisySeed2Dfm::audio_callback_proc (const float * const * in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  SubmoduleDaisySeed2Dfm::audio_callback (const float * const * in, float ** out, size_t /* size */)
{
   raw_audio_inputs = in;
   raw_audio_outputs = out;

   _run ();

   _clock.tick ();

#if defined (erb_DAISY_HEARTBEAT)
   static uint16_t phase = 0;
   phase += 100;
   _seed.SetLed (phase < 32000);
#endif
}



SubmoduleDaisySeed2Dfm * SubmoduleDaisySeed2Dfm::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
