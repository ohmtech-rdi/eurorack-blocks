/*****************************************************************************

      Filter2Poles.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "dsp/Filter2Poles.h"

#include "erb/def.h"

#include <cmath>



namespace dsp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set_sample_freq
==============================================================================
*/

void  Filter2Poles::set_sample_freq (float sample_freq)
{
   _sample_freq = sample_freq;
}



/*
==============================================================================
Name : set_type_low_pass
==============================================================================
*/

void  Filter2Poles::set_type_low_pass ()
{
   _type = Type::LowPass;
}



/*
==============================================================================
Name : set_type_high_pass
==============================================================================
*/

void  Filter2Poles::set_type_high_pass ()
{
   _type = Type::HighPass;
}



/*
==============================================================================
Name : set_type_band_pass
==============================================================================
*/

void  Filter2Poles::set_type_band_pass ()
{
   _type = Type::BandPass;
}



/*
==============================================================================
Name : set_type_resonator
==============================================================================
*/

void  Filter2Poles::set_type_resonator ()
{
   _type = Type::Resonator;
}



/*
==============================================================================
Name : set_freq
==============================================================================
*/

void  Filter2Poles::set_freq (float f0)
{
   _f0 = f0;
}



/*
==============================================================================
Name : set_resonance
==============================================================================
*/

void  Filter2Poles::set_resonance (float reso)
{
   _reso = reso;
}



/*
==============================================================================
Name : set_q
==============================================================================
*/

void  Filter2Poles::set_q (float q)
{
   _q = q;
}



/*
==============================================================================
Name : update
==============================================================================
*/

void  Filter2Poles::update ()
{
   double s_eq_b [3]; // zeros
   double s_eq_a [3]; // poles

   switch (_type)
   {
   case Type::LowPass:
#if erb_GNUC_SWITCH_COVERAGE_FIX
   default:
#endif
      s_eq_b [2] = 0;
      s_eq_b [1] = 0;
      s_eq_b [0] = 1;
      s_eq_a [1] = 1 / _reso;
      break;

   case Type::HighPass:
      s_eq_b [2] = 1;
      s_eq_b [1] = 0;
      s_eq_b [0] = 0;
      s_eq_a [1] = 1 / _reso;
      break;

   case Type::BandPass:
      s_eq_b [2] = 0;
      s_eq_b [1] = _reso / _q;
      s_eq_b [0] = 0;
      s_eq_a [1] = 1 / _q;
      break;

   case Type::Resonator:
      s_eq_b [2] = 1;
      s_eq_b [1] = _reso / _q;
      s_eq_b [0] = 1;
      s_eq_a [1] = 1 / _q;
      break;
   }

   s_eq_a [2] = 1;
   s_eq_a [0] = 1;

   // s to z, second-order biquad tranform
   // https://en.wikipedia.org/wiki/Bilinear_transform#Transformation_of_a_second-order_biquad

   const double inv_k = tan (double (_f0) * M_PI / double (_sample_freq));
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

void  Filter2Poles::process (float * dst_ptr, const float * src_ptr, size_t nbr_spl)
{
   for (size_t i = 0 ; i < nbr_spl ; ++i)
   {
      dst_ptr [i] = process (src_ptr [i]);
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



} // namespace dsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
