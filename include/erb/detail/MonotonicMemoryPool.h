/*****************************************************************************

      MonotonicMemoryPool.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <atomic>

#include <cstddef>



namespace erb
{



template <size_t MaxSize>
class MonotonicMemoryPool
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  MonotonicMemoryPool () = default;
   virtual        ~MonotonicMemoryPool () = default;

   size_t         allocate (size_t alignment, size_t size);
   size_t         allocate_npos_on_error (size_t alignment, size_t size);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::atomic <size_t>
                  _pos = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  MonotonicMemoryPool (const MonotonicMemoryPool & rhs) = delete;
                  MonotonicMemoryPool (MonotonicMemoryPool && rhs) = delete;
   MonotonicMemoryPool &
                  operator = (const MonotonicMemoryPool & rhs) = delete;
   MonotonicMemoryPool &
                  operator = (MonotonicMemoryPool && rhs) = delete;
   bool           operator == (const MonotonicMemoryPool & rhs) const = delete;
   bool           operator != (const MonotonicMemoryPool & rhs) const = delete;



}; // class MonotonicMemoryPool



}  // namespace erb



#include "erb/detail/MonotonicMemoryPool.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
