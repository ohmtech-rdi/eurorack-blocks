/*****************************************************************************

      Monitor.cpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Monitor.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include <algorithm>

#include <cstring>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

namespace erb
{



/*
==============================================================================
Name : init
==============================================================================
*/

void  Monitor::init ()
{
   Rtt::use ().init ();
   CycleCounter::init ();
   RttProtocol::use ().init ();

   register_command (
      RttProtocol::fourcc ("load"), nullptr, &Monitor::command_load
   );

   register_command (
      RttProtocol::fourcc ("prof"), nullptr, &Monitor::command_prof
   );
}



/*
==============================================================================
Name : idle
==============================================================================
*/

void  Monitor::idle ()
{
   auto & profiler = Profiler::use ();

   // profiler window done: dump incrementally
   // (a few lines per pass, the up ring is small)
   if (_prof_pending && ! profiler.window_running ())
   {
      constexpr std::size_t lines_per_pass = 12;

      const auto nbr_nodes = profiler.nbr_nodes ();
      const auto end = std::min (nbr_nodes, _prof_dump_pos + lines_per_pass);

      for (; _prof_dump_pos < end ; ++_prof_dump_pos)
      {
         const auto label = profiler.node_label (_prof_dump_pos);
         Rtt::use ().printf ("prof %u %c%c%c%c %ld %lu\n",
            unsigned (_prof_dump_pos),
            char (label), char (label >> 8),
            char (label >> 16), char (label >> 24),
            static_cast <long> (profiler.node_parent (_prof_dump_pos)),
            static_cast <unsigned long> (profiler.node_cycles (_prof_dump_pos))
         );
      }

      if (_prof_dump_pos >= nbr_nodes)
      {
         for (std::size_t i = 0 ; i < Profiler::MaxNbrProbes ; ++i)
         {
            if (profiler.probe_count (i) == 0) continue;
            Rtt::use ().printf ("probp %u %lu %lu\n",
               unsigned (i),
               static_cast <unsigned long> (profiler.probe_cycles (i)),
               static_cast <unsigned long> (profiler.probe_count (i))
            );
         }

         Rtt::use ().printf ("ok prof blocks=%lu nodes=%lu truncated=%d\n",
            static_cast <unsigned long> (profiler.blocks_done ()),
            static_cast <unsigned long> (nbr_nodes),
            int (profiler.truncated ())
         );
         _prof_pending = false;
         _prof_dump_pos = 0;
      }
   }

   RttProtocol::use ().idle ();
}



/*
==============================================================================
Name : register_command
==============================================================================
*/

bool  Monitor::register_command (std::uint32_t cmd, void * ctx, RttProtocol::CommandHandler handler)
{
   return RttProtocol::use ().register_command (cmd, ctx, handler);
}



/*
==============================================================================
Name : register_stream
==============================================================================
*/

bool  Monitor::register_stream (std::uint32_t cmd, void * ctx, RttProtocol::StreamHandler handler)
{
   return RttProtocol::use ().register_stream (cmd, ctx, handler);
}



/*
==============================================================================
Name : command_load
   Audio callback load since the previous 'load' query (or since init).
   All numbers are CPU cycles, the block budget is the measured average
   enter-to-enter period, so the host needs no configuration knowledge.
==============================================================================
*/

void  Monitor::command_load (void * /* ctx */, std::span <const std::uint8_t> /* payload */)
{
   auto & self = use ();

   const auto busy_max = self._busy_max;
   const auto busy_sum = self._busy_sum;
   const auto period_sum = self._period_sum;
   const auto count = self._block_count;

   self._load_reset = 1;

   if (count == 0)
   {
      Rtt::use ().printf ("err load no blocks\n");
      return;
   }

   Rtt::use ().printf ("ok load blocks=%lu busy_max=%lu busy_avg=%lu period_avg=%lu\n",
      static_cast <unsigned long> (count),
      static_cast <unsigned long> (busy_max),
      static_cast <unsigned long> (busy_sum / count),
      static_cast <unsigned long> (period_sum / count)
   );
}



/*
==============================================================================
Name : command_prof
   Payload: [u32 nbr_blocks]. Starts a profiler window. The dump follows
   incrementally from idle once the window completes.
==============================================================================
*/

void  Monitor::command_prof (void * /* ctx */, std::span <const std::uint8_t> payload)
{
   auto & self = use ();

   if (payload.size () != 4)
   {
      Rtt::use ().printf ("err prof payload\n");
      return;
   }

   std::uint32_t nbr_blocks = 0;
   std::memcpy (&nbr_blocks, payload.data (), 4);

   if (!Profiler::use ().start (nbr_blocks))
   {
      Rtt::use ().printf ("err prof start (blocks=%lu, running=%d)\n",
         static_cast <unsigned long> (nbr_blocks),
         int (Profiler::use ().window_running ())
      );
      return;
   }

   self._prof_pending = true;
   self._prof_dump_pos = 0;
   Rtt::use ().printf ("ok prof started blocks=%lu\n",
      static_cast <unsigned long> (nbr_blocks)
   );
}



}  // namespace erb

#endif   // erb_MONITOR && erb_TARGET_DAISY
