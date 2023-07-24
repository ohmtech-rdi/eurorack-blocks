/*****************************************************************************

      main.cpp
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

using Logger = daisy::Logger <daisy::LOGGER_INTERNAL>; // USB on DaisyPatch SM



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

   std::size_t cnt = 0;

   std::uint32_t preprocess = 0;
   std::uint32_t process = 0;
   std::uint32_t postprocess = 0;
   std::uint32_t total = 0;

   constexpr size_t MaxNbrChannels = 4;
   std::array <std::array <float, erb_BUFFER_SIZE>, MaxNbrChannels> input_arr;
   std::array <std::array <float, erb_BUFFER_SIZE>, MaxNbrChannels> output_arr;
   std::array <const float *, MaxNbrChannels> inputs;
   std::array <float *, MaxNbrChannels> outputs;

   for (size_t c = 0 ; c < MaxNbrChannels ; ++c)
   {
      inputs [c] = &input_arr [c][0];
      outputs [c] = &output_arr [c][0];
   }

   module.ui.board.submodule ().raw_audio_inputs = &inputs [0];
   module.ui.board.submodule ().raw_audio_outputs = &outputs [0];

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      float x = (i < erb_BUFFER_SIZE / 2) ? -1.f : 1.f;

      for (size_t c = 0 ; c < MaxNbrChannels ; ++c)
      {
         input_arr [c][i] = x;
      }
   }

   module.ui.board.submodule ().adc ().Start ();

   while (true)
   {
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

      module.ui.board.submodule ().clock_tick ();

      const auto tsl_4 = daisy::System::GetTick ();

      preprocess = std::max (preprocess, tsl_2 - tsl_1);
      process = std::max (process, tsl_3 - tsl_2);
      postprocess = std::max (postprocess, tsl_4 - tsl_3);
      total = std::max (total, tsl_4 - tsl_1);

      ++cnt;

      if (cnt >= 1000)
      {
         cnt = 0;

         print_cpu_usage ("ERB preprocess: ", preprocess);
         print_cpu_usage ("%module.name% process: ", process);
         print_cpu_usage ("ERB postprocess: ", postprocess);
         print_cpu_usage ("Total: ", total);
         Logger::PrintLine ("");

         preprocess = 0;
         process = 0;
         postprocess = 0;
         total = 0;
      }
   }
}
