/*****************************************************************************

      PersistentBase.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>

#include <cstring>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : load
==============================================================================
*/

template <typename Type, uint64_t Magic>
template <typename Board>
Type  PersistentBase <Type, Magic>::load (Board & board, size_t page)
{
   const auto bytes = board.template load <sizeof (Magic) + sizeof (Type)> (page);

   uint64_t loaded_magic = 0;
   std::memcpy (&loaded_magic, &bytes [0], sizeof (Magic));

   Type value;

   if (loaded_magic == Magic)
   {
      std::memcpy (&value, &bytes [sizeof (Magic)], sizeof (Type));
   }

   return value;
}



/*
==============================================================================
Name : save
==============================================================================
*/

template <typename Type, uint64_t Magic>
template <typename Board>
void  PersistentBase <Type, Magic>::save (Board & board, size_t page, Type value)
{
   uint64_t magic = Magic;
   std::array <uint8_t, sizeof (Magic) + sizeof (Type)> data;

   std::memcpy (&data [0], &magic, sizeof (Magic));
   std::memcpy (&data [sizeof (Magic)], &value, sizeof (Type));

   board.save (page, data);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
