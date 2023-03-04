/*****************************************************************************

      MonotonicMemoryPool.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#include <new>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : allocate
==============================================================================
*/

template <std::size_t MaxSize>
std::size_t MonotonicMemoryPool <MaxSize>::allocate (std::size_t alignment, size_t size)
{
   std::size_t pos = allocate_npos_on_error (alignment, size);

   if (pos == std::size_t (-1))
   {
#if defined (erb_TARGET_DAISY)
      asm ("bkpt 255");
#elif (erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK)
      // Either:
      // - The module is using too much memory,
      // - Multiple modules are being debugged (check erb/config.h for workaround)
      throw std::bad_alloc ();
#endif
   }

   return pos;
}



/*
==============================================================================
Name : allocate_npos_on_error
==============================================================================
*/

template <std::size_t MaxSize>
std::size_t MonotonicMemoryPool <MaxSize>::allocate_npos_on_error (std::size_t alignment, std::size_t size)
{
   const size_t mask = alignment - 1;
   const size_t max_needed_size = size + mask;
   const size_t pos = _pos.fetch_add (max_needed_size, std::memory_order_relaxed);

   if (pos + max_needed_size > MaxSize)
   {
      _pos = pos; // not concurrent-safe
      return std::size_t (-1);
   }

   const std::size_t aligned_pos = (pos + mask) & ~mask;

   return aligned_pos;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
