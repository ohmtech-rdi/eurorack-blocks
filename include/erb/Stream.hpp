/*****************************************************************************

      Stream.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : write
Description :
   Returns true if ok, false if overflowing
==============================================================================
*/

template <std::size_t BufferSize>
bool  Stream <BufferSize>::write (uint8_t byte)
{
   const std::size_t next_pos = (_write_pos + 1) % BufferSize;
   const bool can_write_flag = next_pos != _read_pos;

   if (can_write_flag)
   {
      _buffer [_write_pos] = byte;
      _write_pos = next_pos;
   }

   return can_write_flag;
}



/*
==============================================================================
Name : read
==============================================================================
*/

template <std::size_t BufferSize>
std::optional <uint8_t> Stream <BufferSize>::read ()
{
   if (_read_pos == _write_pos) return std::nullopt;  // abort

   const uint8_t val = _buffer [_read_pos];
   _read_pos = (_read_pos + 1) % BufferSize;

   return {val};
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
