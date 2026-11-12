/*****************************************************************************

      Spectrogram.hpp
      Copyright (c) 2026 Ohm Force

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>
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

Spectrogram::Spectrogram (Setup setup)
:  Instrument (setup)
{
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Spectrogram::bind (Bench & bench, AudioOut & output)
{
   bind_channel (bench, output);

   return connect ();
}



/*
==============================================================================
Name : set_frame
Description :
   Frame of the spectrogram, power of 2, Hann window, 1/8 frame hop.
==============================================================================
*/

void  Spectrogram::set_frame (std::size_t nbr_samples)
{
   assert (nbr_samples >= 16);
   assert ((nbr_samples & (nbr_samples - 1)) == 0);

   _parameters.frame = nbr_samples;
}



/*
==============================================================================
Name : read
==============================================================================
*/

Spectrogram::Reading Spectrogram::read () const
{
   return magnitudes (window_audio (0));
}



/*
==============================================================================
Name : check
Description :
   Compares the spectrogram of the window with 'expected', frame by frame.
   Per frame, the distance is the mean of the absolute dB differences of
   the bins, weighted by the power of the louder of the two. The worst
   frame must be within 'tolerance_db'.
==============================================================================
*/

void  Spectrogram::check (const Reading & expected, float tolerance_db, std::source_location sloc) const
{
   assert (tolerance_db >= 0.f);

   const auto window = window_audio (0);
   const auto reading = magnitudes (window);
   assert (reading.size () == expected.size ());

   const auto frame = _parameters.frame;
   const auto hop = frame / 8;

   std::vector <float> distances (window.size (), 0.f);
   float worst = 0.f;
   std::size_t worst_frame = 0;

   for (std::size_t f = 0 ; f < reading.size () ; ++f)
   {
      const auto d = distance (reading [f], expected [f]);

      // the frame's center hop
      std::fill_n (distances.begin () + std::ptrdiff_t (f * hop + frame / 2 - hop / 2), hop, d);

      if (d > worst)
      {
         worst = d;
         worst_frame = f;
      }
   }

   if (trace ())
   {
      write_trace (0, {window, distances});
   }

   if (worst > tolerance_db)
   {
      const auto ms = double (worst_frame * hop + frame / 2) * 1000.0 / double (erb_SAMPLE_RATE);

      std::fprintf (
         stderr,
         "check at %s:%u: Spectrogram on %s at %.2f ms reads %.2f dB from expected, tolerance %.2f dB\n",
         sloc.file_name (), unsigned (sloc.line ()), channel_name (0),
         ms, double (worst), double (tolerance_db)
      );
      std::fflush (stderr);
   }

   assert (worst <= tolerance_db);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Spectrogram::name () const
{
   return "Spectrogram";
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : magnitudes
==============================================================================
*/

Spectrogram::Reading Spectrogram::magnitudes (std::span <const float> window) const
{
   const auto frame = _parameters.frame;
   const auto hop = frame / 8;
   assert (window.size () >= frame);

   std::vector <double> hann (frame);
   for (std::size_t n = 0 ; n < frame ; ++n)
   {
      hann [n] = 0.5 - 0.5 * std::cos (2.0 * std::numbers::pi * double (n) / double (frame));
   }

   Reading ret;
   std::vector <std::complex <double>> data (frame);

   for (std::size_t pos = 0 ; pos + frame <= window.size () ; pos += hop)
   {
      for (std::size_t n = 0 ; n < frame ; ++n)
      {
         data [n] = hann [n] * double (window [pos + n]);
      }

      fft (data);

      std::vector <float> bins (frame / 2 + 1);
      for (std::size_t k = 0 ; k < bins.size () ; ++k) bins [k] = float (std::abs (data [k]));
      ret.push_back (std::move (bins));
   }

   return ret;
}



/*
==============================================================================
Name : distance
Description :
   The mean of the absolute dB differences of the bins, weighted by the
   power of the louder of the two
==============================================================================
*/

float Spectrogram::distance (const std::vector <float> & reading, const std::vector <float> & expected)
{
   assert (reading.size () == expected.size ());

   double weighted = 0.0;
   double weights = 0.0;

   for (std::size_t k = 0 ; k < reading.size () ; ++k)
   {
      const double a = expected [k];
      const double b = reading [k];
      const double w = std::max (a, b) * std::max (a, b);

      weighted += w * std::abs (20.0 * std::log10 ((b + 1e-12) / (a + 1e-12)));
      weights += w;
   }

   return (weights > 0.0) ? float (weighted / weights) : 0.f;
}



/*
==============================================================================
Name : fft
Description :
   In place, radix 2, size a power of 2
==============================================================================
*/

void  Spectrogram::fft (std::vector <std::complex <double>> & data)
{
   const auto n = data.size ();

   for (std::size_t i = 1, j = 0 ; i < n ; ++i)
   {
      auto bit = n >> 1;
      for ( ; j & bit ; bit >>= 1) j ^= bit;
      j ^= bit;
      if (i < j) std::swap (data [i], data [j]);
   }

   for (std::size_t len = 2 ; len <= n ; len <<= 1)
   {
      const auto w_len = std::polar (1.0, -2.0 * std::numbers::pi / double (len));

      for (std::size_t i = 0 ; i < n ; i += len)
      {
         std::complex <double> w = 1.0;

         for (std::size_t k = 0 ; k < len / 2 ; ++k)
         {
            const auto u = data [i + k];
            const auto v = data [i + k + len / 2] * w;
            data [i + k] = u + v;
            data [i + k + len / 2] = u - v;
            w *= w_len;
         }
      }
   }
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
