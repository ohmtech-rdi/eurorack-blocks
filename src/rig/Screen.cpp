/*****************************************************************************

      Screen.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/Screen.h"

// this is embarrassing but stb image read and write headers can't be
// compiled in the same translation unit because they both define
// a static function 'stbi__paeth' (which does the same thing).
// So 'ScreenWrite.cpp' will have just the 'stb_image_write' part

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ScreenFile::actual_path
Description :
   '<stem>.actual<extension>'
   "actual" as in actual value of an "expect" test
==============================================================================
*/

std::string ScreenFile::actual_path () const
{
   // the path is ours: it ends with an extension
   const auto pos = path.rfind ('.');
   assert (pos != std::string::npos);
   assert (path.find ('/', pos) == std::string::npos);

   return path.substr (0, pos) + ".actual" + path.substr (pos);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_read_png_gray
==============================================================================
*/

std::vector <std::uint8_t>  impl_read_png_gray (const std::string & path, std::size_t width, std::size_t height)
{
   int w = 0;
   int h = 0;
   int channels = 0;

   auto * data = stbi_load (path.c_str (), &w, &h, &channels, 1);

   if (data == nullptr)
   {
      std::fprintf (stderr, "read_screen: cannot read '%s': %s\n", path.c_str (), stbi_failure_reason ());
      std::fflush (stderr);
      std::abort ();
   }

   if ((std::size_t (w) != width) || (std::size_t (h) != height))
   {
      std::fprintf (stderr, "read_screen: '%s' is %dx%d, display is %zux%zu\n", path.c_str (), w, h, width, height);
      std::fflush (stderr);
      stbi_image_free (data);
      std::abort ();
   }

   std::vector <std::uint8_t> gray (data, data + width * height);

   stbi_image_free (data);

   return gray;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
