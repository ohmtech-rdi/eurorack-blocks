/*****************************************************************************

      Monitor.hpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*
==============================================================================
Name : use
==============================================================================
*/

Monitor &   Monitor::use ()
{
   static Monitor instance;
   return instance;
}



/*
==============================================================================
Name : audio_enter
==============================================================================
*/

void  Monitor::audio_enter ()
{
   const auto now = CycleCounter::now ();

   if (_load_reset != 0)
   {
      _busy_max = 0;
      _busy_sum = 0;
      _period_sum = 0;
      _block_count = 0;
      _load_reset = 0;
   }
   else if (_last_enter_time != 0)
   {
      _period_sum = _period_sum + (now - _last_enter_time);
   }

   _last_enter_time = now;
   _enter_time = now;

   RttProtocol::use ().isr_pump ();
}



/*
==============================================================================
Name : audio_exit
==============================================================================
*/

void  Monitor::audio_exit ()
{
   const auto busy = CycleCounter::now () - _enter_time;

   if (busy > _busy_max) _busy_max = busy;
   _busy_sum = _busy_sum + busy;
   _block_count = _block_count + 1;

   Profiler::use ().block_tick ();
}



/*
==============================================================================
Name : printf
==============================================================================
*/

template <typename... Args>
void  Monitor::printf (const char * format_0, Args... args)
{
   Rtt::use ().printf (format_0, args...);
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
