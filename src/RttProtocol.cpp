/*****************************************************************************

      RttProtocol.cpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/RttProtocol.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include "erb/Rtt.h"
#include "erb/detail/Sdram.h"

#include "sys/system.h"

#include <algorithm>

#include <cstring>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

namespace erb
{



/*
==============================================================================
Name : use
==============================================================================
*/

RttProtocol &  RttProtocol::use ()
{
   static RttProtocol instance;
   return instance;
}



/*
==============================================================================
Name : init
==============================================================================
*/

void  RttProtocol::init ()
{
   register_command (fourcc ("ping"), nullptr, &RttProtocol::command_ping);
   register_stream (fourcc ("sink"), nullptr, &RttProtocol::stream_sink);
}



/*
==============================================================================
Name : register_command
Note :
   Client custom commands.
   Payload is buffered and bounded by MaxPayloadSize, delivered when
   completed.
==============================================================================
*/

bool  RttProtocol::register_command (std::uint32_t cmd, void * ctx, CommandHandler handler)
{
   for (auto & entry : _entries)
   {
      if (entry.kind != Kind::None) continue;

      entry.cmd = cmd;
      entry.kind = Kind::Command;
      entry.command_handler = handler;
      entry.ctx = ctx;

      return true;
   }

   return false;   // table full
}



/*
==============================================================================
Name : register_stream
Note :
   Client custom streams.
   Payload is unbounded, the client pulls using 'stream_read'
==============================================================================
*/

bool  RttProtocol::register_stream (std::uint32_t cmd, void * ctx, StreamHandler handler)
{
   for (auto & entry : _entries)
   {
      if (entry.kind != Kind::None) continue;

      entry.cmd = cmd;
      entry.kind = Kind::Stream;
      entry.stream_handler = handler;
      entry.ctx = ctx;

      return true;
   }

   return false;   // table full
}



/*
==============================================================================
Name : idle
==============================================================================
*/

void  RttProtocol::idle ()
{
   std::uint8_t chunk [512];

   for (;;)
   {
      const auto size = read_source (chunk, sizeof (chunk));

      if (size == 0)
      {
         check_stall ();
         return;
      }

      _last_rx_tick = daisy::System::GetTick ();

      process_chunk (chunk, size);
   }
}



/*
==============================================================================
Name : check_stall
Note :
   A box whose bytes stop flowing mid-way (aborted host transfer) would
   wedge the parser forever: drop it after 2 s of inactivity.
==============================================================================
*/

void  RttProtocol::check_stall ()
{
   const bool mid_box = (_header_pos > 0) || (_payload_pos > 0);
   if (!mid_box) return;

   const auto now = daisy::System::GetTick ();
   if (now - _last_rx_tick <= 2 * daisy::System::GetTickFreq ()) return;

   Rtt::use ().printf ("err %c%c%c%c stalled, dropped (hdr=%u payload=%lu/%lu)\n",
      char (_header.cmd), char (_header.cmd >> 8),
      char (_header.cmd >> 16), char (_header.cmd >> 24),
      unsigned (_header_pos),
      static_cast <unsigned long> (_payload_pos),
      static_cast <unsigned long> (_header.payload_size)
   );

   _header_pos = 0;
   _payload_pos = 0;
}



/*
==============================================================================
Name : process_chunk
Note:
   Protocol: fourcc boxes, little-endian:
      [u32 payload_size]['xxxx'][payload]
==============================================================================
*/

void  RttProtocol::process_chunk (const std::uint8_t * data, std::size_t size)
{
   std::size_t pos = 0;

   while (pos < size)
   {
      pos = (_header_pos < sizeof (Header))
         ? process_header (data, size, pos)
         : process_payload (data, size, pos);
   }
}



/*
==============================================================================
Name : process_header
==============================================================================
*/

