/*****************************************************************************

      Bench.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/SystemClockVirtual.h"

#include <functional>
#include <source_location>
#include <span>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



enum class SlotKind
{
   Digital,
   Analog,
   Audio,
};



class Bench
{
public:
   virtual        ~Bench () = default;

   virtual std::size_t
                  impl_bind (SlotKind kind, const void * slot_data) = 0;
   virtual void   impl_unbind (SlotKind kind, std::size_t slot_index) = 0;

   virtual std::span <const std::uint8_t>
                  impl_recording_digital (std::size_t slot_index) const = 0;
   virtual std::span <const float>
                  impl_recording_analog (std::size_t slot_index) const = 0;
   virtual std::span <const float>
                  impl_recording_audio (std::size_t slot_index) const = 0;
   virtual std::uint64_t
                  impl_recorded_blocks () const = 0;

   virtual const char *
                  control_name (const void * control_ptr) const = 0;

   virtual bool   impl_pump_until (const std::function <bool ()> & predicate, SystemClockVirtual::duration timeout) = 0;

   virtual std::span <const float>
                  impl_get_golden (SlotKind kind, std::size_t slot_index, std::uint64_t nbr_blocks, const char * instrument_name, std::source_location sloc) = 0;
   virtual void   impl_notify_golden_mismatch (SlotKind kind, std::size_t slot_index) = 0;
};



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
