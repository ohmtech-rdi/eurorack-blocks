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
   enable_fz ();

   _this_ptr = this;

   init ();

   _audio.SetBlockSize (erb_BUFFER_SIZE);
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

void  SubmoduleDaisyPatchSm::enable_fz ()
{
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);
}



/*
==============================================================================
Name : init
==============================================================================
*/

void  SubmoduleDaisyPatchSm::init ()
{
   init_system ();
   init_sdram ();
   init_qspi ();
   init_audio ();
}



/*
==============================================================================
Name : init_system
==============================================================================
*/

void  SubmoduleDaisyPatchSm::init_system ()
{
   daisy::System::Config config;

   config.Defaults ();
   _system.Init (config);
}



/*
==============================================================================
Name : init_sdram
==============================================================================
*/

void  SubmoduleDaisyPatchSm::init_sdram ()
{
   _sdram.state = DSY_SDRAM_STATE_ENABLE;
   _sdram.pin_config [DSY_SDRAM_PIN_SDNWE] = {DSY_GPIOH, 5};

   dsy_sdram_init (&_sdram);
}



/*
==============================================================================
Name : init_qspi
==============================================================================
*/

void  SubmoduleDaisyPatchSm::init_qspi ()
{
   erb_DISABLE_WARNINGS_DAISY

   using namespace daisy;

   _qspi.Init (QSPIHandle::Config {
      .pin_config = {
         .io0 = {DSY_GPIOF, 8},
         .io1 = {DSY_GPIOF, 9},
         .io2 = {DSY_GPIOF, 7},
         .io3 = {DSY_GPIOF, 6},
         .clk = {DSY_GPIOF, 10},
         .ncs = {DSY_GPIOG, 6}
      },
      .device = QSPIHandle::Config::Device::IS25LP064A,
      .mode = QSPIHandle::Config::Mode::MEMORY_MAPPED
   });

   erb_RESTORE_WARNINGS
}



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