std::size_t RttProtocol::process_header (const std::uint8_t * data, std::size_t size, std::size_t pos)
{
   const auto copy = std::min (sizeof (Header) - _header_pos, size - pos);

   std::memcpy (
      reinterpret_cast <std::uint8_t *> (&_header) + _header_pos,
      data + pos, copy
   );
   _header_pos += copy;
   pos += copy;

   if (_header_pos == sizeof (Header))
   {
      pos = dispatch (data, size, pos);
   }

   return pos;
}



/*
==============================================================================
Name : process_payload
Note :
   Buffered path: keep what fits, count everything.
==============================================================================
*/

std::size_t RttProtocol::process_payload (const std::uint8_t * data, std::size_t size, std::size_t pos)
{
   const auto copy = std::min (
      std::size_t (_header.payload_size) - _payload_pos, size - pos
   );

   if (_payload_pos < MaxPayloadSize)
   {
      const auto keep = std::min (copy, MaxPayloadSize - _payload_pos);
      std::memcpy (_payload + _payload_pos, data + pos, keep);
   }

   _payload_pos += copy;
   pos += copy;

   if (_payload_pos == _header.payload_size) finish ();

   return pos;
}



/*
==============================================================================
Name : dispatch
Note :
   Called when a box header is complete. An unknown command is reported,
   and its payload consumed and discarded by the buffered path.
==============================================================================
*/

std::size_t RttProtocol::dispatch (const std::uint8_t * data, std::size_t size, std::size_t pos)
{
   _payload_pos = 0;

   auto * entry_ptr = find (_header.cmd);

   if (entry_ptr == nullptr)
   {
      Rtt::use ().printf ("err %c%c%c%c unknown\n",
         char (_header.cmd), char (_header.cmd >> 8),
         char (_header.cmd >> 16), char (_header.cmd >> 24)
      );
   }

   if ((entry_ptr != nullptr) && (entry_ptr->kind == Kind::Stream))
   {
      pos = process_stream (*entry_ptr, data, size, pos);
   }
   else if (_header.payload_size == 0)
   {
      finish ();
   }

   return pos;
}



/*
==============================================================================
Name : process_stream
Note :
   The handler consumes the payload synchronously, ahead of the box state
   machine, starting with the unread bytes of the current chunk. The
   handler may stop before the payload end (error, logical end): the
   remainder is drained so that the channel stays framed.
==============================================================================
*/

std::size_t RttProtocol::process_stream (Entry & entry, const std::uint8_t * data, std::size_t size, std::size_t pos)
{
   _pending_ptr = data + pos;
   _pending_len = size - pos;

   if (_fifo == nullptr)
   {
      _fifo = static_cast <std::uint8_t *> (
         Sdram::allocate_bytes_nullptr_on_error (FifoSize)
      );
   }

   if (_fifo == nullptr)
   {
      Rtt::use ().printf ("err %c%c%c%c fifo alloc\n",
         char (_header.cmd), char (_header.cmd >> 8),
         char (_header.cmd >> 16), char (_header.cmd >> 24)
      );
   }
   else
   {
      // from here to stream end, the audio thread owns the ring
      _fifo_wr.store (0, std::memory_order_relaxed);
      _fifo_rd.store (0, std::memory_order_relaxed);
      _stream_active.store (true, std::memory_order_release);

      entry.stream_handler (entry.ctx, std::size_t (_header.payload_size));

      std::uint8_t scratch [256];

      while (_payload_pos < _header.payload_size)
      {
         const auto part = std::min (
            std::size_t (_header.payload_size) - _payload_pos,
            sizeof (scratch)
         );
         if (stream_read_raw (scratch, part) != part) break;
      }

      _stream_active.store (false, std::memory_order_release);
   }

   pos = size - _pending_len;
   _pending_len = 0;
   _header_pos = 0;
   _payload_pos = 0;

   return pos;
}



