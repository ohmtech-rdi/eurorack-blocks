/*****************************************************************************

      erb.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/SdramObject.h"


#if defined (erb_TARGET_DAISY)
   #include "erb/daisy/DaisyAudioIn.h"
   #include "erb/daisy/DaisyAudioOut.h"
   #include "erb/daisy/DaisyButton.h"
   #include "erb/daisy/DaisyConstants.h"
   #include "erb/daisy/DaisyCvIn.h"
   #include "erb/daisy/DaisyGateIn.h"
   #include "erb/daisy/DaisyGateOut.h"
   #include "erb/daisy/DaisyLed.h"
   #include "erb/daisy/DaisyLedBi.h"
   #include "erb/daisy/DaisyLedRgb.h"
   #include "erb/daisy/DaisyModule.h"
   #include "erb/daisy/DaisyMultiplexer.h"
   #include "erb/daisy/DaisyPins.h"
   #include "erb/daisy/DaisyPot.h"
   #include "erb/daisy/DaisySwitch.h"

   namespace erb
   {
      using AudioIn = DaisyAudioIn;
      using AudioOut = DaisyAudioOut;
      using Button = DaisyButton;
      using CvIn = DaisyCvIn;
      using GateIn = DaisyGateIn;
      using GateOut = DaisyGateOut;
      using Led = DaisyLed;
      using LedBi = DaisyLedBi;
      using LedRgb = DaisyLedRgb;
      using Module = DaisyModule;
      using Multiplexer = DaisyMultiplexer;
      using Pot = DaisyPot;
      using Switch = DaisySwitch;
      using Trim = DaisyPot;
   }

#elif defined (erb_TARGET_VCV_RACK)
   #include "erb/vcvrack/VcvAudioIn.h"
   #include "erb/vcvrack/VcvAudioOut.h"
   #include "erb/vcvrack/VcvButton.h"
   #include "erb/vcvrack/VcvConstants.h"
   #include "erb/vcvrack/VcvCvIn.h"
   #include "erb/vcvrack/VcvGateIn.h"
   #include "erb/vcvrack/VcvGateOut.h"
   #include "erb/vcvrack/VcvLed.h"
   #include "erb/vcvrack/VcvLedBi.h"
   #include "erb/vcvrack/VcvLedRgb.h"
   #include "erb/vcvrack/VcvModule.h"
   #include "erb/vcvrack/VcvMultiplexer.h"
   #include "erb/vcvrack/VcvPins.h"
   #include "erb/vcvrack/VcvPot.h"
   #include "erb/vcvrack/VcvSwitch.h"

   namespace erb
   {
      using AudioIn = VcvAudioIn;
      using AudioOut = VcvAudioOut;
      using Button = VcvButton;
      using CvIn = VcvCvIn;
      using GateIn = VcvGateIn;
      using GateOut = VcvGateOut;
      using Led = VcvLed;
      using LedBi = VcvLedBi;
      using LedRgb = VcvLedRgb;
      using Module = VcvModule;
      using Multiplexer = VcvMultiplexer;
      using Pot = VcvPot;
      using Switch = VcvSwitch;
      using Trim = VcvPot;
   }

#else
   #error Unknown erb target
#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
