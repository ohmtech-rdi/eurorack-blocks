/*****************************************************************************

      JaggedArray.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : resize
==============================================================================
*/

template <typename T>
void  JaggedArray::resize (std::initializer_list <size_t> row_sizes, const T & value)
{
   size_t start_index = 0;

   for (auto && row_size : row_sizes)
   {
      _row_start_indexes.push_back (start_index);
      start_index += row_size;
   }

   _row_start_indexes.push_back (start_index);

   _data.resize (start_index, value);
}



/*
==============================================================================
Name : size
==============================================================================
*/

template <typename T>
size_t   JaggedArray::size () const
{
   return _data.size ();
}



/*
==============================================================================
Name : size
==============================================================================
*/

template <typename T>
size_t   JaggedArray::size (size_t row) const
{
   return _row_start_indexes [row + 1] - _row_start_indexes [row];
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

template <typename T>
T &   JaggedArray::operator [] (size_t global_index)
{
   return _data [global_index];
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

template <typename T>
const T &   JaggedArray::operator [] (size_t global_index) const
{
   return _data [global_index];
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

template <typename T>
T &   JaggedArray::operator [] (size_t row, size_t index)
{
   return _data [_row_start_indexes [row] + index];
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

template <typename T>
const T &   JaggedArray::operator [] (size_t row, size_t index) const
{
   return _data [_row_start_indexes [row] + index];
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
