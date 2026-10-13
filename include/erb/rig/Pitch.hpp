/*****************************************************************************

      Pitch.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>
#include <cmath>
#include <cstdio>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : cents_distance
==============================================================================
*/

float Pitch::cents_distance (float a_hz, float b_hz)
{
   return std::abs (1200.f * std::log2 (a_hz / b_hz));
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

Pitch::Pitch (Setup setup)
:  Instrument (setup)
{
   _breakpoints.push_back ({0, Parameters {}});
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Pitch::bind (Bench & bench, AudioOut & output)
{
   impl_bind (bench, output);

   return impl_connect ();
}



/*
==============================================================================
Name : set_detector
==============================================================================
*/

void  Pitch::set_detector (Detector detector)
{
   auto parameters = _breakpoints.back ().parameters;
   parameters.detector = detector;
   set_breakpoint (parameters);
}



/*
==============================================================================
Name : read
==============================================================================
*/

Pitch::Reading Pitch::read () const
{
   const auto window = impl_window_audio (0);
   const auto parameters = window_parameters ();

   switch (parameters.detector)
   {
   case Detector::Counter:
      return process_counter (window);
   }

   return 0.f;
}



/*
==============================================================================
Name : check
==============================================================================
*/

void  Pitch::check (Reading expected_hz, float tolerance_cents, std::source_location sloc) const
{
   assert (expected_hz > 0.f);
   assert (tolerance_cents >= 0.f);

   const auto reading = read ();
   const auto distance = cents_distance (reading, expected_hz);
   const bool ok = distance <= tolerance_cents;

   if (!ok)
   {
      std::fprintf (
         stderr,
         "check at %s:%u: Pitch on %s reads %.2f Hz, expected %.2f Hz, distance %.2f cents, tolerance %.2f cents\n",
         sloc.file_name (), unsigned (sloc.line ()), impl_channel_name (0),
         double (reading), double (expected_hz), double (distance), double (tolerance_cents)
      );
      std::fflush (stderr);
   }

   assert (ok);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Pitch::name () const
{
   return "Pitch";
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set_breakpoint
==============================================================================
*/

void  Pitch::set_breakpoint (Parameters parameters)
{
   const auto block = impl_bound () ? impl_recorded_blocks () : 0;

   assert (block >= _breakpoints.back ().block);

   _breakpoints.push_back ({block, parameters});
}



/*
==============================================================================
Name : window_parameters
==============================================================================
*/

Pitch::Parameters Pitch::window_parameters () const
{
   assert (impl_bound ());

   const auto window_end = impl_recorded_blocks ();
   const auto window_start = window_end - window ();

   Parameters ret;

   for (const auto & breakpoint : _breakpoints)
   {
      if (breakpoint.block <= window_start)
      {
         ret = breakpoint.parameters;
      }
      else
      {
         assert (breakpoint.block >= window_end);
      }
   }

   return ret;
}



/*
==============================================================================
Name : process_counter
==============================================================================
*/

Pitch::Reading Pitch::process_counter (std::span <const float> window)
{
   double first = 0.0;
   double last = 0.0;
   std::size_t count = 0;

   for (std::size_t i = 1 ; i < window.size () ; ++i)
   {
      const float prev = window [i - 1];
      const float cur = window [i];

      if ((prev < 0.f) && (cur >= 0.f))
      {
         const double t = double (i - 1) + double (-prev) / double (cur - prev);

         if (count == 0) first = t;
         last = t;
         ++count;
      }
   }

   if (count < 2) return 0.f; // no pitch detected, increase window

   return float (double (count - 1) * double (erb_SAMPLE_RATE) / (last - first));
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
