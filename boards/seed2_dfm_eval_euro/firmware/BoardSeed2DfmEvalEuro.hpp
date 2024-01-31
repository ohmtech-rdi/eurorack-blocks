/*****************************************************************************

      BoardSeed2DfmEvalEuro.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/CvOut.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/Led.h"
#include "erb/LedBi.h"
#include "erb/LedRgb.h"
#include "erb/Pot.h"
#include "erb/Switch.h"
#include "erb/detail/fnc.h"

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardSeed2DfmEvalEuro::BoardSeed2DfmEvalEuro ()
:  _display (_display_transport, _oled_buffer)
{
   _this_ptr = this;

   init_qspi ();
   init_audio ();
   init_display ();
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename F>
void  BoardSeed2DfmEvalEuro::run (F && f)
{
   _run = std::forward <F> (f);

   _adc_hnd.Start ();
   _audio.Start (audio_callback_proc);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_preprocess (GpiPin pin)
{
   if (pin.index == GI1.index)
   {
       // BJT => inverted
      _digital_inputs [pin.index] = !_gpio_inputs [pin.index].read ();
   }
   else if ((pin.index >= B1.index) && (pin.index <= B3.index))
   {
       // Pull-up when NO => inverted
      _digital_inputs [pin.index] = !_gpio_inputs [pin.index].read ();
   }
   else if ((pin.index >= B4.index) && (pin.index <= B5.index))
   {
       // Encoder A & B
      _digital_inputs [pin.index] = _gpio_inputs [pin.index].read ();
   }
   else if (pin.index == B6.index)
   {
      // Encoder Switch
      // Pull-up when NO => inverted
      _digital_inputs [pin.index] = !_gpio_inputs [pin.index].read ();
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_preprocess (AdcPin pin)
{
   if ((pin.index >= CI1.index) && (pin.index <= CI3.index))
   {
      // OpAmp inverter/adder with voltage reference

      _analog_inputs [pin.index] = 1.f - to_float_norm (_adc.read (pin.index));
   }
   else if ((pin.index >= P1.index) && (pin.index <= P4.index))
   {
      _analog_inputs [pin.index] = to_float_norm (_adc.read (pin.index));
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_preprocess (AudioInPin pin)
{
   scale (
      _audio_inputs [pin.index],
      raw_audio_inputs [pin.index],
      1.429f
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_postprocess (GpoPin pin)
{
   // Nothing
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_postprocess (DacPin pin)
{
   _dac.write (pin.index, norm_to_u12 (_analog_outputs [pin.index]));
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_postprocess (AudioOutPin pin)
{
   scale (
      raw_audio_outputs [pin.index],
      _audio_outputs [pin.index],
      0.577f
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_postprocess (OledBus)
{
   // Nothing
}



/*
==============================================================================
Name : impl_idle
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::impl_idle ()
{
   _display.update ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_qspi
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::init_qspi ()
{
   _qspi.Init (daisy::QSPIHandle::Config {
      .pin_config = {
         .io0 = {DSY_GPIOF, 8},
         .io1 = {DSY_GPIOF, 9},
         .io2 = {DSY_GPIOF, 7},
         .io3 = {DSY_GPIOF, 6},
         .clk = {DSY_GPIOF, 10},
         .ncs = {DSY_GPIOG, 6}
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

void  BoardSeed2DfmEvalEuro::init_audio ()
{
   erb_DISABLE_WARNINGS_DAISY

   using namespace daisy;

   // "Internal" PCM3060 codec

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
   dsy_gpio codec_1_deemphasis = {
      .pin = {DSY_GPIOB, 11},
      .mode = DSY_GPIO_MODE_OUTPUT_PP,
      .pull = DSY_GPIO_NOPULL,
   };
   dsy_gpio_init (&codec_1_deemphasis);
   dsy_gpio_write (&codec_1_deemphasis, 0);
   // don't deinit GPIO

   // "External" PCM3060 codec

   SaiHandle sai_2_handle;
   sai_2_handle.Init (SaiHandle::Config {
      .periph = SaiHandle::Config::Peripheral::SAI_2,
      .pin_config = {
         .mclk = {DSY_GPIOA, 1},
         .fs = {DSY_GPIOG, 9},
         .sck = {DSY_GPIOA, 2},
         .sa = {DSY_GPIOD, 11},
         .sb = {DSY_GPIOA, 0}
      },
      .sr = SaiHandle::Config::SampleRate::SAI_48KHZ,
      .bit_depth = SaiHandle::Config::BitDepth::SAI_24BIT,
      .a_sync = SaiHandle::Config::Sync::SLAVE,
      .b_sync = SaiHandle::Config::Sync::MASTER,
      .a_dir = SaiHandle::Config::Direction::TRANSMIT,
      .b_dir = SaiHandle::Config::Direction::RECEIVE,
   });

   // PCM3060 disable deemphasis pin put to GND in hardware

   static_assert (erb_SAMPLE_RATE == 48014);
   AudioHandle::Config config_audio;
   config_audio.blocksize = erb_BUFFER_SIZE;
   config_audio.samplerate = SaiHandle::Config::SampleRate::SAI_48KHZ;
   config_audio.postgain = 1.f;
   config_audio.output_compensation = 1.f;

   _audio.Init (
      config_audio,
      sai_1_handle,
      sai_2_handle
   );

   erb_RESTORE_WARNINGS
}



/*
==============================================================================
Name : init_display
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::init_display ()
{
   erb_DISABLE_WARNINGS_DAISY

   using namespace daisy;

   SSD130x4WireSpiTransport::Config transport_config;
   transport_config.spi_config.pin_config = {
      .sclk = SubmoduleDaisySeed2Dfm::B2,
      .miso = SubmoduleDaisySeed2Dfm::PinNC,
      .mosi = SubmoduleDaisySeed2Dfm::B4,
      .nss = SubmoduleDaisySeed2Dfm::B6,
   };
   transport_config.spi_config.periph = SpiHandle::Config::Peripheral::SPI_1;
   transport_config.spi_config.mode = SpiHandle::Config::Mode::MASTER;
   transport_config.spi_config.direction = SpiHandle::Config::Direction::TWO_LINES_TX_ONLY;
   transport_config.spi_config.datasize = 8;
   transport_config.spi_config.clock_polarity = SpiHandle::Config::ClockPolarity::LOW;
   transport_config.spi_config.clock_phase = SpiHandle::Config::ClockPhase::ONE_EDGE;
   transport_config.spi_config.nss = SpiHandle::Config::NSS::HARD_OUTPUT;
   transport_config.spi_config.baud_prescaler = SpiHandle::Config::BaudPrescaler::PS_8;
   transport_config.pin_config.dc = SubmoduleDaisySeed2Dfm::D9;
   transport_config.pin_config.reset = SubmoduleDaisySeed2Dfm::D8;

   _display_transport.Init (transport_config);
   _display.init ();

   erb_RESTORE_WARNINGS
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::audio_callback_proc (const float * const * in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  BoardSeed2DfmEvalEuro::audio_callback (const float * const * in, float ** out, size_t /* size */)
{
   raw_audio_inputs = in;
   raw_audio_outputs = out;

   _run ();

   _clock.tick ();
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
