/*****************************************************************************

      Display.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <cstddef>



namespace erb
{



template <std::size_t W, std::size_t H>
struct FormatSsd130x
{
   static constexpr std::size_t width = W;
   static constexpr std::size_t height = H;

   // pixel arrangement, bit at (x, y)
   // storage [x + (y / 8) * width] & (1 << (y % 8);

   static_assert (width > 0);
   static_assert (height > 0);
   static_assert (height % 8 == 0);

   using Storage = std::array <std::uint8_t, width * height / 8>;
};



template <typename Format>
class Display
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Storage = typename Format::Storage;

   inline         Display (Storage & data);
   virtual        ~Display () = default;

   inline Display &
                  operator = (const Storage & data);

   inline         operator Storage & ();

   inline void    fill (bool val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   Storage &      impl_data;
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Display () = delete;
                  Display (const Display & rhs) = delete;
                  Display (Display && rhs) = delete;
   Display &      operator = (const Display & rhs) = delete;
   Display &      operator = (Display && rhs) = delete;
   bool           operator == (const Display & rhs) const = delete;
   bool           operator != (const Display & rhs) const = delete;



}; // class Display



}  // namespace erb



#include "erb/Display.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
