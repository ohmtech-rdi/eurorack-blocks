/*****************************************************************************

      FloatRange.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



enum class FloatRange
{
   Normalized,
   Bipolar,
   Pitch,
   Adsr,
};


template <FloatRange>
struct FloatRangeTrait
{
};


template <>
struct FloatRangeTrait <FloatRange::Normalized>
{
   static constexpr float Min = 0.f;
   static constexpr float Max = 1.f;
};


template <>
struct FloatRangeTrait <FloatRange::Bipolar>
{
   static constexpr float Min = -1.f;
   static constexpr float Max = 1.f;
};


template <>
struct FloatRangeTrait <FloatRange::Pitch>
{
   static constexpr float Min = 0.f;
   static constexpr float Max = 10.f;
};


template <>
struct FloatRangeTrait <FloatRange::Adsr>
{
   static constexpr float Min = 0.f;
   static constexpr float Max = 1.f;
};





}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
