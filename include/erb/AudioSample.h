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



template <class T, size_t Length, size_t NbrChannels>
struct AudioSample
{
   struct Channel
   {
      std::array <float, NbrChannels> channels;
   };

   float          sample_rate;
   std::array <Channel, Length>
                  frames;
};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
