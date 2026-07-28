/*****************************************************************************

      Monitor.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include "erb/CycleCounter.h"
#include "erb/Profiler.h"
#include "erb/Rtt.h"
#include "erb/RttProtocol.h"

#include <cstddef>
#include <cstdint>



namespace erb
{



class Monitor
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static inline Monitor &
                  use ();

   void           init ();
   void           idle ();

   inline void    audio_enter ();
   inline void    audio_exit ();

   bool           register_command (std::uint32_t cmd, void * ctx, RttProtocol::CommandHandler handler);
   bool           register_stream (std::uint32_t cmd, void * ctx, RttProtocol::StreamHandler handler);

   template <typename... Args>
   inline void    printf (const char * format_0, Args... args);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  Monitor () = default;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   static void    command_load (void * ctx, std::span <const std::uint8_t> payload);
   static void    command_prof (void * ctx, std::span <const std::uint8_t> payload);

   // load meter, audio thread writes / idle thread reads whole words
   std::uint32_t  _enter_time = 0;
   std::uint32_t  _last_enter_time = 0;
   volatile std::uint32_t
                  _busy_max = 0;
   volatile std::uint32_t
                  _busy_sum = 0;
   volatile std::uint32_t
                  _period_sum = 0;
   volatile std::uint32_t
                  _block_count = 0;
   volatile std::uint32_t
                  _load_reset = 0;

   // prof: incremental dump state (paced so the up ring never overflows)
   bool           _prof_pending = false;
   std::size_t    _prof_dump_pos = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  Monitor (const Monitor & rhs) = delete;
                  Monitor (Monitor && rhs) = delete;
   Monitor &      operator = (const Monitor & rhs) = delete;
   Monitor &      operator = (Monitor && rhs) = delete;
};



}  // namespace erb



#include "erb/Monitor.hpp"

#endif   // erb_MONITOR && erb_TARGET_DAISY
