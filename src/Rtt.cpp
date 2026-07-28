/*****************************************************************************

      Rtt.cpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Rtt.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include "daisy_core.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
SEGGER RTT licensing note: this is an independent implementation of the
RTT control block memory layout (the "SEGGER RTT" identifier and the ring
descriptor arrangement), so that standard debug probe software (openocd,
J-Link tools) can locate the buffers. It is used for debugging and logging
purposes only, in accordance with the terms SEGGER publishes for RTT
compatible implementations. No SEGGER source code is included.
*/

namespace erb
{



DMA_BUFFER_MEM_SECTION Rtt::ControlBlock Rtt::_cb;
DMA_BUFFER_MEM_SECTION char Rtt::_buffer_up [Rtt::BufferUpSize];
DMA_BUFFER_MEM_SECTION char Rtt::_buffer_down [Rtt::BufferDownSize];



/*
==============================================================================
Name : use
==============================================================================
*/

Rtt & Rtt::use ()
{
   static Rtt instance;
   return instance;
}



/*
==============================================================================
Name : init
   The control block and its rings live in the non-cacheable DMA RAM region
   so the probe always reads coherent data despite the write-back D-cache.
   That section is NOLOAD: every field is set here, the id last, so the
   probe never matches a half-initialized block.
==============================================================================
*/

void  Rtt::init ()
{
   _cb.max_nbr_up = 1;
   _cb.max_nbr_down = 1;

   _cb.up [0].name_0 = "erb-monitor";
   _cb.up [0].buffer = _buffer_up;
   _cb.up [0].size = BufferUpSize;
   _cb.up [0].wr_off = 0;
   _cb.up [0].rd_off = 0;
   _cb.up [0].flags = 0;

   _cb.down [0].name_0 = "erb-monitor";
   _cb.down [0].buffer = _buffer_down;
   _cb.down [0].size = BufferDownSize;
   _cb.down [0].wr_off = 0;
   _cb.down [0].rd_off = 0;
   _cb.down [0].flags = 0;

   asm volatile ("dmb" ::: "memory");

   std::memset (_cb.id, 0, sizeof (_cb.id));
   std::memcpy (_cb.id, "SEGGER RTT", 10);
}



/*
==============================================================================
Name : printf
==============================================================================
*/

void  Rtt::printf (const char * format_0, ...)
{
   char buf [192];

   va_list args;
   va_start (args, format_0);
   int len = vsnprintf (buf, sizeof (buf), format_0, args);
   va_end (args);

   if (len <= 0) return;

   write (buf, std::min (std::size_t (len), sizeof (buf) - 1));
}



/*
==============================================================================
Name : read
==============================================================================
*/

std::size_t Rtt::read (void * ptr, std::size_t max_size)
{
   auto & down = _cb.down [0];

   std::uint32_t rd = down.rd_off;
   const std::uint32_t wr = down.wr_off;   // written by the host probe

   auto * dst = static_cast <char *> (ptr);
   std::size_t count = 0;

   while ((rd != wr) && (count < max_size))
   {
      dst [count] = down.buffer [rd];
      ++count;
      if (++rd == down.size) rd = 0;
   }

   asm volatile ("dmb" ::: "memory");

   down.rd_off = rd;

   return count;
}



/*
==============================================================================
Name : write
   Non-blocking: when the ring is full the rest is skipped, never blocking
   the caller.
==============================================================================
*/

void  Rtt::write (const char * data, std::size_t size)
{
   auto & up = _cb.up [0];

   std::uint32_t wr = up.wr_off;

   for (std::size_t i = 0 ; i < size ; ++i)
   {
      std::uint32_t next = wr + 1;
      if (next == up.size) next = 0;

      if (next == up.rd_off) break;

      up.buffer [wr] = data [i];
      wr = next;
   }

   asm volatile ("dmb" ::: "memory");

   up.wr_off = wr;
}



}  // namespace erb

#endif   // erb_MONITOR && erb_TARGET_DAISY
