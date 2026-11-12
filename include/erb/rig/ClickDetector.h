/*****************************************************************************

      ClickDetector.h
      Copyright (c) 2026 Ohm Force

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/rig/Instrument.h"

#include <source_location>
#include <span>
#include <vector>

#include <cstddef>



namespace erb
{
namespace rig
{



class ClickDetector
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Highpass
   {
      Butterworth2 = 2, // Butterworth order 2
      Butterworth4 = 4, // Butterworth order 4
      Butterworth6 = 6, // etc.
      Butterworth8 = 8,
   };

   using Reading = float;   // dB, the worst score of the window

   inline explicit
                  ClickDetector (Setup setup);
   virtual        ~ClickDetector () override = default;

   inline Connection
                  bind (Bench & bench, AudioOut & output);

   inline void    set_highpass (Highpass highpass, float hz);
   inline void    set_background (SystemClockVirtual::duration window, float floor_db);

   inline Reading read () const;
   inline void    check (float threshold_db, std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Parameters
   {
      Highpass    highpass = Highpass::Butterworth4;
      float       highpass_hz = 10000.f;
      float       background_s = 0.050f;
      float       floor_db = -90.f;
   };

   struct Worst
   {
      float       db;   // the worst score of the window
      std::size_t at;   // its sample in the window
   };

   static constexpr std::size_t
                  GapSamples = 48;   // 1 ms, a click out of its own background

   inline Worst   score () const;
   inline std::vector <float>
                  filter (std::span <const float> window) const;

   Parameters     _parameters;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  ClickDetector () = delete;
                  ClickDetector (const ClickDetector & rhs) = delete;
                  ClickDetector (ClickDetector && rhs) = delete;
   ClickDetector &
                  operator = (const ClickDetector & rhs) = delete;
   ClickDetector &
                  operator = (ClickDetector && rhs) = delete;
   bool           operator == (const ClickDetector & rhs) const = delete;
   bool           operator != (const ClickDetector & rhs) const = delete;



}; // class ClickDetector



}  // namespace rig
}  // namespace erb



#include "erb/rig/ClickDetector.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
