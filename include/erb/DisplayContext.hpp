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
void  DisplayContext <Format>::draw (int x, int y, int width, int height)
{
   const int bx = std::max (x, 0);
   const int by = std::max (y, 0);
   const int ex = std::min (x + width, int (Format::width));
   const int ey = std::min (y + height, int (Format::height));

   if (ex <= bx) return;
   if (ey <= by) return;

   for (int cx = bx ; cx < ex ; ++cx)
   for (int cy = by ; cy < ey ; ++cy)
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
void  DisplayContext <Format>::draw (int x, int y, const Picture & picture, int width, int height)
{
   const int bx = std::max (x, 0);
   const int by = std::max (y, 0);
   const int ex = std::min (x + width, int (Format::width));
   const int ey = std::min (y + height, int (Format::height));

   if (ex <= bx) return;
   if (ey <= by) return;

   for (int cx = bx, ix = bx - x ; cx < ex ; ++cx, ++ix)
   for (int cy = by, iy = by - y ; cy < ey ; ++cy, ++iy)
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
void  DisplayContext <Format>::draw (int x, int y, const Picture & picture, int width, int height, char c)
{
   const int cw = width / 64;

   const int bx = std::max (x, 0);
   const int by = std::max (y, 0);
   const int ex = std::min (x + cw, int (Format::width));
   const int ey = std::min (y + height, int (Format::height));

   if (ex <= bx) return;
   if (ey <= by) return;

   const int p = (int (c) - 32) * cw;

   for (int cx = bx, ix = p + bx - x ; cx < ex ; ++cx, ++ix)
   for (int cy = by, iy = by - y ; cy < ey ; ++cy, ++iy)
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
void  DisplayContext <Format>::draw (int x, int y, const Picture & picture, int width, int height, const char * str_0)
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
