/*****************************************************************************

      erb.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/AudioSample.h"
#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/CvOut.h"
#include "erb/FloatRange.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/Led.h"
#include "erb/LedBi.h"
#include "erb/LedRgb.h"
#include "erb/Pot.h"
#include "erb/SdramPtr.h"
#include "erb/Switch.h"

#if defined (erb_TARGET_DAISY)
   #include "erb/daisy/BoardDaisyField.h"
   #include "erb/daisy/BoardDaisyMicropatch.h"
   #include "erb/daisy/BoardDaisySeed.h"
   #include "erb/daisy/BoardKivu12.h"

#elif defined (erb_TARGET_VCV_RACK)
   #include "erb/vcvrack/BoardDaisyField.h"
   #include "erb/vcvrack/BoardDaisyMicropatch.h"
   #include "erb/vcvrack/BoardDaisySeed.h"
   #include "erb/vcvrack/BoardKivu12.h"

#else
   #error Unknown erb target
#endif

#include "erb/detail/fnc.h"



namespace erb
{



template <FloatRange Range>
using Trim = Pot <Range>;



}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
