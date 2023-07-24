/*****************************************************************************

      SubmoduleDaisySeed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/SubmoduleDaisySeed.h"

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

SubmoduleDaisySeed::SubmoduleDaisySeed ()
{
   _this_ptr = this;

   init_audio ();

   _seed.SetAudioBlockSize (erb_BUFFER_SIZE);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_audio
==============================================================================
*/

void  SubmoduleDaisySeed::init_audio ()
{
   daisy::SaiHandle::Config sai_config;
   sai_config.periph          = daisy::SaiHandle::Config::Peripheral::SAI_1;
   sai_config.sr              = daisy::SaiHandle::Config::SampleRate::SAI_48KHZ;
   sai_config.bit_depth       = daisy::SaiHandle::Config::BitDepth::SAI_24BIT;
   sai_config.a_sync          = daisy::SaiHandle::Config::Sync::MASTER;
   sai_config.b_sync          = daisy::SaiHandle::Config::Sync::SLAVE;
   sai_config.a_dir           = daisy::SaiHandle::Config::Direction::TRANSMIT;
   sai_config.b_dir           = daisy::SaiHandle::Config::Direction::RECEIVE;
   sai_config.pin_config.fs   = {DSY_GPIOE, 4};
   sai_config.pin_config.mclk = {DSY_GPIOE, 2};
   sai_config.pin_config.sck  = {DSY_GPIOE, 5};
   sai_config.pin_config.sa   = {DSY_GPIOE, 6};
   sai_config.pin_config.sb   = {DSY_GPIOE, 3};

   daisy::SaiHandle sai_1_handle;
   sai_1_handle.Init (sai_config);

   dsy_gpio_pin codec_reset_pin;
   codec_reset_pin = {DSY_GPIOB, 11};
   daisy::Ak4556::Init (codec_reset_pin);

   daisy::AudioHandle::Config audio_config;
   audio_config.blocksize  = 48;
   audio_config.samplerate = daisy::SaiHandle::Config::SampleRate::SAI_48KHZ;
   audio_config.postgain   = 1.f;
   _seed.audio_handle.Init (audio_config, sai_1_handle);
}



/*
==============================================================================
Name : do_run
==============================================================================
*/

void  SubmoduleDaisySeed::do_run ()
{
   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  SubmoduleDaisySeed::audio_callback_proc (const float * const * in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  SubmoduleDaisySeed::audio_callback (const float * const * in, float ** out, size_t /* size */)
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



SubmoduleDaisySeed * SubmoduleDaisySeed::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
