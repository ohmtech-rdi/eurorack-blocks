/*****************************************************************************

      Profiler.cpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Profiler.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include <cstring>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

namespace erb
{



/*
==============================================================================
Name : reset_nodes
Note :
   For structures rebuilt at runtime: clears the table before the
   application re-registers.
==============================================================================
*/

void  Profiler::reset_nodes ()
{
   _nbr_nodes = 0;
   _truncated = false;
}



/*
==============================================================================
Name : register_node
Note :
   Registers a root node. Returns the node index, starting at 0 and
   incremented with each registration; `add` identifies the node with it.
   Labels are 4-character display tags for the host tree, free to repeat.
==============================================================================
*/

std::size_t Profiler::register_node (const char label_0 [5])
{
   // -1 is no parent
   return register_node_any (to_label (label_0), -1);
}



/*
==============================================================================
Name : register_node
==============================================================================
*/

std::size_t Profiler::register_node (const char label_0 [5], std::size_t parent)
{
   return register_node_any (to_label (label_0), std::int32_t (parent));
}



/*
==============================================================================
Name : register_node
   Same, with an already-packed label, eg. straight from a parsed stream.
==============================================================================
*/

std::size_t Profiler::register_node (std::uint32_t label)
{
   return register_node_any (label, -1);
}



/*
==============================================================================
Name : register_node
==============================================================================
*/

std::size_t Profiler::register_node (std::uint32_t label, std::size_t parent)
{
   return register_node_any (label, std::int32_t (parent));
}



/*
==============================================================================
Name : reserve_nodes
Note :
   For parsers that know a group size before its members:
   reserve a contiguous index range, fill it as discovered.
   Returns the base index of the range, or MaxNbrNodes when the table
   cannot hold it ('set_node' and 'add' ignore out-of-range indices,
   'truncated' reports the overflow).
==============================================================================
*/

std::size_t Profiler::reserve_nodes (std::size_t count)
{
   if (_nbr_nodes + count > MaxNbrNodes)
   {
      _truncated = true;
      return MaxNbrNodes;
   }

   const auto base = _nbr_nodes;
   _nbr_nodes += count;

   for (std::size_t node = base ; node < base + count ; ++node)
   {
      _labels [node] = 0;
      _parents [node] = -1;
   }

   return base;
}



/*
==============================================================================
Name : set_node
==============================================================================
*/

void  Profiler::set_node (std::size_t node, std::uint32_t label)
{
   if (node >= _nbr_nodes) return;

   _labels [node] = label;
   _parents [node] = -1;
}



/*
==============================================================================
Name : set_node
==============================================================================
*/

void  Profiler::set_node (std::size_t node, std::uint32_t label, std::size_t parent)
{
   if (node >= _nbr_nodes) return;

   _labels [node] = label;
   _parents [node] = std::int32_t (parent);
}



/*
==============================================================================
Name : nbr_nodes
==============================================================================
*/

std::size_t Profiler::nbr_nodes () const
{
   return _nbr_nodes;
}



/*
==============================================================================
Name : truncated
==============================================================================
*/

bool  Profiler::truncated () const
{
   return _truncated;
}



/*
==============================================================================
Name : start
==============================================================================
*/

bool  Profiler::start (std::uint32_t nbr_blocks)
{
   if (window_running ()) return false;
   if (nbr_blocks == 0) return false;

   std::memset (_cycles, 0, _nbr_nodes * sizeof (_cycles [0]));
   std::memset (_probe_cycles, 0, sizeof (_probe_cycles));
   std::memset (_probe_counts, 0, sizeof (_probe_counts));

   _blocks_left = nbr_blocks;
   _blocks_done = 0;

   _running.store (true, std::memory_order_release);

   return true;
}



/*
==============================================================================
Name : block_tick
==============================================================================
*/

void  Profiler::block_tick ()
{
   if (!window_running ()) return;

   ++_blocks_done;

   if (--_blocks_left == 0)
   {
      _running.store (false, std::memory_order_release);
   }
}



/*
==============================================================================
Name : node_label
==============================================================================
*/

std::uint32_t  Profiler::node_label (std::size_t node) const
{
   return _labels [node];
}



/*
==============================================================================
Name : node_parent
==============================================================================
*/

std::ptrdiff_t Profiler::node_parent (std::size_t node) const
{
   return _parents [node];
}



/*
==============================================================================
Name : node_cycles
==============================================================================
*/

std::uint32_t  Profiler::node_cycles (std::size_t node) const
{
   return _cycles [node];
}



/*
==============================================================================
Name : probe_cycles
==============================================================================
*/

std::uint32_t  Profiler::probe_cycles (std::size_t probe) const
{
   return _probe_cycles [probe];
}



/*
==============================================================================
Name : probe_count
==============================================================================
*/

std::uint32_t  Profiler::probe_count (std::size_t probe) const
{
   return _probe_counts [probe];
}



/*
==============================================================================
Name : blocks_done
==============================================================================
*/

std::uint32_t  Profiler::blocks_done () const
{
   return _blocks_done;
}



/*
==============================================================================
Name : to_label
==============================================================================
*/

std::uint32_t  Profiler::to_label (const char str_0 [5])
{
   return
        std::uint32_t (str_0 [3]) << 24
      | std::uint32_t (str_0 [2]) << 16
      | std::uint32_t (str_0 [1]) << 8
      | std::uint32_t (str_0 [0]) << 0;
}



/*
==============================================================================
Name : register_node_any
Note :
   Returns the node index, or MaxNbrNodes when the table is full.
==============================================================================
*/

std::size_t Profiler::register_node_any (std::uint32_t label, std::int32_t parent)
{
   const auto node = reserve_nodes (1);
   if (node >= MaxNbrNodes) return node;

   _labels [node] = label;
   _parents [node] = parent;

   return node;
}



}  // namespace erb

#endif   // erb_MONITOR && erb_TARGET_DAISY
