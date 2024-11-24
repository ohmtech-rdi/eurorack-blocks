/*****************************************************************************

      DisplayContext.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename Format>
DisplayContext <Format>::DisplayContext (Storage & data)
:  _data (data)
{
}



/*
==============================================================================
Name : operator Storage
==============================================================================
*/

template <typename Format>
DisplayContext <Format>::operator Storage () const
{
   return _data;
}



/*
==============================================================================
Name : rotate_ccw
==============================================================================
*/

template <typename Format>
typename DisplayContext <Format>::Storage DisplayContext <Format>::rotate_ccw (std::size_t width, std::size_t height) const
{
   Storage ret;

   for (std::size_t x = 0 ; x < width ; ++x)
   for (std::size_t y = 0 ; y < height ; ++y)
   {
      auto & d = ret [x + (y / 8) * width];
      const auto s = _data [y + ((width - 1 - x) / 8) * height];
      const auto b = (s & (1 << (width - 1 - x) % 8)) != 0;
      if (b)
      {
         d |= 1 << y % 8;
      }
      else
      {
         d &= ~(1 << y % 8);
      }
   }

   return ret;
}



/*
==============================================================================
Name : rotate_180
==============================================================================
*/

template <typename Format>
typename DisplayContext <Format>::Storage DisplayContext <Format>::rotate_180 (std::size_t width, std::size_t height) const
{
   Storage ret;

   for (std::size_t x = 0 ; x < width ; ++x)
   for (std::size_t y = 0 ; y < height ; ++y)
   {
      auto & d = ret [x + (y / 8) * width];
      const auto s = _data [(width - 1 - x) + ((height - 1 - y) / 8) * width];
      const auto b = (s & (1 << (height - 1 - y) % 8)) != 0;
      if (b)
      {
         d |= 1 << y % 8;
      }
      else
      {
         d &= ~(1 << y % 8);
      }
   }

   return ret;
}



/*
==============================================================================
Name : set
==============================================================================
*/

template <typename Format>
void  DisplayContext <Format>::set (Color color)
{
   _color = color;
}



/*
==============================================================================
Name : fill
==============================================================================
*/

template <typename Format>
void  DisplayContext <Format>::fill ()
{
   switch (_color)
   {
   case Color::On:
      _data.fill (0xff);
      break;

   case Color::Off:
      _data.fill (0x00);
      break;

   case Color::Invert:
      for (auto & b : _data) b = ~b;
      break;
   }
}



/*
==============================================================================
Name : draw
==============================================================================
*/

template <typename Format>
void  DisplayContext <Format>::draw (std::size_t x, std::size_t y, std::size_t width, std::size_t height)
{
   const auto ex = std::min (x + width, Format::width);
   const auto ey = std::min (y + height, Format::height);

   for (std::size_t cx = x ; cx < ex ; ++cx)
   for (std::size_t cy = y ; cy < ey ; ++cy)
   {
      auto & b = _data [cx + (cy / 8) * Format::width];

      switch (_color)
      {
      case Color::On:
         b |= 1 << cy % 8;
         break;

      case Color::Off:
         b &= ~(1 << cy % 8);
         break;

      case Color::Invert:
         b ^= 1 << cy % 8;
         break;
      }
   }
}



/*
==============================================================================
Name : draw
==============================================================================
*/

template <typename Format>
template <typename Picture>
void  DisplayContext <Format>::draw (std::size_t x, std::size_t y, const Picture & picture, std::size_t width, std::size_t height)
{
   const auto ex = std::min (x + width, Format::width);
   const auto ey = std::min (y + height, Format::height);

   for (std::size_t cx = x, ix = 0 ; cx < ex ; ++cx, ++ix)
   for (std::size_t cy = y, iy = 0 ; cy < ey ; ++cy, ++iy)
   {
      auto & d = _data [cx + (cy / 8) * Format::width];
      const auto s = picture [ix + (iy / 8) * width];
      const auto b = (s & (1 << iy % 8)) != 0;

      switch (_color)
      {
      case Color::On:
         if (b) d |= 1 << cy % 8;
         break;

      case Color::Off:
         if (b) d &= ~(1 << cy % 8);
         break;

      case Color::Invert:
         if (b) d ^= 1 << cy % 8;
         break;
      }
   }
}



/*
==============================================================================
Name : draw
==============================================================================
*/

template <typename Format>
template <typename Picture>
void  DisplayContext <Format>::draw (std::size_t x, std::size_t y, const Picture & picture, std::size_t width, std::size_t height, char c)
{
   const auto cw = width / 64;
   const auto ex = std::min (x + cw, Format::width);
   const auto ey = std::min (y + height, Format::height);

   size_t p = (size_t (c) - 32) * cw;

   for (std::size_t cx = x, ix = p ; cx < ex ; ++cx, ++ix)
   for (std::size_t cy = y, iy = 0 ; cy < ey ; ++cy, ++iy)
   {
      auto & d = _data [cx + (cy / 8) * Format::width];
      const auto s = picture [ix + (iy / 8) * width];
      const auto b = (s & (1 << iy % 8)) != 0;

      switch (_color)
      {
      case Color::On:
         if (b) d |= 1 << cy % 8;
         break;

      case Color::Off:
         if (b) d &= ~(1 << cy % 8);
         break;

      case Color::Invert:
         if (b) d ^= 1 << cy % 8;
         break;
      }
   }
}



/*
==============================================================================
Name : draw
==============================================================================
*/

template <typename Format>
template <typename Picture>
void  DisplayContext <Format>::draw (std::size_t x, std::size_t y, const Picture & picture, std::size_t width, std::size_t height, const char * str_0)
{
   const auto cw = width / 64;

   while (*str_0 != '\0')
   {
      draw (x, y, picture, width, height, *str_0);
      x += cw;

      ++str_0;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
