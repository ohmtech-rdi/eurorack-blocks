/*****************************************************************************

      ReverbSc.h
      Copyright (c) 2017 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <utility>



namespace dsp
{



class ReverbSc
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float max_sample_freq = 48014.f;
   static constexpr size_t max_time_spl
      = 4127 + size_t (max_sample_freq * 0.0017f) + 17 /* 16.5 */;

   struct DelayLine
   {
      size_t         time_spl;
      size_t         write_pos;
      float          read_pos;
      float          read_pos_step;
      size_t         rand_val;
      size_t         rand_line_cnt;
      float          filter_state = 0.f;
      std::array <float, max_time_spl>
                     buf;
   };

   using DelayLines = std::array <DelayLine, 8>;

   using Frame = struct { float left, right; };

                  ReverbSc (float sample_freq, DelayLines & delay_lines);
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


   void           update_low_pass ();
   void           write (DelayLine & delay, float val);
   float          read (const DelayLine & delay, size_t pos, int offset);
   void           update_rand_seg (size_t delay_idx);

   static constexpr float
                  _junction_pressure_scale = 0.25f;
   static constexpr float
                  _output_gain = 0.35f;
   static const Params
                  _params [8];

   const float    _sample_freq;
   DelayLines &   _delay_lines;

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
