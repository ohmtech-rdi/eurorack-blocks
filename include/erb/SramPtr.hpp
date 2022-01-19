/*****************************************************************************

      SramPtr.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "detail/Sram.h"

#include <cstdlib>

#if defined (erb_TARGET_VCV_RACK)
   #include <iostream>
#endif



namespace erb
{

/*
==============================================================================
Name : make_sram
==============================================================================
*/

template <typename T, class... Args>
SramPtr <T>   make_sram (Args &&... args)
{
   auto ptr = Sram::allocate <T> (std::forward <Args> (args)...);

   return SramPtr <T> (ptr);
}



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename T>
SramPtr <T>::SramPtr (SramPtr && rhs)
{
   _ptr = rhs._ptr;
   rhs._ptr = nullptr;
}




/*
==============================================================================
Name : dtor
==============================================================================
*/

template <typename T>
SramPtr <T>::~SramPtr ()
{
   release ();
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <typename T>
SramPtr <T> & SramPtr <T>::operator = (SramPtr <T> && rhs)
{
   release ();

   _ptr = rhs._ptr;
   rhs._ptr = nullptr;

   return *this;
}



/*
==============================================================================
Name : get
==============================================================================
*/

template <typename T>
typename SramPtr <T>::pointer   SramPtr <T>::get () const
{
   return _ptr;
}



/*
==============================================================================
Name : operator bool
==============================================================================
*/

template <typename T>
SramPtr <T>::operator bool () const
{
   return _ptr != nullptr;
}



/*
==============================================================================
Name : operator *
==============================================================================
*/

template <typename T>
typename SramPtr <T>::reference SramPtr <T>::operator * () const
{
   return *_ptr;
}



/*
==============================================================================
Name : operator ->
==============================================================================
*/

template <typename T>
typename SramPtr <T>::pointer   SramPtr <T>::operator -> () const
{
   return _ptr;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename T>
SramPtr <T>::SramPtr (pointer ptr)
:  _ptr (ptr)
{
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : release
==============================================================================
*/

template <typename T>
void  SramPtr <T>::release ()
{
   if (_ptr == nullptr) return;

   _ptr->~T ();

   // Potential memory leak

   // Embedded development on a platform with very limited RAM is not the same
   // as in desktop software development.

   // The following trace in the simulator helps to catch them.

#if defined (erb_TARGET_VCV_RACK)
   std::cout << "Warning: erb::SramPtr::release: Potential memory leak.\n";
   std::cout << "         Set a breakpoint to debug.\n";

   // only for simulator, see 'Sram::allocate_raw' for allocation system.
   std::free (_ptr);
#endif

   _ptr = nullptr;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
