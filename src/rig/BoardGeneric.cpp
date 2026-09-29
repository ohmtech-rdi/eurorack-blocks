/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/BoardGeneric.h"

#include "erb/detail/ModuleBoard.h"

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   #include "erb/rig/SdCard.h"
#endif

#include <algorithm>

#include <cassert>
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

   impl_digital_slot (button.impl_data) = 1;
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

   impl_digital_slot (button.impl_data) = 0;
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

   auto & data = impl_digital_slot (gate.impl_data);

   data = 1;
   impl_steps (TriggerBlocks);
   data = 0;
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

   impl_digital_slot (gate.impl_data) = state ? 1 : 0;
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
Name : impl_digital_slot
Description :
   'data' is the 'impl_data' of the control that is const, and in the
   vector.
==============================================================================
*/

uint8_t &   BoardGeneric::impl_digital_slot (const uint8_t & data)
{
   return _digital_inputs [impl_slot_index (_digital_inputs, data)];
}



/*
==============================================================================
Name : impl_analog_slot
==============================================================================
*/

float &  BoardGeneric::impl_analog_slot (const float & data)
{
   return _analog_inputs [impl_slot_index (_analog_inputs, data)];
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
Name : impl_bind
Description :
   Notification from an instrument that the slot will be recorded.
   This avoids to record everything all the time, and more importantly
   to know if the running mode is ui-fast or lock-step.
==============================================================================
*/

std::size_t BoardGeneric::impl_bind (SlotKind kind, const void * slot_data)
{
   assert (!_boot_flag);

   std::size_t index = 0;

   switch (kind)
   {
   case SlotKind::Digital:
      index = impl_slot_index (_digital_outputs, *static_cast <const uint8_t *> (slot_data));
      break;

   case SlotKind::Analog:
      index = impl_slot_index (_analog_outputs, *static_cast <const float *> (slot_data));
      break;

   case SlotKind::Audio:
      index = impl_slot_index (_audio_outputs, *static_cast <const Buffer *> (slot_data));
      break;
   }

   ++impl_recordings (kind) [index].bindings;
   ++_nbr_bindings;

   return index;
}



/*
==============================================================================
Name : impl_unbind
==============================================================================
*/

void  BoardGeneric::impl_unbind (SlotKind kind, std::size_t index)
{
   auto & recordings = impl_recordings (kind);
   auto it = recordings.find (index);
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

std::span <const uint8_t>  BoardGeneric::impl_recording_digital (std::size_t index) const
{
   return _digital_recordings.at (index).digital;
}



/*
==============================================================================
Name : impl_recording_analog
==============================================================================
*/

std::span <const float>   BoardGeneric::impl_recording_analog (std::size_t index) const
{
   return _analog_recordings.at (index).samples;
}



/*
==============================================================================
Name : impl_recording_audio
==============================================================================
*/

std::span <const float>   BoardGeneric::impl_recording_audio (std::size_t index) const
{
   return _audio_recordings.at (index).samples;
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
