/*****************************************************************************

      ReverbSc.cpp
      Copyright (c) 2017 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "dsp/ReverbSc.h"

#include <cmath>
#include <numeric>



namespace dsp
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

ReverbSc::ReverbSc (float sample_freq)
:  _sample_freq (sample_freq)
,  _delay_lines_sptr (erb::make_sdram <DelayLines> ())
{
   reset ();
}



/*
==============================================================================
Name : set_feedback
==============================================================================
*/

void  ReverbSc::set_feedback (float feedback)
{
   _feedback = feedback;
}



/*
==============================================================================
Name : set_low_pass_freq
==============================================================================
*/

void  ReverbSc::set_low_pass_freq (float freq)
{
   _low_pass_freq = freq;
   _low_pass_needs_update = true;
}



/*
==============================================================================
Name : reset
==============================================================================
*/

void  ReverbSc::reset ()
{
   auto & delay_lines = *_delay_lines_sptr;

   for (std::size_t d = 0 ; d < delay_lines.size () ; ++d)
   {
      auto & delay = delay_lines [d];
      auto & state = _delay_states [d];
      const auto & param = _params [d];

      state.write_pos = 0;

      state.time_spl = param.time_spl + param.time_mod_spl * param.seed / 32768;
      state.read_pos
         = (state.write_pos + delay.buf.size () - state.time_spl)
         % delay.buf.size ();
      state.read_pos_step = 1.f;
      state.rand_val = param.seed;
      state.filter_state = 0.f;
      delay.buf.fill (0.f);

      update_rand_seg (d);
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

ReverbSc::Frame   ReverbSc::process (Frame in)
{
   if (_low_pass_needs_update) update_low_pass ();

   auto & delay_lines = *_delay_lines_sptr;

   auto junction_pressure = std::accumulate (
      _delay_states.begin (), _delay_states.end (),
      0.f, [](auto acc, const auto & delay_state){
         return acc + delay_state.filter_state;
      }
   ) * _junction_pressure_scale;

   in.left += junction_pressure;
   in.right += junction_pressure;

   auto out = Frame { 0.f, 0.f };

   for (std::size_t d = 0 ; d < delay_lines.size () ; ++d)
   {
      auto & delay = delay_lines [d];
      auto & state = _delay_states [d];

      write (delay, state, d & 1 ? in.right : in.left);

      float integral;
      float frac = std::modf (state.read_pos, &integral);
      std::size_t read_pos = std::size_t (integral);

      auto vm1 = read (delay, read_pos, -1);
      auto v0  = read (delay, read_pos, 0);
      auto v1  = read (delay, read_pos, 1);
      auto v2  = read (delay, read_pos, 2);

      auto a2 = frac * frac; a2 -= 1.f; a2 *= (1.f / 6.f);
      auto a1 = frac; a1 += 1.f; a1 *= 0.5f;
      auto am1 = a1 - 1.f;
      auto a0 = 3.f * a2; a1 -= a0; am1 -= a2; a0 -= frac;

      v0 = (am1 * vm1 + a0 * v0 + a1 * v1 + a2 * v2) * frac + v0;
      v0 *= _feedback;
      v0 = (state.filter_state - v0) * _damp_factor + v0;
      state.filter_state = v0;

      float & o = d & 1 ? out.right : out.left;
      o += v0;

      state.read_pos += state.read_pos_step;

      if (state.read_pos > float (delay.buf.size ()))
      {
         state.read_pos -= float (delay.buf.size ());
      }

      if (state.rand_line_cnt == 0)
      {
         update_rand_seg (d);
      }
      else
      {
         --state.rand_line_cnt;
      }
   }

   out.left *= _output_gain;
   out.right *= _output_gain;

   return out;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

const ReverbSc::Params  ReverbSc::_params [ReverbSc::nbr_delays] = {
   { 2473, 44, 14226,  1966 },
   { 2767, 49, 12600, 29491 },
   { 3217, 75, 39730, 22937 },
   { 3557, 26, 11100,  9830 },
   { 3907, 44, 18838, 20643 },
   { 4127, 49, 23247, 22937 },
   { 2143, 75, 49495, 29491 },
   { 1933, 26, 13691, 14417 }
};



/*
==============================================================================
Name : update_low_pass
==============================================================================
*/

void  ReverbSc::update_low_pass ()
{
   const double pi = 3.14159265358979323846264338327950288;
   auto tmp = 2.0 - std::cos (double (_low_pass_freq) * 2.0 * pi / double (_sample_freq));

   _damp_factor = float (tmp - std::sqrt (tmp * tmp - 1.0));

   _low_pass_needs_update = false;
}



/*
==============================================================================
Name : write
==============================================================================
*/

void  ReverbSc::write (DelayLine & delay, DelayState & state, float val)
{
   delay.buf [state.write_pos] = val - state.filter_state;

   state.write_pos = (state.write_pos + 1) % delay.buf.size ();
}



/*
==============================================================================
Name : read
==============================================================================
*/

float ReverbSc::read (const DelayLine & delay, std::size_t pos, int offset)
{
   auto past_pos = int (pos + delay.buf.size ()) + offset;
   std::size_t read_pos = std::size_t (past_pos) % delay.buf.size ();

   return delay.buf [read_pos];
}



/*
==============================================================================
Name : update_rand_seg
==============================================================================
*/

void  ReverbSc::update_rand_seg (std::size_t delay_idx)
{
   auto & state = _delay_states [delay_idx];
   const auto & param = _params [delay_idx];

   state.rand_line_cnt = param.rand_line_cnt;
   state.rand_val = (state.rand_val * 15625 + 1) & 0xFFFF;

   std::size_t time_spl
      = param.time_spl
      + (param.time_mod_spl * state.rand_val) / 65535
      - param.time_mod_spl / 2;

   state.read_pos_step
      = 1.f
      + (float (state.time_spl) - float (time_spl)) / float (state.rand_line_cnt);
   state.time_spl = time_spl;
}



}  // namespace dsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
