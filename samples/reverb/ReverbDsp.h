/*****************************************************************************

      ReverbDsp.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "dsp/Filter2Poles.h"
#include "dsp/GainRamp.h"
#include "dsp/ReverbSc.h"

#include <array>
#include <cstddef>



class ReverbDsp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using AuxiliaryBuffer = dsp::ReverbSc::DelayLines;

                  ReverbDsp (float sample_freq, AuxiliaryBuffer & aux_buffer);
   /*virtual*/    ~ReverbDsp () = default;

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
   dsp::ReverbSc  _reverb;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  ReverbDsp () = delete;
                  ReverbDsp (const ReverbDsp & rhs) = delete;
                  ReverbDsp (ReverbDsp && rhs) = delete;
   ReverbDsp &    operator = (const ReverbDsp & rhs) = delete;
   ReverbDsp &    operator = (ReverbDsp && rhs) = delete;
   bool           operator == (const ReverbDsp & rhs) const = delete;
   bool           operator != (const ReverbDsp & rhs) const = delete;



}; // class ReverbDsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
