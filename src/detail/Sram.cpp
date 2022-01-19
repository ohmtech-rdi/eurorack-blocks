/*****************************************************************************

      Sram.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Sram.h"

#include <cstdint>
#include <cstdlib>
#include <type_traits>

#if defined (erb_TARGET_DAISY)
   #include "dev/sdram.h"
#endif



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Sram::Sram ()
#if defined (erb_TARGET_DAISY)
:  _sram_memory_pool_storage (new uint8_t [erb_SRAM_MEM_POOL_SIZE])
#endif
{
}




/*
==============================================================================
Name : allocate_bytes_nullptr_on_error
==============================================================================
*/

void *   Sram::allocate_bytes_nullptr_on_error (size_t size)
{
   return use_instance ().allocate_raw_nullptr_on_error (1, size);
}



/*
==============================================================================
Name : use_instance
==============================================================================
*/

Sram &  Sram::use_instance ()
{
#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

   static Sram instance;

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

void *   Sram::allocate_raw (size_t alignment, size_t size)
{
   const size_t pos = _memory_pool.allocate (alignment, size);

#if defined (erb_TARGET_DAISY)
   return &_sram_memory_pool_storage [pos];

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

void *   Sram::allocate_raw_nullptr_on_error (size_t alignment, size_t size)
{
   const size_t pos = _memory_pool.allocate_npos_on_error (alignment, size);

   if (pos == size_t (-1)) return nullptr;

#if defined (erb_TARGET_DAISY)
   return &_sram_memory_pool_storage [pos];

#else
   ((void)(pos)); // ignore pos

   // Not all c++17 cstdlib do have a 'std::aligned_alloc' implementation.
   // Use 'std::malloc' as optimising alignment is not needed for the simulator.
   return std::malloc (size);
#endif
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
