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

   seed.dac.WriteValue (
      daisy::DacHandle::Channel::ONE,
      norm_to_u16 (_analog_outputs [0])
   );

   seed.dac.WriteValue (
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
   // 8 buttons multiplexed on Pin26
   // 8 buttons multiplexed on Pin27
   // 4 buttons multiplexed on Pin29, inverted
   // Multiplexer address on Pin10, Pin9 and Pin8

   // Problem, the Mux address is instrumented by the ADC channels
   // configuration, so we need to be able to use this also for digital
   // inputs

   /*auto mux_address = MuxAddress {Pin10, Pin9, Pin8};

   init_gpio_input (Pin26);
   init_gpio_input (Pin27);
   init_gpio_input (Pin29);*/
}



/*
==============================================================================
Name : init_analog_inputs
==============================================================================
*/

void  BoardKivu12::init_analog_inputs ()
{
   // 8 CV inputs on ADC0..ADC6, ADC9
   // 8 pots multiplexed on ADC10
   // 4 pots multiplexed on ADC11
   // Multiplexer address on Pin10, Pin9 and Pin8

   auto mux_address = MuxAddress {Pin10, Pin9, Pin8};

   _adc16_channels = init_adc_channels <NBR_ANALOG_INPUTS> ({
      // 8 CVs
      {AdcPin0}, {AdcPin1}, {AdcPin2}, {AdcPin3},
      {AdcPin4}, {AdcPin5}, {AdcPin6}, {AdcPin7},
      // 12 Pots
      {AdcPin10, 8, mux_address},
      {AdcPin11, 8, mux_address} // 4 last ones ignored
   });
}



/*
==============================================================================
Name : init_digital_outputs
==============================================================================
*/

void  BoardKivu12::init_digital_outputs ()
{
   // 2 Gate outputs on Pin30 and Pin7

   init_gpio_output (Pin30);
   init_gpio_output (Pin7);
}



/*
==============================================================================
Name : init_analog_outputs
==============================================================================
*/

static daisy::LedDriverPca9685 <2>::DmaBuffer DMA_BUFFER_MEM_SECTION dma_buffer_a;
static daisy::LedDriverPca9685 <2>::DmaBuffer DMA_BUFFER_MEM_SECTION dma_buffer_b;

void  BoardKivu12::init_analog_outputs ()
{
   // 2 CV outputs on DAC OUT1 (DacPin0) and DAC OUT2 (DacPin1)

   init_dac_channels ({DacPin0, DacPin1});

   // 20 PWM outputs on I2C1
   // 16 on PCA9685 address 0x0
   // 4 on PCA9685 address 0x2

   daisy::I2CHandle::Config i2c_config = {
      I2CHandle::Config::Peripheral::I2C_1,
      {Pin11, Pin12},
      I2CHandle::Config::Speed::I2C_1MHZ
   };

   uint8_t addr [2] = {0x0, 0x2};
   daisy::I2CHandle i2c;
   i2c.Init (i2c_config);
   _led_driver.Init (i2c, addr, dma_buffer_a, dma_buffer_b);
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
