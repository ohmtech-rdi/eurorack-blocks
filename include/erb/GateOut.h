/*****************************************************************************

      GateOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/GateGenerator.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class GateOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  GateOut (uint8_t & data, const uint64_t & clock_ms);
   virtual        ~GateOut () = default;

   void           set (bool val);
   void           on ();
   void           off ();
   void           trigger (std::chrono::milliseconds duration = 6ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_notify_audio_buffer_start ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   uint8_t &      _data;
   const uint64_t &
                  _clock_ms;

   GateGenerator  _generator;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GateOut (const GateOut & rhs) = delete;
                  GateOut (GateOut && rhs) = delete;
   GateOut &      operator = (const GateOut & rhs) = delete;
   GateOut &      operator = (GateOut && rhs) = delete;
   bool           operator == (const GateOut & rhs) const = delete;
   bool           operator != (const GateOut & rhs) const = delete;



}; // class GateOut



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
