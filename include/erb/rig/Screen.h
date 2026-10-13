/*****************************************************************************

      Screen.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Display.h"

#include <string>
#include <vector>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



struct ScreenFile
{
   enum class Rotate
   {
      R0,
      R90Ccw,
      R180,
      R90Cw,
   };

   std::string path;
   Rotate      rotate = Rotate::R0;

   std::string actual_path () const;
};


template <typename Format>
struct Screen
{
   typename Format::Storage
               storage;    // value
   ScreenFile  file;       // metadata
};


template <typename Format>
Screen <Format>
      read_screen (const ScreenFile & file);

template <typename Format>
void  write_screen (const typename Format::Storage & storage, const ScreenFile & file);

template <typename Format>
bool  same (const Display <Format> & display, const Screen <Format> & screen);

std::vector <std::uint8_t>
      impl_read_png_gray (const std::string & path, std::size_t width, std::size_t height);
void  impl_write_png_gray (const std::string & path, std::size_t width, std::size_t height, const std::vector <std::uint8_t> & gray);



}  // namespace rig
}  // namespace erb



#include "erb/rig/Screen.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
