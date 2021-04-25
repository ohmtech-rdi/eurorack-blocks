/*****************************************************************************

      SdramObject.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <utility>



namespace erb
{

/*
==============================================================================
Name : make_sdram_object
==============================================================================
*/

template <typename T, class... Args>
SdramObject <T>   make_sdram_object (Args &&... args)
{
#if defined (erb_TARGET_DAISY)
   auto sdram_addr = reinterpret_cast <void *> (0xc0000000);
   auto ptr = new (sdram_addr) T (std::forward <Args> (args)...);

#elif defined (erb_TARGET_VCV_RACK)
   auto ptr = new T (std::forward <Args> (args)...);

#else
   #error Unknown erb target
#endif

   return SdramObject <T> (ptr);
}



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename T>
SdramObject <T>::SdramObject (SdramObject && rhs)
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
SdramObject <T>::~SdramObject ()
{
   if (_ptr == nullptr) return;

   _ptr->~T ();

#if defined (erb_TARGET_DAISY)
   // nothing

#elif defined (erb_TARGET_VCV_RACK)
   delete _ptr;

#else
   #error Unknown erb target
#endif

   _ptr = nullptr;
}



/*
==============================================================================
Name : operator *
==============================================================================
*/

template <typename T>
T &   SdramObject <T>::operator * () const
{
   return *_ptr;
}



/*
==============================================================================
Name : operator ->
==============================================================================
*/

template <typename T>
T *   SdramObject <T>::operator -> () const
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
SdramObject <T>::SdramObject (T * ptr)
:  _ptr (ptr)
{
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
