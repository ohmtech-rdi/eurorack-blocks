/*****************************************************************************

      Wave.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/Wave.h"

#include <algorithm>
#include <array>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>



namespace erb
{
namespace rig
{



namespace
{

constexpr std::int16_t   Int16Max = 32767;

std::int16_t   to_int16 (float sample)
{
   const auto clamped = std::clamp (sample, -1.f, 1.f);
   return std::int16_t (std::lrint (clamped * float (Int16Max)));
}

float to_float (std::int16_t value)
{
   return float (value) / float (Int16Max);
}

void  put_u16 (std::vector <std::uint8_t> & out, std::uint16_t value)
{
   out.push_back (std::uint8_t (value & 0xff));
   out.push_back (std::uint8_t (value >> 8));
}

void  put_u32 (std::vector <std::uint8_t> & out, std::uint32_t value)
{
   put_u16 (out, std::uint16_t (value & 0xffff));
   put_u16 (out, std::uint16_t (value >> 16));
}

void  put_tag (std::vector <std::uint8_t> & out, const char * tag)
{
   out.insert (out.end (), tag, tag + 4);
}

std::uint16_t  get_u16 (const std::uint8_t * p)
{
   return std::uint16_t (p [0] | (p [1] << 8));
}

std::uint32_t  get_u32 (const std::uint8_t * p)
{
   return std::uint32_t (get_u16 (p)) | (std::uint32_t (get_u16 (p + 2)) << 16);
}

[[noreturn]] void  fail (const char * what, const std::string & path)
{
   std::fprintf (stderr, "read_wave: %s '%s'\n", what, path.c_str ());
   std::fflush (stderr);
   assert (false);
   std::abort ();
}

}  // namespace



/*
==============================================================================
Name : Wave::nbr_frames
==============================================================================
*/

std::size_t Wave::nbr_frames () const
{
   assert (nbr_channels > 0);
   assert (samples.size () % nbr_channels == 0);

   return samples.size () / nbr_channels;
}



/*
==============================================================================
Name : quantize
Description :
   We store the wave files in 16-bit to optimise for space in a repo.
   But we need to still be able to compare to the golden, so the actual
   can be first quantized should we want bit-exact compare
==============================================================================
*/

float quantize (float sample)
{
   return to_float (to_int16 (sample));
}



/*
==============================================================================
Name : read_wave
Note :
   Only RIFF/WAVE PCM 16-bit format
==============================================================================
*/

Wave  read_wave (const std::string & path)
{
   std::FILE * file = std::fopen (path.c_str (), "rb");

   if (file == nullptr)
   {
      fail ("cannot read", path);
   }

   std::vector <std::uint8_t> bytes;
   std::array <std::uint8_t, 65536> chunk;

   for (;;)
   {
      const auto n = std::fread (chunk.data (), 1, chunk.size (), file);
      bytes.insert (bytes.end (), chunk.begin (), chunk.begin () + std::ptrdiff_t (n));
      if (n < chunk.size ()) break;
   }

   std::fclose (file);

   if ((bytes.size () < 12) || (std::memcmp (bytes.data (), "RIFF", 4) != 0) || (std::memcmp (bytes.data () + 8, "WAVE", 4) != 0))
   {
      fail ("not a wave file", path);
   }

   Wave wave;
   bool fmt_seen = false;
   bool data_seen = false;
   std::size_t pos = 12;

   while (pos + 8 <= bytes.size ())
   {
      const auto * tag = bytes.data () + pos;
      const auto size = std::size_t (get_u32 (bytes.data () + pos + 4));
      const auto * body = bytes.data () + pos + 8;

      if (pos + 8 + size > bytes.size ())
      {
         fail ("truncated chunk in", path);
      }

      if (std::memcmp (tag, "fmt ", 4) == 0)
      {
         if (size < 16) fail ("short fmt chunk in", path);

         const auto format = get_u16 (body);
         const auto nbr_channels = get_u16 (body + 2);
         const auto sample_rate = get_u32 (body + 4);
         const auto bits = get_u16 (body + 14);

         if ((format != 1) || (bits != 16)) fail ("not 16-bit PCM", path);
         if (nbr_channels == 0) fail ("no channel in", path);

         wave.sample_rate = sample_rate;
         wave.nbr_channels = nbr_channels;
         fmt_seen = true;
      }
      else if (std::memcmp (tag, "data", 4) == 0)
      {
         if (!fmt_seen) fail ("data before fmt in", path);

         wave.samples.resize (size / 2);

         for (std::size_t i = 0 ; i < wave.samples.size () ; ++i)
         {
            wave.samples [i] = to_float (std::int16_t (get_u16 (body + 2 * i)));
         }

         data_seen = true;
      }

      pos += 8 + size + (size & 1);  // chunk word-aligned
   }

   if (!fmt_seen || !data_seen) fail ("missing fmt or data chunk in", path);
   if (wave.samples.size () % wave.nbr_channels != 0) fail ("partial frame in", path);

   return wave;
}



/*
==============================================================================
Name : write_wave
==============================================================================
*/

void  write_wave (const Wave & wave, const std::string & path, WaveFormat format)
{
   assert (wave.sample_rate > 0);
   assert (wave.nbr_channels > 0);
   assert (wave.samples.size () % wave.nbr_channels == 0);

   const std::size_t bytes_per_sample = (format == WaveFormat::Pcm16) ? 2 : 4;
   const auto data_size = std::uint32_t (wave.samples.size () * bytes_per_sample);
   const auto block_align = std::uint16_t (wave.nbr_channels * bytes_per_sample);

   std::vector <std::uint8_t> bytes;
   bytes.reserve (44 + data_size);

   put_tag (bytes, "RIFF");
   put_u32 (bytes, 36 + data_size);
   put_tag (bytes, "WAVE");

   put_tag (bytes, "fmt ");
   put_u32 (bytes, 16);
   put_u16 (bytes, (format == WaveFormat::Pcm16) ? 1 : 3);  // PCM, IEEE float
   put_u16 (bytes, std::uint16_t (wave.nbr_channels));
   put_u32 (bytes, wave.sample_rate);
   put_u32 (bytes, wave.sample_rate * block_align); // byte rate
   put_u16 (bytes, block_align);
   put_u16 (bytes, std::uint16_t (bytes_per_sample * 8));

   put_tag (bytes, "data");
   put_u32 (bytes, data_size);

   for (auto sample : wave.samples)
   {
      if (format == WaveFormat::Pcm16)
      {
         put_u16 (bytes, std::uint16_t (to_int16 (sample)));
      }
      else
      {
         std::uint32_t bits;
         std::memcpy (&bits, &sample, 4);
         put_u32 (bytes, bits);
      }
   }

   std::FILE * file = std::fopen (path.c_str (), "wb");

   if (file == nullptr)
   {
      std::fprintf (stderr, "write_wave: cannot write '%s'\n", path.c_str ());
      std::fflush (stderr);
      assert (false);
      return;
   }

   std::fwrite (bytes.data (), 1, bytes.size (), file);
   std::fclose (file);
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
