/*****************************************************************************

      SubmoduleDaisySeed.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

template <typename F>
void  SubmoduleDaisySeed::run (F && f)
{
   _run = std::forward <F> (f);

   do_run ();
}



/*
==============================================================================
Name : clock
==============================================================================
*/

const uint64_t &  SubmoduleDaisySeed::clock ()
{
   return _clock.ms ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_adc_channels
==============================================================================
*/

template <size_t MaxNbrChannels>
std::array <uint16_t *, MaxNbrChannels>   SubmoduleDaisySeed::init_adc_channels (std::initializer_list <AdcChannel> adc_channels)
{
   std::array <daisy::AdcChannelConfig, NBR_MAX_ADC_CHANNELS> configs;

   size_t config_nbr = 0;
   for (auto && adc_channel : adc_channels)
   {
      auto & config = configs [config_nbr];
      ++config_nbr;

      if (adc_channel.nbr_channels == 1)
      {
         config.InitSingle (adc_channel.pin.pin);
      }
      else
      {
         config.InitMux (
            adc_channel.pin.pin,
            adc_channel.nbr_channels,
            adc_channel.address.pin_a,
            adc_channel.address.pin_b,
            adc_channel.address.pin_c
         );
      }
   }

   _seed.adc.Init (&configs [0], config_nbr);

   std::array <uint16_t *, MaxNbrChannels> adc_channels_data;

   config_nbr = 0;
   size_t channel_nbr = 0;
   for (auto && adc_channel : adc_channels)
   {
      if (adc_channel.nbr_channels == 1)
      {
         adc_channels_data [channel_nbr] = _seed.adc.GetPtr (uint8_t (config_nbr));
         ++channel_nbr;
      }
      else
      {
         constexpr size_t pot_order [] = {0, 3, 1, 4, 2, 5, 6, 7};

         for (size_t i = 0 ; i < adc_channel.nbr_channels ; ++i)
         {
            adc_channels_data [channel_nbr]
               = _seed.adc.GetMuxPtr (uint8_t (config_nbr), pot_order [i]);
            ++channel_nbr;
         }
      }

      ++config_nbr;

      if (channel_nbr >= MaxNbrChannels) break; // full
   }

   return adc_channels_data;
}




/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
