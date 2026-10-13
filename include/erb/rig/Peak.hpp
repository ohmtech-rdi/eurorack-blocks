/*****************************************************************************

      Peak.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>

#include <cassert>
#include <cmath>
#include <cstdio>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : ctor
==============================================================================
*/

Peak::Peak (Setup setup)
:  Instrument (setup)
{
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Peak::bind (Bench & bench, AudioOut & output)
{
   impl_bind (bench, output);

   return impl_connect ();
}



/*
==============================================================================
Name : read
==============================================================================
*/

Peak::Reading  Peak::read () const
{
   float ret = 0.f;

   for (auto sample : impl_window_audio (0))
   {
      ret = std::max (ret, std::abs (sample));
   }

   return ret;
}



/*
==============================================================================
Name : check
==============================================================================
*/

void  Peak::check (Reading expected, float tolerance, std::source_location sloc) const
{
   assert (tolerance >= 0.f);

   const auto reading = read ();
   const bool ok = scalar_distance (reading, expected) <= tolerance;

   if (!ok)
   {
      std::fprintf (stderr, "check at %s:%u: ", sloc.file_name (), unsigned (sloc.line ()));
      scalar_report (name (), impl_channel_name (0), reading, expected, tolerance);
      std::fflush (stderr);
   }

   assert (ok);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Peak::name () const
{
   return "Peak";
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
