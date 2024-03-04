/*****************************************************************************

      main.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%.h"

#include "erb/module_fnc.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy.h"
#include <stm32h750xx.h>
erb_RESTORE_WARNINGS

#include <atomic>

#if defined (erb_SEMIHOSTING)
extern "C" void initialise_monitor_handles ();
#endif



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_SEMIHOSTING)
using Logger = daisy::Logger <daisy::LOGGER_SEMIHOST>;
#else
using Logger = daisy::Logger <daisy::LOGGER_INTERNAL>; // USB on DaisyPatch SM
#endif



/*
==============================================================================
Name : print_elapsed_time
==============================================================================
*/

void  print_elapsed_time (const char * prefix_0, std::uint32_t ts_beg, std::uint32_t ts_end)
{
#if defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wnarrowing"
#endif

   const auto duration_s = float {ts_end - ts_beg} / float (daisy::System::GetTickFreq ());

#if defined (__GNUC__)
   #pragma GCC diagnostic pop
#endif

   if (duration_s > 1.f)
   {
      Logger::PrintLine ("%s%ds", prefix_0, int (duration_s));
   }
   else if (duration_s * 1.e3f > 1.f)
   {
      Logger::PrintLine ("%s%dms", prefix_0, int (duration_s * 1.e3f));
   }
   else if (duration_s * 1.e6f > 1.f)
   {
      Logger::PrintLine ("%s%dus", prefix_0, int (duration_s * 1.e6f));
   }
   else
   {
      Logger::PrintLine ("%s%dns", prefix_0, int (duration_s * 1.e9f));
   }
}



/*
==============================================================================
Name : print_cpu_usage
==============================================================================
*/

void  print_cpu_usage (const char * prefix_0, std::uint32_t ts_diff)
{
#if defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wnarrowing"
#endif

   const auto usage
      = float {ts_diff}
      / (float (daisy::System::GetTickFreq ()) * float (erb_BUFFER_SIZE) / float (erb_SAMPLE_RATE));

#if defined (__GNUC__)
   #pragma GCC diagnostic pop
#endif

   Logger::PrintLine ("%s%d%%", prefix_0, int (usage * 100));
}



/*
==============================================================================
Name : main
==============================================================================
*/

int main ()
{
#if defined (erb_SEMIHOSTING)
   if (CoreDebug->DHCSR & 0x01)
   {
      initialise_monitor_handles ();
   }
#endif

   // Enable FZ (flush-to-zero) denormal behavior
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);

   // Init system
   daisy::System system;
   daisy::System::Config config;
   config.Boost ();

   auto program_memory_section = daisy::System::GetProgramMemoryRegion ();
   auto boot_version = daisy::System::GetBootloaderVersion ();

   // When using the bootloader prior to v6, clocks have been already configured

   if (
      (boot_version == daisy::System::BootInfo::Version::LT_v6_0)
      && (program_memory_section != daisy::System::MemoryRegion::INTERNAL_FLASH)
      )
   {
      config.skip_clocks = true;
   }

   system.Init (config);

#if (erb_SDRAM_USE_FLAG)
   // Init SDRAM
   // When using the bootloader priori to v6, SDRAM has been already configured

   if (
      (boot_version != daisy::System::BootInfo::Version::LT_v6_0)
      || (
         (boot_version == daisy::System::BootInfo::Version::LT_v6_0)
         && (program_memory_section == daisy::System::MemoryRegion::INTERNAL_FLASH)
         )
      )
   {
      SdramHandle sdram;
      sdram.Init ();
   }
#endif

   Logger::StartLog (true /* wait for PC */);

   //-------------------------------------------------------------------------

   const auto ts_1 = daisy::System::GetTick ();

   %module.name% module;

   const auto ts_2 = daisy::System::GetTick ();

   // The Daisy Seed stack, sitting on SRAM is 512K only.
   // When more memory is needed, move the big buffers like
   // delay lines or samples to the SDRAM, which is 64M.
   // Since we have some heap allocations, we keep a bit of margin
   // and complain when we reach 128K of stack space.

   static_assert (sizeof (module) < 128 * 1024 /* 128 */, "");

   // The SDRAM is compararively slow compared to the SRAM,
   // So try to keep all memory that is accessed often in SRAM.

   // Check 'erb::make_sdram_object' to put your buffers in
   // SDRAM.

   erb::module_init (module);

   const auto ts_3 = daisy::System::GetTick ();

   print_elapsed_time ("%module.name% ctor: ", ts_1, ts_2);
   print_elapsed_time ("%module.name% init: ", ts_2, ts_3);
   Logger::PrintLine ("");

   struct Timings {
      std::atomic <std::uint32_t> preprocess = 0;
      std::atomic <std::uint32_t> process = 0;
      std::atomic <std::uint32_t> postprocess = 0;
      std::atomic <std::uint32_t> total = 0;
   };

   static Timings timings;

   module.ui.board.run ([&module](){
      using BoardType = decltype (module.ui.board);

      const auto tsl_1 = daisy::System::GetTick ();

      module.ui.board.impl_preprocess ();

%     board_preprocess%
%     controls_preprocess%

      const auto tsl_2 = daisy::System::GetTick ();

      module.process ();

      const auto tsl_3 = daisy::System::GetTick ();

%     controls_postprocess%
%     board_postprocess%
      module.ui.board.impl_postprocess ();

      const auto tsl_4 = daisy::System::GetTick ();

      timings.preprocess = std::max (timings.preprocess.load (), tsl_2 - tsl_1);
      timings.process = std::max (timings.process.load (), tsl_3 - tsl_2);
      timings.postprocess = std::max (timings.postprocess.load (), tsl_4 - tsl_3);
      timings.total = std::max (timings.total.load (), tsl_4 - tsl_1);
   });

   const auto tick_freq = daisy::System::GetTickFreq ();

   std::size_t cnt = 0;

   for (;;)
   {
      auto ts_beg = daisy::System::GetTick ();

      erb::module_idle (module);
      module.ui.board.impl_idle ();

      // busy wait so that the idle loop is at least 6ms
      while (daisy::System::GetTick () - ts_beg < tick_freq * 6 / 1000) {}

      ++cnt;
      if (cnt >= 166) // around 1s
      {
         cnt = 0;

         print_cpu_usage ("ERB preprocess: ", timings.preprocess);
         print_cpu_usage ("%module.name% process: ", timings.process);
         print_cpu_usage ("ERB postprocess: ", timings.postprocess);
         print_cpu_usage ("Total: ", timings.total);
         Logger::PrintLine ("");

         timings.preprocess = 0;
         timings.process = 0;
         timings.postprocess = 0;
         timings.total = 0;
      }
   }
}
