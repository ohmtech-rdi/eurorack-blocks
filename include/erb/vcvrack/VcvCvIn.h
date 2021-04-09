/*****************************************************************************

      VcvCvIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvInputBase.h"
#include "erb/vcvrack/VcvPins.h"



namespace erb
{



class VcvModule;

class VcvCvIn
:  public VcvInputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvCvIn (VcvModule & module, const VcvAdcPin & pin);
   virtual        ~VcvCvIn () override = default;

                  operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvCvIn () = delete;
                  VcvCvIn (const VcvCvIn & rhs) = delete;
                  VcvCvIn (VcvCvIn && rhs) = delete;
   VcvCvIn &      operator = (const VcvCvIn & rhs) = delete;
   VcvCvIn &      operator = (VcvCvIn && rhs) = delete;
   bool           operator == (const VcvCvIn & rhs) const = delete;
   bool           operator != (const VcvCvIn & rhs) const = delete;



}; // class VcvCvIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
