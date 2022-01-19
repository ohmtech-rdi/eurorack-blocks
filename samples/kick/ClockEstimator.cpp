/*****************************************************************************

      ClockEstimator.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "ClockEstimator.h"



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

size_t ClockEstimator::process (uint64_t ms)

{
   uint64_t diff_ms_ull = ms - _last_ms;
   _last_ms = ms;

   if (diff_ms_ull > 48000)
   {
      _running = false;
      return 0;
   }

   size_t diff_ms = diff_ms_ull;

   if (_running)
   {
      _diff_ms = (_diff_ms + diff_ms) / 2;
   }
   else
   {
      _diff_ms = diff_ms;
   }

   _running = true;

   return _diff_ms;
}
