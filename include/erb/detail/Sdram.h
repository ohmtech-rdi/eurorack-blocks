/*****************************************************************************

      Sdram.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/MonotonicMemoryPool.h"

#include "erb/config.h"

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

   static void *  allocate_bytes_nullptr_on_error (size_t size);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  Sdram () = default;

   static Sdram & use_instance ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void *         allocate_raw (size_t alignment, size_t size);
   void *         allocate_raw_nullptr_on_error (size_t alignment, size_t size);

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



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
