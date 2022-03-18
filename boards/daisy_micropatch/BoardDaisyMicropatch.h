/*****************************************************************************

      BoardDaisyMicropatch.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #include "firmware/BoardDaisyMicropatch.h"

#elif defined (erb_TARGET_VCV_RACK)
   #include "simulator/BoardDaisyMicropatch.h"

#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
