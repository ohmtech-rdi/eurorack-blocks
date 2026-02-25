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

   init_qspi ();
   init_audio ();

   _audio.SetBlockSize (erb_BUFFER_SIZE);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_qspi
==============================================================================
*/

void  SubmoduleDaisyPatchSm::init_qspi ()
{
   _qspi.Init (daisy::QSPIHandle::Config {
      .pin_config = {
         .io0 = {daisy::PORTF, 8},
         .io1 = {daisy::PORTF, 9},
         .io2 = {daisy::PORTF, 7},
         .io3 = {daisy::PORTF, 6},
         .clk = {daisy::PORTF, 10},
         .ncs = {daisy::PORTG, 6}
      },
      .device = daisy::QSPIHandle::Config::Device::IS25LP064A,
      .mode = daisy::QSPIHandle::Config::Mode::MEMORY_MAPPED
   });
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
         .mclk = {daisy::PORTE, 2},
         .fs = {daisy::PORTE, 4},
         .sck = {daisy::PORTE, 5},
         .sa = {daisy::PORTE, 6},
         .sb = {daisy::PORTE, 3}
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
         .scl = {daisy::PORTB, 10},
         .sda = {daisy::PORTB, 11},
      },
      .speed = I2CHandle::Config::Speed::I2C_400KHZ,
      .mode = I2CHandle::Config::Mode::I2C_MASTER
   });

   _codec.Init (i2c2);

   _audio.Init (
      AudioHandle::Config {}, // block 48 @48kHz, unit gains
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
