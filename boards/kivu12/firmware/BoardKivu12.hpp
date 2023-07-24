/*****************************************************************************

      BoardKivu12.hpp
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

BoardKivu12::BoardKivu12 ()
{
   constexpr auto led_i2c_config = daisy::I2CHandle::Config {
      daisy::I2CHandle::Config::Peripheral::I2C_1,
      {
         SubmoduleDaisyPatchSm::B7, // SCL
         SubmoduleDaisyPatchSm::B8  // SDA
      },
      daisy::I2CHandle::Config::Speed::I2C_1MHZ,
      daisy::I2CHandle::Config::Mode::I2C_MASTER
   };

   using DmaBuffer = decltype (_led_driver)::DmaBuffer;

   static DmaBuffer DMA_BUFFER_MEM_SECTION led_dma_buffer_a;
   static DmaBuffer DMA_BUFFER_MEM_SECTION led_dma_buffer_b;
   const uint8_t addr [] = {0x00};

   daisy::I2CHandle i2c;
   i2c.Init (led_i2c_config);
   _led_driver.Init (
      i2c, addr,
      led_dma_buffer_a, led_dma_buffer_b
   );

#if defined (erb_USE_DAISY_IMPL)
   ShiftRegister::Config sr_config;
   sr_config.clk = SubmoduleDaisyPatchSm::A2;
   sr_config.latch = SubmoduleDaisyPatchSm::A9;
   sr_config.data [0] = SubmoduleDaisyPatchSm::B9;
   sr_config.data [1] = SubmoduleDaisyPatchSm::B10;
   _shift_register.Init (sr_config);
#endif
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess ()
{
#if defined (erb_USE_ERB_IMPL)
   /*
   _gpio_inputs [1]
   B1  D4
   B2  D5
   B3  D6
   B4  D7
   B5  D3
   B6  D2
   B7  D1
   B8  D0

   _gpio_inputs [0]
   B9  D4
   B10 D5
   B11 D6
   B12 D7
   B13 D3
   B14 D2
   B15 D1
   B16 D0
   */

   constexpr size_t gpio0_order [] = {
      11, 10, 9, 8, 12, 13, 14, 15
   };
   constexpr size_t gpio1_order [] = {
      3, 2, 1, 0, 4, 5, 6, 7
   };

   _gpio_b_sr4021_clock.write (false);
   _gpio_b_sr4021_latch.write (true);
   daisy::System::DelayTicks (100);

   _gpio_b_sr4021_latch.write (false);

   for (std::size_t i = 0 ; i < 8 ; ++i)
   {
      _gpio_b_sr4021_clock.write (false);
      daisy::System::DelayTicks (400);

      // GI: BJT => inverted
      _digital_inputs [gpio0_order [i]] = !_gpio_inputs [0].read ();
      _digital_inputs [gpio1_order [i]] = !_gpio_inputs [1].read ();

      _gpio_b_sr4021_clock.write (true);
      daisy::System::DelayTicks (400);
   }

#elif defined (erb_USE_DAISY_IMPL)
   _shift_register.Update ();

   constexpr size_t gpio_order [] = {
      3, 2, 1, 0, 4, 5, 6, 7,
      11, 10, 9, 8, 12, 13, 14, 15
   };

   for (std::size_t i = 0 ; i < 16 ; ++i)
   {
      // GI: BJT => inverted
      _digital_inputs [gpio_order [i]] = !_shift_register.State (i);
   }

#endif
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess (GpiPin /* pin */)
{
   // nothing
   // BX are preprocessed in the board level preprocess above
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess (AdcPin pin)
{
   if ((pin.index >= CI1.index) && (pin.index <= CI8.index))
   {
      /*
      Order of ADCs in libDaisy:
      PIN_ADC_CTRL_1,
      PIN_ADC_CTRL_2,
      PIN_ADC_CTRL_3,
      PIN_ADC_CTRL_4,
      PIN_ADC_CTRL_8,
      PIN_ADC_CTRL_7,
      PIN_ADC_CTRL_5,
      PIN_ADC_CTRL_6,

      CI1 -> CV1 -> PIN_ADC_CTRL_1 -> 0
      CI2 -> CV2 -> PIN_ADC_CTRL_2 -> 1
      CI3 -> CV8 -> PIN_ADC_CTRL_6 -> 5
      CI4 -> CV7 -> PIN_ADC_CTRL_5 -> 4
      CI5 -> CV6 -> PIN_ADC_CTRL_7 -> 6
      CI6 -> CV5 -> PIN_ADC_CTRL_8 -> 7
      CI7 -> CV3 -> PIN_ADC_CTRL_3 -> 2
      CI8 -> CV4 -> PIN_ADC_CTRL_4 -> 3
      */

      constexpr size_t cv_order [] = {
         0, 1, 5, 4, 6, 7, 2, 3
      };

      const auto norm_val = to_float_norm (
         _adc.read (cv_order [pin.index - CI1.index])
      );

      // OpAmp in inverter adder with voltage reference
      _analog_inputs [pin.index] = 1.f - norm_val;
   }
   else if ((pin.index >= P1.index) && (pin.index <= P12.index))
   {
      // IN1-X4, IN2-X6, IN3-X7, IN4-X5
      // IN5-X2, IN6-X1, IN7-X0, IN8-X3
      // IN9-X2, IN10-X1, IN11-X0, IN12-X3

      constexpr size_t pot_order [] = {
         8+4, 8+6, 8+7, 8+5, 8+2, 8+1, 8+0, 8+3, // P1..8
         16+2, 16+1, 16+0, 16+3                  // P9..12
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

void  BoardKivu12::impl_preprocess (AudioInPin pin)
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

void  BoardKivu12::impl_postprocess (GpoPin pin)
{
   _gpio_outputs [pin.index].write (_digital_outputs [pin.index]);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardKivu12::impl_postprocess (DacPin pin)
{
   if (pin.index <= CO2.index)
   {
      _dac.write (pin.index, norm_to_u12 (_analog_outputs [pin.index]));
   }
   else if ((pin.index >= L1.index) && (pin.index <= L16.index))
   {
      // The PCA9685 is made so that the anode is connected to 3V3,
      // not to the pin. Similarly, cathode is connected to the pin, not
      // GND.
      // For this reason, the logic is inverted, and we need to adapt
      // the gamma too.
      // from 4036 to 4094 it is on instead of off, so convert normalized
      // range from 0 to 4035.

      auto val = _analog_outputs [pin.index];
      auto linear = 1.f - val * val * val;
      auto linear_u12 = uint16_t (std::clamp (linear, 0.f, 1.f) * 4035.f);

      // LEDO-L8 LED1-L7 LED2-L6 ... LED7-L1
      // LED8-L9 LED9-L10 LED10-L11 ... LED15-L16

      constexpr size_t led_order [] = {
         7, 6, 5, 4, 3, 2, 1, 0,       // L1..8
         8, 9, 10, 11, 12, 13, 14, 15  // L9..16
      };

      _led_driver.SetLedRaw (
         led_order [pin.index - L1.index], linear_u12
      );
   }
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardKivu12::impl_postprocess (AudioOutPin pin)
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

void  BoardKivu12::impl_postprocess ()
{
   // Linear congruential generator
   _npr_rand_state = _npr_rand_state * 1103515245 + 12345;
   _npr = _npr_rand_state >> 31;
   _gpio_npr.write (_npr != 0);

   _led_driver.SwapBuffersAndTransmit ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
