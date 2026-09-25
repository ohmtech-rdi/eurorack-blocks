/*****************************************************************************

      Peak.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>

#include <cassert>
#include <cmath>
#include <cstdint>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Peak::Peak (SystemClockVirtual::duration window)
{
   assert (window.count () > 0);

   const auto ns = std::uint64_t (window.count ());
   const auto samples = (ns * std::uint64_t (erb_SAMPLE_RATE) + 999999999ull) / 1000000000ull;
   const auto frames = (samples + erb_BUFFER_SIZE - 1) / erb_BUFFER_SIZE;

   _frame_peaks.assign (std::size_t (std::max <std::uint64_t> (frames, 1)), 0.f);
}



/*
==============================================================================
Name : reading
==============================================================================
*/

Peak::Reading  Peak::reading () const
{
   float ret = 0.f;

   for (std::size_t i = 0 ; i < _count ; ++i)
   {
      ret = std::max (ret, _frame_peaks [i]);
   }

   return ret;
}



/*
==============================================================================
Name : distance
==============================================================================
*/

float Peak::distance (Reading a, Reading b)
{
   return scalar_distance (a, b);
}



/*
==============================================================================
Name : report
==============================================================================
*/

void  Peak::report (const char * name, const char * output_name, Reading reading, Reading expected, float tolerance)
{
   scalar_report (name, output_name, reading, expected, tolerance);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Peak::name () const
{
   return "Peak";
}



/*
==============================================================================
Name : impl_start
==============================================================================
*/

void  Peak::impl_start ()
{
   _pos = 0;
   _count = 0;
}



/*
==============================================================================
Name : impl_feed
==============================================================================
*/

void  Peak::impl_feed (const Buffer & buffer)
{
   float peak = 0.f;

   for (auto sample : buffer)
   {
      peak = std::max (peak, std::abs (sample));
   }

   _frame_peaks [_pos] = peak;

   _pos = (_pos + 1) % _frame_peaks.size ();
   _count = std::min (_count + 1, _frame_peaks.size ());
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
