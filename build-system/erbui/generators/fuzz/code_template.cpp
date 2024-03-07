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
#include <cmath>

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
Name : check_cpu_usage
==============================================================================
*/

void  check_cpu_usage (std::uint32_t ts_diff)
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

   if (usage > 0.98f)
   {
      Logger::PrintLine ("Realtime constraint failed");
      asm ("bkpt 255");
   }
}



/*
==============================================================================
Name : check_audio_buffer
==============================================================================
*/

void  check_audio_buffer (const erb::Buffer & buf)
{
   for (std::size_t i = 0 ; i < buf.size () ; ++i)
   {
      if (std::isnan (buf [i]))
      {
         Logger::PrintLine ("Audio buffer contains NaN");
         asm ("bkpt 255");
      }
   }
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

   %module.name% module;

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

   struct Osc {
      void  set (float freq_norm) {
         const double phase_step = double (freq_norm) * 2.0 * std::numbers::pi;
         _step_cos = float (std::cos (phase_step));
         _step_sin = float (std::sin (phase_step));
      }
      void  process () {
         const float old_cos = _pos_cos;
         const float old_sin = _pos_sin;
         _pos_cos = old_cos * _step_cos - old_sin * _step_sin;
         _pos_sin = old_cos * _step_sin + old_sin * _step_cos;

         const float norm_sq = _pos_cos * _pos_cos + _pos_sin * _pos_sin;
         const float mult = 1.f / std::sqrt (norm_sq);

         _pos_cos *= mult;
         _pos_sin *= mult;
      }

      operator float () { return _pos_cos; }

      float _pos_cos = 1.f;
      float _pos_sin = 0.f;
      float _step_cos = 1.f;
      float _step_sin = 0.f;
   };

   struct Vco {
      Vco (float freq, float freq_mod) {
         const float freq_norm = freq / float (erb_SAMPLE_RATE);
         const float freq_mod_norm = freq_mod / float (erb_SAMPLE_RATE);
         _freq_norm = freq_norm;
         _osc2.set (freq_mod_norm);
      }
      void  process () {
         for (std::size_t i = 0 ; i < _buf.size () ; ++i)
         {
            _osc1.set (_freq_norm + _osc2 * _freq_norm);
            _osc1.process ();
            _osc2.process ();
            _buf [i] = _osc1;
         }
      }

      operator erb::Buffer () { return _buf; };

      Osc   _osc1;
      Osc   _osc2;
      float _freq_norm;
      erb::Buffer _buf;
   };

   struct Lfo {
      Lfo (float freq, float freq_mod) {
         const float freq_norm = freq / float (erb_SAMPLE_RATE / erb_BUFFER_SIZE);
         const float freq_mod_norm = freq_mod / float (erb_SAMPLE_RATE / erb_BUFFER_SIZE);
         _freq_norm = freq_norm;
         _osc2.set (freq_mod_norm);
      }
      void  process () {
         _osc1.set (_freq_norm + _osc2 * _freq_norm);
         _osc1.process ();
         _osc2.process ();
      }

      operator float () { return (1.f + _osc1) * 0.5f; }

      Osc   _osc1;
      Osc   _osc2;
      float _freq_norm;
   };

   struct Context {
%     controls_context_decl%
      std::atomic <std::uint32_t> execution_duration = 0;
   };

   static Context context;

   module.ui.board.run ([&module](){
      using BoardType = decltype (module.ui.board);

%     controls_context_process%

      const auto tsl_beg = daisy::System::GetTick ();

      module.ui.board.impl_preprocess ();

%     board_preprocess%
%     controls_instrument%
%     controls_preprocess%

      module.process ();

%     controls_postprocess%
%     board_postprocess%
      module.ui.board.impl_postprocess ();

      const auto tsl_end = daisy::System::GetTick ();

%     controls_check_audio%

      context.execution_duration
         = std::max (context.execution_duration.load (), tsl_end - tsl_beg);
   });

   const auto tick_freq = daisy::System::GetTickFreq ();

   for (;;)
   {
      auto ts_beg = daisy::System::GetTick ();

      erb::module_idle (module);
      module.ui.board.impl_idle ();

      // busy wait so that the idle loop is at least 6ms
      while (daisy::System::GetTick () - ts_beg < tick_freq * 6 / 1000) {}

      check_cpu_usage (context.execution_duration);
   }
}
