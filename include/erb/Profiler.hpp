/*****************************************************************************

      Profiler.hpp
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

Profiler &  Profiler::use ()
{
   static Profiler instance;
   return instance;
}



/*
==============================================================================
Name : window_running
   Only needed to skip instrumentation more expensive than the two
   CycleCounter reads around the measured section: `add` and `probe_add`
   check it themselves.
==============================================================================
*/

bool  Profiler::window_running () const
{
   return _running.load (std::memory_order_relaxed);
}



/*
==============================================================================
Name : add
Note :
   Self-guarded: cycles added after a window completes but before the dump
   is collected must not inflate the results.
==============================================================================
*/

void  Profiler::add (std::size_t node, std::uint32_t cycles)
{
   if (window_running () && (node < MaxNbrNodes))
   {
      _cycles [node] += cycles;
   }
}



/*
==============================================================================
Name : probe_add
==============================================================================
*/

void  Profiler::probe_add (std::size_t probe, std::uint32_t cycles)
{
   if (window_running () && (probe < MaxNbrProbes))
   {
      _probe_cycles [probe] += cycles;
      _probe_counts [probe] += 1;
   }
}



/*
==============================================================================
Name : ScopedTimer::ctor
==============================================================================
*/

ScopedTimer::ScopedTimer (std::size_t node)
:  _node (node)
,  _t0 (CycleCounter::now ())
{
}



/*
==============================================================================
Name : ScopedTimer::dtor
==============================================================================
*/

ScopedTimer::~ScopedTimer ()
{
   Profiler::use ().add (_node, CycleCounter::now () - _t0);
}



/*
==============================================================================
Name : ScopedTimerProbe::ctor
==============================================================================
*/

ScopedTimerProbe::ScopedTimerProbe (std::size_t probe)
:  _probe (probe)
,  _t0 (CycleCounter::now ())
{
}



/*
==============================================================================
Name : ScopedTimerProbe::dtor
==============================================================================
*/

ScopedTimerProbe::~ScopedTimerProbe ()
{
   Profiler::use ().probe_add (_probe, CycleCounter::now () - _t0);
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
