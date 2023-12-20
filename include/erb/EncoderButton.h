/*****************************************************************************

      EncoderButton.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Button.h"
#include "erb/Encoder.h"

#include <cstdint>



namespace erb
{



class EncoderButton
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = 0.f;
   static constexpr float ValueMax = 1000.f;

                  EncoderButton (const uint8_t & data_a, const uint8_t & data_b, const uint8_t & data_sw);
   virtual        ~EncoderButton () = default;

   Encoder        encoder;
   Button         button;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_preprocess ();
   void           impl_postprocess ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  EncoderButton (const EncoderButton & rhs) = delete;
                  EncoderButton (EncoderButton && rhs) = delete;
   EncoderButton &      operator = (const EncoderButton & rhs) = delete;
   EncoderButton &      operator = (EncoderButton && rhs) = delete;
   bool           operator == (const EncoderButton & rhs) const = delete;
   bool           operator != (const EncoderButton & rhs) const = delete;



}; // class EncoderButton



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
