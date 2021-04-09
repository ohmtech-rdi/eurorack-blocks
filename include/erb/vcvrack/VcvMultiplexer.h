/*****************************************************************************

      VcvMultiplexer.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvPins.h"



namespace erb
{



class VcvModule;

class VcvMultiplexer
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Color
   {
      Red, Yellow, Green
   };

                  VcvMultiplexer (VcvModule & module, const VcvAdcPin & pin, const VcvPin & pin_a);
                  VcvMultiplexer (VcvModule & module, const VcvAdcPin & pin, const VcvPin & pin_a, const VcvPin & pin_b);
                  VcvMultiplexer (VcvModule & module, const VcvAdcPin & pin, const VcvPin & pin_a, const VcvPin & pin_b, const VcvPin & pin_c);
   virtual        ~VcvMultiplexer () = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   VcvModule &    module ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   VcvModule &    _module;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvMultiplexer () = delete;
                  VcvMultiplexer (const VcvMultiplexer & rhs) = delete;
                  VcvMultiplexer (VcvMultiplexer && rhs) = delete;
   VcvMultiplexer &
                  operator = (const VcvMultiplexer & rhs) = delete;
   VcvMultiplexer &
                  operator = (VcvMultiplexer && rhs) = delete;
   bool           operator == (const VcvMultiplexer & rhs) const = delete;
   bool           operator != (const VcvMultiplexer & rhs) const = delete;



}; // class VcvMultiplexer



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
