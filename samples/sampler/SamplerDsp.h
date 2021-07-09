/*****************************************************************************

      SamplerDsp.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "dsp/Filter2Poles.h"
#include "dsp/GainRamp.h"
#include "dsp/SamplerSc.h"

#include <array>
#include <cstddef>



class SamplerDsp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using AuxiliaryBuffer = dsp::SamplerSc::DelayLines;

                  SamplerDsp (float sample_freq, AuxiliaryBuffer & aux_buffer);
   /*virtual*/    ~SamplerDsp () = default;

   void           set_wet (float wet);
   void           set_feedback (float feedback);
   void           set_low_pass_freq (float freq);
   void           set_high_pass_freq (float freq);

   void           process (float * const out [], const float * const in [], size_t size);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum {         NBR_CHANNELS = 2 };

   using Filters = std::array <dsp::Filter2Poles, NBR_CHANNELS>;

   dsp::GainRamp  _wet;
   Filters        _filters_lp;
   Filters        _filters_hp;
   dsp::SamplerSc  _reverb;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SamplerDsp () = delete;
                  SamplerDsp (const SamplerDsp & rhs) = delete;
                  SamplerDsp (SamplerDsp && rhs) = delete;
   SamplerDsp &    operator = (const SamplerDsp & rhs) = delete;
   SamplerDsp &    operator = (SamplerDsp && rhs) = delete;
   bool           operator == (const SamplerDsp & rhs) const = delete;
   bool           operator != (const SamplerDsp & rhs) const = delete;



}; // class SamplerDsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
