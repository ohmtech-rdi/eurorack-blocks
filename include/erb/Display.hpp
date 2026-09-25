/*****************************************************************************

      Display.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : get_pixel
==============================================================================
*/

template <typename Format>
requires is_format_ssd130x <Format>::value
bool  get_pixel (const typename Format::Storage & storage, std::size_t x, std::size_t y)
{
   return (storage [x + (y / 8) * Format::width] & (1 << (y % 8))) != 0;
}



/*
==============================================================================
Name : set_pixel
==============================================================================
*/

template <typename Format>
requires is_format_ssd130x <Format>::value
void  set_pixel (typename Format::Storage & storage, std::size_t x, std::size_t y, bool on)
{
   auto & byte = storage [x + (y / 8) * Format::width];
   const auto bit = std::uint8_t (1 << (y % 8));

   byte = on ? (byte | bit) : (byte & ~bit);
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename Format>
Display <Format>::Display (Storage & data)
:  impl_data (data)
{
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <typename Format>
Display <Format> &   Display <Format>::operator = (const Storage & data)
{
   impl_data = data;

   return *this;
}



/*
==============================================================================
Name : operator Storage &
==============================================================================
*/

template <typename Format>
Display <Format>::operator Storage & ()
{
   return impl_data;
}



/*
==============================================================================
Name : fill
==============================================================================
*/

template <typename Format>
void  Display <Format>::fill (bool val)
{
   impl_data.fill (val ? 0xff : 0x00);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
