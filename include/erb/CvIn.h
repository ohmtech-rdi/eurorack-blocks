/*****************************************************************************

      CvIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/ControlInputNormFloat.h"



namespace erb
{



class CvIn
:  public ControlInputNormFloat
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Mode
   {
      Normalized, Bipolar
   };

                  CvIn (Mode mode = Mode::Bipolar);
   virtual        ~CvIn () override = default;

   void           set_mode (Mode mode);
                  operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   virtual void   impl_bind_data (const float & norm_val) override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Mode           _mode;
   const float *  _norm_val_ptr = nullptr;



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
