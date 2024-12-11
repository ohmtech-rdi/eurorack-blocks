/*****************************************************************************

      Seed2DfmEvalEuro.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Seed2DfmEvalEuro.h"

#include <cmath>



/*
==============================================================================
Name : init
==============================================================================
*/

void  Seed2DfmEvalEuro::init ()
{
#if 0
   // Interactive test to check basic SDMMC firmware support
   #define erb_FATAL_IF(cond) if (cond) do { for (;;) {} } while (false)

   auto status = ui.sdmmc.mount ("/", erb::SdMmc::MountOption::Immediate);
   erb_FATAL_IF (status != erb::SdMmc::Status::OK);

   // Since this involves DMA transfers, the structures need to be stored
   // in AXI SRAM.
   static __attribute__((section(".text"))) erb::SdMmc::File file;

   status = file.open ("/test.txt", "w");
   erb_FATAL_IF (status != erb::SdMmc::Status::OK);

   std::size_t size = 4;
   status = file.write ("joy!", size);
   erb_FATAL_IF (status != erb::SdMmc::Status::OK);
   erb_FATAL_IF (size != 4);

   status = file.close ();
   erb_FATAL_IF (status != erb::SdMmc::Status::OK);

   status = file.open ("/test.txt", "r");
   erb_FATAL_IF (status != erb::SdMmc::Status::OK);

   size = 4;
   char buf_0 [4];
   status = file.read (buf_0, size);
   erb_FATAL_IF (status != erb::SdMmc::Status::OK);
   erb_FATAL_IF (size != 4);
   erb_FATAL_IF (strncmp (buf_0, "joy!", 4) != 0);

   #undef erb_FATAL_IF
#endif

}



/*
==============================================================================
Name : process
==============================================================================
*/

void  Seed2DfmEvalEuro::process ()
{
   const auto to_freq = [](float norm){
      return 20.f * std::pow (500.f, std::abs (norm));
   };

   const auto to_shape = [](erb::SwitchPosition pos, float x){
      switch (pos)
      {
      case erb::SwitchPosition::First:
      default:
         return x;
      case erb::SwitchPosition::Center:
         return x * x * x;
      case erb::SwitchPosition::Last:
         return x > 0 ? 1.f : 0.f;
      }
   };

   osc1.set (to_freq (std::clamp (ui.osc1_pot + ui.osc1_cv, 0.f, 1.f)));
   osc2.set (to_freq (std::clamp (ui.osc2_pot + ui.osc2_cv, 0.f, 1.f)));
   osc3.set (to_freq (std::clamp (ui.osc3_pot + ui.osc3_cv, 0.f, 1.f)));
   osc4.set (to_freq (std::clamp (float (ui.osc4_pot), 0.f, 1.f)));

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.osc1_out [i]
         = (ui.osc1_in [i] + osc1 ())
         * ((ui.osc1_but.held () || ui.osc1_gate) ? 1.f : 0.f);

      ui.osc2_out [i] = ui.osc2_in [i] + osc2 ();
      ui.osc3_out [i] = ui.osc3_in [i] + osc3 ();
      ui.osc4_out [i] = to_shape (ui.osc4_shape, ui.osc4_in [i] + osc4 ());
   }

   ui.osc1_cv_out = ui.osc1_cv;
   ui.osc2_cv_out = ui.osc2_cv;

   if (ui.enc.button.held ())
   {
      pic = 4;
   }
   else
   {
      pic = (pic + int (ui.enc.encoder) + 4) % 4;
   }
}



/*
==============================================================================
Name : idle
==============================================================================
*/

void  Seed2DfmEvalEuro::idle ()
{
   using Format = erb::FormatSsd130x <128, 64>;
   using Context = erb::DisplayContext <Format>;

   Format::Storage buf = {};
   Context ctx (buf);

   ctx.set (Context::Color::Off);
   ctx.fill ();
   ctx.set (Context::Color::On);

   switch (pic)
   {
   case 0: ctx.draw (0, 0, Seed2DfmEvalEuroData::pic0, 128, 64); break;
   case 1: ctx.draw (0, 0, Seed2DfmEvalEuroData::pic1, 128, 64); break;
   case 2: ctx.draw (0, 0, Seed2DfmEvalEuroData::pic2, 128, 64); break;
   case 3: ctx.draw (0, 0, Seed2DfmEvalEuroData::pic3, 128, 64); break;
   case 4: ctx.fill (); break;
   }

   if (!mounted)
   {
      auto status = ui.sdmmc.mount ("/", erb::SdMmc::MountOption::Immediate);
      if (status == erb::SdMmc::Status::OK)
      {
         mounted = true;
      }
   }

   if (mounted)
   {
      static erb::SdMmc::Directory directory;
      auto status = directory.open ("/");
      if (status == erb::SdMmc::Status::OK)
      {
         int y = 0;
         for (int i = 0 ; i < 5 ; ++i)
         {
            erb::SdMmc::Directory::FileInfo file_info;
            status = directory.read (file_info);

            if (file_info.name_0 [0] == '\0') break;

            int x = 0;
            for (std::size_t j = 0 ; j < 256 ; ++j)
            {
               char c = file_info.name_0 [j];
               if (c == '\0') break;
               ctx.draw (x, y, Seed2DfmEvalEuroData::font, 256, 8, std::toupper (c));
               x += 256 / 64;
            }
            y += 8;
         }
      }
   }

   ui.screen = ctx;
}
