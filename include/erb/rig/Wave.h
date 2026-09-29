/*****************************************************************************

      Wave.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <string>
#include <vector>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



struct Wave
{
   std::uint32_t  sample_rate = 0;
   std::size_t    nbr_channels = 0;
   std::vector <float>
                  samples;       // interleaved, 16-bit "pre-quantised"

   std::size_t    nbr_frames () const;
};

float    quantise (float sample);

Wave     read_wave (const std::string & path);
void     write_wave (const Wave & wave, const std::string & path);



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
