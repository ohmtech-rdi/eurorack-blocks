/*****************************************************************************

      Sdram.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Sdram.h"

#include <cstdint>
#include <cstdlib>
#include <type_traits>

#if defined (erb_TARGET_DAISY)
   #include "dev/sdram.h"
#endif



namespace erb
{



#if defined (erb_TARGET_DAISY)
std::aligned_storage <erb_SDRAM_MEM_POOL_SIZE>::type DSY_SDRAM_BSS
   erb_sdram_memory_pool_storage;
#endif



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : allocate_bytes_nullptr_on_error
==============================================================================
*/

void *   Sdram::allocate_bytes_nullptr_on_error (size_t size)
{
   return use_instance ().allocate_raw_nullptr_on_error (1, size);
}



/*
==============================================================================
Name : use_instance
==============================================================================
*/

Sdram &  Sdram::use_instance ()
{
#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

   static Sdram instance;

#if defined (__clang__)
   #pragma clang diagnostic pop
#endif

   return instance;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : allocate_raw
==============================================================================
*/

void *   Sdram::allocate_raw (size_t alignment, size_t size)
{
   const size_t pos = _memory_pool.allocate (alignment, size);

#if defined (erb_TARGET_DAISY)
   auto raw_ptr = static_cast <void *> (&erb_sdram_memory_pool_storage);
   auto byte_ptr = static_cast <uint8_t *> (raw_ptr);
   return &byte_ptr [pos];

#else
   ((void)(pos)); // ignore pos

   // Not all c++17 cstdlib do have a 'std::aligned_alloc' implementation.
   // Use 'std::malloc' as optimising alignment is not needed for the simulator.
   return std::malloc (size);
#endif
}



/*
==============================================================================
Name : allocate_raw_nullptr_on_error
==============================================================================
*/

void *   Sdram::allocate_raw_nullptr_on_error (size_t alignment, size_t size)
{
   const size_t pos = _memory_pool.allocate_npos_on_error (alignment, size);

   if (pos == size_t (-1)) return nullptr;

#if defined (erb_TARGET_DAISY)
   auto raw_ptr = static_cast <void *> (&erb_sdram_memory_pool_storage);
   auto byte_ptr = static_cast <uint8_t *> (raw_ptr);
   return &byte_ptr [pos];

#else
   ((void)(pos)); // ignore pos

   // Not all c++17 cstdlib do have a 'std::aligned_alloc' implementation.
   // Use 'std::malloc' as optimising alignment is not needed for the simulator.
   return std::malloc (size);
#endif
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
