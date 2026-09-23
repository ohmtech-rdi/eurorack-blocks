/*****************************************************************************

      BoardGeneric.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>

#include <cstring>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : load
==============================================================================
*/

template <std::size_t N>
std::array <uint8_t, N> BoardGeneric::load (size_t page)
{
   // This is a NAND flash so any untouched bits read as 1

   auto ret = std::array <uint8_t, N> {};
   ret.fill (0xff);

   auto it = _persistent_map.find (page);

   if (it != _persistent_map.end ())
   {
      const auto & stored = it->second;
      std::memcpy (&ret [0], &stored [0], std::min (stored.size (), N));
   }

   return ret;
}



/*
==============================================================================
Name : save
==============================================================================
*/

template <typename Data>
void  BoardGeneric::save (size_t page, const Data & data)
{
   // trim trailing 0xff bytes as they can be treated as untouched bits

   auto end = std::find_if (
      data.rbegin (), data.rend (),
      [](uint8_t byte){ return byte != 0xff; }
   ).base ();

   if (end == data.begin ())
   {
      _persistent_map.erase (page);
   }
   else
   {
      _persistent_map [page] = std::vector <uint8_t> { data.begin (), end };
   }
}



/*
==============================================================================
Name : erase
==============================================================================
*/

void  BoardGeneric::erase (size_t page)
{
   _persistent_map.erase (page);
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
