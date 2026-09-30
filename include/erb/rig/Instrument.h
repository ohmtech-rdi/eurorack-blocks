/*****************************************************************************

      Instrument.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/Buffer.h"
#include "erb/CvOut.h"
#include "erb/GateOut.h"
#include "erb/rig/Bench.h"
#include "erb/rig/SlotKindTrait.h"
#include "erb/rig/Connection.h"
#include "erb/rig/SystemClockVirtual.h"
#include "erb/rig/Wave.h"

#include <source_location>
#include <span>
#include <vector>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



// lab measurement device abstraction (peak meter, etc.)

class Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   struct Setup
   {
      SystemClockVirtual::duration
                  analysis_window {};       // one of the two
      std::uint64_t
                  analysis_window_nbr_blocks = 0;
      bool        trace = false;
   };

   inline explicit
                  Instrument (Setup setup);
   virtual        ~Instrument ();

   virtual const char *
                  name () const = 0;

   inline std::uint64_t
                  window () const;   // blocks



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
   template <typename Control>
   void           impl_bind (Bench & bench, Control & output);
   inline Connection
                  impl_connect ();

   inline std::span <const float>
                  impl_window_audio (std::size_t channel) const;
   inline std::span <const float>
                  impl_window_analog (std::size_t channel) const;
   inline std::span <const std::uint8_t>
                  impl_window_digital (std::size_t channel) const;

   inline std::span <const float>
                  impl_golden_window_audio (std::size_t channel, std::source_location sloc) const;
   inline std::span <const float>
                  impl_golden_window_analog (std::size_t channel, std::source_location sloc) const;
   static inline std::vector <float>
                  impl_quantized (std::span <const float> window);
   inline void    impl_notify_golden_mismatch (std::size_t channel) const;

   inline bool    impl_trace () const;
   inline void    impl_write_trace (std::size_t channel, const std::vector <std::span <const float>> & traces) const;

   inline const char *
                  impl_channel_name (std::size_t channel) const;
   inline bool    impl_bound () const;
   inline std::uint64_t
                  impl_recorded_blocks () const;   // since 'start'



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Channel
   {
      SlotKind    kind;
      std::size_t slot_index;
      const void *
                  control_ptr;   // for logs
   };

   inline void    impl_unbind ();
   inline void    impl_check_window (std::size_t channel) const;

   const std::uint64_t
                  _window;   // blocks
   const bool     _trace_flag;
   Bench *        _bench_ptr = nullptr;
   std::vector <Channel>
                  _channels;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Instrument () = delete;
                  Instrument (const Instrument & rhs) = delete;
                  Instrument (Instrument && rhs) = delete;
   Instrument &   operator = (const Instrument & rhs) = delete;
   Instrument &   operator = (Instrument && rhs) = delete;
   bool           operator == (const Instrument & rhs) const = delete;
   bool           operator != (const Instrument & rhs) const = delete;



}; // class Instrument



inline float   scalar_distance (float a, float b);
inline void    scalar_report (const char * name, const char * output_name, float reading, float expected, float tolerance);



}  // namespace rig
}  // namespace erb



#include "erb/rig/Instrument.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
