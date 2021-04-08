/*****************************************************************************

      erb.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #include "erb/daisy/DaisyAudioInDaisy.h"
   #include "erb/daisy/DaisyAudioOutDaisy.h"
   #include "erb/daisy/DaisyButton.h"
   #include "erb/daisy/DaisyConstants.h"
   #include "erb/daisy/DaisyCvIn.h"
   #include "erb/daisy/DaisyGateIn.h"
   #include "erb/daisy/DaisyGateOut.h"
   #include "erb/daisy/DaisyLed.h"
   #include "erb/daisy/DaisyLedBi.h"
   #include "erb/daisy/DaisyModule.h"
   #include "erb/daisy/DaisyMultiplexer.h"
   #include "erb/daisy/DaisyPins.h"
   #include "erb/daisy/DaisyPot.h"
   #include "erb/daisy/DaisySwitch.h"

   namespace erb
   {
      using AudioInDaisy = DaisyAudioInDaisy;
      using AudioOutDaisy = DaisyAudioOutDaisy;
      using Button = DaisyButton;
      using CvIn = DaisyCvIn;
      using GateIn = DaisyGateIn;
      using GateOut = DaisyGateOut;
      using Led = DaisyLed;
      using LedBi = DaisyLedBi;
      using Module = DaisyModule;
      using Multiplexer = DaisyMultiplexer;
      using Pot = DaisyPot;
      using Switch = DaisySwitch;
      using Trim = DaisyPot;
   }

#else
   #error Unknown erb target
#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
