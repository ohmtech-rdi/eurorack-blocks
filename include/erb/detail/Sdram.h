/*****************************************************************************

      Sdram.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"
#if (erb_SDRAM_USE_FLAG)

#include "erb/detail/MonotonicMemoryPool.h"

#include <atomic>

#include <cstddef>



namespace erb
{



class Sdram
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   virtual        ~Sdram () = default;

   template <typename T, class... Args>
   static T *     allocate (Args &&... args);

   static void *  allocate_bytes_nullptr_on_error (std::size_t size);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  Sdram (uint8_t * storage);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   static Sdram & use_instance ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void *         allocate_raw (std::size_t alignment, std::size_t size);
   void *         allocate_raw_nullptr_on_error (std::size_t alignment, std::size_t size);

   uint8_t *      _sdram_memory_pool_storage = nullptr;

   MonotonicMemoryPool <erb_SDRAM_MEM_POOL_SIZE>
                  _memory_pool;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Sdram (const Sdram & rhs) = delete;
                  Sdram (Sdram && rhs) = delete;
   Sdram &        operator = (const Sdram & rhs) = delete;
   Sdram &        operator = (Sdram && rhs) = delete;
   bool           operator == (const Sdram & rhs) const = delete;
   bool           operator != (const Sdram & rhs) const = delete;



}; // class Sdram



}  // namespace erb



#include "erb/detail/Sdram.hpp"



#endif   // erb_SDRAM_USE_FLAG



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
