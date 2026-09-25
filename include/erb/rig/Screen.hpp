/*****************************************************************************

      Screen.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>



namespace erb
{
namespace rig
{



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_file_width
==============================================================================
*/

template <typename Format>
std::size_t impl_file_width (ScreenFile::Rotate rotate)
{
   const bool quarter
      = (rotate == ScreenFile::Rotate::R90Ccw)
      || (rotate == ScreenFile::Rotate::R90Cw);

   return quarter ? Format::height : Format::width;
}



/*
==============================================================================
Name : impl_file_height
==============================================================================
*/

template <typename Format>
std::size_t impl_file_height (ScreenFile::Rotate rotate)
{
   const bool quarter
      = (rotate == ScreenFile::Rotate::R90Ccw)
      || (rotate == ScreenFile::Rotate::R90Cw);

   return quarter ? Format::width : Format::height;
}



/*
==============================================================================
Name : impl_storage_x
==============================================================================
*/

template <typename Format>
std::size_t impl_storage_x (ScreenFile::Rotate rotate, std::size_t fx, std::size_t fy)
{
   switch (rotate)
   {
   case ScreenFile::Rotate::R0:
      return fx;

   case ScreenFile::Rotate::R90Ccw:
      return Format::width - 1 - fy;

   case ScreenFile::Rotate::R180:
      return Format::width - 1 - fx;

   case ScreenFile::Rotate::R90Cw:
      return fy;
   }

   __builtin_unreachable ();
}




/*
==============================================================================
Name : impl_storage_y
==============================================================================
*/

template <typename Format>
std::size_t impl_storage_y (ScreenFile::Rotate rotate, std::size_t fx, std::size_t fy)
{
   switch (rotate)
   {
   case ScreenFile::Rotate::R0:
      return fy;

   case ScreenFile::Rotate::R90Ccw:
      return fx;

   case ScreenFile::Rotate::R180:
      return Format::height - 1 - fy;

   case ScreenFile::Rotate::R90Cw:
      return Format::height - 1 - fx;
   }

   __builtin_unreachable ();
}



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : read_screen
==============================================================================
*/

template <typename Format>
Screen <Format>   read_screen (const ScreenFile & file)
{
   const auto width = impl_file_width <Format> (file.rotate);
   const auto height = impl_file_height <Format> (file.rotate);

   const auto gray = impl_read_png_gray (file.path, width, height);

   Screen <Format> screen;
   screen.storage.fill (0);
   screen.file = file;

   for (std::size_t fy = 0 ; fy < height ; ++fy)
   {
      for (std::size_t fx = 0 ; fx < width ; ++fx)
      {
         const auto x = impl_storage_x <Format> (file.rotate, fx, fy);
         const auto y = impl_storage_y <Format> (file.rotate, fx, fy);

         const bool on = gray [fx + fy * width] >= 128;
         set_pixel <Format> (screen.storage, x, y, on);
      }
   }

   return screen;
}



/*
==============================================================================
Name : write_screen
==============================================================================
*/

template <typename Format>
void  write_screen (const typename Format::Storage & storage, const ScreenFile & file)
{
   const auto width = impl_file_width <Format> (file.rotate);
   const auto height = impl_file_height <Format> (file.rotate);

   std::vector <std::uint8_t> gray (width * height, 0);

   for (std::size_t fy = 0 ; fy < height ; ++fy)
   {
      for (std::size_t fx = 0 ; fx < width ; ++fx)
      {
         const auto x = impl_storage_x <Format> (file.rotate, fx, fy);
         const auto y = impl_storage_y <Format> (file.rotate, fx, fy);

         gray [fx + fy * width] = get_pixel <Format> (storage, x, y) ? 255 : 0;
      }
   }

   impl_write_png_gray (file.path, width, height, gray);
}



/*
==============================================================================
Name : same
==============================================================================
*/

template <typename Format>
bool  same (const Display <Format> & display, const Screen <Format> & screen)
{
   return display.impl_data == screen.storage;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
