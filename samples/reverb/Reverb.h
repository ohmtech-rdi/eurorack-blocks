/*****************************************************************************

      Reverb.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "ReverbDsp.h"
#include "artifacts/ReverbUi.h"

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


struct Reverb
{
   // Construct the auxiliary buffer of the Reverb DSP (here the delay lines)
   // into an SdramObject, that will be at the right place in memory.
   /*erb::SdramObject <ReverbDsp::AuxiliaryBuffer> object
      = erb::make_sdram_object <ReverbDsp::AuxiliaryBuffer> ();*/

   Reverb ();

#if defined (erb_TARGET_VCV_RACK)
   ReverbDsp::AuxiliaryBuffer aux_buffer;
#endif

   ReverbDsp dsp;
   ReverbUi ui;

   void  process ();
};
