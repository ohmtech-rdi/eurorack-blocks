/*****************************************************************************

      Sampler.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "SamplerDsp.h"
#include "artifacts/SamplerUi.h"

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct Sampler
{
   // Construct the auxiliary buffer of the Sampler DSP (here the delay lines)
   // into an SdramObject, that will be at the right place in memory.
   erb::SdramObject <SamplerDsp::AuxiliaryBuffer> object
      = erb::make_sdram_object <SamplerDsp::AuxiliaryBuffer> ();

   SamplerDsp dsp { erb_SAMPLE_RATE, *object };
   SamplerUi ui;

   void  process ();
};
