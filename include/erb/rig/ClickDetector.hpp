/*****************************************************************************

      ClickDetector.hpp
      Copyright (c) 2026 Ohm Force

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>
#include <chrono>
#include <limits>
#include <numbers>

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

ClickDetector::ClickDetector (Setup setup)
:  Instrument (setup)
{
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  ClickDetector::bind (Bench & bench, AudioOut & output)
{
   bind_channel (bench, output);

   return connect ();
}



/*
==============================================================================
Name : set_highpass
==============================================================================
*/

void  ClickDetector::set_highpass (Highpass highpass, float hz)
{
   assert (hz > 0.f);
   assert (hz < 0.5f * float (erb_SAMPLE_RATE));

   _parameters.highpass = highpass;
   _parameters.highpass_hz = hz;
}



/*
==============================================================================
Name : set_background
Description :
   The output is highpassed first.

   For each sample of the analysis window, we measure what we assume to be
   the "background" before this sample. The window for this background is
   taken over -window-1ms ... -1ms to leave a small 1ms gap before,
   for the potential click to not be part of its own background.

   For this sample, the "score" is the (highpassed) sample over its background.
   The final score is the worst score from all samples.
   The background never goes under 'floor_db', so that a sample after digital
   silence or near-silence scores against a finite value.
==============================================================================
*/

void  ClickDetector::set_background (SystemClockVirtual::duration window, float floor_db)
{
   assert (window.count () > 0);

   _parameters.background_s = float (std::chrono::duration <double> (window).count ());
   _parameters.floor_db = floor_db;
}



/*
==============================================================================
Name : read
==============================================================================
*/

ClickDetector::Reading  ClickDetector::read () const
{
   return score ().db;
}



/*
==============================================================================
Name : check
==============================================================================
*/

void  ClickDetector::check (float threshold_db, std::source_location sloc) const
{
   const auto worst = score ();

   if (worst.db > threshold_db)
   {
      const auto ms = double (worst.at) * 1000.0 / double (erb_SAMPLE_RATE);

      std::fprintf (
         stderr,
         "check at %s:%u: ClickDetector on %s at %.2f ms reads %.2f dB, threshold %.2f dB\n",
         sloc.file_name (), unsigned (sloc.line ()), channel_name (0),
         ms, double (worst.db), double (threshold_db)
      );
      std::fflush (stderr);
   }

   assert (worst.db <= threshold_db);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   ClickDetector::name () const
{
   return "ClickDetector";
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : score
==============================================================================
*/

ClickDetector::Worst ClickDetector::score () const
{
   const auto window = window_audio (0);
   const auto filtered = filter (window);

   const auto background_samples = std::size_t (std::lround (double (_parameters.background_s) * double (erb_SAMPLE_RATE)));
   const auto first = background_samples + GapSamples;
   assert (window.size () > first);   // the window covers the background of its first scored sample

   // running sum of the squares, the rms of any span
   std::vector <double> sums (filtered.size () + 1, 0.0);

   for (std::size_t i = 0 ; i < filtered.size () ; ++i)
   {
      sums [i + 1] = sums [i] + double (filtered [i]) * double (filtered [i]);
   }

   const double floor = std::pow (10.0, double (_parameters.floor_db) / 20.0);

   std::vector <float> backgrounds (filtered.size (), 0.f);
   double worst = 0.0;
   Worst ret {-std::numeric_limits <float>::infinity (), first};

   for (std::size_t i = first ; i < filtered.size () ; ++i)
   {
      const auto end = i - GapSamples;
      const double background = std::max (std::sqrt ((sums [end] - sums [end - background_samples]) / double (background_samples)), floor);
      const double score = std::abs (double (filtered [i])) / background;

      backgrounds [i] = float (background);

      if (score > worst)
      {
         worst = score;
         ret.at = i;
      }
   }

   if (worst > 0.0)
   {
      ret.db = float (20.0 * std::log10 (worst));
   }

   if (trace ())
   {
      write_trace (0, {window, filtered, backgrounds});
   }

   return ret;
}



/*
==============================================================================
Name : filter
Note :
   Butterworth highpass as cascaded biquads
==============================================================================
*/

std::vector <float>  ClickDetector::filter (std::span <const float> window) const
{
   const auto order = std::size_t (_parameters.highpass);

   std::vector <double> signal (window.begin (), window.end ());

   const double w0 = 2.0 * std::numbers::pi * double (_parameters.highpass_hz) / double (erb_SAMPLE_RATE);
   const double cos_w0 = std::cos (w0);

   for (std::size_t k = 1 ; k <= order / 2 ; ++k)
   {
      const double q = 1.0 / (2.0 * std::cos (double (2 * k - 1) * std::numbers::pi / double (2 * order)));
      const double alpha = std::sin (w0) / (2.0 * q);
      const double a0 = 1.0 + alpha;
      const double b0 = 0.5 * (1.0 + cos_w0) / a0;
      const double b1 = -(1.0 + cos_w0) / a0;
      const double b2 = b0;
      const double a1 = -2.0 * cos_w0 / a0;
      const double a2 = (1.0 - alpha) / a0;

      // transposed direct form II
      double z1 = 0.0;
      double z2 = 0.0;

      for (auto & x : signal)
      {
         const double y = b0 * x + z1;
         z1 = b1 * x - a1 * y + z2;
         z2 = b2 * x - a2 * y;
         x = y;
      }
   }

   return std::vector <float> (signal.begin (), signal.end ());
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
