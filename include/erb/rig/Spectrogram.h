/*****************************************************************************

      Spectrogram.h
      Copyright (c) 2026 Ohm Force

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/rig/Instrument.h"

#include <complex>
#include <source_location>
#include <span>
#include <vector>

#include <cstddef>



namespace erb
{
namespace rig
{



class Spectrogram
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Reading = std::vector <std::vector <float>>;   // magnitudes per frame per bin

   inline explicit
                  Spectrogram (Setup setup);
   virtual        ~Spectrogram () override = default;

   inline Connection
                  bind (Bench & bench, AudioOut & output);

   inline void    set_frame (std::size_t nbr_samples);

   inline Reading read () const;
   inline void    check (const Reading & expected, float tolerance_db, std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Parameters
   {
      std::size_t frame = 2048;
   };

   inline Reading magnitudes (std::span <const float> window) const;
   static inline float
                  distance (const std::vector <float> & reading, const std::vector <float> & expected);
   static inline void
                  fft (std::vector <std::complex <double>> & data);

   Parameters     _parameters;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Spectrogram () = delete;
                  Spectrogram (const Spectrogram & rhs) = delete;
                  Spectrogram (Spectrogram && rhs) = delete;
   Spectrogram &  operator = (const Spectrogram & rhs) = delete;
   Spectrogram &  operator = (Spectrogram && rhs) = delete;
   bool           operator == (const Spectrogram & rhs) const = delete;
   bool           operator != (const Spectrogram & rhs) const = delete;



}; // class Spectrogram



}  // namespace rig
}  // namespace erb



#include "erb/rig/Spectrogram.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
