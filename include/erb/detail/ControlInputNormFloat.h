/*****************************************************************************

      ControlInputNormFloat.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstdint>



namespace erb
{



class ControlInputNormFloat
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   virtual        ~ControlInputNormFloat () = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   virtual void   impl_bind_data (const float & norm_val) = 0;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  ControlInputNormFloat () = default;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  ControlInputNormFloat (const ControlInputNormFloat & rhs) = delete;
                  ControlInputNormFloat (ControlInputNormFloat && rhs) = delete;
   ControlInputNormFloat &
                  operator = (const ControlInputNormFloat & rhs) = delete;
   ControlInputNormFloat &
                  operator = (ControlInputNormFloat && rhs) = delete;
   bool           operator == (const ControlInputNormFloat & rhs) const = delete;
   bool           operator != (const ControlInputNormFloat & rhs) const = delete;



}; // class ControlInputNormFloat



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
