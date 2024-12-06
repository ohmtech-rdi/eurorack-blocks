/*****************************************************************************

      DisplayContext.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <cstddef>



namespace erb
{



template <typename Format>
class DisplayContext
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Storage = typename Format::Storage;

   enum class Color
   {
      On, Off, Invert
   };

                  DisplayContext (Storage & data);
   virtual        ~DisplayContext () = default;

                  operator Storage () const;
   Storage        rotate_ccw (std::size_t width, std::size_t height) const;
   Storage        rotate_180 (std::size_t width, std::size_t height) const;

   void           set (Color color);

   void           fill ();
   void           draw (std::size_t x, std::size_t y, std::size_t width, std::size_t height);
   template <typename Picture>
   void           draw (std::size_t x, std::size_t y, const Picture & picture, std::size_t width, std::size_t height);
   template <typename Picture>
   void           draw (std::size_t x, std::size_t y, const Picture & picture, std::size_t width, std::size_t height, char c);
   template <typename Picture>
   void           draw (std::size_t x, std::size_t y, const Picture & picture, std::size_t width, std::size_t height, const char * str_0);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Storage &      _data;

   Color          _color = Color::On;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DisplayContext () = delete;
                  DisplayContext (const DisplayContext & rhs) = delete;
                  DisplayContext (DisplayContext && rhs) = delete;
   DisplayContext &
                  operator = (const DisplayContext & rhs) = delete;
   DisplayContext &
                  operator = (DisplayContext && rhs) = delete;
   bool           operator == (const DisplayContext & rhs) const = delete;
   bool           operator != (const DisplayContext & rhs) const = delete;



}; // class DisplayContext



}  // namespace erb



#include "erb/DisplayContext.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
