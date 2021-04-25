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

ReverbSc::ReverbSc (float sample_freq, DelayLines & delay_lines)
:  _sample_freq (sample_freq)
,  _delay_lines (delay_lines)
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
   for (size_t d = 0 ; d < _delay_lines.size () ; ++d)
   {
      auto & delay = _delay_lines [d];
      const auto & param = _params [d];

      delay.write_pos = 0;

      delay.time_spl = param.time_spl + param.time_mod_spl * param.seed / 32768;
      delay.read_pos
         = (delay.write_pos + delay.buf.size () - delay.time_spl)
         % delay.buf.size ();
      delay.read_pos_step = 1.f;
      delay.rand_val = param.seed;
      delay.filter_state = 0.f;
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

   auto junction_pressure = std::accumulate (
      _delay_lines.begin (), _delay_lines.end (),
      0.f, [](auto acc, const auto & delay_line){
         return acc + delay_line.filter_state;
      }
   ) * _junction_pressure_scale;

   in.left += junction_pressure;
   in.right += junction_pressure;

   auto out = Frame { 0.f, 0.f };

   for (size_t d = 0 ; d < _delay_lines.size () ; ++d)
   {
      auto & delay = _delay_lines [d];

      write (delay, d & 1 ? in.right : in.left);

      float integral;
      float frac = std::modf (delay.read_pos, &integral);
      size_t read_pos = size_t (integral);

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
      v0 = (delay.filter_state - v0) * _damp_factor + v0;
      delay.filter_state = v0;

      float & o = d & 1 ? out.right : out.left;
      o += v0;

      delay.read_pos += delay.read_pos_step;

      if (delay.read_pos > float (delay.buf.size ()))
      {
         delay.read_pos -= float (delay.buf.size ());
      }

      if (delay.rand_line_cnt == 0)
      {
         update_rand_seg (d);
      }
      else
      {
         --delay.rand_line_cnt;
      }
   }

   out.left *= _output_gain;
   out.right *= _output_gain;

   return out;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

const ReverbSc::Params  ReverbSc::_params [8] = {
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

void  ReverbSc::write (DelayLine & delay, float val)
{
   delay.buf [delay.write_pos] = val - delay.filter_state;

   delay.write_pos = (delay.write_pos + 1) % delay.buf.size ();
}



/*
==============================================================================
Name : read
==============================================================================
*/

float ReverbSc::read (const DelayLine & delay, size_t pos, int offset)
{
   auto past_pos = int (pos + delay.buf.size ()) + offset;
   size_t read_pos = size_t (past_pos) % delay.buf.size ();

   return delay.buf [read_pos];
}



/*
==============================================================================
Name : update_rand_seg
==============================================================================
*/

void  ReverbSc::update_rand_seg (size_t delay_idx)
{
   auto & delay = _delay_lines [delay_idx];
   const auto & param = _params [delay_idx];

   delay.rand_line_cnt = param.rand_line_cnt;
   delay.rand_val = (delay.rand_val * 15625 + 1) & 0xFFFF;

   size_t time_spl
      = param.time_spl
      + (param.time_mod_spl * delay.rand_val) / 65535
      - param.time_mod_spl / 2;

   delay.read_pos_step
      = 1.f
      + (float (delay.time_spl) - float (time_spl)) / float (delay.rand_line_cnt);
   delay.time_spl = time_spl;
}



}  // namespace dsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
