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
   _value = _base.load (board, Page);

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
   if (!(value == _value))
   {
      _value = value;
      _need_commit_flag = true;
      _earliest_commit_tp = SystemClock::now () + std::chrono::milliseconds {RateLimitMs};
   }

   if (_need_commit_flag && (SystemClock::now () > _earliest_commit_tp || RateLimitMs == 0))
   {
      _base.save (board, Page, _value);

      _need_commit_flag = false;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
