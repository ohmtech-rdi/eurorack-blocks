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
   else if ((pin.index >= B1.index) && (pin.index <= B5.index))
   {
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
   if ((pin.index >= AI1.index) && (pin.index <= AI2.index))
   {
      scale (
         _audio_inputs [pin.index],
         _submodule.raw_audio_inputs [pin.index],
         _submodule.gain_input_scaling
      );
   }
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
   if ((pin.index >= AO1.index) && (pin.index <= AO2.index))
   {
      scale (
         _submodule.raw_audio_outputs [pin.index],
         _audio_outputs [pin.index],
         _submodule.gain_output_scaling
      );
   }
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



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
