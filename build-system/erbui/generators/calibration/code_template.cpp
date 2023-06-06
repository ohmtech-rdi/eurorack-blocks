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


struct CalibrationData
{
   struct CvIn
   {
      float mul;
      float offset;
   };

   std::array <CvIn, 256> cv_ins;
};



/*
==============================================================================
Name : sample_cv_in
==============================================================================
*/

template <typename CvInType>
float sample_cv_in (%module.name%Ui & module_ui, CvInType & cv_in)
{
   using BoardType = decltype (module_ui.board);

   const size_t nbr_loop = 100;
   double avg = 0.0;

   for (size_t i = 0 ; i < nbr_loop ; ++i)
   {
      module_ui.board.impl_preprocess ();

%     board_preprocess%
      avg += double (cv_in.impl_data);

      module_ui.board.impl_postprocess ();

      daisy::System::Delay (1);
   }

   return float (avg / double (nbr_loop));
}



/*
==============================================================================
Name : calibrate
==============================================================================
*/

template <typename CvInType>
CalibrationData::CvIn   calibrate (%module.name%Ui & module_ui, CvInType & cv_in, const char * control_name_0, const char * pin_name_0)
{
   char line_0 [256];
   sprintf (line_0, "Unplug %s (%s), press enter to continue\n", control_name_0, pin_name_0);
   scanf ("%s", line_0);

   float ideal = 0.5f;
   auto sampled = sample_cv_in (module_ui, cv_in);
   auto diff = ideal - sampled;

   sprintf (line_0, "   0V: diff=%f\n", diff);

   write (STDOUT_FILENO, line_0, strlen (line_0));

   return { .mul = 0.f, .offset = diff };
}



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

   module_ui.board.impl_deactivate_npr ();

   CalibrationData data;

%  controls_calibrate%

   const uint32_t address_offset = 0;
   qspi.Erase (address_offset, address_offset + sizeof (data));
   qspi.Write (address_offset, sizeof (data), reinterpret_cast <uint8_t *> (&data));
}
