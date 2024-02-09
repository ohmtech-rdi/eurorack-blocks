/*****************************************************************************

      Persistent.hpp
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

template <typename Type, size_t Page, uint64_t Magic, size_t RateLimitMs>
template <typename Board>
Type  Persistent <Type, Page, Magic, RateLimitMs>::load (Board & board)
{
   const auto bytes = board.template load <sizeof (Magic) + sizeof (Type)> (Page);

   uint64_t loaded_magic = 0;
   std::memcpy (&loaded_magic, &bytes [0], sizeof (Magic));

   if (loaded_magic == Magic)
   {
      std::memcpy (&_value, &bytes [sizeof (Magic)], sizeof (Type));
   }

   return _value;
}



/*
==============================================================================
Name : save
==============================================================================
*/

template <typename Type, size_t Page, uint64_t Magic, size_t RateLimitMs>
template <typename Board>
void  Persistent <Type, Page, Magic, RateLimitMs>::save (Board & board, Type value)
{
   if (value != _value)
   {
      _value = value;
      _need_commit_flag = true;
      _earliest_commit_tp = Clock::now () + std::chrono::milliseconds {RateLimitMs};
   }

   if (_need_commit_flag && (Clock::now () > _earliest_commit_tp || RateLimitMs == 0))
   {
      uint64_t magic = Magic;
      std::array <uint8_t, sizeof (Magic) + sizeof (Type)> data;

      std::memcpy (&data [0], &magic, sizeof (Magic));
      std::memcpy (&data [sizeof (Magic)], &_value, sizeof (Type));

      board.save (Page, data);

      _need_commit_flag = false;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
