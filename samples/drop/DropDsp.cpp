/*****************************************************************************

      DropDsp.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropDsp.h"

#include <cmath>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DropDsp::DropDsp (float sample_rate)
{
   for (auto & filter : _filters) filter.set_sample_freq (sample_rate);
}



/*
==============================================================================
Name : toggle_arm
==============================================================================
*/

void  DropDsp::toggle_arm ()
{
   _arm_active = !_arm_active;
}



/*
==============================================================================
Name : tick
==============================================================================
*/

void  DropDsp::sync ()
{
   _active = float (_arm_active);
}



/*
==============================================================================
Name : set_mode
==============================================================================
*/

void  DropDsp::set_mode (Mode mode)
{
   _mode = float (mode == Mode::Mute);
}



/*
==============================================================================
Name : set_highpass_freq
==============================================================================
*/

void  DropDsp::set_highpass_freq (float freq)
{
   for (auto & filter : _filters) filter.set_cutoff_freq (freq);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  DropDsp::process (float * const out [], const float * const in [], size_t size)
{
   for (size_t i = 0 ; i < size ; ++i)
   {
      _active.process ();
      _mode.process ();

      for (size_t c = 0 ; c < NBR_CHANNELS ; ++c)
      {
         auto & filter = _filters [c];
         auto in_chn = in [c];
         auto out_chn = out [c];

         float in_spl = in_chn [i];
         float & out_spl = out_chn [i];

         auto hp = filter.process (in_spl);
         auto mix = hp * (1.f - _mode);

         out_spl = in_spl + (mix - in_spl) * _active;
      }
   }
}



/*
==============================================================================
Name : state
==============================================================================
*/

DropDsp::State DropDsp::state ()
{
   if (_active.target == float (_arm_active))
   {
      if (_active.target == 0.f)
      {
         return State::Off;
      }
      else
      {
         return State::Active;
      }
   }
   else
   {
      return State::Armed;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : operator =
==============================================================================
*/

DropDsp::GainRamp &  DropDsp::GainRamp::operator = (float val)
{
   target = val;

   return *this;
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

DropDsp::GainRamp::operator float () const
{
   return cur;
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  DropDsp::GainRamp::process ()
{
   constexpr float step = 1.f / 256.f;

   if (cur < target)
   {
      cur += step;
      if (cur > target) cur = target;
   }
   else if (cur > target)
   {
      cur -= step;
      if (cur < target) cur = target;
   }
}



/*
==============================================================================
Name : set_sample_freq
==============================================================================
*/

void  DropDsp::Filter::set_sample_freq (float sample_freq)
{
   _sample_freq = sample_freq;
}



/*
==============================================================================
Name : set_cutoff_freq
==============================================================================
*/

void  DropDsp::Filter::set_cutoff_freq (float freq)
{
   double s_eq_b [3]; // zeros
   double s_eq_a [3]; // poles

   // high pass
   const double reso = 1;
   s_eq_b [2] = 1;
   s_eq_b [1] = 0;
   s_eq_b [0] = 0;
   s_eq_a [2] = 1;
   s_eq_a [1] = 1 / reso;
   s_eq_a [0] = 1;

   // s to z, second-order biquad tranform
   // https://en.wikipedia.org/wiki/Bilinear_transform#Transformation_of_a_second-order_biquad

   const double inv_k = tan (double (freq) * M_PI / double (_sample_freq));
   const double k = 1 / inv_k;
   const double kk = k*k;

   const double b1k = s_eq_b [1] * k;
   const double b2kk = s_eq_b [2] * kk;
   const double b2kk_plus_b0 = b2kk + s_eq_b [0];
   const double b0z = b2kk_plus_b0 + b1k;
   const double b2z = b2kk_plus_b0 - b1k;
   const double b1z = 2 * (s_eq_b [0] - b2kk);

   const double a1k = s_eq_a [1] * k;
   const double a2kk = s_eq_a [2] * kk;
   const double a2kk_plus_a0 = a2kk + s_eq_a [0];
   const double a0z = a2kk_plus_a0 + a1k;
   const double a2z = a2kk_plus_a0 - a1k;
   const double a1z = 2 * (s_eq_a [0] - a2kk);

   // IIR
   const double   mult = 1 / a0z;

   _z_eq_b [0] = float (b0z * mult);
   _z_eq_b [1] = float (b1z * mult);
   _z_eq_b [2] = float (b2z * mult);

   _z_eq_a [0] = 1;
   _z_eq_a [1] = float (a1z * mult);
   _z_eq_a [2] = float (a2z * mult);
}



/*
==============================================================================
Name : process
==============================================================================
*/

float DropDsp::Filter::process (float x)
{
   const int alt_pos = 1 - _mem_pos;
   const float y
      = _z_eq_b [0] * x
      + (_z_eq_b [1] * _mem_x [_mem_pos] + _z_eq_b [2] * _mem_x [alt_pos])
      - (_z_eq_a [1] * _mem_y [_mem_pos] + _z_eq_a [2] * _mem_y [alt_pos]);

   _mem_x [alt_pos] = x;
   _mem_y [alt_pos] = y;
   _mem_pos = alt_pos;

   return y;
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
