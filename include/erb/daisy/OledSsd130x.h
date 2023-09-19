/*****************************************************************************

      OledSsd130x.h
      Copyright (c) 2020 Raphael DINGE

      This is a copy of dev/oled_ssd130x because it doesn't
      allow to access internal buffer directly.

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "per/spi.h"
#include "dev/oled_ssd130x.h"
erb_RESTORE_WARNINGS

#include <array>
#include <cstddef>
#include <cstdint>



namespace erb
{




class OledSsd130xTransport4WireSpi
{
public:
   using Pin = dsy_gpio_pin;

   inline         OledSsd130xTransport4WireSpi (daisy::SpiHandle & spi, const dsy_gpio_pin & rst, const dsy_gpio_pin & dc);

   inline void    init ();
   inline void    send_cmd (uint8_t cmd);
   inline void    send_data (const uint8_t * ptr, size_t size);

private:
   daisy::SpiHandle
                  _spi;

   dsy_gpio       _rst;
   dsy_gpio       _dc;
};



template <size_t Width, size_t Height, typename Transport>
class OledSsd130x
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using Buffer = std::array <uint8_t, Width * Height / 8>;

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
