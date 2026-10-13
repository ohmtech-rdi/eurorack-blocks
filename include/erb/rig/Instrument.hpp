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
,  _trace_flag (setup.trace)
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
   assert (!bound ()); // a connection outlived its instrument
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
Name : bind_channel
Note :
   One 'bind_channel' per Control and then 'connect'
==============================================================================
*/

template <typename Control>
void  Instrument::bind_channel (Bench & bench, Control & output)
{
   constexpr auto kind = SlotKindTrait <Control>::value;

   assert ((_bench_ptr == nullptr) || (_bench_ptr == &bench));

   _bench_ptr = &bench;
   _channels.push_back ({kind, bench.impl_bind_output (kind, &output.impl_data), &output});
}



/*
==============================================================================
Name : connect
==============================================================================
*/

Connection  Instrument::connect ()
{
   assert (bound ());

   return Connection {[this] () { unbind (); }};
}



/*
==============================================================================
Name : window_audio
Description :
   Gets the board recorded data. channel is 0 when instrument has only 1
   input.
==============================================================================
*/

std::span <const float>  Instrument::window_audio (std::size_t channel) const
{
   check_window (channel);
   assert (_channels [channel].kind == SlotKind::Audio);

   const auto recording = _bench_ptr->impl_recording_audio (_channels [channel].slot_index);
   const auto nbr_samples = std::size_t (_window) * erb_BUFFER_SIZE;

   return recording.last (nbr_samples);
}



/*
==============================================================================
Name : window_analog
==============================================================================
*/

std::span <const float>  Instrument::window_analog (std::size_t channel) const
{
   check_window (channel);
   assert (_channels [channel].kind == SlotKind::Analog);

   return _bench_ptr->impl_recording_analog (_channels [channel].slot_index).last (std::size_t (_window));
}



/*
==============================================================================
Name : window_digital
==============================================================================
*/

std::span <const std::uint8_t>   Instrument::window_digital (std::size_t channel) const
{
   check_window (channel);
   assert (_channels [channel].kind == SlotKind::Digital);

   return _bench_ptr->impl_recording_digital (_channels [channel].slot_index).last (std::size_t (_window));
}



/*
==============================================================================
Name : golden_window_audio
==============================================================================
*/

std::span <const float>  Instrument::golden_window_audio (std::size_t channel, std::source_location sloc) const
{
   check_window (channel);
   assert (_channels [channel].kind == SlotKind::Audio);

   return _bench_ptr->impl_get_golden (SlotKind::Audio, _channels [channel].slot_index, _window, name (), sloc);
}



/*
==============================================================================
Name : golden_window_analog
==============================================================================
*/

std::span <const float>  Instrument::golden_window_analog (std::size_t channel, std::source_location sloc) const
{
   check_window (channel);
   assert (_channels [channel].kind == SlotKind::Analog);

   return _bench_ptr->impl_get_golden (SlotKind::Analog, _channels [channel].slot_index, _window, name (), sloc);
}



/*
==============================================================================
Name : golden_window_digital
Note :
   0 and 1 as floats at block rate.
==============================================================================
*/

std::span <const float>  Instrument::golden_window_digital (std::size_t channel, std::source_location sloc) const
{
   check_window (channel);
   assert (_channels [channel].kind == SlotKind::Digital);

   return _bench_ptr->impl_get_golden (SlotKind::Digital, _channels [channel].slot_index, _window, name (), sloc);
}



/*
==============================================================================
Name : quantized
==============================================================================
*/

std::vector <float>  Instrument::quantized (std::span <const float> window)
{
   std::vector <float> ret (window.begin (), window.end ());

   for (auto & sample : ret) sample = quantize (sample);

   return ret;
}



/*
==============================================================================
Name : trace
==============================================================================
*/

bool  Instrument::trace () const
{
   return _trace_flag;
}



/*
==============================================================================
Name : write_trace
==============================================================================
*/

void  Instrument::write_trace (std::size_t channel, const std::vector <std::span <const float>> & traces) const
{
   assert (bound ());
   assert (channel < _channels.size ());
   assert (!traces.empty ());

   const auto file = _bench_ptr->impl_get_trace_file (_channels [channel].kind, _channels [channel].slot_index, channel_name (channel), name ());

   Wave wave;
   wave.sample_rate = file.sample_rate;
   wave.nbr_channels = traces.size ();

   const auto nbr_frames = traces [0].size ();

   for (std::size_t i = 0 ; i < nbr_frames ; ++i)
   {
      for (const auto & trace : traces)
      {
         assert (trace.size () == nbr_frames);
         wave.samples.push_back (trace [i]);
      }
   }

   write_wave (wave, file.path, WaveFormat::Float32);
}



/*
==============================================================================
Name : notify_golden_mismatch
==============================================================================
*/

void  Instrument::notify_golden_mismatch (std::size_t channel) const
{
   assert (bound ());
   assert (channel < _channels.size ());

   _bench_ptr->impl_notify_golden_mismatch (_channels [channel].kind, _channels [channel].slot_index);
}



/*
==============================================================================
Name : channel_name
==============================================================================
*/

const char *   Instrument::channel_name (std::size_t channel) const
{
   assert (bound ());

   return _bench_ptr->control_name (_channels [channel].control_ptr);
}



/*
==============================================================================
Name : recorded_blocks
==============================================================================
*/

std::uint64_t  Instrument::recorded_blocks () const
{
   assert (bound ());

   return _bench_ptr->impl_recorded_blocks ();
}



/*
==============================================================================
Name : bound
==============================================================================
*/

bool  Instrument::bound () const
{
   return _bench_ptr != nullptr;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : unbind
==============================================================================
*/

void  Instrument::unbind ()
{
   assert (bound ());

   for (const auto & channel : _channels)
   {
      _bench_ptr->impl_unbind_output (channel.kind, channel.slot_index);
   }

   _channels.clear ();
   _bench_ptr = nullptr;
}



/*
==============================================================================
Name : check_window
==============================================================================
*/

void  Instrument::check_window (std::size_t channel) const
{
   assert (bound ());
   assert (channel < _channels.size ());

   const auto recorded = _bench_ptr->impl_recorded_blocks ();

   if (_window > recorded)
   {
      std::fprintf (
         stderr,
         "check: %s on %s: window of %llu blocks, %llu blocks recorded since start\n",
         name (), channel_name (channel),
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
