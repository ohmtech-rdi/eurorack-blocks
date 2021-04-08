/*****************************************************************************

      DaisyCvIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAnalogControlBase.h"
#include "erb/daisy/DaisyPins.h"

#include <cstdint>



namespace erb
{



class DaisyModule;

class DaisyCvIn
:  public DaisyAnalogControlBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DaisyCvIn (DaisyModule & module, const AdcPin & pin);
   virtual        ~DaisyCvIn () override = default;

                  operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyCvIn () = delete;
                  DaisyCvIn (const DaisyCvIn & rhs) = delete;
                  DaisyCvIn (DaisyCvIn && rhs) = delete;
   DaisyCvIn &    operator = (const DaisyCvIn & rhs) = delete;
   DaisyCvIn &    operator = (DaisyCvIn && rhs) = delete;
   bool           operator == (const DaisyCvIn & rhs) const = delete;
   bool           operator != (const DaisyCvIn & rhs) const = delete;



}; // class DaisyCvIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
