/*****************************************************************************

      CvIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/FloatRange.h"

#include <cstdint>



namespace erb
{



template <FloatRange Range>
class CvIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  CvIn (const std::uint16_t & data);
   virtual        ~CvIn () = default;

                  operator float () const;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   const float * const
                  _data_ptr = nullptr;



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
