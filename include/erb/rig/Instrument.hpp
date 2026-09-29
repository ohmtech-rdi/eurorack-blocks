/*****************************************************************************

      Instrument.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <utility>

#include <cassert>
#include <cmath>
#include <cstdio>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : ctor
==============================================================================
*/

Instrument::Instrument (Setup setup)
:  _window (
      setup.analysis_window_nbr_blocks != 0
      ? setup.analysis_window_nbr_blocks
      : SystemClockVirtual::to_blocks_nbr (setup.analysis_window)
   )
{
   // one of the two not both
   assert ((setup.analysis_window_nbr_blocks != 0) != (setup.analysis_window.count () != 0));
   assert (_window > 0);
}



/*
==============================================================================
Name : dtor
==============================================================================
*/

Instrument::~Instrument ()
{
   assert (!impl_bound ()); // a connection outlived its instrument
}



/*
==============================================================================
Name : window
==============================================================================
*/

std::uint64_t  Instrument::window () const
{
   return _window;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_bind
Note :
   One 'impl_bind' per Control and then 'impl_connect'
==============================================================================
*/

template <typename Control>
void  Instrument::impl_bind (Bench & bench, Control & output)
{
   constexpr auto kind = slot_kind_of <Control>::value;

   assert ((_bench_ptr == nullptr) || (_bench_ptr == &bench));

   _bench_ptr = &bench;
   _channels.push_back ({kind, bench.impl_bind (kind, &output.impl_data), &output});
}



/*
==============================================================================
Name : impl_connect
==============================================================================
*/

Connection  Instrument::impl_connect ()
{
   assert (impl_bound ());

   return Connection {[this] () { impl_unbind (); }};
}



/*
==============================================================================
Name : impl_window_audio
Description :
   Gets the board recorded data. channel is 0 when instrument has only 1
   input.
==============================================================================
*/

std::span <const float>  Instrument::impl_window_audio (std::size_t channel) const
{
   impl_check_window (channel);
   assert (_channels [channel].kind == SlotKind::Audio);

   const auto recording = _bench_ptr->impl_recording_audio (_channels [channel].slot_index);
   const auto nbr_samples = std::size_t (_window) * erb_BUFFER_SIZE;

   return recording.last (nbr_samples);
}



/*
==============================================================================
Name : impl_window_analog
==============================================================================
*/

std::span <const float>  Instrument::impl_window_analog (std::size_t channel) const
{
   impl_check_window (channel);
   assert (_channels [channel].kind == SlotKind::Analog);

   return _bench_ptr->impl_recording_analog (_channels [channel].slot_index).last (std::size_t (_window));
}



/*
==============================================================================
Name : impl_window_digital
==============================================================================
*/

std::span <const std::uint8_t>   Instrument::impl_window_digital (std::size_t channel) const
{
   impl_check_window (channel);
   assert (_channels [channel].kind == SlotKind::Digital);

   return _bench_ptr->impl_recording_digital (_channels [channel].slot_index).last (std::size_t (_window));
}



/*
==============================================================================
Name : impl_golden_window_audio
==============================================================================
*/

std::span <const float>  Instrument::impl_golden_window_audio (std::size_t channel, std::source_location sloc) const
{
   impl_check_window (channel);
   assert (_channels [channel].kind == SlotKind::Audio);

   return _bench_ptr->impl_get_golden (SlotKind::Audio, _channels [channel].slot_index, _window, name (), sloc);
}



/*
==============================================================================
Name : impl_golden_window_analog
==============================================================================
*/

std::span <const float>  Instrument::impl_golden_window_analog (std::size_t channel, std::source_location sloc) const
{
   impl_check_window (channel);
   assert (_channels [channel].kind == SlotKind::Analog);

   return _bench_ptr->impl_get_golden (SlotKind::Analog, _channels [channel].slot_index, _window, name (), sloc);
}



/*
==============================================================================
Name : impl_quantised
==============================================================================
*/

std::vector <float>  Instrument::impl_quantised (std::span <const float> window)
{
   std::vector <float> ret (window.begin (), window.end ());

   for (auto & sample : ret) sample = quantise (sample);

   return ret;
}



/*
==============================================================================
Name : impl_notify_golden_mismatch
==============================================================================
*/

void  Instrument::impl_notify_golden_mismatch (std::size_t channel) const
{
   assert (impl_bound ());
   assert (channel < _channels.size ());

   _bench_ptr->impl_notify_golden_mismatch (_channels [channel].kind, _channels [channel].slot_index);
}



/*
==============================================================================
Name : impl_channel_name
==============================================================================
*/

const char *   Instrument::impl_channel_name (std::size_t channel) const
{
   assert (impl_bound ());

   return _bench_ptr->control_name (_channels [channel].control_ptr);
}



/*
==============================================================================
Name : impl_recorded_blocks
==============================================================================
*/

std::uint64_t  Instrument::impl_recorded_blocks () const
{
   assert (impl_bound ());

   return _bench_ptr->impl_recorded_blocks ();
}



/*
==============================================================================
Name : impl_bound
==============================================================================
*/

bool  Instrument::impl_bound () const
{
   return _bench_ptr != nullptr;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_unbind
==============================================================================
*/

void  Instrument::impl_unbind ()
{
   assert (impl_bound ());

   for (const auto & channel : _channels)
   {
      _bench_ptr->impl_unbind (channel.kind, channel.slot_index);
   }

   _channels.clear ();
   _bench_ptr = nullptr;
}



/*
==============================================================================
Name : impl_check_window
==============================================================================
*/

void  Instrument::impl_check_window (std::size_t channel) const
{
   assert (impl_bound ());
   assert (channel < _channels.size ());

   const auto recorded = _bench_ptr->impl_recorded_blocks ();

   if (_window > recorded)
   {
      std::fprintf (
         stderr,
         "check: %s on %s: window of %llu blocks, %llu blocks recorded since start\n",
         name (), impl_channel_name (channel),
         (unsigned long long) _window, (unsigned long long) recorded
      );
      std::fflush (stderr);
      assert (false);
   }
}



/*
==============================================================================
Name : scalar_distance
==============================================================================
*/

float scalar_distance (float a, float b)
{
   return std::abs (a - b);
}



/*
==============================================================================
Name : scalar_report
==============================================================================
*/

void  scalar_report (const char * name, const char * output_name, float reading, float expected, float tolerance)
{
   std::fprintf (
      stderr,
      "%s on %s reads %f, expected %f, distance %f, tolerance %f\n",
      name, output_name,
      double (reading), double (expected),
      double (scalar_distance (reading, expected)), double (tolerance)
   );
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
