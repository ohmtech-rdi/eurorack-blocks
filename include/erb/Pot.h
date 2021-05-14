/*****************************************************************************

      Pot.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/FloatRange.h"



namespace erb
{



template <FloatRange Range>
class Pot
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   inline         Pot (const std::uint16_t & data);
   virtual        ~Pot () = default;

   inline         operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const void *   impl_data () const { return &_data; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   const std::uint16_t &
                  _data;



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
