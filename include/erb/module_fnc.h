/*****************************************************************************

      module_fnc.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <type_traits>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

namespace erb
{



template <typename T>
struct has_init
{
   template <typename U, void (U::*) ()> struct sfinae {};

   template <typename U> static char test (sfinae <U, &U::init> *);
   template <typename U> static long test (...);

   enum { value = (sizeof test <T> (nullptr) == 1) };
};

template <typename T>
typename std::enable_if <has_init <T>::value>::type module_init (T & t)
{
    t.init ();
}

template <typename T>
typename std::enable_if <!has_init <T>::value>::type module_init (T &)
{
    // nothing
}



template <typename T>
struct has_idle
{
   template <typename U, void (U::*) ()> struct sfinae {};

   template <typename U> static char test (sfinae <U, &U::idle> *);
   template <typename U> static long test (...);

   enum { value = (sizeof test <T> (nullptr) == 1) };
};

template <typename T>
typename std::enable_if <has_idle <T>::value>::type module_idle (T & t)
{
    t.idle ();
}

template <typename T>
typename std::enable_if <!has_idle <T>::value>::type module_idle (T &)
{
    // nothing
}



} // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
