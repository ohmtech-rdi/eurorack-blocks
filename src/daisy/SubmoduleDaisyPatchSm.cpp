/*****************************************************************************

      SubmoduleDaisyPatchSm.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/SubmoduleDaisyPatchSm.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

SubmoduleDaisyPatchSm::SubmoduleDaisyPatchSm ()
{
   _this_ptr = this;

   init_audio ();

   _audio.SetBlockSize (erb_BUFFER_SIZE);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_audio
==============================================================================
*/

void  SubmoduleDaisyPatchSm::init_audio ()
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
      .a_dir = SaiHandle::Config::Direction::RECEIVE,
      .b_dir = SaiHandle::Config::Direction::TRANSMIT,
   });

   I2CHandle i2c2;
   i2c2.Init ({
      .periph = I2CHandle::Config::Peripheral::I2C_2,
      .pin_config = {
         .scl = {DSY_GPIOB, 10},
         .sda = {DSY_GPIOB, 11},
      },
      .speed = I2CHandle::Config::Speed::I2C_400KHZ,
      .mode = I2CHandle::Config::Mode::I2C_MASTER
   });

   _codec.Init (i2c2);

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

void  SubmoduleDaisyPatchSm::do_run ()
{
   _adc.Start ();
   _audio.Start (audio_callback_proc);

   for (;;) {}
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  SubmoduleDaisyPatchSm::audio_callback_proc (const float * const * in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  SubmoduleDaisyPatchSm::audio_callback (const float * const * in, float ** out, size_t /* size */)
{
   raw_audio_inputs = in;
   raw_audio_outputs = out;

   _run ();

   _clock.tick ();
}



SubmoduleDaisyPatchSm * SubmoduleDaisyPatchSm::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
