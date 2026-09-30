/*****************************************************************************

      Pitch.h
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



class Pitch
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Detector
   {
      Counter,    // reciprocal frequency counter on rising zero crossings
   };

   using Reading = float; // Hertz, no detection=0

   static inline float
                  cents_distance (float a_hz, float b_hz);

   inline explicit
                  Pitch (Setup setup);
   virtual        ~Pitch () override = default;

   inline Connection
                  bind (Bench & bench, AudioOut & output);

   inline void    set_detector (Detector detector);

   inline Reading read () const;
   inline void    check (Reading expected_hz, float tolerance_cents, std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Parameters
   {
      Detector    detector = Detector::Counter;
   };

   struct Breakpoint
   {
      std::uint64_t
                  block;      // since 'start'
      Parameters  parameters;
   };

   inline void    set_breakpoint (Parameters parameters);
   inline Parameters
                  window_parameters () const;
   static inline Reading
                  process_counter (std::span <const float> window);

   std::vector <Breakpoint>
                  _breakpoints;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Pitch () = delete;
                  Pitch (const Pitch & rhs) = delete;
                  Pitch (Pitch && rhs) = delete;
   Pitch &        operator = (const Pitch & rhs) = delete;
   Pitch &        operator = (Pitch && rhs) = delete;
   bool           operator == (const Pitch & rhs) const = delete;
   bool           operator != (const Pitch & rhs) const = delete;



}; // class Pitch



}  // namespace rig
}  // namespace erb



#include "erb/rig/Pitch.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
