/*****************************************************************************

      AdcDaisy.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

erb_DISABLE_WARNINGS_DAISY
#include "per/adc.h"
erb_RESTORE_WARNINGS



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <size_t MaxNbrData>
AdcDaisy <MaxNbrData>::AdcDaisy (daisy::AdcHandle & adc, std::initializer_list <Channel> channels)
{
   std::array <daisy::AdcChannelConfig, MaxNbrData> configs;

   size_t config_nbr = 0;
   for (auto && channel : channels)
   {
      auto & config = configs [config_nbr];
      ++config_nbr;

      if (channel.nbr_channels == 1)
      {
         config.InitSingle (channel.pin);
      }
      else
      {
         config.InitMux (
            channel.pin,
            channel.nbr_channels,
            channel.address.pin_a,
            channel.address.pin_b,
            channel.address.pin_c
         );
      }
   }

   adc.Init (&configs [0], config_nbr);

   config_nbr = 0;
   size_t channel_nbr = 0;
   for (auto && channel : channels)
   {
      if (channel.nbr_channels == 1)
      {
         _data [channel_nbr] = adc.GetPtr (uint8_t (config_nbr));
         ++channel_nbr;
      }
      else
      {
         constexpr size_t pot_order [] = {0, 3, 1, 4, 2, 5, 6, 7};

         for (size_t i = 0 ; i < channel.nbr_channels ; ++i)
         {
            _data [channel_nbr]
               = adc.GetMuxPtr (uint8_t (config_nbr), pot_order [i]);
            ++channel_nbr;
         }
      }

      ++config_nbr;

      if (channel_nbr >= MaxNbrData) break; // full
   }
}



/*
==============================================================================
Name : read
==============================================================================
*/

template <size_t MaxNbrData>
uint16_t AdcDaisy <MaxNbrData>::read (size_t index)
{
   return *_data [index];
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
