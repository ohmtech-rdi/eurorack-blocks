/*****************************************************************************

      ReverbSc.h
      Copyright (c) 2017 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/SdramPtr.h"

#include <array>
#include <utility>



namespace dsp
{



class ReverbSc
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Frame = struct { float left, right; };

                  ReverbSc (float sample_freq);
   /*virtual*/    ~ReverbSc () = default;

   void           set_feedback (float feedback);
   void           set_low_pass_freq (float freq);

   void           reset ();
   Frame          process (Frame in);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   struct Params
   {
      size_t         time_spl;
      size_t         time_mod_spl;
      size_t         rand_line_cnt;
      size_t         seed;
   };

   static constexpr float max_sample_freq = 48014.f;
   static constexpr size_t max_time_spl
      = 4127 + size_t (max_sample_freq * 0.0017f) + 17 /* 16.5 */;
   static constexpr size_t nbr_delays = 8;

   struct DelayLine
   {
      std::array <float, max_time_spl>
                     buf = {};
   };

   using DelayLines = std::array <DelayLine, nbr_delays>;

   struct DelayState
   {
      size_t         time_spl = 0;
      size_t         write_pos = 0;
      float          read_pos = 0;
      float          read_pos_step = 0;
      size_t         rand_val = 0;
      size_t         rand_line_cnt = 0;
      float          filter_state = 0.f;
   };

   using DelayStates = std::array <DelayState, nbr_delays>;


   void           update_low_pass ();
   void           write (DelayLine & delay, DelayState & state, float val);
   float          read (const DelayLine & delay, size_t pos, int offset);
   void           update_rand_seg (size_t delay_idx);

   static constexpr float
                  _junction_pressure_scale = 0.25f;
   static constexpr float
                  _output_gain = 0.35f;
   static const Params
                  _params [nbr_delays];

   const float    _sample_freq;
   erb::SdramPtr <DelayLines>
                  _delay_lines_sptr;
   DelayStates    _delay_states = {};

   float          _feedback = 0.97f;

   float          _low_pass_freq = 10000.f;
   float          _damp_factor = 1.f;

   bool           _low_pass_needs_update = true;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  ReverbSc () = delete;
                  ReverbSc (const ReverbSc & rhs) = delete;
   ReverbSc &     operator = (const ReverbSc & rhs) = delete;
                  ReverbSc (ReverbSc && rhs) = delete;
   ReverbSc &     operator = (ReverbSc && rhs) = delete;
   bool           operator == (const ReverbSc & rhs) const = delete;
   bool           operator != (const ReverbSc & rhs) const = delete;



}; // class ReverbSc



}  // namespace dsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
