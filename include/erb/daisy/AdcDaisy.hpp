/*****************************************************************************

      AdcDaisy.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <size_t MaxNbrData>
AdcDaisy <MaxNbrData>::AdcDaisy (daisy::AdcHandle & adc, std::initializer_list <Channel> channels, AdcOversampling oversampling, AdcSamplingTimeCycles sampling_time)
{
   std::array <daisy::AdcChannelConfig, MaxNbrData> configs;

   size_t config_nbr = 0;
   for (auto && channel : channels)
   {
      auto & config = configs [config_nbr];
      ++config_nbr;

      if (channel.nbr_channels == 1)
      {
         config.InitSingle (channel.pin, to_ConversionSpeed (sampling_time));
      }
      else
      {
         config.InitMux (
            channel.pin,
            channel.nbr_channels,
            channel.address.pin_a,
            channel.address.pin_b,
            channel.address.pin_c,
            to_ConversionSpeed (sampling_time)
         );
      }
   }

   adc.Init (&configs [0], config_nbr, to_OverSampling (oversampling));

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
         for (size_t i = 0 ; i < channel.nbr_channels ; ++i)
         {
            _data [channel_nbr]
               = adc.GetMuxPtr (uint8_t (config_nbr), i);
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

/*
==============================================================================
Name : to_ConversionSpeed
==============================================================================
*/

template <size_t MaxNbrData>
daisy::AdcChannelConfig::ConversionSpeed  AdcDaisy <MaxNbrData>::to_ConversionSpeed (AdcSamplingTimeCycles sampling_time)
{
   switch (sampling_time)
   {
   case AdcSamplingTimeCycles::_1_5:
      return daisy::AdcChannelConfig::SPEED_1CYCLES_5;

   case AdcSamplingTimeCycles::_2_5:
      return daisy::AdcChannelConfig::SPEED_2CYCLES_5;

   case AdcSamplingTimeCycles::_8_5:
      return daisy::AdcChannelConfig::SPEED_8CYCLES_5;
   }

   __builtin_unreachable ();
}


/*
==============================================================================
Name : to_OverSampling
==============================================================================
*/

template <size_t MaxNbrData>
daisy::AdcHandle::OverSampling   AdcDaisy <MaxNbrData>::to_OverSampling (AdcOversampling oversampling)
{
   switch (oversampling)
   {
   case AdcOversampling::None:
      return daisy::AdcHandle::OVS_NONE;

   case AdcOversampling::_4:
      return daisy::AdcHandle::OVS_4;

   case AdcOversampling::_8:
      return daisy::AdcHandle::OVS_8;

   case AdcOversampling::_16:
      return daisy::AdcHandle::OVS_16;

   case AdcOversampling::_32:
      return daisy::AdcHandle::OVS_32;
   }

   __builtin_unreachable ();
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
