/*****************************************************************************

      SdramPtr.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "detail/Sdram.h"

#include <cstdlib>

#if defined (erb_TARGET_VCV_RACK)
   #include <iostream>
#endif



namespace erb
{

/*
==============================================================================
Name : make_sdram
==============================================================================
*/

template <typename T, class... Args>
SdramPtr <T>   make_sdram (Args &&... args)
{
   auto ptr = Sdram::allocate <T> (std::forward <Args> (args)...);

   return SdramPtr <T> (ptr);
}



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename T>
SdramPtr <T>::SdramPtr (SdramPtr && rhs)
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
SdramPtr <T>::~SdramPtr ()
{
   release ();
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <typename T>
SdramPtr <T> & SdramPtr <T>::operator = (SdramPtr <T> && rhs)
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
typename SdramPtr <T>::pointer   SdramPtr <T>::get () const
{
   return _ptr;
}



/*
==============================================================================
Name : operator bool
==============================================================================
*/

template <typename T>
SdramPtr <T>::operator bool () const
{
   return _ptr != nullptr;
}



/*
==============================================================================
Name : operator *
==============================================================================
*/

template <typename T>
typename SdramPtr <T>::reference SdramPtr <T>::operator * () const
{
   return *_ptr;
}



/*
==============================================================================
Name : operator ->
==============================================================================
*/

template <typename T>
typename SdramPtr <T>::pointer   SdramPtr <T>::operator -> () const
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
SdramPtr <T>::SdramPtr (pointer ptr)
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
void  SdramPtr <T>::release ()
{
   if (_ptr == nullptr) return;

   _ptr->~T ();

   // Potential memory leak

   // Embedded development on a platform with very limited RAM is not the same
   // as in desktop software development.

   // The following trace in the simulator helps to catch them.

#if defined (erb_TARGET_VCV_RACK)
   std::cout << "Warning: erb::SramPtr::release: Potential memory leak, unless you were removing the module\n";
   std::cout << "         Set a breakpoint to debug.\n";
#endif

   _ptr = nullptr;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
