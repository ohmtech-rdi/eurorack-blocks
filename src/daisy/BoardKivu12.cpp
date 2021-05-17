/*****************************************************************************

      BoardKivu12.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardKivu12.h"



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
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardKivu12::impl_postprocess ()
{
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

   /*init_gpio_output (Pin30);
   init_gpio_output (Pin7);*/
}



/*
==============================================================================
Name : init_analog_outputs
==============================================================================
*/

void  BoardKivu12::init_analog_outputs ()
{
   // 2 CV outputs on DAC OUT1 and DAC OUT2
   // 20 PWM outputs on I2C1
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
