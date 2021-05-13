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

                  GateIn () = default;
   virtual        ~GateIn () = default;

   bool           triggered () const;
                  operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind_data (const uint8_t & val);
   void           impl_notify_audio_buffer_start ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   bool           _previous = false;
   bool           _current = false;
   const uint8_t *_current_ptr = nullptr;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
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
