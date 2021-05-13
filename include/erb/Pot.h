/*****************************************************************************

      Pot.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/ControlInputNormFloat.h"



namespace erb
{



class Pot
:  public ControlInputNormFloat
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Mode
   {
      Normalized, Bipolar
   };

                  Pot (Mode mode = Mode::Normalized);
   virtual        ~Pot () override = default;

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
                  Pot () = delete;
                  Pot (const Pot & rhs) = delete;
                  Pot (Pot && rhs) = delete;
   Pot &          operator = (const Pot & rhs) = delete;
   Pot &          operator = (Pot && rhs) = delete;
   bool           operator == (const Pot & rhs) const = delete;
   bool           operator != (const Pot & rhs) const = delete;



}; // class Pot



}  // namespace erb



#include "erb/Pot.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
