/*****************************************************************************

      BoardGeneric.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <cstring>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : load
==============================================================================
*/

template <std::size_t N>
std::array <uint8_t, N> BoardGeneric::load (size_t page)
{
   // This is a NAND flash so any untouched bits read as 1

   auto ret = std::array <uint8_t, N> {};
   ret.fill (0xff);

   auto it = _persistent_map.find (page);

   if (it != _persistent_map.end ())
   {
      const auto & stored = it->second;
      std::memcpy (&ret [0], &stored [0], std::min (stored.size (), N));
   }

   return ret;
}



/*
==============================================================================
Name : save
==============================================================================
*/

template <typename Data>
void  BoardGeneric::save (size_t page, const Data & data)
{
   // trim trailing 0xff bytes as they can be treated as untouched bits

   auto end = std::find_if (
      data.rbegin (), data.rend (),
      [](uint8_t byte){ return byte != 0xff; }
   ).base ();

   if (end == data.begin ())
   {
      _persistent_map.erase (page);
   }
   else
   {
      _persistent_map [page] = std::vector <uint8_t> { data.begin (), end };
   }
}



/*
==============================================================================
Name : erase
==============================================================================
*/

void  BoardGeneric::erase (size_t page)
{
   _persistent_map.erase (page);
}



/*
==============================================================================
Name : scroll
Description :
   Convenience to emits multiple events for as many counts.
   Encoder detects a detent when the leading pin reads high then
   low for the number of frames set by 'configure'
==============================================================================
*/

template <EncoderLeadingType LeadingType>
void  BoardGeneric::scroll (Encoder <LeadingType> & encoder, int nbr_detents)
{
   assert (_boot_flag);

   auto & data_a = impl_digital_slot (encoder.impl_data_a);
   auto & data_b = impl_digital_slot (encoder.impl_data_b);

   const bool positive = nbr_detents > 0;
   const bool pulse_a = positive == (LeadingType == EncoderLeadingType::B);
   auto & data = pulse_a ? data_a : data_b;

   const auto nbr_zeros = encoder.impl_nbr_debounce_zeros ();

   for (int i = 0 ; i < std::abs (nbr_detents) ; ++i)
   {
      data = 1;
      impl_steps (1);
      data = 0;
      impl_steps (nbr_zeros);
   }
}



/*
==============================================================================
Name : scroll
==============================================================================
*/

template <EncoderLeadingType LeadingType>
void  BoardGeneric::scroll (EncoderButton <LeadingType> & encoder, int nbr_detents)
{
   scroll (encoder.encoder, nbr_detents);
}



/*
==============================================================================
Name : set
==============================================================================
*/

template <FloatRange Range>
void  BoardGeneric::set (Pot <Range> & pot, float value)
{
   assert (_boot_flag);
   assert (value >= Pot <Range>::ValueMin);
   assert (value <= Pot <Range>::ValueMax);

   impl_analog_slot (pot.impl_data) = value;
}



/*
==============================================================================
Name : set
==============================================================================
*/

template <FloatRange Range>
void  BoardGeneric::set (CvIn <Range> & cv, float value)
{
   assert (_boot_flag);
   assert (value >= CvIn <Range>::ValueMin);
   assert (value <= CvIn <Range>::ValueMax);

   impl_analog_slot (cv.impl_data) = value;
}



/*
==============================================================================
Name : connect
==============================================================================
*/

template <typename Control, SlotKind Kind>
void  BoardGeneric::connect (Control & output, Measurement <Kind> & measurement)
{
   static_assert (slot_kind_of <Control>::value == Kind);

   assert (_setup_flag);
   assert (!_boot_flag);
   assert (impl_measurement_output_name (measurement) == nullptr); // only once

   if constexpr (Kind == SlotKind::Digital)
   {
      _digital_measurements.push_back ({impl_slot_index (_digital_outputs, output.impl_data), &output, &measurement});
   }
   else if constexpr (Kind == SlotKind::Analog)
   {
      _analog_measurements.push_back ({impl_slot_index (_analog_outputs, output.impl_data), &output, &measurement});
   }
   else
   {
      _audio_measurements.push_back ({impl_slot_index (_audio_outputs, output.impl_data), &output, &measurement});
   }

   ++_nbr_measurements;
}



/*
==============================================================================
Name : check
==============================================================================
*/

template <typename Measurement>
void  BoardGeneric::check (const Measurement & measurement, const typename Measurement::Reading & expected, float tolerance)
{
   assert (_boot_flag);
   assert (tolerance >= 0.f);

   const auto * output_name = impl_measurement_output_name (measurement);
   assert (output_name != nullptr);

   const auto reading = measurement.reading ();
   const bool ok = Measurement::distance (reading, expected) <= tolerance;

   if (!ok)
   {
      std::fprintf (stderr, "check: ");
      Measurement::report (
         measurement.name (), output_name,
         reading, expected, tolerance
      );
      std::fflush (stderr);
   }

   assert (ok);
}



/*
==============================================================================
Name : wait_until
==============================================================================
*/

template <typename Predicate>
void  BoardGeneric::wait_until (Predicate predicate, SystemClockVirtual::duration timeout)
{
   const bool ok = impl_wait_until (predicate, timeout);

   if (!ok)
   {
      const auto ms = std::chrono::duration_cast <std::chrono::milliseconds> (timeout).count ();
      std::fprintf (stderr, "wait_until: condition not met within %lld ms\n", (long long) ms);
      std::fflush (stderr);
   }

   assert (ok);
}



/*
==============================================================================
Name : wait_until_equal
==============================================================================
*/

template <typename Format>
void  BoardGeneric::wait_until_equal (Display <Format> & display, const Screen <Format> & screen, SystemClockVirtual::duration timeout)
{
   const bool ok = impl_wait_until (
      [&display, &screen] () { return same (display, screen); },
      timeout
   );

   const auto actual_path = screen.file.actual_path ();

   if (ok)
   {
      std::remove (actual_path.c_str ());   // stale if present
   }
   else
   {
      const auto ms = std::chrono::duration_cast <std::chrono::milliseconds> (timeout).count ();
      std::fprintf (
         stderr,
         "wait_until_equal: display did not match '%s' within %lld ms, actual written to '%s'\n",
         screen.file.path.c_str (), (long long) ms, actual_path.c_str ()
      );
      std::fflush (stderr);

      write_screen <Format> (display.impl_data, {.path = actual_path, .rotate = screen.file.rotate});
   }

   assert (ok);
}



/*
==============================================================================
Name : impl_slot_index
Description :
   'data' is the 'impl_data' of a control, a reference into 'slots'.
==============================================================================
*/

template <typename T>
std::size_t BoardGeneric::impl_slot_index (const std::vector <T> & slots, const T & data)
{
   const auto * begin = slots.data ();
   const auto * end = begin + slots.size ();
   assert (!std::less <> {} (&data, begin));
   assert (std::less <> {} (&data, end));

   return std::size_t (&data - begin);
}



/*
==============================================================================
Name : impl_wait_until
==============================================================================
*/

template <typename Predicate>
bool  BoardGeneric::impl_wait_until (Predicate predicate, SystemClockVirtual::duration timeout)
{
   assert (_boot_flag);

   const auto deadline = SystemClockVirtual::now () + timeout;

   while (!predicate ())
   {
      if (SystemClockVirtual::now () >= deadline)
      {
         return false;
      }

      impl_step ();
   }

   return true;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
