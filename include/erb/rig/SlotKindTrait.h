/*****************************************************************************

      SlotKindTrait.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/CvIn.h"
#include "erb/CvOut.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/rig/Bench.h"



namespace erb
{
namespace rig
{



template <typename Control>
struct SlotKindTrait;

template <> struct SlotKindTrait <AudioOut> {
   static constexpr SlotKind value = SlotKind::Audio;
};

template <FloatRange Range> struct SlotKindTrait <CvOut <Range>> {
   static constexpr SlotKind value = SlotKind::Analog;
};

template <> struct SlotKindTrait <GateOut> {
   static constexpr SlotKind value = SlotKind::Digital;
};

template <> struct SlotKindTrait <AudioIn> {
   static constexpr SlotKind value = SlotKind::Audio;
};

template <FloatRange Range> struct SlotKindTrait <CvIn <Range>> {
   static constexpr SlotKind value = SlotKind::Analog;
};

template <> struct SlotKindTrait <GateIn> {
   static constexpr SlotKind value = SlotKind::Digital;
};



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
