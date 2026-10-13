/*****************************************************************************

      Envelope.hpp
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

Envelope::Envelope (Setup setup)
:  Instrument (setup)
{
   _breakpoints.push_back ({0, Parameters {}});
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Envelope::bind (Bench & bench, AudioOut & output)
{
   impl_bind (bench, output);

   return impl_connect ();
}



/*
==============================================================================
Name : set_detector
==============================================================================
*/

void  Envelope::set_detector (Detector detector)
{
   auto parameters = _breakpoints.back ().parameters;
   parameters.detector = detector;
   set_breakpoint (parameters);
}



/*
==============================================================================
Name : set_attack
==============================================================================
*/

void  Envelope::set_attack (SystemClockVirtual::duration attack)
{
   assert (attack.count () > 0);

   auto parameters = _breakpoints.back ().parameters;
   parameters.attack_s = float (std::chrono::duration <double> (attack).count ());
   set_breakpoint (parameters);
}



/*
==============================================================================
Name : set_release
==============================================================================
*/

void  Envelope::set_release (SystemClockVirtual::duration release)
{
   assert (release.count () > 0);

   auto parameters = _breakpoints.back ().parameters;
   parameters.release_s = float (std::chrono::duration <double> (release).count ());
   set_breakpoint (parameters);
}



/*
==============================================================================
Name : to_db
==============================================================================
*/

float Envelope::to_db (float level)
{
   return 20.f * std::log10 (std::max (level, Floor));
}



/*
==============================================================================
Name : read
==============================================================================
*/

Envelope::Reading   Envelope::read () const
{
   return process (impl_window_audio (0));
}



/*
==============================================================================
Name : check
==============================================================================
*/

void  Envelope::check (float tolerance_db, std::source_location sloc) const
{
   assert (tolerance_db >= 0.f);

   const auto golden_samples = impl_golden_window_audio (0, sloc);
   const auto golden = process (golden_samples);
   const auto actual_samples = impl_quantized (impl_window_audio (0));
   const auto actual = process (actual_samples);

   assert (golden.size () == actual.size ());

   float ratio = 1.f;   // >= 1, the worst either way
   std::size_t worst = 0;

   for (std::size_t i = 0 ; i < actual.size () ; ++i)
   {
      const auto r = (actual [i] > golden [i]) ? actual [i] / golden [i] : golden [i] / actual [i];

      if (r > ratio)
      {
         ratio = r;
         worst = i;
      }
   }

   const auto distance = 20.f * std::log10 (ratio);

   if (impl_trace () || distance > tolerance_db)
   {
      impl_write_trace (0, {actual_samples, actual, golden_samples, golden});
   }

   if (distance > tolerance_db)
   {
      const auto ms = double (worst) * 1000.0 / double (erb_SAMPLE_RATE);

      std::fprintf (
         stderr,
         "check at %s:%u: Envelope on %s at %.2f ms reads %.2f dB, golden %.2f dB, distance %.2f dB, tolerance %.2f dB, ",
         sloc.file_name (), unsigned (sloc.line ()), impl_channel_name (0),
         ms, double (to_db (actual [worst])), double (to_db (golden [worst])),
         double (distance), double (tolerance_db)
      );
      std::fflush (stderr);

      impl_notify_golden_mismatch (0);
   }
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Envelope::name () const
{
   return "Envelope";
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set_breakpoint
==============================================================================
*/

void  Envelope::set_breakpoint (Parameters parameters)
{
   const auto block = impl_bound () ? impl_recorded_blocks () : 0;

   assert (block >= _breakpoints.back ().block);

   _breakpoints.push_back ({block, parameters});
}



/*
==============================================================================
Name : process
==============================================================================
*/

Envelope::Reading   Envelope::process (std::span <const float> window) const
{
   Reading ret;
   ret.resize (window.size ());

   const auto nbr_blocks = std::uint64_t (window.size () / erb_BUFFER_SIZE);
   assert (impl_bound ());
   const auto window_start = impl_recorded_blocks () - nbr_blocks;
   const auto window_end = window_start + nbr_blocks;

   double state = 0.0;

   for (std::size_t c = 0 ; c < _breakpoints.size () ; ++c)
   {
      const auto seg_start = std::max (_breakpoints [c].block, window_start);
      const auto seg_end = std::min ((c + 1 < _breakpoints.size ()) ? _breakpoints [c + 1].block : window_end, window_end);

      if (seg_start >= seg_end) continue;

      // 1-pole envelope follower
      const auto & parameters = _breakpoints [c].parameters;
      const bool rms = (parameters.detector == Detector::Rms);
      const double attack_coef = 1.0 - std::exp (-1.0 / (double (parameters.attack_s) * double (erb_SAMPLE_RATE)));
      const double release_coef = 1.0 - std::exp (-1.0 / (double (parameters.release_s) * double (erb_SAMPLE_RATE)));

      const auto first = std::size_t (seg_start - window_start) * erb_BUFFER_SIZE;
      const auto last = std::size_t (seg_end - window_start) * erb_BUFFER_SIZE;

      for (std::size_t i = first ; i < last ; ++i)
      {
         const double x = double (window [i]);
         const double in = rms ? x * x : std::abs (x);

         state += ((in > state) ? attack_coef : release_coef) * (in - state);

         const double level = rms ? std::sqrt (state) : state;

         ret [i] = std::max (float (level), Floor);
      }
   }

   return ret;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
