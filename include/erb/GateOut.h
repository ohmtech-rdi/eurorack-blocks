/*****************************************************************************

      GateOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class GateOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  GateOut () = default;
   virtual        ~GateOut () = default;

   void           on ();
   void           off ();
   void           trigger (std::chrono::milliseconds duration = 6ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (uint8_t & val, uint64_t & now_ms);
   void           impl_notify_audio_buffer_start ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Mode
   {
      Constant, Pulse
   };

   Mode           _mode;
   bool           _current = false;
   uint64_t       _start = 0;
   uint64_t       _duration = 0;
   uint8_t *      _val_ptr = nullptr;
   uint64_t *     _now_ms_ptr = nullptr;



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
