/*****************************************************************************

      GateIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstdint>



namespace erb
{



class GateIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   inline         GateIn (const uint8_t & data);
   virtual        ~GateIn () = default;

   inline bool    triggered () const;
   inline         operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const uint8_t &
                  impl_data;
   inline void    impl_preprocess ();
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           _previous = false;
   bool           _current = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GateIn () = delete;
                  GateIn (const GateIn & rhs) = delete;
                  GateIn (GateIn && rhs) = delete;
   GateIn &       operator = (const GateIn & rhs) = delete;
   GateIn &       operator = (GateIn && rhs) = delete;
   bool           operator == (const GateIn & rhs) const = delete;
   bool           operator != (const GateIn & rhs) const = delete;



}; // class GateIn



}  // namespace erb



#include "erb/GateIn.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
