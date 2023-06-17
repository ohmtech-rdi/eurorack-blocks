/*****************************************************************************

      Sram.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Sram.h"

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
std::aligned_storage <erb_SRAM_MEM_POOL_SIZE>::type __attribute__((section(".heap")))
   erb_sram_memory_pool_storage;
#endif



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Sram::Sram (uint8_t * storage)
:  _sram_memory_pool_storage (storage)
{
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : allocate_bytes_nullptr_on_error
==============================================================================
*/

void *   Sram::allocate_bytes_nullptr_on_error (std::size_t size)
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
#if defined (erb_TARGET_DAISY)
   static Sram instance (reinterpret_cast <uint8_t *> (&erb_sram_memory_pool_storage));
   return instance;

#elif defined (erb_TARGET_VCV_RACK)
   return ModuleBoard::current ().sram ();

#elif defined (erb_TARGET_UNIT_TEST)

   #if defined (__clang__)
      #pragma clang diagnostic push
      #pragma clang diagnostic ignored "-Wexit-time-destructors"
   #endif

   static std::array <uint8_t, erb_SRAM_MEM_POOL_SIZE> storage;
   static Sram instance (&storage [0]);
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

void *   Sram::allocate_raw (std::size_t alignment, std::size_t size)
{
   const std::size_t pos = _memory_pool.allocate (alignment, size);

   return &_sram_memory_pool_storage [pos];
}



/*
==============================================================================
Name : allocate_raw_nullptr_on_error
==============================================================================
*/

void *   Sram::allocate_raw_nullptr_on_error (std::size_t alignment, std::size_t size)
{
   const std::size_t pos = _memory_pool.allocate_npos_on_error (alignment, size);

   if (pos == std::size_t (-1)) return nullptr;

   return &_sram_memory_pool_storage [pos];
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
