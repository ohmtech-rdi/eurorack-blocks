/*****************************************************************************

      ScreenWrite.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/Screen.h"

// stb writer, see 'Screen.cpp'

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>



namespace erb
{
namespace rig
{



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_write_png_gray
==============================================================================
*/

void  impl_write_png_gray (const std::string & path, std::size_t width, std::size_t height, const std::vector <std::uint8_t> & gray)
{
   assert (gray.size () == width * height);

   const int ok = stbi_write_png (path.c_str (), int (width), int (height), 1, gray.data (), int (width));

   if (ok == 0)
   {
      std::fprintf (stderr, "write_screen: cannot write '%s'\n", path.c_str ());
      std::fflush (stderr);
      std::abort ();
   }
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
