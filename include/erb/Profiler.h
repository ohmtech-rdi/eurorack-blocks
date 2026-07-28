/*****************************************************************************

      Profiler.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include "erb/CycleCounter.h"

#include <atomic>

#include <cstddef>
#include <cstdint>



namespace erb
{



class Profiler
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr std::size_t MaxNbrNodes = 1024;
   static constexpr std::size_t MaxNbrProbes = 8;

   static inline Profiler &
                  use ();

   // registration, at structure discovery time (not audio)
   void           reset_nodes ();
   std::size_t    register_node (const char label_0 [5]);
   std::size_t    register_node (const char label_0 [5], std::size_t parent);
   std::size_t    register_node (std::uint32_t label);
   std::size_t    register_node (std::uint32_t label, std::size_t parent);

   // out-of-order registration
   std::size_t    reserve_nodes (std::size_t count);
   void           set_node (std::size_t node, std::uint32_t label);
   void           set_node (std::size_t node, std::uint32_t label, std::size_t parent);

   std::size_t    nbr_nodes () const;
   bool           truncated () const;

   // window
   bool           start (std::uint32_t nbr_blocks);
   void           block_tick ();   // audio thread, once per block
   inline bool    window_running () const;

   // measure (audio thread)
   inline void    add (std::size_t node, std::uint32_t cycles);
   inline void    probe_add (std::size_t probe, std::uint32_t cycles);

   // dump access (idle thread, window not running)
   std::uint32_t  node_label (std::size_t node) const;
   std::ptrdiff_t node_parent (std::size_t node) const;
   std::uint32_t  node_cycles (std::size_t node) const;
   std::uint32_t  probe_cycles (std::size_t probe) const;
   std::uint32_t  probe_count (std::size_t probe) const;
   std::uint32_t  blocks_done () const;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  Profiler () = default;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   static std::uint32_t
                  to_label (const char str_0 [5]);

   std::size_t    register_node_any (std::uint32_t label, std::int32_t parent);

   std::atomic <bool>
                  _running = false;
   std::uint32_t  _blocks_left = 0;
   std::uint32_t  _blocks_done = 0;

   std::size_t    _nbr_nodes = 0;
   bool           _truncated = false;

   std::uint32_t  _labels [MaxNbrNodes] = {};
   std::int32_t   _parents [MaxNbrNodes] = {};
   std::uint32_t  _cycles [MaxNbrNodes] = {};

   std::uint32_t  _probe_cycles [MaxNbrProbes] = {};
   std::uint32_t  _probe_counts [MaxNbrProbes] = {};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  Profiler (const Profiler & rhs) = delete;
                  Profiler (Profiler && rhs) = delete;
   Profiler &     operator = (const Profiler & rhs) = delete;
   Profiler &     operator = (Profiler && rhs) = delete;
};



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

// RAII backing for erb_PROFILER_SCOPE and erb_PROFILER_SCOPE_PROBE

class ScopedTimer
{
public:
   inline         ScopedTimer (std::size_t node);
   inline         ~ScopedTimer ();

private:
   const std::size_t
                  _node;
   const std::uint32_t
                  _t0;

                  ScopedTimer (const ScopedTimer & rhs) = delete;
   ScopedTimer &
                  operator = (const ScopedTimer & rhs) = delete;
};



class ScopedTimerProbe
{
public:
   inline         ScopedTimerProbe (std::size_t probe);
   inline         ~ScopedTimerProbe ();

private:
   const std::size_t
                  _probe;
   const std::uint32_t
                  _t0;

                  ScopedTimerProbe (const ScopedTimerProbe & rhs) = delete;
   ScopedTimerProbe &
                  operator = (const ScopedTimerProbe & rhs) = delete;
};



}  // namespace erb



#include "erb/Profiler.hpp"

#endif   // erb_MONITOR && erb_TARGET_DAISY



/*\\\ MACROS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#define erb_PROFILER_CONCAT_IMPL(a, b) a ## b
#define erb_PROFILER_CONCAT(a, b) erb_PROFILER_CONCAT_IMPL (a, b)
#define erb_PROFILER_EXPAND(x) x
#define erb_PROFILER_SELECT(_1, _2, _3, name, ...) name

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#define erb_PROFILER_REGISTER_2(label, node) \
   node = erb::Profiler::use ().register_node (label)

#define erb_PROFILER_REGISTER_3(label, node, parent) \
   node = erb::Profiler::use ().register_node (label, parent)

#define erb_PROFILER_REGISTER(...) \
   erb_PROFILER_EXPAND (erb_PROFILER_SELECT (__VA_ARGS__, erb_PROFILER_REGISTER_3, erb_PROFILER_REGISTER_2) (__VA_ARGS__))

#define erb_PROFILER_SCOPE(node) \
   const erb::ScopedTimer erb_PROFILER_CONCAT (erb_profiler_scope_, __LINE__) (node)

#define erb_PROFILER_SCOPE_PROBE(slot) \
   const erb::ScopedTimerProbe erb_PROFILER_CONCAT (erb_profiler_scope_probe_, __LINE__) (slot)

#else

#define erb_PROFILER_REGISTER(...)
#define erb_PROFILER_SCOPE(node)
#define erb_PROFILER_SCOPE_PROBE(slot)

#endif   // erb_MONITOR && erb_TARGET_DAISY