/*
==============================================================================
Name : isr_pump
Note :
   Audio thread. While a stream is active the parser can stall for
   milliseconds. The debug probe drops down-channel bytes whenever the
   small RTT ring fills, so the audio thread drains the ring into a large
   SDRAM fifo at block rate instead.
==============================================================================
*/

void  RttProtocol::isr_pump ()
{
   if (!_stream_active.load (std::memory_order_acquire)) return;

   std::uint8_t chunk [512];

   for (;;)
   {
      const auto wr = _fifo_wr.load (std::memory_order_relaxed);
      const auto rd = _fifo_rd.load (std::memory_order_acquire);
      const auto free = FifoSize - 1 - (wr - rd);
      if (free == 0) return;

      const auto size = Rtt::use ().read (
         chunk, std::min (sizeof (chunk), std::size_t (free))
      );
      if (size == 0) return;

      for (std::size_t i = 0 ; i < size ; ++i)
      {
         _fifo [(wr + i) % FifoSize] = chunk [i];
      }

      _fifo_wr.store (wr + size, std::memory_order_release);
   }
}



/*
==============================================================================
Name : stream_read
Note :
   Blocking pull of 'size' payload bytes, updating the running crc.
   Returns less than 'size' only on the 2 s inactivity timeout.
==============================================================================
*/

std::size_t RttProtocol::stream_read (void * ptr, std::size_t size)
{
   const auto nbr_read = stream_read_raw (ptr, size);

   crc_update (static_cast <const std::uint8_t *> (ptr), nbr_read);

   return nbr_read;
}



/*
==============================================================================
Name : stream_read_raw
Note :
   Same as stream_read, without the crc update.
==============================================================================
*/

std::size_t RttProtocol::stream_read_raw (void * ptr, std::size_t size)
{
   const auto nbr_read = pull_raw (ptr, size);

   _payload_pos += nbr_read;

   return nbr_read;
}



/*
==============================================================================
Name : stream_consumed
Note :
   Payload bytes consumed so far by the current stream, whoever read them
   (the handler or a parser it delegated to).
==============================================================================
*/

std::size_t RttProtocol::stream_consumed () const
{
   return _payload_pos;
}



/*
==============================================================================
Name : stream_crc_reset
==============================================================================
*/

void  RttProtocol::stream_crc_reset ()
{
   _crc = 0xFFFFFFFFu;
}



/*
==============================================================================
Name : stream_crc
Note :
   CRC-32 (IEEE) of the stream_read bytes since the last reset.
==============================================================================
*/

std::uint32_t  RttProtocol::stream_crc ()
{
   return ~_crc;
}



/*
==============================================================================
Name : command_ping
==============================================================================
*/

void  RttProtocol::command_ping (void * /* ctx */, std::span <const std::uint8_t> /* payload */)
{
   Rtt::use ().printf ("ok ping\n");
}



/*
==============================================================================
Name : stream_sink
Note :
   Down-channel throughput measurement, the payload is pulled and discarded.
==============================================================================
*/

void  RttProtocol::stream_sink (void * /* ctx */, std::size_t payload_size)
{
   auto & self = use ();

   const auto start_tick = daisy::System::GetTick ();

   std::uint8_t scratch [256];
   std::size_t done = 0;

   while (done < payload_size)
   {
      const auto part = std::min (payload_size - done, sizeof (scratch));
      const auto nbr_read = self.stream_read_raw (scratch, part);
      done += nbr_read;
      if (nbr_read != part) break;
   }

   const auto elapsed = daisy::System::GetTick () - start_tick;
   const auto us = elapsed / (daisy::System::GetTickFreq () / 1000000);
   const auto kb_per_s = (us > 0)
      ? std::uint32_t ((std::uint64_t (done) * 1000000u) / us / 1024u)
      : 0u;

   Rtt::use ().printf ("ok sink bytes=%lu us=%lu rate_kb_s=%lu\n",
      static_cast <unsigned long> (done),
      static_cast <unsigned long> (us),
      static_cast <unsigned long> (kb_per_s)
   );
}



