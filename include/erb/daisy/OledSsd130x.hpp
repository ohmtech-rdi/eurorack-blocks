/*****************************************************************************

      OledSsd130x.hpp
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

OledSsd130xTransport4WireSpi::OledSsd130xTransport4WireSpi (daisy::SpiHandle & spi, const dsy_gpio_pin & rst, const dsy_gpio_pin & dc)
:  _spi (spi)
,  _rst ({rst, DSY_GPIO_MODE_OUTPUT_PP})
,  _dc ({dc, DSY_GPIO_MODE_OUTPUT_PP})
{
   dsy_gpio_init (&_dc);
   dsy_gpio_init (&_rst);
}



/*
==============================================================================
Name : init
==============================================================================
*/

void  OledSsd130xTransport4WireSpi::init ()
{
   dsy_gpio_write (&_rst, 0);
   daisy::System::Delay (10);

   dsy_gpio_write (&_rst, 1);
   daisy::System::Delay (10);
}



/*
==============================================================================
Name : send_cmd
==============================================================================
*/

void  OledSsd130xTransport4WireSpi::send_cmd (uint8_t cmd)
{
   dsy_gpio_write (&_dc, 0);
   _spi.BlockingTransmit (&cmd, 1);
}



/*
==============================================================================
Name : send_data
==============================================================================
*/

void  OledSsd130xTransport4WireSpi::send_data (const uint8_t * ptr, size_t size)
{
   dsy_gpio_write (&_dc, 1);
   _spi.BlockingTransmit (const_cast <uint8_t *> (ptr), size);
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

template <size_t Width, size_t Height, typename Transport>
OledSsd130x <Width, Height, Transport>::OledSsd130x (Transport & transport, Buffer & buffer)
:  _transport (transport)
,  _buffer (buffer)
{
}



/*
==============================================================================
Name : init
==============================================================================
*/

template <size_t Width, size_t Height, typename Transport>
void  OledSsd130x <Width, Height, Transport>::init ()
{
   _transport.send_cmd (0xae);   // Turn off

   uint8_t clock_divide_ratio = 0;
   uint8_t multiplex_ratio = 0;
   uint8_t com_pins = 0;

   if constexpr (Height == 16)
   {
      clock_divide_ratio = 0x60;
      multiplex_ratio = 0x0f;
      com_pins = 0x02;
   }
   else if constexpr (Height == 32)
   {
      clock_divide_ratio = 0x80;
      multiplex_ratio = 0x1f;
      com_pins = (Width == 64) ? 0x12 : 0x02;
   }
   else if constexpr (Height == 48)
   {
      clock_divide_ratio = 0x80;
      multiplex_ratio = 0x2f;
      com_pins = 0x12;
   }
   else // 128
   {
      clock_divide_ratio = 0x80;
      multiplex_ratio = 0x3f;
      com_pins = 0x12;
   }

   _transport.send_cmd (0xd5);
   _transport.send_cmd (clock_divide_ratio);

   _transport.send_cmd (0xa8);
   _transport.send_cmd (multiplex_ratio);

   _transport.send_cmd (0xda);
   _transport.send_cmd (com_pins);

   _transport.send_cmd (0xd3);   // Offset
   _transport.send_cmd (0x00);

   _transport.send_cmd (0x40);   // Start line address
   _transport.send_cmd (0xa6);   // Normal display
   _transport.send_cmd (0xa4);   // All on resume

   _transport.send_cmd (0x8d);   // Charge pump
   _transport.send_cmd (0x14);

   _transport.send_cmd (0xa1);   // Set segment remap
   _transport.send_cmd (0xc8);   // COM output scan direction

   _transport.send_cmd (0x81);   // Contrast control
   _transport.send_cmd (0x8f);

   _transport.send_cmd (0xd9);   // Pre charge
   _transport.send_cmd (0x25);

   _transport.send_cmd (0xdb);   // VCOM detect
   _transport.send_cmd (0x34);

   _transport.send_cmd (0xaf);   // Turn on
}



/*
==============================================================================
Name : update
==============================================================================
*/

template <size_t Width, size_t Height, typename Transport>
void  OledSsd130x <Width, Height, Transport>::update ()
{
   const uint8_t high_column_addr = (Height == 32) ? 0x12 : 0x10;

   for (size_t i = 0 ; i < Height / 8 ; ++i)
   {
      _transport.send_cmd (0xb0 + uint8_t (i));
      _transport.send_cmd (0x00);
      _transport.send_cmd (high_column_addr);
      _transport.send_data (&_buffer [Width * i], Width);
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
