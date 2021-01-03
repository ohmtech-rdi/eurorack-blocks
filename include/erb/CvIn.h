/*****************************************************************************

      CvIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Control.h"
#include "erb/Pins.h"

#include <cstdint>



namespace erb
{



class Module;

class CvIn
:  public Control
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  CvIn (Module & module, const AdcPin & pin);
   virtual        ~CvIn () override = default;

                  operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (uint16_t * val_ptr);

   // Control
   virtual void   impl_process () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   uint16_t *     _val_ptr = nullptr;
   float          _val = 0.f;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  CvIn () = delete;
                  CvIn (const CvIn & rhs) = delete;
                  CvIn (CvIn && rhs) = delete;
   CvIn &         operator = (const CvIn & rhs) = delete;
   CvIn &         operator = (CvIn && rhs) = delete;
   bool           operator == (const CvIn & rhs) const = delete;
   bool           operator != (const CvIn & rhs) const = delete;



}; // class CvIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
