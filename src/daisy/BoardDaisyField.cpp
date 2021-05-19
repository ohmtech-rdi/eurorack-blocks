/*****************************************************************************

      BoardKivu12.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardKivu12.h"

#include "erb/detail/fnc.h"



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
   init_digital_inputs ();
   init_analog_inputs ();

   init_digital_outputs ();
   init_analog_outputs ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess ()
{
   /*for (size_t i = 0 ; i < _digital_inputs.size () ; ++i)
   {
   }*/

   for (size_t i = 0 ; i < _analog_inputs.size () ; ++i)
   {
      constexpr float u16_to_float_norm = 1.f / 65535.f;

      auto & val_f = _analog_inputs [i];
      auto val = *_adc16_channels [i];

      val_f = float (val) * u16_to_float_norm;
   }

   scale (_audio_inputs, _raw_audio_inputs, _gain_input_scaling);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardKivu12::impl_postprocess ()
{
   write_gpio (Pin30, _digital_outputs [0]);
   write_gpio (Pin7, _digital_outputs [1]);

   _seed.dac.WriteValue (
      daisy::DacHandle::Channel::ONE,
      norm_to_u16 (_analog_outputs [0])
   );

   _seed.dac.WriteValue (
      daisy::DacHandle::Channel::TWO,
      norm_to_u16 (_analog_outputs [1])
   );

   for (size_t i = 0 ; i < 20 ; ++i)
   {
      _led_driver.SetLed (i, _analog_outputs [2 + i]);
   }

   scale (_raw_audio_outputs, _audio_outputs, _gain_output_scaling);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_digital_inputs
==============================================================================
*/

void  BoardKivu12::init_digital_inputs ()
{
   init_gpio_input (Pin30, Pull::Up);  // SW1
   init_gpio_input (Pin29, Pull::Up);  // SW2
   init_gpio_input (Pin0);             // Gate In
}



/*
==============================================================================
Name : init_analog_inputs
==============================================================================
*/

void  BoardKivu12::init_analog_inputs ()
{
   // 4 CV inputs on ADC2, ADC3, ADC10, ADC9
   // 8 pots multiplexed on ADC1
   // Multiplexer address on Pin21, Pin20, Pin19

   auto mux_address = MuxAddress {Pin21, Pin20, Pin19};

   _adc16_channels = init_adc_channels <NBR_ANALOG_INPUTS> ({
      // 4 CVs
      {AdcPin2}, {AdcPin3}, {AdcPin10}, {AdcPin9},
      // 8 Pots
      {AdcPin1, 8, mux_address},
   });
}



/*
==============================================================================
Name : init_digital_outputs
==============================================================================
*/

void  BoardKivu12::init_digital_outputs ()
{
   // 1 Gate output on Pin15

   init_gpio_output (Pin15);
}



/*
==============================================================================
Name : init_analog_outputs
==============================================================================
*/

static daisy::LedDriverPca9685 <1>::DmaBuffer DMA_BUFFER_MEM_SECTION dma_buffer_a;
static daisy::LedDriverPca9685 <1>::DmaBuffer DMA_BUFFER_MEM_SECTION dma_buffer_b;

void  BoardKivu12::init_analog_outputs ()
{
   // 2 CV outputs on DAC OUT1 (DacPin0) and DAC OUT2 (DacPin1)

   init_dac_channels ({DacPin0, DacPin1});

   // 8 PWM outputs on I2C1
   // 8 on PCA9685 address 0x0

   daisy::I2CHandle::Config i2c_config = {
      daisy::I2CHandle::Config::Peripheral::I2C_1,
      {Pin11, Pin12},
      daisy::I2CHandle::Config::Speed::I2C_1MHZ
   };

   uint8_t addr [1] = {0x2};
   daisy::I2CHandle i2c;
   i2c.Init (i2c_config);
   _led_driver.Init (i2c, addr, dma_buffer_a, dma_buffer_b);
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
