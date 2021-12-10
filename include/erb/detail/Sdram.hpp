/*****************************************************************************

      Sdram.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <new>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : allocate
==============================================================================
*/

template <typename T, class... Args>
T *   Sdram::allocate (Args &&... args)
{
   auto ptr = use_instance ().allocate_raw (alignof (T), sizeof (T));

   if (ptr == nullptr)
   {
#if defined (erb_TARGET_DAISY)
      asm("bkpt 255");

#elif defined (erb_TARGET_VCV_RACK)
      throw std::bad_alloc ();

#endif
   }

   return new (ptr) T (std::forward <Args> (args)...);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
