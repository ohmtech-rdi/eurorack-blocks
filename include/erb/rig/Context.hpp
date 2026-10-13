/*****************************************************************************

      Context.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>
#include <cstdio>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : context
==============================================================================
*/

template <typename T>
T  context (const std::string & key)
{
   ContextMap & instance = impl_context_singleton ();

   auto it = instance.find (key);

   if (it == instance.end ())
   {
      std::fprintf (stderr, "context: missing key '%s'\n", key.c_str ());
      std::fflush (stderr);
      assert (false);
   }

   const T * value_ptr = std::any_cast <T> (&it->second);

   if (value_ptr == nullptr)
   {
      std::fprintf (stderr, "context: key '%s' does not hold a '%s'\n", key.c_str (), typeid (T).name ());
      std::fflush (stderr);
      assert (false);
   }

   return *value_ptr;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
