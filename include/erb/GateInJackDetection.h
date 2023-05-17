/*****************************************************************************

      GateInJackDetection.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/JackDetection.h"

#include <type_traits>
#include <cstdint>



namespace erb
{



class GateInJackDetection
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = 0.f;
   static constexpr float ValueMax = 1.f;

   inline         GateInJackDetection (const uint8_t & data, const uint8_t & npr);
   virtual        ~GateInJackDetection () = default;

   inline bool    plugged () const;

   inline bool    triggered () const;
   inline         operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const uint8_t &
                  impl_data;
   const uint8_t &
                  impl_npr;
   inline void    impl_preprocess ();
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           _previous = false;
   bool           _current = false;
   JackDetection  _jack_detection;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GateInJackDetection () = delete;
                  GateInJackDetection (const GateInJackDetection & rhs) = delete;
                  GateInJackDetection (GateInJackDetection && rhs) = delete;
   GateInJackDetection &
                  operator = (const GateInJackDetection & rhs) = delete;
   GateInJackDetection &
                  operator = (GateInJackDetection && rhs) = delete;
   bool           operator == (const GateInJackDetection & rhs) const = delete;
   bool           operator != (const GateInJackDetection & rhs) const = delete;



}; // class GateInJackDetection



}  // namespace erb



#include "erb/GateInJackDetection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
