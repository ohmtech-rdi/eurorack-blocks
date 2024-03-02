/*****************************************************************************

      Sdram.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Sdram.h"

#if (erb_SDRAM_USE_FLAG)

#if defined (erb_TARGET_VCV_RACK)
   #include "erb/vcvrack/ModuleBoard.h"
#endif

#if defined (erb_TARGET_UNIT_TEST)
   #include <array>
#endif
#include <cstdint>
#include <cstdlib>
#include <type_traits>



namespace erb
{



#if defined (erb_TARGET_DAISY)
std::aligned_storage <erb_SDRAM_MEM_POOL_SIZE>::type __attribute__((section(".sdram_bss")))
   erb_sdram_memory_pool_storage;
#endif



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Sdram::Sdram (uint8_t * storage)
:  _sdram_memory_pool_storage (storage)
{
}



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
#if defined (erb_TARGET_DAISY)
   static Sdram instance (reinterpret_cast <uint8_t *> (&erb_sdram_memory_pool_storage));
   return instance;

#elif defined (erb_TARGET_VCV_RACK)
   return ModuleBoard::current ().sdram ();

#elif defined (erb_TARGET_UNIT_TEST)

   #if defined (__clang__)
      #pragma clang diagnostic push
      #pragma clang diagnostic ignored "-Wexit-time-destructors"
   #endif

   static std::array <uint8_t, erb_SDRAM_MEM_POOL_SIZE> storage;
   static Sdram instance (&storage [0]);
   return instance;

   #if defined (__clang__)
      #pragma clang diagnostic pop
   #endif

#endif
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : allocate_raw
==============================================================================
*/

void *   Sdram::allocate_raw (size_t alignment, size_t size)
{
   const std::size_t pos = _memory_pool.allocate (alignment, size);

   return &_sdram_memory_pool_storage [pos];
}



/*
==============================================================================
Name : allocate_raw_nullptr_on_error
==============================================================================
*/

void *   Sdram::allocate_raw_nullptr_on_error (size_t alignment, size_t size)
{
   const std::size_t pos = _memory_pool.allocate_npos_on_error (alignment, size);

   if (pos == std::size_t (-1)) return nullptr;

   return &_sdram_memory_pool_storage [pos];
}



}  // namespace erb



#endif   // erb_SDRAM_USE_FLAG



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
