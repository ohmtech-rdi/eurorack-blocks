/*****************************************************************************

      AdcChannels.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AdcChannels.h"

#include "erb/AnalogControlBase.h"

#if defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wpedantic"
   #pragma GCC diagnostic ignored "-Wignored-qualifiers"
   #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "daisy_seed.h"

#if defined (__GNUC__)
   #pragma GCC diagnostic pop
#endif



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

AdcChannels::AdcChannels (daisy::DaisySeed & seed)
:  _seed (seed)
{
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  AdcChannels::add (AnalogControlBase & control, const dsy_gpio_pin & pin)
{
   auto & channel = _channels [_nbr_adc_channel];
   ++_nbr_adc_channel;

   channel.control_ptr = &control;
   channel.pin = pin;
}



/*
==============================================================================
Name : init
==============================================================================
*/

void  AdcChannels::init ()
{
   std::array <daisy::AdcChannelConfig, NBR_MAX_ADC_CHANNELS> configs;

   for (size_t i = 0 ; i < _nbr_adc_channel ; ++i)
   {
      const auto & channel = _channels [i];
      auto & config = configs [i];

      config.InitSingle (channel.pin);
   }

   _seed.adc.Init (&configs [0], _nbr_adc_channel);

   for (size_t i = 0 ; i < _nbr_adc_channel ; ++i)
   {
      const auto & channel = _channels [i];
      auto control_ptr = channel.control_ptr;

      control_ptr->impl_bind (_seed.adc.GetPtr (i));
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
