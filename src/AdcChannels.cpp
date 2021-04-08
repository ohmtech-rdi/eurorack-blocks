/*****************************************************************************

      AdcChannels.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AdcChannels.h"

#include "erb/AnalogControlBase.h"
#include "erb/Multiplexer.h"
#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS



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

void  AdcChannels::add (AnalogControlBase & control, const Pin & pin)
{
   auto & channel = _channels [_nbr_adc_channel];
   ++_nbr_adc_channel;

   channel.pin = pin;
   channel.control_ptr = &control;
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  AdcChannels::add (Multiplexer & multiplexer, const Pin & pin, const MultiplexerAddressPins & address_pins)
{
   auto & channel = _channels [_nbr_adc_channel];
   ++_nbr_adc_channel;

   channel.pin = pin;
   channel.multiplexer_ptr = &multiplexer;
   channel.address_pins = address_pins;
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

      if (channel.control_ptr != nullptr)
      {
         config.InitSingle (channel.pin);
      }
      else if (channel.multiplexer_ptr != nullptr)
      {
         size_t mux_channels = 0;
         if (channel.address_pins.pin_b == PinNC)
         {
            mux_channels = 2;
         }
         else if (channel.address_pins.pin_c == PinNC)
         {
            mux_channels = 4;
         }
         else
         {
            mux_channels = 8;
         }

         config.InitMux (
            channel.pin, mux_channels,
            channel.address_pins.pin_a,
            channel.address_pins.pin_b,
            channel.address_pins.pin_c
         );
      }
   }

   _seed.adc.Init (&configs [0], _nbr_adc_channel);

   for (size_t i = 0 ; i < _nbr_adc_channel ; ++i)
   {
      const auto & channel = _channels [i];

      if (auto control_ptr = channel.control_ptr)
      {
         control_ptr->impl_bind (_seed.adc.GetPtr (uint8_t (i)));
      }
      else if (auto multiplexer_ptr = channel.multiplexer_ptr)
      {
         multiplexer_ptr->impl_bind (_seed.adc.GetMuxPtr (uint8_t (i), 0));
      }
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
