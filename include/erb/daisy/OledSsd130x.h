/*****************************************************************************

      OledSsd130x.h
      Copyright (c) 2020 Raphael DINGE

      This is a copy of dev/oled_ssd130x because it doesn't
      allow to access internal buffer directly.

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

#include <array>
#include <cstddef>



namespace erb
{



template <size_t Width, size_t Height, typename Transport>
class OledSsd130x
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using Buffer = std::array <std::uint8_t, width * height / 8>;

                  OledSsd130x (Transport & transport, Buffer & buffer);
   virtual        ~OledSsd130x () = default;

   void           init ();
   void           update ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Transport &    _transport;
   Buffer &       _buffer;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  OledSsd130x (const OledSsd130x & rhs) = delete;
                  OledSsd130x (OledSsd130x && rhs) = delete;
   OledSsd130x &  operator = (const OledSsd130x & rhs) = delete;
   OledSsd130x &  operator = (OledSsd130x && rhs) = delete;
   bool           operator == (const OledSsd130x & rhs) const = delete;
   bool           operator != (const OledSsd130x & rhs) const = delete;



}; // class OledSsd130x



}  // namespace erb



#include "erb/daisy/OledSsd130x.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
