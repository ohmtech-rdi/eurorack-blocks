/*****************************************************************************

      Scope.hpp
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



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Scope::Scope (Setup setup)
:  Instrument (setup)
{
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Scope::bind (Bench & bench, AudioOut & output)
{
   impl_bind (bench, output);

   return impl_connect ();
}



/*
==============================================================================
Name : read
==============================================================================
*/

Scope::Reading Scope::read () const
{
   const auto window = impl_window_audio (0);

   return Reading (window.begin (), window.end ());
}



/*
==============================================================================
Name : check
Description :
   Distance is largest absolute differance sample per sample.
   Fails if sizes are different.
==============================================================================
*/

void  Scope::check (const Reading & expected, float tolerance, std::source_location sloc) const
{
   assert (tolerance >= 0.f);

   const auto reading = read ();

   bool ok = reading.size () == expected.size ();
   std::size_t worst = 0;
   float distance = 0.f;

   if (ok)
   {
      for (std::size_t i = 0 ; i < reading.size () ; ++i)
      {
         const float d = std::abs (reading [i] - expected [i]);

         if (d > distance)
         {
            distance = d;
            worst = i;
         }
      }

      ok = distance <= tolerance;
   }

   if (!ok)
   {
      std::fprintf (stderr, "check at %s:%u: ", sloc.file_name (), unsigned (sloc.line ()));

      if (reading.size () != expected.size ())
      {
         std::fprintf (
            stderr, "%s on %s reads %zu samples, expected %zu\n",
            name (), impl_channel_name (0), reading.size (), expected.size ()
         );
      }
      else
      {
         std::fprintf (
            stderr, "%s on %s reads %.9g at sample %zu, expected %.9g, distance %.9g, tolerance %.9g\n",
            name (), impl_channel_name (0), reading [worst], worst, expected [worst], distance, tolerance
         );
      }

      std::fflush (stderr);
   }

   assert (ok);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Scope::name () const
{
   return "Scope";
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
