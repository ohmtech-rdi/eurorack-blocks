/*****************************************************************************

      Measurement.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/Buffer.h"
#include "erb/CvOut.h"
#include "erb/GateOut.h"

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

template <SlotKind Kind>
struct SlotKindType;

template <> struct SlotKindType <SlotKind::Digital> { using type = std::uint8_t; };
template <> struct SlotKindType <SlotKind::Analog> { using type = float; };
template <> struct SlotKindType <SlotKind::Audio> { using type = Buffer; };


template <typename Control>
struct slot_kind_of;

template <> struct slot_kind_of <AudioOut> { static constexpr SlotKind value = SlotKind::Audio; };
template <FloatRange Range> struct slot_kind_of <CvOut <Range>> { static constexpr SlotKind value = SlotKind::Analog; };
template <> struct slot_kind_of <GateOut> { static constexpr SlotKind value = SlotKind::Digital; };


class MeasurementBase
{
public:
   virtual        ~MeasurementBase () = default;

   virtual const char *
                  name () const = 0;

   // session time zero
   virtual void   impl_start () = 0;
};

// lab measurement device abstraction (peak meter, etc.)
// measurement is connected before 'boot', and idle before 'start'
// then it is fed one frame after every postprocess so it can do everything
// a real-world device could do.
// Concrete class must support:
// - Reading: the type of the data measured
// - reading: the operator simulated look at the equipment
// - distance: the distance between 2 readings
// - report: a structured report on failure

template <SlotKind Kind>
class Measurement
:  public MeasurementBase
{
public:
   using Slot = typename SlotKindType <Kind>::type;

   static constexpr SlotKind
                  kind = Kind;

   virtual void   impl_feed (const Slot & slot) = 0;
};



inline float   scalar_distance (float a, float b);
inline void    scalar_report (const char * name, const char * output_name, float reading, float expected, float tolerance);



}  // namespace rig
}  // namespace erb



#include "erb/rig/Measurement.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
