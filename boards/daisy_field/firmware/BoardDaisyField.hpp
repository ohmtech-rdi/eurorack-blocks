/*****************************************************************************

      BoardDaisyField.hpp
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

BoardDaisyField::BoardDaisyField ()
{
   uint8_t addr [] = {0x02};

   constexpr auto led_i2c_config = daisy::I2CHandle::Config {
      daisy::I2CHandle::Config::Peripheral::I2C_1,
      {SubmoduleDaisySeed::Pin11, SubmoduleDaisySeed::Pin12},
      daisy::I2CHandle::Config::Speed::I2C_1MHZ,
      daisy::I2CHandle::Config::Mode::I2C_MASTER
   };

   using DmaBuffer = decltype (_led_driver)::DmaBuffer;

   static DmaBuffer DMA_BUFFER_MEM_SECTION led_dma_buffer_a;
   static DmaBuffer DMA_BUFFER_MEM_SECTION led_dma_buffer_b;

   daisy::I2CHandle i2c;
   i2c.Init (led_i2c_config);
   _led_driver.Init (
      i2c, addr,
      led_dma_buffer_a, led_dma_buffer_b
   );
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyField::impl_preprocess (GpiPin pin)
{
   // Topology:
   // - GI: BJT
   // - BX: switch to ground with pull-up
   // => Both are inverted

   _digital_inputs [pin.index] = !_gpio_inputs [pin.index].read ();
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyField::impl_preprocess (AdcPin pin)
{
   if ((pin.index >= CI1.index) && (pin.index <= CI4.index))
   {
      const auto norm_val = to_float_norm (_adc.read (pin.index));
      // OpAmp in non-inverting amplifier
      _analog_inputs [pin.index] = norm_val;
   }
   else if ((pin.index >= P1.index) && (pin.index <= P8.index))
   {
      constexpr size_t pot_order [] = {
         4+0, 4+3, 4+1, 4+4, 4+2, 4+5, 4+6, 4+7, // P1..8
      };

      const auto norm_val = to_float_norm (
         _adc.read (pot_order [pin.index - P1.index])
      );

      _analog_inputs [pin.index] = norm_val;
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyField::impl_preprocess (AudioInPin pin)
{
   scale (
      _audio_inputs [pin.index],
      _submodule.raw_audio_inputs [pin.index],
      _submodule.gain_input_scaling
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess (GpoPin pin)
{
   _gpio_outputs [pin.index].write (_digital_outputs [pin.index]);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess (DacPin pin)
{
   if (pin.index <= CO2.index)
   {
      _dac.write (pin.index, norm_to_u12 (_analog_outputs [pin.index]));
   }
   else
   {
      _led_driver.SetLed (
         pin.index - L1.index, _analog_outputs [pin.index]
      );
   }
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess (AudioOutPin pin)
{
   scale (
      _submodule.raw_audio_outputs [pin.index],
      _audio_outputs [pin.index],
      _submodule.gain_output_scaling
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess ()
{
   _led_driver.SwapBuffersAndTransmit ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
