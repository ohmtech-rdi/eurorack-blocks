/*****************************************************************************

      CvInJackDetection.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/FloatRange.h"
#include "erb/JackDetection.h"

#include <type_traits>
#include <cstdint>



namespace erb
{



template <FloatRange Range>
class CvInJackDetection
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = FloatRangeTrait <Range>::Min;
   static constexpr float ValueMax = FloatRangeTrait <Range>::Max;

   inline         CvInJackDetection (const float & data, const uint8_t & npr);
   virtual        ~CvInJackDetection () = default;

   inline bool    plugged () const;

   inline         operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const float &  impl_data;
   const uint8_t &
                  impl_npr;
   inline void    impl_preprocess ();
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   JackDetection  _jack_detection;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  CvInJackDetection () = delete;
                  CvInJackDetection (const CvInJackDetection & rhs) = delete;
                  CvInJackDetection (CvInJackDetection && rhs) = delete;
   CvInJackDetection &
                  operator = (const CvInJackDetection & rhs) = delete;
   CvInJackDetection &
                  operator = (CvInJackDetection && rhs) = delete;
   bool           operator == (const CvInJackDetection & rhs) const = delete;
   bool           operator != (const CvInJackDetection & rhs) const = delete;



}; // class CvInJackDetection



}  // namespace erb



#include "erb/CvInJackDetection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
