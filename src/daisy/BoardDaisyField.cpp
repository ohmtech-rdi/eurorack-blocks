/*****************************************************************************

      BoardDaisyField.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardDaisyField.h"



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
   _submodule.init_gpio_input (GI.pin);
   _submodule.init_gpio_output (GO.pin);
   _submodule.init_gpio_input (B1.pin, SubmoduleDaisySeed::Pull::Up);
   _submodule.init_gpio_input (B2.pin, SubmoduleDaisySeed::Pull::Up);

   _analog_inputs_u16 = _submodule.init_adc_channels <12> ({
      {SubmoduleDaisySeed::AdcPin2},
      {SubmoduleDaisySeed::AdcPin3},
      {SubmoduleDaisySeed::AdcPin10},
      {SubmoduleDaisySeed::AdcPin9},
      {
         SubmoduleDaisySeed::AdcPin1, 8,
         {
            SubmoduleDaisySeed::Pin21,
            SubmoduleDaisySeed::Pin20,
            SubmoduleDaisySeed::Pin19
         }
      },
   });

   _submodule.init_dac_channels ({
      SubmoduleDaisySeed::DacPin0,
      SubmoduleDaisySeed::DacPin1,
   });

   uint8_t addr [] = {0x02};

   constexpr auto led_i2c_config = daisy::I2CHandle::Config {
      daisy::I2CHandle::Config::Peripheral::I2C_1,
      {SubmoduleDaisySeed::Pin11, SubmoduleDaisySeed::Pin12},
      daisy::I2CHandle::Config::Speed::I2C_1MHZ
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



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
