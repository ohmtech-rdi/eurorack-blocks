/*****************************************************************************

      Clock.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstdint>



namespace erb
{



class Clock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Clock () = default;
   virtual        ~Clock () = default;

   inline const uint64_t &
                  ms () const;
   inline const uint64_t &
                  sample () const;

   inline void    tick ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   uint64_t       _spl = 0;
   uint64_t       _ms = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Clock (const Clock & rhs) = delete;
                  Clock (Clock && rhs) = delete;
   Clock &        operator = (const Clock & rhs) = delete;
   Clock &        operator = (Clock && rhs) = delete;
   bool           operator == (const Clock & rhs) const = delete;
   bool           operator != (const Clock & rhs) const = delete;



}; // class Clock



}  // namespace erb



#include "erb/detail/Clock.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
