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
      std::array <float, Length> samples;
   };

   float          sample_rate;
   std::array <Channel, NbrChannels>
                  channels;
};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
