/*****************************************************************************

      Filter2Poles.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>



namespace dsp
{



class Filter2Poles
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Filter2Poles ();
   /*virtual*/    ~Filter2Poles () = default;

   void           set_sample_freq (float fs);

   void           set_type_low_pass ();
   void           set_type_high_pass ();
   void           set_type_band_pass ();
   void           set_type_resonator ();
   void           set_freq (float f0);
   void           set_resonance (float reso);
   void           set_q (float q);

   void           update ();

   void           reset ();

   void           process (float * dst_ptr, const float * src_ptr, std::size_t nbr_spl);
   inline float   process (float x);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Type
   {
      LowPass, HighPass, BandPass, Resonator
   };

   float       _sample_freq = 48014.f;
   Type        _type = Type::LowPass;
   float       _f0 = 1000.f;
   float       _reso = 1.f;
   float       _q = 1.f;

   float       _z_eq_b [3];   // Direct, order z^(-n)
   float       _z_eq_a [3];   // Recursive

   float       _mem_x [2];    // Input memory, order z^(-n)
   float       _mem_y [2];    // Output memory
   int         _mem_pos = 0;  // 0 or 1



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Filter2Poles (const Filter2Poles & rhs) = delete;
                  Filter2Poles (Filter2Poles && rhs) = delete;
   Filter2Poles & operator = (const Filter2Poles & rhs) = delete;
   Filter2Poles & operator = (Filter2Poles && rhs) = delete;
   bool           operator == (const Filter2Poles & rhs) const = delete;
   bool           operator != (const Filter2Poles & rhs) const = delete;



}; // class Filter2Poles



} // namespace dsp



#include "dsp/Filter2Poles.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
