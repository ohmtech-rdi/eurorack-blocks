/*****************************************************************************

      CycleCounter.cpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/CycleCounter.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)



namespace erb
{



/*
==============================================================================
Name : init
==============================================================================
*/

void  CycleCounter::init ()
{
   // CoreDebug->DEMCR and DWT->CTRL are volatile hardware registers.
   // So separate read and write (ie no |=)

   CoreDebug->DEMCR = CoreDebug->DEMCR | CoreDebug_DEMCR_TRCENA_Msk;
   DWT->CTRL = DWT->CTRL | DWT_CTRL_CYCCNTENA_Msk;
}



}  // namespace erb

#endif   // erb_MONITOR && erb_TARGET_DAISY
