/*****************************************************************************

      Bypass.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

using namespace erb;

struct Bypass {
   Module module;
   AudioInDaisy audio_in { module, AudioInDaisyPinLeft };
   AudioOutDaisy audio_out { module, AudioOutDaisyPinLeft };

   void process ();
};
