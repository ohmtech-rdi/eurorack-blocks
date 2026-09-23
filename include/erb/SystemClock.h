/*****************************************************************************

      SystemClock.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #include "erb/daisy/ClockHal.h"

#elif defined (erb_TARGET_VCV_RACK) || defined (erb_TARGET_ACCEPTANCE_TEST) || defined (erb_TARGET_UNIT_TEST)
   #include <chrono>

#else
   #error

#endif



namespace erb
{



#if defined (erb_TARGET_DAISY)
   using SystemClock = ClockHal;

#elif defined (erb_TARGET_VCV_RACK) || defined (erb_TARGET_ACCEPTANCE_TEST) || defined (erb_TARGET_UNIT_TEST)
   using SystemClock = std::chrono::steady_clock;

#endif



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
