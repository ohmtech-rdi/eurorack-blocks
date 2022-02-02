/*****************************************************************************

      main_daisy.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%.h"

#include "erb/module_init.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy.h"
erb_RESTORE_WARNINGS



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : main
==============================================================================
*/

int main ()
{
   // Enable FZ (flush-to-zero) denormal behavior
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);

   // Init system
   daisy::System system;
   daisy::System::Config config;
   config.Boost ();

   auto program_memory_section = daisy::System::GetProgramMemoryRegion ();

   // When using the bootloader, clocks have been already configured
   if (program_memory_section != daisy::System::MemoryRegion::INTERNAL_FLASH)
   {
      config.skip_clocks = true;
   }

   system.Init (config);

   // Init SDRAM

   // When using the bootloader, SDRAM has been already configured
   if (program_memory_section == daisy::System::MemoryRegion::INTERNAL_FLASH)
   {
      SdramHandle sdram;
      sdram.Init ();
   }

   // Init QSPI
   daisy::QSPIHandle qspi;

   // When using QSPI for program, QSPI has already been configured
   if (program_memory_section != daisy::System::MemoryRegion::QSPI)
   {
      qspi.Init (daisy::QSPIHandle::Config {
         .pin_config = {
            .io0 = {DSY_GPIOF, 8},
            .io1 = {DSY_GPIOF, 9},
            .io2 = {DSY_GPIOF, 7},
            .io3 = {DSY_GPIOF, 6},
            .clk = {DSY_GPIOF, 10},
            .ncs = {DSY_GPIOG, 6}
         },
         .device = daisy::QSPIHandle::Config::Device::IS25LP064A,
         .mode = daisy::QSPIHandle::Config::Mode::MEMORY_MAPPED
      });
   }

   //-------------------------------------------------------------------------

   %module.name% module;

   // The Daisy Seed stack, sitting on SRAM is 512K only.
   // When more memory is needed, move the big buffers like
   // delay lines or samples to the SDRAM, which is 64M.
   // Since we have some heap allocations, we keep a bit of margin
   // and complain when we reach 384K of stack space.

   static_assert (sizeof (module) < 384 * 1024 /* 384K */, "");

   // The SDRAM is compararively slow compared to the SRAM,
   // So try to keep all memory that is accessed often in SRAM.

   // Check 'erb::make_sdram_object' to put your buffers in
   // SDRAM.

   erb::module_init (module);

   module.ui.board.run ([&](){
      using BoardType = decltype (module.ui.board);

      module.ui.board.impl_preprocess ();

%     board_preprocess%
%     controls_preprocess%
      module.process ();

%     controls_postprocess%
%     board_postprocess%
      module.ui.board.impl_postprocess ();
   });
}
