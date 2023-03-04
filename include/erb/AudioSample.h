/*****************************************************************************

      AudioSample.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <cstddef>



namespace erb
{



template <class T, std::size_t Length, std::size_t NbrChannels>
struct AudioSampleInterleaved
{
   struct Frame
   {
      std::array <T, NbrChannels> channels;
   };

   float          sample_rate;
   std::array <Frame, Length>
                  frames;
};



template <class T, std::size_t Length, std::size_t NbrChannels>
struct AudioSamplePlanar
{
   struct Channel
   {
      std::array <T, Length> samples;
   };

   float          sample_rate;
   std::array <Channel, NbrChannels>
                  channels;
};



template <class T, std::size_t Length>
struct AudioSampleMono
{
   float          sample_rate;
   std::array <T, Length>
                  samples;
};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
