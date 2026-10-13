/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/BoardGeneric.h"
#include "erb/rig/Wave.h"

#include "erb/detail/ModuleBoard.h"

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   #include "erb/rig/SdCard.h"
#endif

#include <algorithm>
#include <filesystem>
#include <set>

#include "erb/rig/Source.h"
#include <cassert>
#include <utility>
#include <cmath>
#include <cstdio>
#include <functional>



namespace erb
{
namespace rig
{



#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

// process-lifetime memory pools, allocates before 'main'
static ModuleBoard module_board;

#if defined (__clang__)
   #pragma clang diagnostic pop
#endif

static struct ModuleBoardCurrent
{
   ModuleBoardCurrent () { ModuleBoard::impl_set_current (&module_board); }
} module_board_current;



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardGeneric::BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs)
:  _digital_inputs (nbr_digital_inputs, 0)
,  _analog_inputs (nbr_analog_inputs, 0.f)
,  _audio_inputs (nbr_audio_inputs, Buffer {})
,  _digital_inputs_standing (nbr_digital_inputs, 0)
,  _analog_inputs_standing (nbr_analog_inputs, 0.f)
,  _digital_outputs (nbr_digital_outputs, 0)
,  _analog_outputs (nbr_analog_outputs, 0.f)
,  _audio_outputs (nbr_audio_outputs, Buffer {})
{
   // board is first member, so pools are reset before anything else,
   // and the previous module is guaranteed to be already gone

   ModuleBoard::current ().impl_reset_pools ();
}



/*
==============================================================================
Name : dtor
==============================================================================
*/

BoardGeneric::~BoardGeneric ()
{
   if (_boot_flag)
   {
      impl_print_stats ();
   }
}



/*
==============================================================================
Name : stats
==============================================================================
*/

BoardGeneric::Stats  BoardGeneric::stats () const
{
   Stats stats;

   stats.qspi_erases = _qspi_erases;
   stats.qspi_saves = _qspi_saves;

   auto & module_board = ModuleBoard::current ();
   stats.sram_pool_position = module_board.sram ().impl_pool_position ();
#if (erb_SDRAM_USE_FLAG)
   stats.sdram_pool_position = module_board.sdram ().impl_pool_position ();
#endif

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   stats.sd_bytes_read = SdCard::impl_nbr_bytes_read ();
   stats.sd_bytes_written = SdCard::impl_nbr_bytes_written ();
#endif

   stats.block_count = _block_count;
   stats.idle_count = _idle_count;

   if (_boot_flag)
   {
      const auto elapsed = std::chrono::steady_clock::now () - _wall_start;
      stats.wall_seconds = std::chrono::duration <double> (elapsed).count ();
   }

   stats.output_max_abs = _output_max_abs;
   stats.output_nbr_non_finite = _output_nbr_non_finite;

   return stats;
}



/*
==============================================================================
Name : use_persistent_map
==============================================================================
*/

BoardGeneric::PersistentMap & BoardGeneric::use_persistent_map ()
{
   return _persistent_map;
}



/*
==============================================================================
Name : start
Description :
   Ends the "Given" phase.
   Mode is deduced from there on, when no instrument is connected it means
   we don't care about audio, and so UI can run fast.
==============================================================================
*/

void  BoardGeneric::start ()
{
   assert (_boot_flag);
   assert (!_start_flag);

   _start_flag = true;

   _mode = (_nbr_bindings > 0) ? Mode::Lockstep : Mode::UiFast;

   // recordings begin here (doc 4.5)
   for (auto & r : _digital_recordings) r.second.digital.clear ();
   for (auto & r : _analog_recordings) r.second.samples.clear ();
   for (auto & r : _audio_recordings) r.second.samples.clear ();
   _recorded_blocks = 0;
}



/*
==============================================================================
Name : run
Description :
   Pumps the current mode until 'duration' of system time has passed.
==============================================================================
*/

void  BoardGeneric::run (SystemClockVirtual::duration duration)
{
   assert (_boot_flag);

   const auto target = SystemClockVirtual::now () + duration;

   while (SystemClockVirtual::now () < target)
   {
      // last step may overshoot by one, but this is deterministic
      impl_step ();
   }
}



/*
==============================================================================
Name : press
Note :
   Firmware sees 'pressed' and 'held', button stays pressed
==============================================================================
*/

void  BoardGeneric::press (Button & button)
{
   assert (_boot_flag);

   impl_set_digital_input (button.impl_data, 1);
   impl_steps (DebounceBlocks);
}



/*
==============================================================================
Name : release
==============================================================================
*/

void  BoardGeneric::release (Button & button)
{
   assert (_boot_flag);

   impl_set_digital_input (button.impl_data, 0);
   impl_steps (DebounceBlocks);
}



/*
==============================================================================
Name : click
==============================================================================
*/

void  BoardGeneric::click (Button & button)
{
   press (button);
   release (button);
}



/*
==============================================================================
Name : long_press
==============================================================================
*/

void  BoardGeneric::long_press (Button & button, SystemClockVirtual::duration duration)
{
   press (button);
   run (duration);
   release (button);
}



/*
==============================================================================
Name : trigger
==============================================================================
*/

void  BoardGeneric::trigger (GateIn & gate)
{
   assert (_boot_flag);

   impl_plug (SlotKind::Digital, impl_slot_index (_digital_inputs, gate.impl_data));

   impl_set_digital_input (gate.impl_data, 1);
   impl_steps (TriggerBlocks);
   impl_set_digital_input (gate.impl_data, 0);
   impl_steps (1);
}



/*
==============================================================================
Name : set
==============================================================================
*/

void  BoardGeneric::set (GateIn & gate, bool state)
{
   assert (_boot_flag);

   impl_set_digital_input (gate.impl_data, state ? 1 : 0);
   impl_plug (SlotKind::Digital, impl_slot_index (_digital_inputs, gate.impl_data));
}



/*
==============================================================================
Name : control_name
Description :
   Returns erbui name of a control mostly for logs
==============================================================================
*/

const char *  BoardGeneric::control_name (const void * control_ptr) const
{
   assert (_boot_flag);

   return _glue.control_name (control_ptr);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_setup
==============================================================================
*/

void  BoardGeneric::impl_setup (const ContextMap & context)
{
   assert (!_setup_flag);
   assert (!_boot_flag);

   _persistent_map.clear ();
   SystemClockVirtual::impl_reset ();

   context_set (context);
   probe_reset ();

   _setup_flag = true;
}



/*
==============================================================================
Name : impl_boot
==============================================================================
*/

void  BoardGeneric::impl_boot (Glue glue)
{
   assert (_setup_flag);
   assert (!_boot_flag);
   assert (glue.preprocess);
   assert (glue.process);
   assert (glue.postprocess);
   assert (glue.idle);
   assert (glue.control_name);

   _glue = std::move (glue);

   impl_reset_stats ();

   _boot_flag = true;
}



/*
==============================================================================
Name : impl_reset_stats
==============================================================================
*/

void  BoardGeneric::impl_reset_stats ()
{
   _qspi_erases.clear ();
   _qspi_saves.clear ();

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   SdCard::impl_reset_stats ();
#endif

   _wall_start = std::chrono::steady_clock::now ();
   _output_max_abs = 0.f;
   _output_nbr_non_finite = 0;
}



/*
==============================================================================
Name : impl_print_stats
Note :
   Memory usage is on host, usually 64-bit, so stats are different from
   the firmware running on the real hardware (32-bit).
==============================================================================
*/

void  BoardGeneric::impl_print_stats () const
{
   const auto s = stats ();

   auto total = [] (const std::map <std::size_t, std::size_t> & per_page) {
      std::size_t sum = 0;
      for (const auto & [page, count] : per_page) sum += count;
      return sum;
   };

   std::printf (
      "stats: blocks %llu, idles %llu, wall %.3f s, qspi saves %zu on %zu pages, erases %zu on %zu pages",
      (unsigned long long) s.block_count, (unsigned long long) s.idle_count, s.wall_seconds,
      total (s.qspi_saves), s.qspi_saves.size (), total (s.qspi_erases), s.qspi_erases.size ()
   );

   std::printf (
      ", sd read %zu B, written %zu B, sram %zu B, sdram %zu B, out max %f, non-finite %zu\n",
      s.sd_bytes_read, s.sd_bytes_written, s.sram_pool_position, s.sdram_pool_position,
      double (s.output_max_abs), s.output_nbr_non_finite
   );
   std::fflush (stdout);
}



/*
==============================================================================
Name : impl_step
==============================================================================
*/

void  BoardGeneric::impl_step ()
{
   switch (_mode)
   {
   case Mode::UiFast:
      impl_step_pair ();
      break;

   case Mode::Lockstep:
      impl_step_block ();
      break;
   }
}



/*
==============================================================================
Name : impl_step_pair
Description :
   For 'UiFast', one 'process' then one 'idle'. We need 'process' because
   the UI state is from 'process'.
==============================================================================
*/

void  BoardGeneric::impl_step_pair ()
{
   impl_block ();
   impl_idle ();

   SystemClockVirtual::impl_advance (erb_BUFFER_SIZE * BlocksPerIdle);
}



/*
==============================================================================
Name : impl_step_block
Description :
   For 'Lockstep', one 'process' then many 'idle', eg. 18 for a system with
   16 buffer size @ 48kHz and around 6ms min period for UI.
==============================================================================
*/

void  BoardGeneric::impl_step_block ()
{
   impl_block ();

   SystemClockVirtual::impl_advance (erb_BUFFER_SIZE);

   if (_block_count % BlocksPerIdle == 0)
   {
      impl_idle ();
   }
}



/*
==============================================================================
Name : impl_block
==============================================================================
*/

void  BoardGeneric::impl_block ()
{
   // see rationale in 'impl_set_digital_input'
   _digital_inputs = _digital_inputs_standing;
   _analog_inputs = _analog_inputs_standing;

   // idle before 'start', before control for normalling
   if (_start_flag)
   {
      for (auto * source_ptr : _sources) source_ptr->impl_process ();
   }

   _glue.preprocess ();
   _glue.process ();
   _glue.postprocess ();

   ++_block_count;
}



/*
==============================================================================
Name : impl_idle
==============================================================================
*/

void  BoardGeneric::impl_idle ()
{
   _glue.idle ();

   ++_idle_count;
}



/*
==============================================================================
Name : impl_steps
==============================================================================
*/

void  BoardGeneric::impl_steps (std::size_t nbr_steps)
{
   for (std::size_t i = 0 ; i < nbr_steps ; ++i)
   {
      impl_step ();
   }
}



/*
==============================================================================
Name : impl_set_digital_input
Description :
   Setting a value is different from the simulator where the host resend
   the value for every block. A 'set' in our abstraction is an imperative
   way to describe a test, so are not resent every block. However the
   value itself should be "standing".

   Some modules happen to mess with that when for example some pins are
   multiplexed in the hardware, so we need a copy of what the test expects
   so we can set it for every block like the simulator.

   On the other hand, when setting a value, the test can expect to read back
   the value it just wrote, so we need also to ensure that.
==============================================================================
*/

void  BoardGeneric::impl_set_digital_input (const uint8_t & data, uint8_t value)
{
   const auto slot_index = impl_slot_index (_digital_inputs, data);

   _digital_inputs_standing [slot_index] = value;
   _digital_inputs [slot_index] = value;
}



/*
==============================================================================
Name : impl_set_analog_input
==============================================================================
*/

void  BoardGeneric::impl_set_analog_input (const float & data, float value)
{
   const auto slot_index = impl_slot_index (_analog_inputs, data);

   _analog_inputs_standing [slot_index] = value;
   _analog_inputs [slot_index] = value;
}



/*
==============================================================================
Name : impl_plug
Description:
   Plug notification for the normalling system.
   A plug is assumed to stay for a whole run.
==============================================================================
*/

void  BoardGeneric::impl_plug (SlotKind kind, std::size_t slot_index)
{
   _plugged.insert ({kind, slot_index});
}



/*
==============================================================================
Name : impl_bind_input
==============================================================================
*/

std::size_t BoardGeneric::impl_bind_input (SlotKind kind, const void * slot_data)
{
   assert (!_boot_flag);   // a cable is in before the module boots

   std::size_t slot_index = 0;

   switch (kind)
   {
   case SlotKind::Digital:
      slot_index = impl_slot_index (_digital_inputs, *static_cast <const uint8_t *> (slot_data));
      break;

   case SlotKind::Analog:
      slot_index = impl_slot_index (_analog_inputs, *static_cast <const float *> (slot_data));
      break;

   case SlotKind::Audio:
      slot_index = impl_slot_index (_audio_inputs, *static_cast <const Buffer *> (slot_data));
      break;
   }

   impl_plug (kind, slot_index);

   return slot_index;
}



/*
==============================================================================
Name : impl_attach
==============================================================================
*/

void  BoardGeneric::impl_attach (Source & source)
{
   assert (std::find (_sources.begin (), _sources.end (), &source) == _sources.end ());

   _sources.push_back (&source);
}



/*
==============================================================================
Name : impl_detach
==============================================================================
*/

void  BoardGeneric::impl_detach (Source & source)
{
   const auto it = std::find (_sources.begin (), _sources.end (), &source);
   assert (it != _sources.end ());

   _sources.erase (it);
}



/*
==============================================================================
Name : impl_input_audio
==============================================================================
*/

Buffer & BoardGeneric::impl_input_audio (std::size_t slot_index)
{
   assert (slot_index < _audio_inputs.size ());

   return _audio_inputs [slot_index];
}



/*
==============================================================================
Name : impl_apply_normalling
==============================================================================
*/

void  BoardGeneric::impl_apply_normalling (const uint8_t & data, float value)
{
   const auto slot_index = impl_slot_index (_digital_inputs, data);

   if (_plugged.contains ({SlotKind::Digital, slot_index})) return;

   _digital_inputs [slot_index] = (value > 0.5f) ? 1 : 0;
}



/*
==============================================================================
Name : impl_apply_normalling
==============================================================================
*/

void  BoardGeneric::impl_apply_normalling (const float & data, float value)
{
   const auto slot_index = impl_slot_index (_analog_inputs, data);

   if (_plugged.contains ({SlotKind::Analog, slot_index})) return;

   _analog_inputs [slot_index] = value;
}



/*
==============================================================================
Name : impl_apply_normalling
==============================================================================
*/

void  BoardGeneric::impl_apply_normalling (const Buffer & data, float value)
{
   const auto slot_index = impl_slot_index (_audio_inputs, data);

   if (_plugged.contains ({SlotKind::Audio, slot_index})) return;

   _audio_inputs [slot_index].fill (value);
}



/*
==============================================================================
Name : impl_apply_normalling
==============================================================================
*/

void  BoardGeneric::impl_apply_normalling (const uint8_t & data, const uint8_t & from)
{
   const auto slot_index = impl_slot_index (_digital_inputs, data);

   if (_plugged.contains ({SlotKind::Digital, slot_index})) return;

   _digital_inputs [slot_index] = from;
}



/*
==============================================================================
Name : impl_apply_normalling
==============================================================================
*/

void  BoardGeneric::impl_apply_normalling (const Buffer & data, const Buffer & from)
{
   const auto slot_index = impl_slot_index (_audio_inputs, data);

   if (_plugged.contains ({SlotKind::Audio, slot_index})) return;

   _audio_inputs [slot_index] = from;
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardGeneric::impl_preprocess ()
{
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardGeneric::impl_postprocess ()
{
   // Linear congruential generator (same as simulator)
   _npr_rand_state = _npr_rand_state * 1103515245 + 12345;
   _npr = _npr_rand_state >> 31;

   _clock.tick ();

   // for the stats
   for (const auto & buffer : _audio_outputs)
   {
      for (const auto sample : buffer)
      {
         if (!std::isfinite (sample))
         {
            ++_output_nbr_non_finite;
         }
         else
         {
            _output_max_abs = std::max (_output_max_abs, std::abs (sample));
         }
      }
   }

   if (_start_flag) // record
   {
      for (auto & r : _digital_recordings)
         r.second.digital.push_back (_digital_outputs [r.first]);

      for (auto & r : _analog_recordings)
         r.second.samples.push_back (_analog_outputs [r.first]);

      for (auto & r : _audio_recordings)
      {
         const auto & block = _audio_outputs [r.first];
         r.second.samples.insert (r.second.samples.end (), block.begin (), block.end ());
      }

      ++_recorded_blocks;
   }
}



/*
==============================================================================
Name : impl_bind_output
Description :
   Notification from an instrument that the slot will be recorded.
   This avoids to record everything all the time, and more importantly
   to know if the running mode is ui-fast or lock-step.
==============================================================================
*/

std::size_t BoardGeneric::impl_bind_output (SlotKind kind, const void * slot_data)
{
   assert (!_boot_flag);

   std::size_t slot_index = 0;

   switch (kind)
   {
   case SlotKind::Digital:
      slot_index = impl_slot_index (_digital_outputs, *static_cast <const uint8_t *> (slot_data));
      break;

   case SlotKind::Analog:
      slot_index = impl_slot_index (_analog_outputs, *static_cast <const float *> (slot_data));
      break;

   case SlotKind::Audio:
      slot_index = impl_slot_index (_audio_outputs, *static_cast <const Buffer *> (slot_data));
      break;
   }

   ++impl_recordings (kind) [slot_index].bindings;
   ++_nbr_bindings;

   return slot_index;
}



/*
==============================================================================
Name : impl_unbind_output
==============================================================================
*/

void  BoardGeneric::impl_unbind_output (SlotKind kind, std::size_t slot_index)
{
   auto & recordings = impl_recordings (kind);
   auto it = recordings.find (slot_index);
   assert (it != recordings.end ());
   assert (it->second.bindings > 0);
   assert (_nbr_bindings > 0);

   --it->second.bindings;
   --_nbr_bindings;

   if (it->second.bindings == 0)
   {
      recordings.erase (it);
   }
}



/*
==============================================================================
Name : impl_recording_digital
==============================================================================
*/

std::span <const uint8_t>  BoardGeneric::impl_recording_digital (std::size_t slot_index) const
{
   return _digital_recordings.at (slot_index).digital;
}



/*
==============================================================================
Name : impl_recording_analog
==============================================================================
*/

std::span <const float>   BoardGeneric::impl_recording_analog (std::size_t slot_index) const
{
   return _analog_recordings.at (slot_index).samples;
}



/*
==============================================================================
Name : impl_recording_audio
==============================================================================
*/

std::span <const float>   BoardGeneric::impl_recording_audio (std::size_t slot_index) const
{
   return _audio_recordings.at (slot_index).samples;
}



/*
==============================================================================
Name : impl_recorded_blocks
==============================================================================
*/

std::uint64_t  BoardGeneric::impl_recorded_blocks () const
{
   return _recorded_blocks;
}



/*
==============================================================================
Name : impl_pump_until
==============================================================================
*/

bool  BoardGeneric::impl_pump_until (const std::function <bool ()> & predicate, SystemClockVirtual::duration timeout)
{
   return impl_wait_until (predicate, timeout);
}



/*
==============================================================================
Name : mark
Description :
   Gives the base name of the golden for this region (up to the next one).
   Must be unique per process.
==============================================================================
*/

void  BoardGeneric::mark (const std::string & name)
{
   assert (_start_flag);
   assert (!name.empty ());
   assert (name.find ('/') == std::string::npos);

   static std::set <std::string> names;
   const bool inserted = names.insert (name).second;

   if (!inserted)
   {
      std::fprintf (stderr, "mark: '%s' used twice\n", name.c_str ());
      std::fflush (stderr);
      assert (false);
   }

   _mark_name = name;
   _mark_flag = true;
   _region_flag = false;
   _region_start = 0;
   _region_end = 0;

   for (auto & group : _groups)
   {
      group.golden_loaded = false;
      group.golden_exists = false;
      group.golden.clear ();
   }
}



/*
==============================================================================
Name : impl_declare_group
Description :
   A group is a private logical association of multiple outputs, for example
   the left and right audio output
==============================================================================
*/

void  BoardGeneric::impl_declare_group (const std::string & name, std::uint32_t sample_rate, std::vector <std::pair <SlotKind, std::size_t>> slots)
{
   assert (!_boot_flag);
   assert (!name.empty ());
   assert (sample_rate > 0);
   assert (!slots.empty ());

   for (const auto & slot : slots)
   {
      assert (slot.first != SlotKind::Digital); // no region file for a gate
      for (const auto & group : _groups)
      {
         for (const auto & other : group.slots) assert (other != slot); // one group per slot
      }
   }

   _groups.push_back ({name, sample_rate, std::move (slots)});
}



/*
==============================================================================
Name : impl_set_region_directory
==============================================================================
*/

void  BoardGeneric::impl_set_region_directory (const std::string & directory)
{
   assert (!directory.empty ());
   assert (directory.back () != '/');

   _region_directory = directory;
}



/*
==============================================================================
Name : impl_get_golden
==============================================================================
*/

std::span <const float>   BoardGeneric::impl_get_golden (SlotKind kind, std::size_t slot_index, std::uint64_t nbr_blocks, const char * instrument_name, std::source_location sloc)
{
   assert (_start_flag);
   assert (nbr_blocks > 0);
   assert (nbr_blocks <= _recorded_blocks);

   if (!_mark_flag)
   {
      std::fprintf (stderr, "check at %s:%u: %s golden check with no mark\n", sloc.file_name (), unsigned (sloc.line ()), instrument_name);
      std::fflush (stderr);
      assert (false);
   }

   auto & group = impl_group_of (kind, slot_index);
   const auto channel = impl_channel_of (group, kind, slot_index);

   const auto window_start = _recorded_blocks - nbr_blocks;
   const auto window_end = _recorded_blocks;

   if (!_region_flag)
   {
      _region_flag = true;
      _region_start = window_start;
      _region_end = window_end;
   }
   else if (window_start < _region_start)
   {
      std::fprintf (
         stderr,
         "check at %s:%u: %s window starts at block %llu, before the region '%s' started at block %llu\n",
         sloc.file_name (), unsigned (sloc.line ()), instrument_name,
         (unsigned long long) window_start, _mark_name.c_str (), (unsigned long long) _region_start
      );
      std::fflush (stderr);
      assert (false);
   }

   _region_end = std::max (_region_end, window_end);

   impl_load_golden (group);

   const auto samples_per_block = (kind == SlotKind::Audio) ? std::size_t (erb_BUFFER_SIZE) : std::size_t (1);
   const auto needed = std::size_t (window_end - _region_start) * samples_per_block;
   const auto path = impl_region_path (group, false);

   if (!group.golden_exists || (group.golden [channel].size () < needed))
   {
      std::fprintf (
         stderr,
         "check at %s:%u: %s golden '%s' %s, actual written to '%s'\n",
         sloc.file_name (), unsigned (sloc.line ()), instrument_name, path.c_str (),
         group.golden_exists ? "shorter than the region" : "missing",
         impl_region_path (group, true).c_str ()
      );
      std::fflush (stderr);

      impl_write_actual (group);
      assert (false);
      std::abort ();
   }

   const auto offset = std::size_t (window_start - _region_start) * samples_per_block;

   return std::span <const float> (group.golden [channel]).subspan (offset, std::size_t (nbr_blocks) * samples_per_block);
}



/*
==============================================================================
Name : impl_notify_golden_mismatch
==============================================================================
*/

void  BoardGeneric::impl_notify_golden_mismatch (SlotKind kind, std::size_t slot_index)
{
   assert (_mark_flag);
   assert (_region_flag);

   const auto & group = impl_group_of (kind, slot_index);

   std::fprintf (stderr, "actual written to '%s'\n", impl_region_path (group, true).c_str ());
   std::fflush (stderr);

   impl_write_actual (group);
   assert (false);
   std::abort ();
}



/*
==============================================================================
Name : impl_group_of
==============================================================================
*/

BoardGeneric::Group &   BoardGeneric::impl_group_of (SlotKind kind, std::size_t slot_index)
{
   return const_cast <Group &> (std::as_const (*this).impl_group_of (kind, slot_index));
}



const BoardGeneric::Group &   BoardGeneric::impl_group_of (SlotKind kind, std::size_t slot_index) const
{
   for (auto & group : _groups)
   {
      for (const auto & slot : group.slots)
      {
         if ((slot.first == kind) && (slot.second == slot_index)) return group;
      }
   }

   std::fprintf (stderr, "check: output not in any group, no region file for it\n");
   std::fflush (stderr);
   assert (false);
   std::abort ();
}



/*
==============================================================================
Name : impl_channel_of
==============================================================================
*/

std::size_t BoardGeneric::impl_channel_of (const Group & group, SlotKind kind, std::size_t slot_index) const
{
   for (std::size_t channel = 0 ; channel < group.slots.size () ; ++channel)
   {
      if (group.slots [channel] == std::make_pair (kind, slot_index)) return channel;
   }

   assert (false);
   return 0;
}



/*
==============================================================================
Name : impl_get_trace_file
==============================================================================
*/

Bench::TraceFile  BoardGeneric::impl_get_trace_file (SlotKind kind, std::size_t slot_index, const char * control_name, const char * instrument_name) const
{
   assert (_mark_flag);

   const auto & group = impl_group_of (kind, slot_index);

   return {
      _region_directory + "/" + _mark_name + "." + control_name + "." + instrument_name + ".trace.wav",
      group.sample_rate
   };
}



/*
==============================================================================
Name : impl_region_path
==============================================================================
*/

std::string BoardGeneric::impl_region_path (const Group & group, bool actual) const
{
   assert (!_region_directory.empty ());

   return _region_directory + "/" + _mark_name + "." + group.name + (actual ? ".actual.wav" : ".wav");
}



/*
==============================================================================
Name : impl_load_golden
==============================================================================
*/

void  BoardGeneric::impl_load_golden (Group & group)
{
   if (group.golden_loaded) return;

   group.golden_loaded = true;
   group.golden.assign (group.slots.size (), {});

   const auto path = impl_region_path (group, false);

   if (!std::filesystem::exists (path))
   {
      group.golden_exists = false;
      return;
   }

   const auto wave = read_wave (path);

   if ((wave.nbr_channels != group.slots.size ()) || (wave.sample_rate != group.sample_rate))
   {
      std::fprintf (
         stderr, "golden '%s': %zu channels at %u Hz, group '%s' is %zu channels at %u Hz\n",
         path.c_str (), wave.nbr_channels, wave.sample_rate, group.name.c_str (), group.slots.size (), group.sample_rate
      );
      std::fflush (stderr);
      assert (false);
   }

   const auto nbr_frames = wave.nbr_frames ();

   for (std::size_t channel = 0 ; channel < group.slots.size () ; ++channel)
   {
      auto & samples = group.golden [channel];
      samples.resize (nbr_frames);

      for (std::size_t frame = 0 ; frame < nbr_frames ; ++frame)
      {
         samples [frame] = wave.samples [frame * wave.nbr_channels + channel];
      }
   }

   group.golden_exists = true;
}



/*
==============================================================================
Name : impl_write_actual
Note :
   Write is quantized
==============================================================================
*/

void  BoardGeneric::impl_write_actual (const Group & group)
{
   assert (_region_flag);

   Wave wave;
   wave.sample_rate = group.sample_rate;
   wave.nbr_channels = group.slots.size ();

   const auto samples_per_block = (group.slots.front ().first == SlotKind::Audio) ? std::size_t (erb_BUFFER_SIZE) : std::size_t (1);

   for (auto block = _region_start ; block < _region_end ; ++block)
   {
      for (std::size_t sample = 0 ; sample < samples_per_block ; ++sample)
      {
         for (const auto & slot : group.slots)
         {
            wave.samples.push_back (quantize (impl_recorded_sample (slot.first, slot.second, block, sample)));
         }
      }
   }

   write_wave (wave, impl_region_path (group, true));
}



/*
==============================================================================
Name : impl_recorded_sample
==============================================================================
*/

float BoardGeneric::impl_recorded_sample (SlotKind kind, std::size_t slot_index, uint64_t block, std::size_t sample) const
{
   if (kind == SlotKind::Audio)
   {
      auto it = _audio_recordings.find (slot_index);
      if (it == _audio_recordings.end ()) return 0.f;
      return it->second.samples [std::size_t (block) * erb_BUFFER_SIZE + sample];
   }
   else
   {
      auto it = _analog_recordings.find (slot_index);
      if (it == _analog_recordings.end ()) return 0.f;
      return it->second.samples [std::size_t (block)];
   }
}



/*
==============================================================================
Name : impl_recordings
==============================================================================
*/

std::map <std::size_t, BoardGeneric::Recorded> &  BoardGeneric::impl_recordings (SlotKind kind)
{
   switch (kind)
   {
   case SlotKind::Digital: return _digital_recordings;
   case SlotKind::Analog: return _analog_recordings;
   case SlotKind::Audio: default: return _audio_recordings;
   }
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
