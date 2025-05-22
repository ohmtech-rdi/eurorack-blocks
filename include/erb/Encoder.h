/*****************************************************************************

      Encoder.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstdint>



namespace erb
{



enum class EncoderLeadingType
{
   A, B
};


template <EncoderLeadingType LeadingType>
class Encoder
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = 0.f;
   static constexpr float ValueMax = 1000.f;

                  Encoder (const uint8_t & data_a, const uint8_t & data_b);
   virtual        ~Encoder () = default;

   void           configure (size_t nbr_debounce_zeros);

                  operator int () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const uint8_t &
                  impl_data_a;
   const uint8_t &
                  impl_data_b;
   void           impl_preprocess ();
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   uint32_t       _state_a = 0xffffffff;
   uint32_t       _state_b = 0xffffffff;
   uint32_t       _test = 0x04;
   uint32_t       _mask = 0x07;
   int            _val = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Encoder (const Encoder & rhs) = delete;
                  Encoder (Encoder && rhs) = delete;
   Encoder &      operator = (const Encoder & rhs) = delete;
   Encoder &      operator = (Encoder && rhs) = delete;
   bool           operator == (const Encoder & rhs) const = delete;
   bool           operator != (const Encoder & rhs) const = delete;



}; // class Encoder



}  // namespace erb



#include "erb/Encoder.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
