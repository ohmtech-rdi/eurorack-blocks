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
                  samples;       // interleaved, 16-bit "pre-quantized"

   std::size_t    nbr_frames () const;
};

enum class WaveFormat
{
   Pcm16,
   Float32,
};

float    quantize (float sample);

Wave     read_wave (const std::string & path);

void     write_wave (const Wave & wave, const std::string & path, WaveFormat format = WaveFormat::Pcm16);



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
