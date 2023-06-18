/*****************************************************************************

      Sram.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/MonotonicMemoryPool.h"

#include "erb/config.h"

#include <atomic>

#include <cstddef>
#include <cstdint>



namespace erb
{



class Sram
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   virtual        ~Sram () = default;

   template <typename T, class... Args>
   static T *     allocate (Args &&... args);

   static void *  allocate_bytes_nullptr_on_error (std::size_t size);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  Sram (uint8_t * storage);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   static Sram &  use_instance ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void *         allocate_raw (std::size_t alignment, std::size_t size);
   void *         allocate_raw_nullptr_on_error (std::size_t alignment, std::size_t size);

   uint8_t *      _sram_memory_pool_storage = nullptr;

   MonotonicMemoryPool <erb_SRAM_MEM_POOL_SIZE>
                  _memory_pool;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Sram (const Sram & rhs) = delete;
                  Sram (Sram && rhs) = delete;
   Sram &         operator = (const Sram & rhs) = delete;
   Sram &         operator = (Sram && rhs) = delete;
   bool           operator == (const Sram & rhs) const = delete;
   bool           operator != (const Sram & rhs) const = delete;



}; // class Sram



}  // namespace erb



#include "erb/detail/Sram.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
