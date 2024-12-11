/*****************************************************************************

      erb.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#include "erb/AudioIn.h"
#include "erb/AudioInJackDetection.h"
#include "erb/AudioOut.h"
#include "erb/AudioSample.h"
#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/CvInJackDetection.h"
#include "erb/CvOut.h"
#include "erb/Display.h"
#include "erb/DisplayContext.h"
#include "erb/Encoder.h"
#include "erb/EncoderButton.h"
#include "erb/FloatRange.h"
#include "erb/GateIn.h"
#include "erb/GateInJackDetection.h"
#include "erb/GateOut.h"
#include "erb/Led.h"
#include "erb/LedBi.h"
#include "erb/LedRgb.h"
#include "erb/Persistent.h"
#include "erb/Pot.h"
#if (erb_USE_FATFS)
   #include "erb/SdMmc.h"
#endif
#if (erb_SDRAM_USE_FLAG)
   #include "erb/SdramPtr.h"
#endif
#include "erb/SramPtr.h"
#include "erb/Switch.h"

#include "erb/detail/fnc.h"



namespace erb
{



template <FloatRange Range>
using Trim = Pot <Range>;



}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
