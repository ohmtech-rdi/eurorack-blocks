/*****************************************************************************

      TestDc.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestDc.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  TestDc::process ()
{
}



/*
==============================================================================
Name : idle
==============================================================================
*/

void  TestDc::idle ()
{
   ui.screen.fill (false);

   using Format = erb::FormatSsd130x <128, 64>;
   using Context = erb::DisplayContext <Format>;

   Format::Storage buf = {};
   Context ctx (buf);

   ctx.draw (10, 20, 30, 40);

   ctx.set (Context::Color::Off);
   ctx.draw (15, 25, 5, 5);

   ctx.set (Context::Color::Invert);
   ctx.draw (30, 40, 20, 20);

   ctx.set (Context::Color::On);
   ctx.draw (0, 0, TestDcData::pic, 8, 8);

   ctx.set (Context::Color::Off);
   ctx.draw (20, 25, TestDcData::pic, 8, 8);

   ctx.set (Context::Color::Invert);
   ctx.draw (36, 20, TestDcData::pic, 8, 8);

   ctx.set (Context::Color::On);
   ctx.draw (0, 8, TestDcData::font, 384, 8);

   ctx.draw (4, 16, TestDcData::font, 384, 8, 'A');

   ctx.draw (60, 16, TestDcData::font, 384, 8, "HELLO,WORLD!");

   ctx.set (Context::Color::Invert);
   ctx.draw (0, 32, TestDcData::font, 384, 8, "HELLO,WORLD!");

   ui.screen = ctx;
}