/*
==============================================================================
Name : find
==============================================================================
*/

RttProtocol::Entry *  RttProtocol::find (std::uint32_t cmd)
{
   for (auto & entry : _entries)
   {
      if ((entry.kind != Kind::None) && (entry.cmd == cmd)) return &entry;
   }

   return nullptr;
}



/*
==============================================================================
Name : finish
Note :
   Called when a buffered box is complete.
==============================================================================
*/

void  RttProtocol::finish ()
{
   auto * entry_ptr = find (_header.cmd);

   if ((entry_ptr != nullptr) && (entry_ptr->kind == Kind::Command))
   {
      if (_header.payload_size > MaxPayloadSize)
      {
         Rtt::use ().printf ("err %c%c%c%c payload too big (%lu)\n",
            char (_header.cmd), char (_header.cmd >> 8),
            char (_header.cmd >> 16), char (_header.cmd >> 24),
            static_cast <unsigned long> (_header.payload_size)
         );
      }
      else
      {
         entry_ptr->command_handler (
            entry_ptr->ctx,
            std::span <const std::uint8_t> (_payload, std::size_t (_header.payload_size))
         );
      }
   }

   _header_pos = 0;
   _payload_pos = 0;
}



/*
==============================================================================
Name : read_source
Note :
   Non-blocking: leftover fifo bytes first (from a past stream), then the
   ring. While a stream is active the ring belongs to the audio thread and
   only the fifo is read.
==============================================================================
*/

std::size_t RttProtocol::read_source (void * ptr, std::size_t size)
{
   auto * dst = static_cast <std::uint8_t *> (ptr);
   std::size_t count = 0;

   if (_fifo != nullptr)
   {
      const auto wr = _fifo_wr.load (std::memory_order_acquire);
      auto rd = _fifo_rd.load (std::memory_order_relaxed);

      while ((rd != wr) && (count < size))
      {
         dst [count] = _fifo [rd % FifoSize];
         ++count;
         ++rd;
      }

      _fifo_rd.store (rd, std::memory_order_release);
   }

   if (count < size && ! _stream_active.load (std::memory_order_acquire))
   {
      count += Rtt::use ().read (dst + count, size - count);
   }

   return count;
}



/*
==============================================================================
Name : pull_raw
Note :
   Blocking pull from pending bytes then read_source, 2s inactivity
   timeout.
==============================================================================
*/

std::size_t RttProtocol::pull_raw (void * ptr, std::size_t size)
{
   auto * dst = static_cast <std::uint8_t *> (ptr);
   std::size_t count = 0;

   if (_pending_len > 0)
   {
      const auto copy = std::min (_pending_len, size);
      std::memcpy (dst, _pending_ptr, copy);
      _pending_ptr += copy;
      _pending_len -= copy;
      count += copy;
   }

   auto last_tick = daisy::System::GetTick ();

   while (count < size)
   {
      const auto nbr_read = read_source (dst + count, size - count);
      count += nbr_read;

      const auto now = daisy::System::GetTick ();
      if (nbr_read > 0)
      {
         last_tick = now;
      }
      else if (now - last_tick > 2 * daisy::System::GetTickFreq ())
      {
         break;   // timeout
      }
   }

   return count;
}



/*
==============================================================================
Name : crc_update
Note : CRC-32 (IEEE)
Reference: https://en.wikipedia.org/wiki/Cyclic_redundancy_check
==============================================================================
*/

void  RttProtocol::crc_update (const std::uint8_t * data, std::size_t size)
{
   auto crc = _crc;

   for (std::size_t i = 0 ; i < size ; ++i)
   {
      crc ^= data [i];
      for (int j = 0 ; j < 8 ; ++j)
      {
         crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
      }
   }

   _crc = crc;
}



}  // namespace erb

#endif   // erb_MONITOR && erb_TARGET_DAISY
