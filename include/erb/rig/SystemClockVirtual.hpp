/*****************************************************************************

      SystemClockVirtual.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



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
