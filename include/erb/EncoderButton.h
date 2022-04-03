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

                  EncoderButton (const uint8_t & data_0, const uint8_t & data_1, const uint8_t & data_2);
   virtual        ~EncoderButton () = default;

                  operator int () const;

   bool           idle () const;
   bool           pressed () const;
   bool           held () const;
   bool           released () const;

   Encoder        encoder;
   Button         button;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_preprocess ();
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  EncoderButton (const EncoderButton & rhs) = delete;
                  EncoderButton (EncoderButton && rhs) = delete;
   EncoderButton &operator = (const EncoderButton & rhs) = delete;
   EncoderButton &operator = (EncoderButton && rhs) = delete;
   bool           operator == (const EncoderButton & rhs) const = delete;
   bool           operator != (const EncoderButton & rhs) const = delete;



}; // class EncoderButton



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
