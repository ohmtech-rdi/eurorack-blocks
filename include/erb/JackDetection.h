/*****************************************************************************

      JackDetection.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <type_traits>
#include <cstdint>



namespace erb
{



class JackDetection
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         JackDetection () = default;
   virtual        ~JackDetection () = default;

   inline void    push (bool current_val, bool expected_val);
   inline bool    plugged () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   int            _mismatch = 0;
   int            _run = 0;
   bool           _plugged_flag = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  JackDetection (const JackDetection & rhs) = delete;
                  JackDetection (JackDetection && rhs) = delete;
   JackDetection &operator = (const JackDetection & rhs) = delete;
   JackDetection &operator = (JackDetection && rhs) = delete;
   bool           operator == (const JackDetection & rhs) const = delete;
   bool           operator != (const JackDetection & rhs) const = delete;



}; // class JackDetection



}  // namespace erb



#include "erb/JackDetection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
