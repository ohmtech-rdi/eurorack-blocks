/*****************************************************************************

      SystemClockVirtual.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once

#include <cassert>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : now
Description :
   Nanoseconds since the module boot.
   This is the system clock implementation for the acceptance tests, it
   simulates a 'steady_clock', but is not real world elapsed time.
   The clock is synchronised to the audio clock for full determinism.
==============================================================================
*/

SystemClockVirtual::time_point   SystemClockVirtual::now ()
{
   const auto ns = (_samples * 1000000000ull) / std::uint64_t (erb_SAMPLE_RATE);

   return time_point {duration {rep (ns)}};
}



/*
==============================================================================
Name : to_blocks_nbr
Note :
   Rounded up so that it matches the 'board.run' advances.
   Problem is mainly that the daisy audio clock rate is non standard.
==============================================================================
*/

std::uint64_t  SystemClockVirtual::to_blocks_nbr (duration d)
{
   assert (d.count () > 0);

   const auto ns = std::uint64_t (d.count ());
   const auto samples_x_1e9 = ns * std::uint64_t (erb_SAMPLE_RATE);
   constexpr auto block_x_1e9 = 1000000000ull * erb_BUFFER_SIZE;

   return (samples_x_1e9 + block_x_1e9 - 1) / block_x_1e9;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_reset
==============================================================================
*/

void  SystemClockVirtual::impl_reset ()
{
   _samples = 0;
}



/*
==============================================================================
Name : impl_advance
==============================================================================
*/

void  SystemClockVirtual::impl_advance (std::uint64_t nbr_samples)
{
   _samples += nbr_samples;
}



/*
==============================================================================
Name : impl_samples
==============================================================================
*/

std::uint64_t  SystemClockVirtual::impl_samples ()
{
   return _samples;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
