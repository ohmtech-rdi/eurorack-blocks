/*****************************************************************************

      calibrator.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "../%module.name%Ui.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy.h"
#include <stm32h750xx.h>
erb_RESTORE_WARNINGS


extern "C" void initialise_monitor_handles ();



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : main
==============================================================================
*/

int main ()
{
   if (CoreDebug->DHCSR & 0x01)
   {
      initialise_monitor_handles ();

      const char * line_0 = "Calibration started\n";
      write (STDOUT_FILENO, line_0, strlen (line_0));
   }

   // Enable FZ (flush-to-zero) denormal behavior
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);

   // Init system
   daisy::System system;
   daisy::System::Config config;
   config.Boost ();
   system.Init (config);

   // Init SDRAM
   SdramHandle sdram;
   sdram.Init ();

   // Init QSPI
   daisy::QSPIHandle qspi;

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

   //-------------------------------------------------------------------------

   %module.name%Ui module_ui;

   module_ui.board.deactivate_npr ();

   {
      module_ui.board.impl_preprocess ();

%     board_preprocess%
%     controls_preprocess%
      //module.process ();

%     controls_postprocess%
%     board_postprocess%
      module_ui.board.impl_postprocess ();
   }
}
