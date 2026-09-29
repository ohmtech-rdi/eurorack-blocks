/*****************************************************************************

      Envelope.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/rig/Instrument.h"

#include <source_location>
#include <span>
#include <vector>

#include <cstdint>



namespace erb
{
namespace rig
{



class Envelope
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Detector
   {
      Peak,
      Rms,
   };

   using Reading = std::vector <float>;   // linear

   static constexpr float
                  Floor = 1e-6f; // -120 dB, linear 0 in 16-bit

   static inline float
                  to_db (float level);

   inline explicit
                  Envelope (Setup setup);
   virtual        ~Envelope () override = default;

   inline Connection
                  bind (Bench & bench, AudioOut & output);

   inline void    set_detector (Detector detector);
   inline void    set_attack (SystemClockVirtual::duration attack);
   inline void    set_release (SystemClockVirtual::duration release);

   inline Reading read () const;
   inline void    check (float tolerance_db, std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Parameters
   {
      Detector    detector = Detector::Peak;
      float       attack_s = 0.001f;
      float       release_s = 0.020f;
   };

   struct Breakpoint
   {
      std::uint64_t
                  block;      // since 'start'
      Parameters  parameters;
   };

   inline void    set_breakpoint (Parameters parameters);
   inline Reading process (std::span <const float> window) const;

   std::vector <Breakpoint>
                  _breakpoints;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Envelope () = delete;
                  Envelope (const Envelope & rhs) = delete;
                  Envelope (Envelope && rhs) = delete;
   Envelope &     operator = (const Envelope & rhs) = delete;
   Envelope &     operator = (Envelope && rhs) = delete;
   bool           operator == (const Envelope & rhs) const = delete;
   bool           operator != (const Envelope & rhs) const = delete;



}; // class Envelope



}  // namespace rig
}  // namespace erb



#include "erb/rig/Envelope.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
