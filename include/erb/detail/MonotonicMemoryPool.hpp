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

template <size_t MaxSize>
size_t   MonotonicMemoryPool <MaxSize>::allocate (size_t alignment, size_t size)
{
   const size_t mask = alignment - 1;
   const size_t max_needed_size = size + mask;
   const size_t pos = _pos.fetch_add (max_needed_size, std::memory_order_relaxed);

   if (pos + max_needed_size > MaxSize)
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

   const size_t aligned_pos = (pos + mask) & ~mask;

   return aligned_pos;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
